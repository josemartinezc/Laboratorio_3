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

void led_sequence(void){
 if(button3On==true){
            LEDA_SetHigh ();
            UT_delayDs (20);  
            LEDA_SetLow();
            button3On = false; 
        }
}
 
void led_sequence_no_bloqueante(void){
    if (UT_delayDs(ptimer,40) == true) {
        switch (i){
            case (0):
                LEDA_SetHigh();
                i++;
                break;
            case (1):
                LEDA_SetLow();
                i++;
                break;
            case (2):
                i = 0;
                break;
        }
    }
}