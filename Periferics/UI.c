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
static uint8_t numero_evento=0;
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
    uint8_t datos[20]={0};
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

void seleccionar_opcion();

bool configurar_hora();
void configurar_hora_interface();
bool config_hora_function();

void dar_hora();

bool agregar_evento();
void configurar_evento_interface();
bool configurar_evento();

//void consultar_eventos();


void UI_menu(){
    static uint8_t ini[16];
   
    switch (state_UI){
        case INIT:
            real_time.tm_mday=0;
            if( USBGetDeviceState() == CONFIGURED_STATE ){
                if(getsUSBUSART(ini, sizeof(ini))>0){
                    UI_send_text("\n\n\nBIENVENIDO A SU CALENDARIO\n");
                    state_UI=MENU;
                }
            }
            break;
        case MENU:
                UI_send_text("\nIngrese una opcion del 1-4\n1.Configurar fecha y hora\n2.consultar hora\n3.Agregar evento\n4.Consultar eventos\n\n>>>");
                state_UI=ESPERA;
            break;
        case ESPERA:
            seleccionar_opcion();
            break;
        case CONFIGURAR:
            //configurar_hora();
            if (configurar_hora()==true){
                UI_send_text("\n\nSu hora a sido configurada con exito!\n\n\n\n");
                state_UI=MENU;   
            }
            break;
        case DAR_HORA:
            dar_hora();
            state_UI=MENU;
            break;
        case AGREGAR_EVENTO:
            //agregar_evento();
            if (agregar_evento()== true){
            state_UI=MENU;      
            }
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
            if(UI_int_lecture>0){
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
            RTCC_BCDTimeSet(&real_time);
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
            if(UI_int_lecture<10000 && UI_int_lecture>999){
                real_time.tm_year=(UI_int_lecture-1900);
                return true;
            }
            else{
                UI_send_text("\nIngrese un anio valido");
                return false;
            }
            break;
        case 3:
            if(UI_int_lecture<24 && UI_int_lecture>0){
                real_time.tm_hour=UI_int_lecture;
                return true;
            }
            else{
                UI_send_text("\nIngrese una hora valida");    
                return false;
            }
            break;
        case 4:
            if(UI_int_lecture<60 && UI_int_lecture>0){
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


void dar_hora(void){    
    if((real_time.tm_mday)>0){
        RTCC_TimeGet(&real_time);
        strftime(date_time_representation, 32, "%c", &real_time);
        UI_send_text("\n\n");
        UI_send_text(date_time_representation); 
        UI_send_text("\n\n");
    }
    else{
        UI_send_text("\nUsted aun no a ingresado fecha y hora");  
    }
}


bool agregar_evento(void){
    static TASKS_STATE state_events=INTERFACE;
    static int p_agregar_eventos_state;
    bool dato_ingresado_valido;
    
    if(real_time.tm_mday==0){
        UI_send_text("\nDebe configurar fecha y hora para agregar un evento\n");
        return true;
    }
    else{
        switch(state_events)
        {
            case INTERFACE:
                configurar_evento_interface(p_agregar_eventos_state);
                state_events=WAIT;
                return false;
                break;
            case WAIT:
                UI_int_lecture=read_USB_int();
                if(UI_int_lecture>0){
                    state_events=DO_TASKS;
                }
                return false;
                break;
            case DO_TASKS:
                dato_ingresado_valido=configurar_evento(p_agregar_eventos_state);
                if(dato_ingresado_valido==true){
                    p_agregar_eventos_state++;
                    if(p_agregar_eventos_state>4){
                        state_events=END;
                    }
                }
                else{
                    state_events=INTERFACE;
                }
                return false;
                break;
            case END:
                p_agregar_eventos_state=0;
                state_events=INTERFACE;
                if(numero_evento<17){
                    numero_evento++;
                }
                else{
                    UI_send_text("\nSu agenda esta llena!\n Sus nuevos eventos sustituiran un evento viejos\n");
                    numero_evento=0;
                }
                return true;
                break;
            default:
                return false;
                break;
        }
    }
}


void configurar_evento_interface(int estado){
    switch (estado){
        case 0:
            UI_send_text("\nIngrese el led que desea encender (1 al 8)\n>>>");
            break;
        case 1:
            UI_send_text("\nIngrese:\n1. Si desea que la led se encienda\n2.2.Si desea que la led se apague\n>>>");
            break;
        case 2:
            UI_send_text("\nIngrese el color de evento\n0.Blanco\n1.Rojo\n2.Azul\n3.Verde\n>>>");
            break;
        case 3:
            UI_send_text("\nIngrese la hora en la que sera programado (00-23)\n>>>");
            break;
        case 4:
            UI_send_text("\nIngrese los minutos en la que sera programado (00 al 59)\n>>>");
            break;
        default:
            break;       
    }               
}

bool configurar_evento(int estado){
    switch (estado){
        case 0:
            if(UI_int_lecture>0 && UI_int_lecture<9){
                eventos[numero_evento].param=UI_int_lecture;
                return true;
            }
            else{
                UI_send_text("\nEl numero de led a encender es invalido!");
                return false;
            }//ingrese el numero de event
            break;
        case 1:
            if(UI_int_lecture==0 || UI_int_lecture==1){
                eventos[numero_evento].command=UI_int_lecture;
                return true;
            }
            else{
                UI_send_text("\nSu comando es invalido!");
                return false;
            }
            //ingrese la funcion a ejecutarse
            break;
        case 2:
            if(UI_int_lecture>=0 && UI_int_lecture<4)
            {
                eventos[numero_evento].color=UI_int_lecture;
                return true;
            }
            else{
                UI_send_text("\nEl numero de color seleccionado es invalido!");
                return false;
            }
            //ingrese el color del evento
            break;
        case 3:
             if(UI_int_lecture<24 && UI_int_lecture>0){
                event_dates[numero_evento].tm_hour=UI_int_lecture;
                return true;
            }
            else{
                UI_send_text("\nIngrese una hora valida");    
                return false;
            }
            break;
        case 4:
            if(UI_int_lecture<60 && UI_int_lecture>0){
                event_dates[numero_evento].tm_min=UI_int_lecture;
                event_dates[numero_evento].tm_sec=0;
                event_dates[numero_evento].tm_mon=real_time.tm_mon;
                event_dates[numero_evento].tm_year=real_time.tm_year;
                return true;
            }
            else{
                UI_send_text("\nIngrese minutos validos");    
                return false;
            }
        default:
            break;
    }
}
/*
void consultar_eventos(void){
    
}
*/

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

