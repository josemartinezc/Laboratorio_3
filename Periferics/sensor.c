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
#include "../LEDs_RGB/RGB_leds.h"
#include "sensor.h"

//VARIABLES


//FUNCIONES
int estado_humedad();//funcion que me devuelva RED_LOW, RED_HIGH, YELLOW_LOW, YELLOW_HIGH, GREEN
void encender_leds(int nivel_de_humedad);//funcion que enciende la tira de RGB dependiendo del estado de la humedad 
uint8_t analog_scale_to_Cb(); //funcion que linealiza los valores de 0-1024 a 0-60. Debuelve un int entre 0 y 60
void threshold_SetUp();

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
}

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

/*int analog_scale_to_cb(void){
 
 }
 */