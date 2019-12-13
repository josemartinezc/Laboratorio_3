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
#include "GPS.h"
#include "SIM808.h"
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
 ut_tmrDelay_t timer8; 
 uint8_t tiempo;
 uint8_t rxBuffer[30];
 
 //uint8_t pepe[128]; 
/*******************************************************************************/    
/************************* INTERFACE FUNCTIONS *********************************/    
/*******************************************************************************/
 
 void SIM808_ini_tasks(){
    PWR_KEY_SetDigitalInput();
    STATUS_SetDigitalInput();
    RESET_SetHigh();
    RESET_SetDigitalOutput();
 }
 
TRI_STATUS wait_usart_answer(uint8_t *p_answer, uint8_t delay){
    static bool waiting=false;
    uint8_t answer_aux[128];
    
    if(waiting==false){
        timer8.state=0;
        waiting=true;
    }

    memset(answer_aux, 0, sizeof(answer_aux));
    if (UT_delayDs (&timer8, delay)== true ){
        UART1_ReadBuffer ( answer_aux , sizeof(answer_aux));
        //sprintf(pepe,"1<%s",answer_aux);//check USART
        //UI_send_text(pepe); //check USART
        waiting=false;
        if (strstr(answer_aux,p_answer)!= NULL) //es p_answer lo que mandó?
        { 
            return DONE;
        }
        else{
            return ERROR;
        }
    }
    else{
        return WORKING;
    }
}
 
 bool Initialize_SIM808 () { 
    static bool punteros_inicializados=false;
    static uint32_t POWER_KEY=0;
    
    if (punteros_inicializados == false){
        PWR_KEY_SetLow();
        PWR_KEY_SetDigitalOutput();
        init_punteros ();
        punteros_inicializados = true;
    }
    else{   
        switch (POWER_KEY){
            case 0:
                if (UT_delayDs (ptimer2,12) == true ){
                     PWR_KEY_SetDigitalInput();
                     POWER_KEY = 1;   
                }
                break;
            case 1:
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
                        //sprintf(pepe,"2<%s",rxBuffer);//check USART
                        //UI_send_text(pepe); //check USART
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