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

#include "../mcc_generated_files/rtcc.h"
#include "UI.h"
#include "../mcc_generated_files/usb/usb.h"
#include "../utils/utils.h"


static UI_STATE state_UI=INIT;    

//funcion que devuelve lo que hay en el usb, transformando el ascii a decimales
int leer_USB_int(void){
    uint8_t datos[20];
    if(getsUSBUSART(datos, sizeof(datos))>0){
        int dato_int=atoi(datos);
        return dato_int;
    }
    else{
        return 0;
    }
}

void seleccionar_opcion();
bool configurar_hora();
bool dar_hora();
//void agregar_evento();
//void consultar_eventos();


void UI_menu(){
    static ut_tmrDelay_t timer;
    static ut_tmrDelay_t *ptimer;
    static uint8_t ini[16];
    
    uint8_t i=0; 
    ptimer = &timer;
    
    switch (state_UI){
        case INIT:
            calendar_time.tm_mday=0;
            if(getsUSBUSART(ini, sizeof(ini))>0){
            putUSBUSART("\n\n\nBIENVENIDO A SU CALENDARIO\n", strlen("\n\n\nBIENVENIDO A SU CALENDARIO\n"));
            state_UI=MENU;
            }
            break;
        case MENU:
            putUSBUSART("\nIngrese una opcion del 1-4\n", strlen("\nIngrese una opcion del 1-4\n")); 
            //me falla en la linea de arriba, vi que cd_trf_state en este punto es distinto de ready y por eso
            //putUSBUSART no entra al if en donde guarda lo que tiene que pasar al usb
            //pero no se donde es que esa variable cambia, y si la chequeo en el main nunca entra a UI.C
            //me hago una funcion mandar_daros? que tenga un dela incluido y el putusbusart?no tiene sentido.
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
    
    if (leer_USB_int()>0){
        opcion_int=leer_USB_int();
        switch(opcion_int){
            case 0:
                state_UI=ESPERA;
                break;
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

    switch(state_config){
        case 0:
            
            putUSBUSART("Ingriese el dia (00 a 31)", strlen("Ingrese el dia (00 a 31)"));
            if (leer_USB_int()>0){
                if(leer_USB_int()<32){
                    calendar_time.tm_mday=leer_USB_int();
                    state_config=2;
                }
                else{
                putUSBUSART("Ingrese un dia valido", strlen("Ingrese un dia valido"));
                }
            }
            return false;
            break;
            
        case 1:
            putUSBUSART("Ingrese el mes (1 a 12)", strlen("Ingrese el mes (1 a 12)"));
            if (leer_USB_int()>0){
                if(leer_USB_int()<13){
                    calendar_time.tm_mon=leer_USB_int();
                    state_config=3;
                }
                else{
                putUSBUSART("Ingrese un mes valido", strlen("Ingrese un mes valido"));
                }
            }
            return false;
            break;
            
        case 2:
            putUSBUSART("Ingrese el anio", strlen("Ingrese el anio"));
            if (leer_USB_int()>0){
                if(leer_USB_int()<2025){
                    calendar_time.tm_year=leer_USB_int();
                    state_config=3;
                }
                else{
                putUSBUSART("Ingrese un ano valido", strlen("Ingrese un ano valido"));
                }
            }
            return false;
            break;
            
        case 3:
            putUSBUSART("Ingrese las horas (00 a 24)", strlen("Ingrese las horas (00 a 24)"));
            if (leer_USB_int()>0){
                if(leer_USB_int()<25){
                calendar_time.tm_hour=leer_USB_int();
                state_config=1;
                }
                else{
                putUSBUSART("Ingrese una hora valida", strlen("Ingrese una hora valida"));    
                }
            }
            return false;
            break;
        
        case 4:
            putUSBUSART("Ingrese los minutos (00 a 60)", strlen("Ingrese las horas (00 a 24)"));
            if(leer_USB_int()>0){
                if(leer_USB_int()<61){
                calendar_time.tm_min=leer_USB_int();
                calendar_time.tm_sec=0;
                state_config=5;
                }
                else{
                putUSBUSART("Ingrese minutos validos", strlen("Ingrese minutos validos"));    
                }
            }
            return false;
            break;
            
            
        case 5:
            RTCC_BCDTimeSet(&calendar_time);
            state_config=6;
            return true;
            break;
            
        case 6:
            return true;
            break;
            
        default:
            state_config=0;
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
void agregar_evento(void){
    
}

void consultar_eventos(void){
    
}
*/

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

