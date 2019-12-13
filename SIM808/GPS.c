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
#include "../SIM808/SIM808.h"
#include "../mcc_generated_files/pin_manager.h"
#include "../utils/utils.h"

/*******************************************************************************/    
/************************* LOCAL VARIABLES *************************************/    
/*******************************************************************************/     

char RxBuffer[128];
ut_tmrDelay_t timer4;
ut_tmrDelay_t timer5;
ut_tmrDelay_t timer6; 

ut_tmrDelay_t *ptimer5;

uint8_t pepe2[128];
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

    offset=strlen("\r\n+CGNSINF: ")+GPS_RMC_RUN_LEN+GPS_RMC_COMMA_LEN+GPS_RMC_FIX_LEN+GPS_RMC_COMMA_LEN+GPS_RMC_UTC_LEN+GPS_RMC_COMMA_LEN;
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

    offset=strlen("\r\n+CGNSINF: ")+GPS_RMC_RUN_LEN+GPS_RMC_COMMA_LEN+GPS_RMC_FIX_LEN+GPS_RMC_COMMA_LEN;
    // Copy Year YYYY
    memset( temp_str, 0, 5 );
    strncpy( temp_str, (p_sentence+offset), 4 );
    p_newtime->tm_year=atoi( temp_str )-1900;
    offset+=4;
    // Copy Month MM
    memset( temp_str, 0, 5 );
    strncpy( temp_str, (p_sentence+offset), 2 );
    p_newtime->tm_mon = atoi(temp_str)-1;
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
    static uint8_t ini_GPS_com=0;
    TRI_STATUS recibo_ok;

    switch(ini_GPS_com){
        case 0:
            UART1_WriteBuffer ("AT+CGNSPWR=1\r", strlen ("AT+CGNSPWR=1\r"));
            ini_GPS_com = 1;
            break;
        case 1:
            recibo_ok=Recibo_OK();
            if (recibo_ok == DONE) {
                
                UART1_WriteBuffer ("AT+CGNSSEQ=RMC\r", strlen ("AT+CGNSSEQ=RMC\r"));
                ini_GPS_com = 2;
            }
            else if(recibo_ok==ERROR){
                memset (RxBuffer, 0, sizeof(RxBuffer));
                ini_GPS_com=0;
            }
            break;
        case 2:
            recibo_ok=Recibo_OK();
            if ( recibo_ok == DONE){
                memset (RxBuffer, 0, sizeof(RxBuffer));
                UART1_WriteBuffer ("ATE0\r", strlen ("ATE0\r"));
                ini_GPS_com = 3;
            }
            else if (recibo_ok==ERROR){
                memset (RxBuffer, 0, sizeof(RxBuffer));
                ini_GPS_com=1;
            }
            break;        
        case 3:
            recibo_ok=Recibo_OK();
            if ( recibo_ok == DONE){
                memset (RxBuffer, 0, sizeof(RxBuffer));
                return true;
            }
            else if (recibo_ok==ERROR){
                memset (RxBuffer, 0, sizeof(RxBuffer));
                ini_GPS_com=2;
            }
            break;
            
    }
    return false;
}

TRI_STATUS Recibo_OK (){
    static bool puntero_no_init = true;
    TRI_STATUS answer_status;

    if(answer_status=wait_usart_answer("OK", 10)==DONE){
        return DONE;
    }
    else if(answer_status==ERROR){
        puntero_no_init = true;
        return ERROR;
    }
    
    return WORKING;
}

TRI_STATUS get_trama (char *p_trama){
    static stage_state_t stage = STG0;
    static bool waiting_trama=false;
    TRI_STATUS answer_status;
    
    switch(stage){
        case STG0:
        if(waiting_trama==false){
            timer6.state=0;
            UART1_WriteBuffer ("AT+CGNSINF\r", strlen ("AT+CGNSINF\r"));
                      //UI_send_text( "4>" ); //check USART
                      //UI_send_text( "AT+CGNSINF\r" ); //check USART
            waiting_trama=true;
            stage=STG1;
        }
        case STG1:
            if(UT_delayDs (&timer6,1)== true){
                memset (RxBuffer, 0, sizeof(RxBuffer));
                UART1_ReadBuffer (RxBuffer , sizeof(RxBuffer)); 
                 //   UI_send_text( "4<" ); //check USART
                 //   UI_send_text( RxBuffer ); //check USART
                if (check_correct_trama(RxBuffer)==true){
                    memset(p_trama,0, sizeof(p_trama));
                    strcpy(p_trama, RxBuffer);
                    memset (RxBuffer, 0, sizeof(RxBuffer));
                    stage = STG0;
                    return DONE;
                }
                else{
                    memset (RxBuffer, 0, sizeof(RxBuffer));
                    stage=STG0;
                    waiting_trama=false;

                }
            }
            break;
        case STG2:
            if(UART1_IsTxReady()==true){
                UART1_WriteBuffer ("AT+CGNSURC=0\r", strlen ("AT+CGNSURC=0\r"));
                stage=STG3;
            }
            break;
        case STG3:
            answer_status=wait_usart_answer("OK", 1);
            if(answer_status==DONE){   
                stage=STG0;
                waiting_trama=false;
                return DONE;
            }
            else if(answer_status==ERROR){
                stage=STG2;
            }
            break;
    }
    return WORKING;
}

bool check_correct_trama(uint8_t* p_trama){
    uint8_t aux_trama[11];
    
    memset(aux_trama, 0, sizeof(aux_trama));
    if (strstr(p_trama,"+CGNSINF: 1,1,")!=NULL){
        strncpy(aux_trama, p_trama, 10);
        if(strcmp(aux_trama, "\r\n+CGNSINF")==0){
            return true;
        }
    }
    return false;
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

void get_google_link(GPSPosition_t position, uint8_t* p_gps_link ){
    uint8_t gps_link[100];
    uint8_t coord_posicion_str[100];
    
    memset (gps_link, 0, sizeof(gps_link));
    strcat(gps_link, "http://maps.google.com/maps?q=");

    memset(coord_posicion_str,0,sizeof(coord_posicion_str));
    sprintf(coord_posicion_str, "%lf", position.latitude);
    strcat(gps_link, coord_posicion_str);

    memset(coord_posicion_str,0,sizeof(coord_posicion_str));
    sprintf(coord_posicion_str, "%lf", position.longitude);
    strcat(gps_link, coord_posicion_str);
    
    strcpy(p_gps_link, gps_link);
}


bool false_frame_maker(char *p_frame){
    strcpy(p_frame, "+CGNSINF:1,1,20150327014838.000,31.221783,121.354528,114.600,0.28,0.0,1,,1.9,2.2,1.0,,8,4,,,42,,");
    return true;
}

