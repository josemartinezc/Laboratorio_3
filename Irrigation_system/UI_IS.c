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

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#include "system_control.h"
#include "../mcc_generated_files/usb/usb.h"
#include "../periferics/sensor.h"
#include "../periferics/UI.h"
#include "UI_IS.h"


//variables
    static IS_INTERFACE_STATE state_UI=INIT; 

void interface_IS(){
    static uint8_t ini[16];
    bcdTime_t real_time;
   
    switch (state_UI){       
        case INIT:
            if( USBGetDeviceState() == CONFIGURED_STATE ){
                if(getsUSBUSART(ini, sizeof(ini))>0){
                    UI_send_text("\n\n\nBIENVENIDO A SU SISTEMA DE RIEGO!\n");
                    state_UI=MENU;
                }
            }
            break;
        case MENU:
                UI_send_text("\nIngrese una opcion del 1-3\n1.Configurar UMBRALES\n2.\n3.\n4.Consultar hora\n5.Ver mensaje critico\n\n>>>");
                state_UI=ESPERA;
            break;
        case ESPERA:
            seleccionar_opcion();
            break;
        case CONFIGURAR_UMBRALES:    
            if(threshold_SetUp()==true){
                state_UI=MENU;
                UI_send_text("\nSus umbrales fueron configurados con exito.\n");
            }
            break;
        case CONFIGURAR_ID:
            //if(ID_SetUp()==true){
                state_UI=MENU;
            //}
            break;
        case CONFIGURAR_TELEFONO:
            //if(Telephone_SetUp()==true){
                state_UI=MENU;
            //}
            break;
        case DAR_HORA:
            get_real_time_IS(&real_time);
            dar_hora(real_time);
            state_UI=MENU;
            break;
        case CHECK_CRITIC_MESSAGE:
            show_critic_message();
            state_UI=MENU;
            break;
        default:
            state_UI=MENU;
            break;
    }
}


void show_critic_message(void){
    char message[120];
    int humidity_local_state;
    
    humidity_local_state=humidity_state_function();
    if (humidity_local_state==RED_HIGH || humidity_local_state==RED_LOW){
        memset(message, 0, sizeof(message));
        send_critic_message(humidity_local_state, message);
        UI_send_text(message);
    }
    else{
        UI_send_text("No hay mensaje critico para enviar");
    }
}


IS_INTERFACE_STATE seleccionar_opcion(void){
    int8_t opcion_int;
    
    opcion_int=read_USB_int();
    
    if (opcion_int>0){
        switch(opcion_int){
            case 1:
                state_UI=CONFIGURAR_UMBRALES;
                break;
            case 2:
                state_UI=CONFIGURAR_ID;
                break;
            case 3:
                state_UI=CONFIGURAR_TELEFONO;
                break;
            case 4:
                state_UI=DAR_HORA;
                break;
            case 5:
                state_UI=CHECK_CRITIC_MESSAGE;
                break;
            default:
                state_UI=MENU;
                break;
        }
    }
} 

bool threshold_SetUp(){
    static TASKS_STATE state_config=INTERFACE;
    static threshold_limits limit_state=RY_max;
    bool valid_data;
    
    switch (state_config){
        case INTERFACE:
            threshold_SetUp_interface(limit_state);
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
            valid_data=threshold_SetUp_tasks(limit_state);
            if(valid_data==true){
                if(limit_state==RY_max){
                    state_config=INTERFACE;
                    limit_state=YG_max;
                    return false;
                }
                else if(limit_state==YG_max){
                    state_config=INTERFACE;
                    limit_state=YG_min;
                    return false;
                }
                else if(limit_state==YG_min){
                    state_config=INTERFACE;
                    limit_state=RY_min;
                    return false;
                }
                else{
                    state_config=END;
                }
            }
            else{
                state_config=WAIT;
                return false;
            }
            break;
        case END:
            state_config=INTERFACE;
            limit_state=RY_max;
            return true;
            break;
        default:
            return false;
            break;
    }
}

void threshold_SetUp_interface(int limit){    
    switch(limit){
        case RY_max:
            UI_send_text("\nIngrese el limite entre el umbral maximo entre amarillo y rojo(menor a 60)\n>>>");
            break;
        case YG_max:
            UI_send_text("\nIngrese el limite entre el umbral maximo entre amarillo y verde(menor al ingresado antes)\n>>>");
            break;
        case YG_min:
            UI_send_text("\nIngrese el limite entre el umbral minimo entre amarillo y verde(menor al ingresado antes)\n>>>");
            break;
        case RY_min:
            UI_send_text("\nIngrese el limite entre el umbral minimo entre amarillo y rojo(menor al ingresado antes)\n>>>");
            break;
        default:
            break;
    }    
}

