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

#ifndef _UI_H    /* Guard against multiple inclusion */
#define _UI_H

#endif
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "../mcc_generated_files/rtcc.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
        
    typedef enum{
        INIT,
        MENU,        
        ESPERA,
        CONFIGURAR,
        DAR_HORA,
        AGREGAR_EVENTO,
        CONSULTAR_EVENTOS,                
    }UI_STATE;

    static bcdTime_t calendar_time;
    
/* *****************************************************************************
 End of File
 */
