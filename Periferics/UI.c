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

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#include "../mcc_generated_files/rtcc.h"
#include "UI.h"
#include "../mcc_generated_files/usb/usb.h"
#include"../mcc_generated_files/usb/usb_device_cdc.h"
#include "../utils/utils.h"
#include "../LEDs_RGB/RGB_leds.h"


//static UI_STATE state_UI=INIT;   
static int8_t numero_evento=0;
static bcdTime_t real_time;
static uint8_t buffer_USB_send_text[TAMANO_SEND];
static uint8_t buffer_USB_save_text[TAMANO_SAVE];
static bool all_sent=true;
static bool sending = false;
static bool undone_events=false;
char date_time_representation[32];
int32_t UI_int_lecture;


void UI_tasks(){
    if(sending == false){
        if(USBUSARTIsTxTrfReady()){
            memset(buffer_USB_send_text, 0, TAMANO_SEND);
            if(buffer_USB_save_text[0]!=0){
                memcpy(buffer_USB_send_text,buffer_USB_save_text,TAMANO_SEND-1);    
                memcpy(buffer_USB_save_text,buffer_USB_save_text+TAMANO_SEND-1, TAMANO_SAVE-TAMANO_SEND+1);
                memset(buffer_USB_save_text+TAMANO_SAVE-TAMANO_SEND+1, 0, TAMANO_SEND-1 );
                putUSBUSART(buffer_USB_send_text,strlen(buffer_USB_send_text)); 
            }
            else{
               all_sent = true;
               sending = false;
            }
        }
    }
    else{
        if(all_sent==false){
           sending = true;
        }
    }
    
    CDCTxService();
}

void UI_send_text( uint8_t *p_text ){
    if(strlen(p_text) == 0 ){
        return;
    }
    
    if(strlen(p_text)<(TAMANO_SAVE-strlen(buffer_USB_save_text))){
        strcat(buffer_USB_save_text, p_text);
    }
    else{
        strncat(buffer_USB_save_text, p_text, (TAMANO_SAVE - strlen(buffer_USB_save_text)));
    }
    all_sent = false;
}

//funcion que devuelve lo que hay en el usb, transformando el ascii a decimales
int32_t read_USB_int(void){
    uint8_t datos[64];
    int32_t dato_int;
    
    memset(datos,0,sizeof(datos));
    
    if(getsUSBUSART(datos, sizeof(datos))>0){
        dato_int=atoi(datos);
        return dato_int;
    }
    else{
        return -1;
    }
}


void dar_hora(bcdTime_t* time){
    strftime(date_time_representation, 32, "%c", time);
    UI_send_text("\n\n");
    UI_send_text(date_time_representation); 
    UI_send_text("\n\n");
}


/*
bool configurar_hora(void){
    static TASKS_STATE state_config=INTERFACE;
    static int p_config_hora_state;
    bool dato_ingresado_valido;
    
    switch (state_config){
        case INTERFACE:
            configurar_hora_interface(p_config_hora_state);
            state_config=WAIT;
            return false;
            break;
        case WAIT:
            UI_int_lecture=read_USB_int();
            if(UI_int_lecture>=0){
                state_config=DO_TASKS;
            }
            return false;
            break;
        case DO_TASKS:
            dato_ingresado_valido=config_hora_function(p_config_hora_state);
            if(dato_ingresado_valido==true){
                if(p_config_hora_state<4){
                    state_config=INTERFACE;
                    p_config_hora_state++;
                    return false;
                }
                else{
                    state_config=END;
                    return false;
                }
            }
            else{
                state_config=INTERFACE;
                return false;
            }
            break;
        case END:
            RTCC_TimeSet(&real_time);
            state_config=INTERFACE;
            p_config_hora_state=0;
            return true;
            break;
        default:
            return false;
            break;
    }
}

void configurar_hora_interface(int config_hora_state){    
    switch(config_hora_state){
        case 0:
            UI_send_text("\nIngrese el dia (1 a 31)\n>>>");
            break;
        case 1:
            UI_send_text("\nIngrese el mes (1 a 12)\n>>>");
            break;
        case 2:
            UI_send_text("\nIngrese el anio (4 digitos)\n>>>");
            break;
        case 3:
            UI_send_text("\nIngrese la hora (00 al 23)\n>>>");
            break;
        case 4:
            UI_send_text("\nIngrese los minutos (00 al 59)\n>>>");
            break;
        default:
            break;
    }
}

bool config_hora_function(int config_hora_state){ 
    switch(config_hora_state){
        case 0:
            if(UI_int_lecture<32 && UI_int_lecture>0){
                real_time.tm_mday=UI_int_lecture;
                return true;
            }
            else{
                UI_send_text("\nIngrese un dia valido");
                return false;
            }
            break;            
        case 1:
            if(UI_int_lecture<13 && UI_int_lecture>0){
                real_time.tm_mon=(UI_int_lecture-1);
                return true;
            }
            else{
                UI_send_text("\nIngrese un mes valido");
                return false;
            }
            break;            
        case 2:
            if(UI_int_lecture<10000 && UI_int_lecture>1900){
                real_time.tm_year=(UI_int_lecture-1900);
                return true;
            }
            else{
                UI_send_text("\nIngrese un anio valido");
                return false;
            }
            break;
        case 3:
            if(UI_int_lecture<24 && UI_int_lecture>=0){
                real_time.tm_hour=UI_int_lecture;
                return true;
            }
            else{
                UI_send_text("\nIngrese una hora valida");    
                return false;
            }
            break;
        case 4:
            if(UI_int_lecture<60 && UI_int_lecture>=0){
                real_time.tm_min=UI_int_lecture;
                real_time.tm_sec=0;
                return true;
            }
            else{
                UI_send_text("\nIngrese minutos validos");    
                return false;
            }
            break;                
        default:
            return false;
            break;
    }
}      

*/
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

