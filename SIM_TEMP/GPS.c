/* ************************************************************************** */
/** GPS

  @Company
    Ucudal

  @File Name
    GPS.c

  @Summary
    Contains the structures and functions to obtain information from GPS frames obtained via SIM808 module
 */
/* ************************************************************************** */

/*******************************************************************************/    
/************************* INCLUDED FILES **************************************/    
/*******************************************************************************/    
#include "GPS.h"
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "../mcc_generated_files/pin_manager.h"
#include "../utils/utils.h"

/*******************************************************************************/    
/************************* LOCAL VARIABLES *************************************/    
/*******************************************************************************/     

char RxBuffer[105];
ut_tmrDelay_t timer4;
ut_tmrDelay_t timer5;
ut_tmrDelay_t *ptimer4;
ut_tmrDelay_t *ptimer5;


/*******************************************************************************/    
/************************* INTERFACE FUNCTIONS *********************************/    
/*******************************************************************************/

/**
    @Function
        void GPS_getPosition( GPSPosition_t* pos, uint8_t *sentence )      
      
    @Summary
        Fills the position structure with information from the GPS frame received.
   
    @Remarks
        String must start after +CGNSINF: 
 **/
void GPS_getPosition( GPSPosition_t *p_pos, uint8_t *p_sentence ){
    uint8_t offset;
    uint8_t *ptr;

    offset=strlen("+CGNSINF:")+GPS_RMC_RUN_LEN+GPS_RMC_COMMA_LEN+GPS_RMC_FIX_LEN+GPS_RMC_COMMA_LEN+GPS_RMC_UTC_LEN+GPS_RMC_COMMA_LEN;
    p_pos->latitude=strtod( (p_sentence+offset), (char**)&ptr );
    p_pos->longitude=strtod( (ptr+GPS_RMC_COMMA_LEN), (char**)&ptr );
    Nop();
}


/**
    @Function
        void GPS_getUTC( struct tm *p_newtime, uint8_t *p_sentence )      
      
    @Summary
        Fills the time structure with TIME information from the GPS frame received.

    @Remarks
        String must start after +CGNSINF: 
 **/
void GPS_getUTC( struct tm *p_newtime, uint8_t *p_sentence ){
    uint8_t offset;
    uint8_t temp_str[5];

    offset=GPS_RMC_RUN_LEN+GPS_RMC_COMMA_LEN+GPS_RMC_FIX_LEN+GPS_RMC_COMMA_LEN;
    // Copy Year YYYY
    memset( temp_str, 0, 5 );
    strncpy( temp_str, (p_sentence+offset), 4 );
    p_newtime->tm_year=atoi( temp_str )-1900;
    offset+=4;
    // Copy Month MM
    memset( temp_str, 0, 5 );
    strncpy( temp_str, (p_sentence+offset), 2 );
    p_newtime->tm_mon = atoi(temp_str);
    offset+=2;
    // Copy Day DD
    memset( temp_str, 0, 5 );
    strncpy( temp_str, (p_sentence+offset), 2 );
    p_newtime->tm_mday = atoi(temp_str);
    offset+=2;
    // Copy Hour HH
    memset( temp_str, 0, 5 );
    strncpy( temp_str, (p_sentence+offset), 2 );
    p_newtime->tm_hour = atoi(temp_str);
    offset+=2;
    // Copy Minutes MM
    memset( temp_str, 0, 5 );
    strncpy( temp_str, (p_sentence+offset), 2 );
    p_newtime->tm_min = atoi(temp_str);
    offset+=2;
    // Copy Seconds SS
    memset( temp_str, 0, 5 );
    strncpy( temp_str, (p_sentence+offset), 2 );
    p_newtime->tm_sec = atoi(temp_str);
}

/**
    @Function
        double GPS_getGroundDistance( GPSPosition_t *a, GPSPosition_t *b )     
      
    @Summary
        Calculates ground distance(in km) between to geographical points. (Uses spherical earth model)

    @Remarks
        None
 **/
