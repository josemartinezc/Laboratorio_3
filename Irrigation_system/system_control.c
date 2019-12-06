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
static uint8_t telephone_number[9]; 

void plant_init(){
    plant.status=GREEN_;
    plant.ID=0;
}

bool hour_SetUp(){
    char trama[120];   
    bool time_is_set=false;
    
    if(time_is_set==true){
        return true;
    }
    
    memset(trama, 0, sizeof(trama));
    if (get_trama(trama)==true){
        GPS_getUTC(&real_time_IS, trama);
        RTCC_TimeSet(&real_time_IS);
        time_is_set=true;
        return true;
    }
    else{
        return false;
    }
}

bcdTime_t get_real_time_IS (){
    RTCC_TimeGet(&real_time_IS);
    return real_time_IS;
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
    static TASKS_STATE state_config;
    switch (state_config){
        case INTERFACE:
            UI_send_text("\nIngrese el ID de su planta (max 99999)\n\n>>>");
            state_config=WAIT;
            break;
        case WAIT:
            UI_int_lecture=read_USB_int();
            if(UI_int_lecture>=0){
                state_config=DO_TASKS;
            }
            break;
        case DO_TASKS:
            if(UI_int_lecture<=99999){
                plant.ID=UI_int_lecture;
                UI_send_text("\n\nEl ID de su planta a sido configurado con exito!");
                return true;
            }
            else{
                state_config=INTERFACE;
            }
            break;
        default:
            break;
    }
    return false;
}

bool Telephone_SetUp(){
    static TASKS_STATE state_config;
    static uint8_t aux_telephone_number[8];
    
    switch (state_config){
        case INTERFACE:
            UI_send_text("\nIngrese el numero de telefono para recibir alertas\nComplete los 9 digitos:\n>>>09");
            state_config=WAIT;
            break;
        case WAIT:
            UI_int_lecture=read_USB_int();
            if(UI_int_lecture>=0){
                state_config=DO_TASKS;
            }
            break;
        case DO_TASKS:
            memset(aux_telephone_number,0,sizeof(aux_telephone_number));
            sprintf(aux_telephone_number, "%i", UI_int_lecture);
            if(save_telephone_number(aux_telephone_number)==true){
                UI_send_text("\n\nEl numero ");
                UI_send_text(telephone_number);
                UI_send_text(" ha sido configurado con exito.\n");
                state_config=INTERFACE;
                return true;
            }
            else{
                UI_send_text("\n\nIngrese un numero de telefono valido\n>>09");
                state_config=WAIT;
            }   
            break;
        default:
            break;
    }
    return false;
}

bool save_telephone_number(uint8_t* p_aux_number){
    uint8_t telephone_strlen;
    uint8_t i;
    
    if(UI_int_lecture<=9999999 && p_aux_number[0]>0){
        telephone_strlen=strlen(p_aux_number);
        memset(telephone_number,0,sizeof(telephone_number));
        strcat(telephone_number, "09");
        if(telephone_strlen==7){
            strcat(telephone_number, p_aux_number);
            return true;
        }
        else{
            if(p_aux_number[7]==0){
                strcat(telephone_number, p_aux_number);
                for(i=(telephone_strlen+1); i<=7; i++){
                    strcat(0,p_aux_number);
                    return true;
                }
            }
        }
    }
    return false;
}

void send_critic_message(SENSOR_STATE critic_state, char* p_message){
    uint8_t trama[110];
    GPSPosition_t coord_posicion;
    char coord_posicion_str[50];
    char ID[32];
    char message[120];
    uint8_t gps_link[100];
    
    
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
        get_google_link(coord_posicion, gps_link);
        strcat(message, gps_link);
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

void get_humidity_state_string(SENSOR_STATE status, uint8_t* status_str){
    switch(status){
        case RED_HIGH:
            strcpy(status_str, "Rojo alto, suelo muy seco");
            break;
        case RED_LOW:
            strcpy(status_str, "Rojo bajo, suelo muy humedo");
            break;
        case YELLOW_HIGH:
            strcpy(status_str, "Amarillo alto, levemente seco");
            break;
        case YELLOW_LOW:
            strcpy(status_str, "Amarillo bajo, levemente humedo");
            break;
        case GREEN_:
            strcpy(status_str, "Verde, humedad optima.");
            break;
    }
}