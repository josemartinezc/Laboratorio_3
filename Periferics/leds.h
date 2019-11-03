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

    void led_Sequence_bloqueante();
    void led_sequence();
    
#endif