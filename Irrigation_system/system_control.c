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

#include "../mcc_generated_files/rtcc.h"
#include "../mcc_generated_files/pin_manager.h"
#include "system_control.h"
#include "../periferics/UI.h"
#include "../periferics/sensor.h"
#include "../LEDs_RGB/RGB_leds.h"
#include "../SIM_TEMP/GPS.h"


static bcdTime_t real_time_IS;
plant_t plant;
bool critic_message_pending;

void plant_init(){
    plant.status=GREEN_;
    plant.ID=0;
}

void hour_SetUp(){
    char trama[120];   
    false_frame_maker(trama);
    GPS_getUTC(&real_time_IS, trama);
    RTCC_TimeSet(&real_time_IS);
}

void get_real_time_IS (bcdTime_t *real_time){
    *real_time=real_time_IS;
}


void system_control_menu(void){
    char message[120];
    memset(message,0,sizeof(message));
    
    if (plant.status!=humidity_state_function()){
        if(humidity_state_function()==RED_LOW || humidity_state_function()==RED_HIGH){
            critic_message_pending=true;
        }
    }

        plant.status=humidity_state_function();

        switch(plant.status){
            case RED_HIGH:
            case RED_LOW:
                if(critic_message_pending==true){
                    send_critic_message(plant.status, message);
                }
                irrigation(plant.status);
                break;
            case YELLOW_HIGH:
                if(analog_conversion_to_cb()>=get_irrigation_high_threshold()){
                    irrigation(plant.status);
                }
                break;
            case GREEN_:
                if(analog_conversion_to_cb()<=get_irrigation_low_threshold()){
                    irrigation(plant.status);
                }
                break;
            case YELLOW_LOW:
                irrigation(plant.status);
                break;
        }
        RGB_humidity_state(plant.status);
}

void RGB_humidity_state(uint8_t estado_de_humedad){
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
        if(estado_de_humedad==RED_HIGH || estado_de_humedad==RED_LOW){
            if(critic_message_pending==true){
                tira_leds[1]=BLUE;
            }
            else{
                tira_leds[1]=GREEN;
            }
        }
    }
    
    WS2812_send(tira_leds, CANTIDAD_LEDS);
}

//void SMS_tasks(void);
//void irrigation(void); //funcion q
uint8_t get_irrigation_low_threshold(){
    return ((get_yellow_green_max()+get_yellow_green_min())/2);
}

uint8_t get_irrigation_high_threshold(){
    return ((get_red_yellow_max()+get_yellow_green_max())/2);
}


bool ID_SetUp(){
    
}

bool Telephone_SetUp(){
    
}

void send_critic_message(SENSOR_STATE critic_state, char* p_message){
    uint8_t trama[110];
    GPSPosition_t coord_posicion;
    char coord_posicion_str[50];
    char ID[32];
    char message[120];
    ws2812_t led_emergencia[1];
    
    
    memset(message,0,sizeof(message));
     
    //hay que cambiar esta funcion por la de la trama de verdad
    if (false_frame_maker(trama)==true){
        GPS_getPosition(&coord_posicion, trama);
    }
    else{
        coord_posicion.latitude=0;
        coord_posicion.longitude=0;
    }
    
    memset(ID,0,sizeof(ID));
    sprintf(ID, "%i", plant.ID);
    strcat(message, ID);
    
    if(critic_state==RED_LOW){
        strcat(message, " - SUELO MUY HUMEDO - ");
    }
    else{
        strcat(message, " - SUELO MUY SECO - ");
    }
    
    if(coord_posicion.latitude!=0 && coord_posicion.longitude!=0){
        strcat(message, "http://maps.google.com/maps?q=");

        memset(coord_posicion_str,0,sizeof(coord_posicion_str));
        sprintf(coord_posicion_str, "%lf,", coord_posicion.latitude);
        strcat(message, coord_posicion_str);

        memset(coord_posicion_str,0,sizeof(coord_posicion_str));
        sprintf(coord_posicion_str, "%lf", coord_posicion.longitude);
        strcat(message, coord_posicion_str);
    }
    else{
        strcat(message, "Conexion con GPS debil");
    }
    
    if(send_text_message(message)==true){
        critic_message_pending==false;
    }
    strcpy(p_message, message);
}

void irrigation(SENSOR_STATE state_irrigation){
    if((state_irrigation==YELLOW_HIGH)||(state_irrigation==RED_HIGH)){
        LEDB_SetHigh();
    }
    else{
        LEDB_SetLow();
    }
}

