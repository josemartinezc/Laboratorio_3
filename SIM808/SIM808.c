/* ************************************************************************** */
/** SIM808

  @Company
    Ucudal

  @File Name
    SIM808.c

  @Summary
    Contains the structures and functions to use SIM808
 */
/* ************************************************************************** */

/*******************************************************************************/    
/************************* INCLUDED FILES **************************************/    
/*******************************************************************************/    

#include <string.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <proc/p32mm0256gpm064.h>
//#include "../GPS/GPS.h"
#include "SIM808.h"
#include "../utils/utils.h"
#include "../mcc_generated_files/mcc.h"
#include "../mcc_generated_files/../Periferics/UI.h"
#include "../mcc_generated_files/pin_manager.h"

/*******************************************************************************/    
/************************* LOCAL VARIABLES *************************************/    
/*******************************************************************************/     
 
 ut_tmrDelay_t timer1;
 ut_tmrDelay_t timer2;
 ut_tmrDelay_t timer3;
 ut_tmrDelay_t *ptimer1;
 ut_tmrDelay_t *ptimer2;
 ut_tmrDelay_t *ptimer3;
 uint8_t tiempo;
 uint8_t rxBuffer[30];
 
 bool espero_OK ();
 void init_punteros();
 void Leer_Buffer_debug ();
 
/*******************************************************************************/    
/************************* INTERFACE FUNCTIONS *********************************/    
/*******************************************************************************/
 bool Initialize_SIM808 () { 
    static bool punteros_inicializados=false;
    static uint32_t POWER_KEY=0;
    
    if (punteros_inicializados == false){
        PWR_KEY_SetLow();
        PWR_KEY_SetDigitalOutput();
        init_punteros ();
        punteros_inicializados = true;
    }
    else
    {   
        switch (POWER_KEY){
            case 0:
                if (UT_delayDs (ptimer2,11) == true ){
                     PWR_KEY_SetDigitalInput();
                     POWER_KEY = 1;   
                }
                break;
            case 1:
                if (UT_delayDs (ptimer3,21) == true ){
                     POWER_KEY = 2;   
                }
                break;
            case 2:
                if (STATUS_GetValue() == 1) {
                    if (espero_OK()==true){
                        return true;
                    } //aca veo si la conexion sim808-pic funciona
                }
                else
                {
                    POWER_KEY = 0;
                }
                break; 
        }
    }
    return false;
}
 
bool espero_OK (){ //funcion que espera a que el SIM me mande OK
    static st_inicializacion_SIM808 st_Espero_OK = INITi;
    static bool espero = false;
    if (espero == false){
        UART1_Write ('A');
        espero = true;
    }
    else
    {   
        switch (st_Espero_OK){
            case INITi:
                if (UT_delayDs (ptimer1,50) == true){
                    UART1_WriteBuffer ( "AT\r" ,  strlen ("AT\r"));
                    st_Espero_OK = WAITi;
                }
            break;

            case WAITi:
                if (UT_delayDs (ptimer1,10)== true){
                    if(UART1_ReceiveBufferIsEmpty()==false)
                    {
                        UART1_ReadBuffer ( rxBuffer , sizeof(rxBuffer)); 
                        if (strstr(rxBuffer,"OK")!= NULL){ //es OK lo que mandó?
                            LEDB_SetHigh();
                            memset (rxBuffer, 0, sizeof(rxBuffer));
                            return true;
                        }
                    }
                }
            break;
        }            
    }
    return false;
}
 
void init_punteros (void){
    ptimer1 = &timer1;
    ptimer1->state = 0;
    ptimer2 = &timer2;
    ptimer2->state = 0;
    ptimer3 = &timer3;
    ptimer3->state = 0;
}


/*void Leer_Buffer_debug (void){
    char content_buffer[10];
    sprintf (content_buffer, "%s", rxBuffer); 
    UI_send_text(content_buffer); 
}*/