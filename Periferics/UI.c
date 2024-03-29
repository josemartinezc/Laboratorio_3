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




/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

