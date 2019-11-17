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
//#include "UI.h"
//VARIABLES

//umbrales
static uint8_t red_yellow_max;
static uint8_t yellow_green_max;
static uint8_t yellow_green_min;
static uint8_t red_yellow_min;

//FUNCIONES
//funcion que me devuelva RED_LOW, RED_HIGH, YELLOW_LOW, YELLOW_HIGH, GREEN


void threshold_SetUp(){
    red_yellow_max=49;
    yellow_green_max=20;
    yellow_green_min=10;
    red_yellow_min=6;
}

       
int humidity_state_function(void){//funcion que me devuelva RED_LOW, RED_HIGH, YELLOW_LOW, YELLOW_HIGH, GREEN   
    uint16_t humidity_value;
    
    humidity_value=analog_scale_to_cb();
    if(humidity_value>=41){
        return RED_HIGH;        
    }
    else if(humidity_value<=5){
        return RED_LOW;        
    }
    else if(humidity_value>=10 && humidity_value<=20){
        return GREEN_;        
    }
    else{   
        if(humidity_value>20){
            return YELLOW_HIGH;        
        }
        else{
            return YELLOW_LOW;
        }
    }
}


uint16_t analog_scale_to_cb(void){
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
    
    conversion=analog_scale_to_cb();
    itoa(array_cb_conversion, conversion, 10);
}