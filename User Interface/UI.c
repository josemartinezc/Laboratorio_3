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
#include "../utils/utils.h"


static UI_STATE state_UI=INIT;    
static uint8_t evento;
static int UI_int_lecture;

bool UI_tasks (void){  
    if( USBGetDeviceState() < CONFIGURED_STATE ){
        return false;
    }

    if( USBIsDeviceSuspended()== true ){
        return false;
    }

    if( USBUSARTIsTxTrfReady() == true && all_sent==false){
        putUSBUSART(buffer_USB_send_text, strlen(buffer_USB_send_text));
        all_sent=true;
    }
    
    CDCTxService();
    return true;
}


//funcion que devuelve lo que hay en el usb, transformando el ascii a decimales
int read_USB_int(void){
    static uint8_t datos[20];
    int dato_int;
    
    if(getsUSBUSART(datos, sizeof(datos))>0){
        dato_int=atoi(datos);
        return dato_int;
    }
    else{
        return 0;
    }
}

void UI_send_text(const char *text){
    
    if (all_sent==true){
        memset(buffer_USB_send_text, 0, sizeof(buffer_USB_send_text));
    }
        strcat(buffer_USB_send_text, text);           
        all_sent=false;
}

void configurar_hora_interface();
bool config_hora_function();
void seleccionar_opcion();
bool configurar_hora();
bool dar_hora();
//bool agregar_evento();
//void consultar_eventos();


void UI_menu(){
    static uint8_t ini[16];
   
    switch (state_UI){
        case INIT:
            calendar_time.tm_mday=0;
            if( USBGetDeviceState() == CONFIGURED_STATE ){
                if(getsUSBUSART(ini, sizeof(ini))>0){
                    UI_send_text("\n\n\nBIENVENIDO A SU CALENDARIO\n");
                    state_UI=MENU;
                }
            }
            break;
        case MENU:
                UI_send_text("\nIngrese una opcion del 1-4\n");
                state_UI=ESPERA;
            break;
        case ESPERA:
            seleccionar_opcion();
            break;
        case CONFIGURAR:
            configurar_hora();
            if (configurar_hora()==true){
                state_UI=MENU;   
            }
            break;
        case DAR_HORA:
            dar_hora();
            if(dar_hora()==true){
                state_UI=MENU;
            }
            break;
        case AGREGAR_EVENTO:
            //agregar_evento();
            state_UI=MENU;  
            break;
        case CONSULTAR_EVENTOS:
            //consultar_eventos();
            state_UI=MENU;  
            break;
        default:
            state_UI=MENU;
            break;
    }
}

void seleccionar_opcion(void){
    uint8_t opcion_int;
    
    opcion_int=read_USB_int();
    
    if (opcion_int>0){
        switch(opcion_int){
            case 1:
                state_UI=CONFIGURAR;
                break;
            case 2:
                state_UI=DAR_HORA;
                break;
            case 3:
                state_UI=AGREGAR_EVENTO;
                break;
            case 4:
                state_UI=CONSULTAR_EVENTOS;
                break;
            default:
                state_UI=MENU;
                break;
        }
    }
}       


bool configurar_hora(void){
    static int state_config=0;
    static int p_config_hora_state;
    bool dato_ingresado_valido;
    
    switch (state_config){
        case 0:
            configurar_hora_interface(p_config_hora_state);
            state_config=1;
            return false;
            break;
        case 1:
            UI_int_lecture=read_USB_int();
            if(UI_int_lecture>0){
                state_config=2;
            }
            return false;
            break;
        case 2:
            dato_ingresado_valido=config_hora_function(p_config_hora_state);
            if(dato_ingresado_valido==true){
                if(p_config_hora_state<5){
                    state_config=0;
                    p_config_hora_state++;
                    return false;
                }
                else{
                    state_config=3;
                    p_config_hora_state=0;
                    return false;
                }
            }
            else{
                state_config=0;
                return false;
            }
            break;
        case 3:
            RTCC_BCDTimeSet(&calendar_time);
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
    }
}

bool config_hora_function(int config_hora_state){ 
    switch(config_hora_state){
        case 0:
            if(UI_int_lecture<32 && UI_int_lecture>0){
                calendar_time.tm_mday=UI_int_lecture;
                return true;
            }
            else{
                UI_send_text("\nIngrese un dia valido");
                return false;
            }
            break;            
        case 1:
            if(UI_int_lecture<13 && UI_int_lecture>0){
                calendar_time.tm_mon=UI_int_lecture;
                return true;
            }
            else{
                UI_send_text("\nIngrese un mes valido");
                return false;
            }
            break;            
        case 2:
            if(UI_int_lecture<10000 && UI_int_lecture>999){
                calendar_time.tm_year=UI_int_lecture;
                return true;
            }
            else{
                UI_send_text("\nIngrese un ano valido");
                return false;
            }
            break;
        case 3:
            if(UI_int_lecture<24 && UI_int_lecture>0){
                calendar_time.tm_hour=UI_int_lecture;
                return true;
            }
            else{
                UI_send_text("\nIngrese una hora valida");    
                return false;
            }
            break;
        case 4:
            if(UI_int_lecture<60 && UI_int_lecture>0){
                calendar_time.tm_min=UI_int_lecture;
                calendar_time.tm_sec=0;
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


bool dar_hora(void){
    char horario[8];
    char fecha[8];
    
    if((calendar_time.tm_mday)>0){
        strftime(horario, 8, "%X", &calendar_time);
        strftime(fecha, 8, "%x", &calendar_time);
        putUSBUSART("Hora: ", strlen("Hora: "));
        putUSBUSART(horario, sizeof horario);
        putUSBUSART("\nFecha: ", strlen("\nFecha: "));
        putUSBUSART(fecha, sizeof fecha); 
        return true;
    }
    else{
        putUSBUSART("\nUsted aun no a ingresado fecha y hora", strlen("\nUsted aun no a ingresado fecha y hora"));  
        return false;
    }
}


/*
bool agregar_evento(void){
    static int state_eventos=0;
    
    switch(state_eventos)
    {
        case 0:
            putUSBUSART("Ingrese el numero de evento a configurar (Del 1 al 8)", strlen("Ingrese el numero de evento a configurar (Del 1 al 8)"));  
            if (read_USB_int>0){
                evento=read_USB_int();
                configurar_evento(evento);
            }
    }
}

void configurar_evento (int numero_evento){
    
}
*/
/*
void consultar_eventos(void){
    
}
*/

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

