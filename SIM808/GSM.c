/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "GSM.h"
#include "../SIM808/SIM808.h"
#include "../Irrigation_system/system_control.h"
#include "GPS.h"
#include "../utils/utils.h"


//****************************** VARIABLES *******************************

bool available_SIM_card;
ut_tmrDelay_t timer7; 
uint8_t message[64]; 

//************************************************************************

bool Init_SIMCard(void){
    static sim_card_state_t SIM_state = NET;
    static TRI_STATUS answer_status = WORKING;
    static bool SIM_pin=false;
    static uint8_t retries=0;
    
    if(GPSIsReady()){
        switch(SIM_state){
            case NET:
                available_SIM_card=true;
                UART1_WriteBuffer ("AT+CREG?\r", strlen ("AT+CREG?\r")); //consultar estado de la red
                SIM_state=PIN;
                break;
            case PIN:
                answer_status=wait_usart_answer("OK", 1);
                    if(answer_status==DONE){
                        if(UART1_IsTxReady()==true){
                            UART1_WriteBuffer ("AT+CPIN?\r", strlen ("AT+CPIN?\r")); //tiene pin?
                            //UI_send_text("5>AT+CPIN?\r"); //check USART
                            SIM_state = COMPANY;
                        }
                    }
                    else if(answer_status==ERROR){
                        SIM_state=NET;
                    }
                break;
            case COMPANY:
                if(SIM_pin==false){
                    answer_status=wait_usart_answer("READY", 1);
                    //answer_status=wait_usart_answer("SMS Ready", 1);
                    if(answer_status==DONE){
                        SIM_pin=true;
                    }
                    else if(answer_status==ERROR){
                        available_SIM_card=false;
                        SIM_state=NET;
                        return true;
                    }
                }
                if(SIM_pin==true){
                    if(UART1_IsTxReady()==true){
                        UART1_WriteBuffer ("AT+COPS=1,2,\"74801\"\r", strlen ("AT+COPS=1,2,\"74801\"\r")); //Antel
                        // UI_send_text("5>AT+COPS=1,2,\"74801\"\r"); //check USART
                        SIM_state=END_TEL;
                    }
                }
                break;
            case END_TEL:
                answer_status=wait_usart_answer("OK", 15);
                if(answer_status==DONE){
                    retries=0;
                    return true;
                }
                else if(answer_status==ERROR ){
                    retries ++;
                    if( retries > 15 ){
                        available_SIM_card=false;
                        SIM_state=NET;
                        retries=0;
                        return true;
                    }
                }
                break;
        }
    }
    else{
        return true;
    }
    return false;
}

/*  bool set_pin(){
            answer_status=wait_usart_answer("SIM PIN");
            if(answer_status==DONE){
                UART1_WriteBuffer ("AT+CPIN=1234\r", strlen ("AT+CPIN=1234\r")); //PIN
                SIM_state=END_PIN;
            }
            else if(answer_status==ERROR){
                SIM_pin=false;
                SIM_state=PIN;

            }
*/

bool send_text_message (uint8_t *p_message, uint8_t *p_telephone_num){
    static TRI_STATUS answer_status=WORKING;
    static stage_state_t stage = STG0;
    uint8_t select_num[64];
    static uint8_t message[256];
    
    if(SIMIsReady()){
        switch (stage){
            case STG0:
                if(UART1_IsTxReady()==true){
                    UART1_WriteBuffer ("AT+CMGF=1\r", strlen ("AT+CMGF=1\r")); //seleccionar modo texto
                    stage = STG1;
                }
                break;
            case STG1:
                answer_status=wait_usart_answer("OK", 1);
                if(answer_status==DONE){   
                    stage=STG2;
                }
                else if(answer_status==ERROR){
                    stage=STG0;
                }
                break;
            case STG2:
                if(UART1_IsTxReady()==true){
                    memset(select_num, 0, sizeof(select_num));
                    strcat(select_num, "AT+CMGS=\"");
                    strcat(select_num, p_telephone_num);
                    strcat(select_num, "\"\r");
                    UART1_WriteBuffer(select_num, strlen(select_num)); 
                    stage=STG3;
                }
                break;
            case STG3:
                if (UT_delayDs (&timer7, 20)==true){ 
                    stage=STG4;
                }
                break;
            case STG4:
                if(UART1_IsTxReady()==true){
                    memset(message, 0, sizeof(message));
                    strcat(message, p_message);
                    strcat(message, "\r");
                    UART1_WriteBuffer(message, strlen(message)); 
                    //UI_send_text( "3>" ); //check USART
                    //UI_send_text( pepe3 ); //check USART
                    stage=STG5;
                }
                break;
            case STG5:
                if (UT_delayDs (&timer7, 5)==true){ 
                    stage=STG6;
                }
                break;
            case STG6:
                if(UART1_IsTxReady()==true){
                    UART1_Write(0x1A);  
                    stage=STG7;
                }
                break;
            case STG7:
                answer_status=wait_usart_answer("+CMGS", 10);
                if(answer_status==DONE){   
                    stage=STG0;
                    return true;
                }
                else if(answer_status==ERROR){
                    stage=STG6;
                }
                break;
            default:
                break;
        }
    }
    return false;
}
    

bool config_SIM_UI(){
    static uint8_t SIM_card_state=0;
    
    switch (SIM_card_state){
        case 0:
            if(GPSIsReady() && SIMIsReady()){
                SIM_card_state=1;
            }
            else{
                SIM_card_state=2;
            }
            break;
        case 1:
            if(available_SIM_card==false){
                SIM_card_state=3;
            }
            else{
                UI_send_text("\n\nSu SIM a sido configurada con exito");
                SIM_card_state=0;
                return true;
            }
            break;
        case 2:
            if(GPSIsReady()){
                SIM_card_state=3;
            }
            else{
                UI_send_text("\n\nAguarde un momento a que el modem sea configurado");
                SIM_card_state=0;
                return true;
            }
            break;
        case 3:
            if(TRAMAIsSaved()){
                if(Init_SIMCard()==true){
                    if(available_SIM_card==false){
                        UI_send_text("\n\nNo se pudo identificar ninguna tarjeta SIM.");
                        SIM_card_state=0;
                        return true;
                    }
                    else{
                        SIM_card_state=1;
                    }
                }
            }
            else if(!TRAMAIsSaved()){
                UI_send_text("\n\nIntentelo de nuevo en un momento.");                    
                SIM_card_state=0;
                return true;
            }
            break;
    }
    return false;
}


 
 