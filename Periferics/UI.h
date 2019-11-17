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
#include "../LEDs_RGB/RGB_leds.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
    #define TAMANO 256
    #define MAX_EVENTOS 16
    
    typedef enum{
        INIT,
        MENU,        
        ESPERA,
        CONFIGURAR,
        DAR_HORA,
        AGREGAR_EVENTO,
        CONSULTAR_EVENTOS,
        DEBUG,
    }UI_STATE;
    
    typedef enum{
        INTERFACE,
        DO_TASKS,
        WAIT,
        END,        
    }TASKS_STATE;
    
    typedef struct{
        uint8_t command;
        uint8_t param;
        uint8_t color;
        uint32_t time;
    } app_event_t ;
    
    static app_event_t eventos[MAX_EVENTOS];
    static bcdTime_t event_dates[MAX_EVENTOS];
    
    int read_USB_int(void);
    void UI_send_text(const char *text);
    
    bool UI_tasks (void);
    void UI_menu (void);
    void do_events(void);
    
    void seleccionar_opcion();
    bool configurar_hora();
    void configurar_hora_interface();
    bool config_hora_function();

    void dar_hora();

    bool agregar_evento();
    void configurar_evento_interface();
    bool configurar_evento();

    ws2812_t interpret_event_color(uint8_t);

    void consultar_eventos();
    
/* *****************************************************************************
 End of File
 */
