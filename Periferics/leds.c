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

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <stdbool.h>
#include <xc.h> 

#include "../utils/utils.h"
#include "leds.h"
#include "../mcc_generated_files/mcc.h"


/*
                         Main application
*/

ut_tmrDelay_t timer;
ut_tmrDelay_t *ptimer;
uint8_t i;


void led_sequence_bloqueante(void){
 if(button3On==true){
            LEDA_SetHigh ();
            UT_delayDs_bolqueante(20);  
            LEDA_SetLow();
            button3On = false; 
        }
}
 
void sequence_configuration(void){
    uint8_t i=0;         
    ptimer = &timer;
    ptimer->state = 0;
}

void led_sequence(void){
    static bool estado_leds=false;

    switch (estado_leds){
        case false:
            sequence_configuration();
            estado_leds=true;
            break;
        case true:
            if (UT_delayDs(ptimer,40) == true) {
                switch (i){
                    case 0:
                        LEDA_SetHigh();
                        i++;
                        break;
                    case 1:
                        LEDA_SetLow();
                        i++;
                        break;
                    case 2:
                        i = 0;
                        break;
                }
            }
    }
}