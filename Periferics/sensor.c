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

static uint8_t humidity_value;
static SENSOR_STATE humidity_state; //indica el anillo en el que esta lo sensado en el potenciometro
static bool critic_humidity; //si es true, es porque la humedad esta en anillo rojo
static bool irrigation_on; //prende el riego 
static bool irrigation_off;//apaga el riego

//FUNCIONES
int estado_humedad();//funcion que me devuelva RED_LOW, RED_HIGH, YELLOW_LOW, YELLOW_HIGH, GREEN
void encender_leds(int nivel_de_humedad);//funcion que enciende la tira de RGB dependiendo del estado de la humedad 

/*
void sensor_menu(void){
    switch(estado_humedad()){
        case RED_LOW:
            critic_humidity=true;
            //irrigation_off= x ; // falta determinar
            //irrigation_on= x ;
            break;
        case RED_HIGH:
            critic_humidity=true;
            //irrigation_off= x ; // falta determinar
            //irrigation_on= x ;
            break;
        case YELLOW_LOW:
            critic_humidity=false;
            //irrigation_off= x ; // falta determinar
            //irrigation_on= x ;
            break;
        case YELLOW_HIGH:
            critic_humidity=false;
            if (humitity_value>=((yellow_red_max+yellow_green_min)/2)){
            //irrigation_off= x ; // falta determinar
            //irrigation_on= x ;
            }
            break;
        case GREEN:
            critic_humidity=false;
            if (humitity_value<=((yellow_green_max+yellow_green_min)/2)){
            //irrigation_off= x ; // falta determinar
            //irrigation_on= x ;
            }
            break;
        default:
            break;
    }
    encender_leds(humidity_state);
}*/

void threshold_SetUp(){
    red_yellow_max=49;
    yellow_green_max=20;
    yellow_green_min=10;
    red_yellow_min=6;
}

/*        
int estado_humedad(void){//funcion que me devuelva RED_LOW, RED_HIGH, YELLOW_LOW, YELLOW_HIGH, GREEN
    humidity_value=analog_scale_to_Cb();
    if(umbral estado rojo alto){
        humidity_state=RED_HIGH;        
    }
    else if(umbral estado rojo bajo){
        humidity_state=RED_LOW;        
    }
    else if(umbral estado verde){
        humidity_state=GREEN;        
    }
    else{   
        if(umbral estado amarillo alto){
            humidity_state=YELLOW_HIGH;        
        }
        else{
            humidity_state=YELLOW_LOW
        }
    }
}
*/

char* analog_scale_to_cb(void){
    uint16_t conversion;
    char conv_array[20];
       int i;
        ADC1_Start();
        //Provide Delay
        for(i=0;i <1000;i++)
        {
        }
        ADC1_Stop();
        while(!ADC1_IsConversionComplete())
        {
            Nop();   
        }
        conversion=(ADC1_ConversionResultGet()/17);
        itoa(conv_array, conversion, 10);
        return conv_array;
 }
 