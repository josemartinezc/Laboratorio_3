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
#include "../utils/utils.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
    #define TAMANO_SEND 255
    #define TAMANO_SAVE 511
    
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
    
    
    int32_t read_USB_int(void);
    void UI_send_text(uint8_t *text);
    extern int32_t UI_int_lecture;
    
    void Initialize_USB_delay(ut_tmrDelay_t*);
    void UI_tasks (void);
    void UI_menu (void);
    void do_events(void);
    
    bool configurar_hora();
    void configurar_hora_interface();
    bool config_hora_function();

    void dar_hora(bcdTime_t);

    bool agregar_evento();
    void configurar_evento_interface();
    bool configurar_evento();

    ws2812_t interpret_event_color(uint8_t);

    void consultar_eventos();
    
/* *****************************************************************************
 End of File
 */
