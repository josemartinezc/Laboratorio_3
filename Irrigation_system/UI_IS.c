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
#include "UI_IS.h"
#include "data_register.h"
#include "sensor.h"
#include "../mcc_generated_files/usb/usb.h"
#include "../periferics/UI.h"
#include "../SIM808/GPS.h"
#include "../SIM808/GSM.h"


//variables
    static IS_INTERFACE_STATE state_UI=INIT; 

void interface_IS(){
    static uint8_t ini[16];
    bcdTime_t real_time;
   
    switch (state_UI){       
        case INIT:
            if( USBGetDeviceState() == CONFIGURED_STATE ){
                if(getsUSBUSART(ini, sizeof(ini))>0){
                    UI_send_text("\nBIENVENIDO A SU SISTEMA DE RIEGO!");
                    state_UI=MENU;
                }
            }
            break;
        case MENU:
                UI_send_text("\n\nIngrese una opcion del 1-7\n1.Configurar UMBRALES\n2.Configurar ID\n3.Configurar telefono\n4.Consultar hora\n5.Ver mensaje critico\n6.Mostrar registros guardados\n7.Configurar SIM\n>>>");
                state_UI=ESPERA;
            break;
        case ESPERA:
            seleccionar_opcion();
            break;
        case CONFIGURAR_UMBRALES:    
            if(threshold_SetUp()==true){
                state_UI=MENU;
            }
            break;
        case CONFIGURAR_ID:
            if(ID_SetUp()==true){
                state_UI=MENU;
            }
            break;
        case CONFIGURAR_TELEFONO:
            if(Telephone_SetUp()==true){
                state_UI=MENU;
            }
            break;
        case DAR_HORA:
            if(hour_SetUp()==true){
                dar_hora(get_real_time_IS());
            }
            else{
                UI_send_text("\n\nLa hora aún no ha podido ser configurada\n");
            }
            state_UI=MENU;
            break;
        case CHECK_CRITIC_MESSAGE:
            show_critic_message();
            state_UI=MENU;
            break;
        case SHOW_REGISTERS:
            if(show_data_registers()==true){
                state_UI=MENU;
            }
            break;
        case CONFIG_SIM:
            if(config_SIM_UI()==true){
                state_UI=MENU;
            }
            break;
        default:
            state_UI=MENU;
            break;
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
            case 6:
                state_UI=SHOW_REGISTERS;
                break;
            case 7:
                state_UI=CONFIG_SIM;
                break;
            default:
                state_UI=MENU;
                break;
        }
    }
} 

bool show_data_registers(){
    historic_data data_register;
    static uint8_t i=0;
    static bool all_data_sent=true;
    uint8_t hora[16];
    uint8_t numero_de_registro[8];
    uint8_t google_link[128];
    uint8_t status_str[64];
    uint8_t register_info[256];
    
    if (get_empty_buffer_value()==false){
        all_data_sent=get_register(&data_register);
        memset(register_info,0,sizeof(register_info));
        memset(hora,0,sizeof(hora));
        memset(numero_de_registro, 0, sizeof(numero_de_registro));
        memset(google_link, 0, sizeof(google_link));
        memset(status_str, 0, sizeof(status_str));

        sprintf(numero_de_registro, "%i", (data_register.event_number));
        get_humidity_state_string(data_register.status, status_str);
        if(data_register.hour_and_date.tm_mday!=0){
            strftime(hora, sizeof(hora), "%X", &data_register.hour_and_date);
        }
        else{
            strcpy(hora, "-");
        }
        if(data_register.position.latitude!=0 && data_register.position.longitude!=0){
            get_google_link(data_register.position, google_link);
        }
        else{
            strcpy(google_link, "no se pudo obtener, conexion a GPS debil.");
        }

        strcat(register_info, "\n\nREGISTRO NUMERO ");
        strcat(register_info, numero_de_registro);
        strcat(register_info, " estado ");
        strcat(register_info, status_str);
        strcat(register_info, "\nGuardado a la hora ");
        strcat(register_info, hora);
        strcat(register_info, "\nUbicacion ");
        strcat(register_info, google_link);
        UI_send_text(register_info);
        if(all_data_sent==false){
            return false;
        }
    }
    else{
        UI_send_text("\n\nNo hay datos para mostrar");
    }
    return true;
}

void show_critic_message(void){
    char message[256];
    int humidity_local_state;
    bool critic_message_state;
    
    humidity_local_state=humidity_state_function();
    if (humidity_local_state==RED_HIGH || humidity_local_state==RED_LOW){
        memset(message, 0, sizeof(message));
        get_critic_message(humidity_local_state, message);
        UI_send_text("\n\n");
        UI_send_text(message);
    }
    else{
        UI_send_text("\n\nNo hay mensaje critico para enviar");
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