double GPS_getGroundDistance( GPSPosition_t *a, GPSPosition_t *b ){
    double angle;
    double lat_a, lon_a, lat_b, lon_b;

    lat_a=a->latitude*M_PI/180;
    lon_a=a->longitude*M_PI/180;
    lat_b=b->latitude*M_PI/180;
    lon_b=b->longitude*M_PI/180;

	angle = sqrt(cos(lat_a)*cos(lat_b)*pow(sin((lon_a - lon_b)/2), 2) + pow(sin((lat_a - lat_b)/2), 2));
	angle = 2*asin(angle);

	return angle * GPS_EARTH_RADIUS;		 
}


bool Initialize_GPS (){
    static bool AT = false;
    if (AT == false)
    {       
        UART1_WriteBuffer ("AT+CGNSPWR=1\r", strlen ("AT+CGNSPWR=1\r"));
        AT = true;
    }
    else{
        if (Recibo_OK() == true) {
            memset (RxBuffer, 0, sizeof(RxBuffer));
            UART1_WriteBuffer ("AT+CGNSSEQ=\"RMC\"\r", strlen ("AT+CGNSSEQ=\"RMC\"\r"));
            if ( Recibo_OK() == true){
                //GPS inicializado
                memset (RxBuffer, 0, sizeof(RxBuffer));
                return true;
            } 
        }
        else
            return false;
    }
}

bool Recibo_OK (void){
    static bool puntero_no_init = true;
    if (puntero_no_init)
    {
        ptimer4 = &timer4;
        ptimer4->state = 0;
        puntero_no_init = false;
    }
    if (UT_delayDs (ptimer4,10)== true)
    {
        UART1_ReadBuffer ( RxBuffer , sizeof(RxBuffer));
        if (strstr(RxBuffer,"OK")!= NULL) //es OK lo que mandó?
        { 
            LEDA_SetHigh();
            return true;
        }
        else
            return false;
    }
}

bool get_trama (char *p_trama){
    UART1_WriteBuffer ("AT+CGNSINF", strlen ("AT+CGNSINF"));
    if(UART1_ReceiveBufferIsEmpty()==false)
    {
        UART1_ReadBuffer (RxBuffer , sizeof(RxBuffer)); 
        if (strstr(RxBuffer,"OK")!= NULL) // hay OK en lo que mandó?
        {
            strcpy(p_trama, RxBuffer);
            memset (RxBuffer, 0, sizeof(RxBuffer));
            return true;
        }
        else
            return false;
    }       
}

bool send_message (char *message)
{
    UART1_WriteBuffer ("AT+CMGF=1", strlen ("AT+CMGF=1")); //seleccionar modo texto
    if( check_envio() == true)
    {
        UART1_WriteBuffer ("AT+CMGS=\"095769097\"", strlen ("AT+CMGS=\"095769097\""));
        if (check_envio() == true)
        {
            UART1_Write(0x0D);
            if (check_envio() == true)
            {
                UART1_WriteBuffer (*message, strlen (*message)); //mensaje guardado en el puntero
                if (check_envio() == true)
                    UART1_Write(0x1A);
            }
        }
    }  
}

bool check_envio (void)
{
    if( !UART1_ReceiveBufferIsEmpty() )
    {
        UART1_ReadBuffer ( RxBuffer , sizeof(RxBuffer)); 
        if (strstr(RxBuffer,"OK")!= NULL) // hay OK en lo que mandó?
        {
            //config OK
            memset (RxBuffer, 0, sizeof(RxBuffer));
            return true;
        }
        else
            return false; 
    }
}


bool false_frame_maker(char *p_frame){
    strcpy(p_frame, "+CGNSINF:1,1,20150327014838.000,31.221783,121.354528,114.600,0.28,0.0,1,,1.9,2.2,1.0,,8,4,,,42,,");
    return true;
}

