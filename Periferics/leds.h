/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _LEDS_H    /* Guard against multiple inclusion */
#define _LEDS_H


#include <xc.h>
#include <stdint.h>
#include "../mcc_generated_files/rtcc.h"
#include "../mcc_generated_files/mcc.h"
#include "../utils/utils.h"


/* ************************************************************************** */
#ifdef __cplusplus
extern "C" {
#endif


    static ut_tmrDelay_t timer;
    ut_tmrDelay_t *ptimer;
    uint8_t i=0; 
    int ptimer = &timer;
    ptimer->state = 0;
    
    void led_sequence_no_bloqueante();
    
#endif