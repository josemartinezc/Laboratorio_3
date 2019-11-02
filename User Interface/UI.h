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
    
    #define TAMANO 128
    
    
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
    
    typedef struct{
        uint8_t command;
        uint8_t param;
        uint8_t color;
        uint32_t time;
    } app_event_t ;
    
    app_event_t eventos[8];
    
    static uint8_t buffer_USB_send_text[TAMANO];
    static bool all_sent;
    
    bool UI_tasks (void);
    
    
/* *****************************************************************************
 End of File
 */
