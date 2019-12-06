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

#include "../utils/utils.h"
#include "../LEDs_RGB/RGB_leds.h"
#include "sensor.h"
#include "UI.h"


//VARIABLES

//umbrales
static uint8_t red_yellow_max;
static uint8_t yellow_green_max;
static uint8_t yellow_green_min;
static uint8_t red_yellow_min;

uint8_t get_red_yellow_max(){
    return red_yellow_max;
}

uint8_t get_yellow_green_max(){
    return yellow_green_max;
}

uint8_t get_yellow_green_min(){
    return yellow_green_min;
}

uint8_t get_red_yellow_min(){
    return red_yellow_min;
}


void threshold__default_SetUp(){
    red_yellow_max=41;
    yellow_green_max=20;
    yellow_green_min=10;
    red_yellow_min=6;
}

bool threshold_SetUp_tasks(uint8_t limit_state){
    char limite_valido[8];
    
    switch(limit_state){
        case RY_max:
            if(UI_int_lecture<MAX_CB_VALUE){
                red_yellow_max=UI_int_lecture;
                return true;
            }
            else{
                UI_send_text("\nIngrese un valor valido, menor a ");
                sprintf(limite_valido, "%i", MAX_CB_VALUE);
                UI_send_text(limite_valido);
                UI_send_text("\n>>>");
                return false;
            }
            break;
        case YG_max:
            if(UI_int_lecture<red_yellow_max){
                yellow_green_max=UI_int_lecture;
                return true;
            }
            else{
                UI_send_text("\nIngrese un valor valido, menor a ");
                sprintf(limite_valido, "%i", red_yellow_max);
                UI_send_text(limite_valido);
                UI_send_text("\n>>>");
                return false;
            }
            break;
        case YG_min:
            if(UI_int_lecture<yellow_green_max){
                yellow_green_min=UI_int_lecture;
                return true;
            }
            else{
                UI_send_text("\nIngrese un valor valido, menor a ");
                sprintf(limite_valido, "%i", yellow_green_max);
                UI_send_text(limite_valido);
                UI_send_text("\n>>>");
                return false;
            }
            break;
        case RY_min:
            if(UI_int_lecture<yellow_green_min){
                red_yellow_min=UI_int_lecture;
                return true;
            }
            else{
                UI_send_text("\nIngrese un valor valido, menor a ");
                sprintf(limite_valido, "%i", yellow_green_min);
                UI_send_text(limite_valido);
                UI_send_text("\n>>>");
                return false;
            }
            break;
        default:
            break;
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
                    return false;
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
            UI_send_text("\n\nSus umbrales fueron configurados con exito.\n");
            return true;
            break;
        default:
            return false;
            break;
    }
}

int humidity_state_function(void){//funcion que me devuelva RED_LOW, RED_HIGH, YELLOW_LOW, YELLOW_HIGH, GREEN   
    uint16_t humidity_value;
    
    humidity_value=analog_conversion_to_cb();
    
    if(humidity_value>=red_yellow_max){
        return RED_HIGH;        
    }
    else if(humidity_value<=red_yellow_min){
        return RED_LOW;        
    }
    else if(humidity_value>=yellow_green_min && humidity_value<=yellow_green_max){
        return GREEN_;        
    }
    else{   
        if(humidity_value>yellow_green_max){
            return YELLOW_HIGH;        
        }
        else{
            return YELLOW_LOW;
        }
    }
}


uint16_t analog_conversion_to_cb(void){
    uint16_t conversion;
    uint16_t conversion_cb_scale;

    int i;
    
    ADC1_Start();
    for(i=0;i <1000;i++){
    }
    ADC1_Stop();
    while(!ADC1_IsConversionComplete()){
        Nop();   
    }
    
    conversion=(ADC1_ConversionResultGet());
    conversion_cb_scale=((conversion*MAX_CB_VALUE)/1023);
    
    return conversion_cb_scale;
}
 
void analog_scale_to_cb_array(char* array_cb_conversion){
    uint16_t conversion;
    
    conversion=analog_conversion_to_cb();
    itoa(array_cb_conversion, conversion, 10);
}