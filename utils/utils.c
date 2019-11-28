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

/* This section lists the other files that are included in this file.
 */
#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#include "utils.h"
#include "../mcc_generated_files/tmr2.h"


void UT_delayDs_bolqueante ( int i ){
    int t;
    t = TMR2_SoftwareCounterGet ();
    while ( TMR2_SoftwareCounterGet () < t + i);
}


bool UT_delayDs(ut_tmrDelay_t* p_timer, uint32_t p_ds){
    switch ( p_timer->state ) {
        case (UT_TMR_DELAY_INIT):
            p_timer -> startValue = TMR2_SoftwareCounterGet ();
            p_timer -> state = 1;
            return false;
        case (UT_TMR_DELAY_WAIT): 
            if (TMR2_SoftwareCounterGet () < p_timer->startValue + p_ds)
                return false;
            else {
                p_timer->state = 0;
                return true;
            }
    }
}


