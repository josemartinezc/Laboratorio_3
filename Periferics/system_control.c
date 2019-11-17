/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    System control describe las funciones que hacen referencia a:
 *  - tiempo real del sistema,
 *  - sistema de riego
 *  - control de SMS.
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
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#include "system_control.h"
#include "../mcc_generated_files/rtcc.h"
#include "UI.h"
#include "sensor.h"
#include "../LEDs_RGB/RGB_leds.h"


void system_control_menu(void){
    humidity_state=humidity_state_function();
    
    RGB_humidity_state(humidity_state);
 /*   if (humidity_state==RED_HIGH || humidity_state==RED_LOW){
        send_text_message();
    }*/
}

void RGB_humidity_state(int estado_de_humedad){
    uint8_t i;
    ws2812_t tira_leds[CANTIDAD_LEDS];
    ws2812_t color_indicator;
    
    if(estado_de_humedad==RED_HIGH || estado_de_humedad==RED_LOW){
        color_indicator=RED;
    }
    else if(estado_de_humedad==YELLOW_HIGH || estado_de_humedad==YELLOW_LOW){
        color_indicator=YELLOW; //hay que hacer el color amarillo
    }
    else{
        color_indicator=GREEN;
    }
    
    for (i=0;i<8;i++){
        tira_leds[i]=color_indicator;
    }
    
    WS2812_send(tira_leds, CANTIDAD_LEDS);
}

//void irrigation(void); //funcion que prende o apaga el riego en caso de que sea necesario
//void SMS_tasks(void);
//void irrigation(void); //funcion q


void send_text_message(void){
    //*int get_GPS_coord(); //funcion que debuelve un puntero a las coordenadas ya sseparadas de la trama
    
}

void irrigation(void){
    
}
