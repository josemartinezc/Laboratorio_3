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

#ifndef _UI_IS_H    /* Guard against multiple inclusion */
#define _UI_IS_H

#include <stdbool.h>

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

    typedef enum{
        INIT,
        MENU,        
        ESPERA,
        CONFIGURAR_ID,
        CONFIGURAR_UMBRALES,
        CONFIGURAR_TELEFONO,
        DAR_HORA,
        CHECK_CRITIC_MESSAGE,
        SHOW_REGISTERS,
        CONFIG_SIM,
    }IS_INTERFACE_STATE;
    
    void interface_IS();

    IS_INTERFACE_STATE seleccionar_opcion();
    bool threshold_SetUp();
    void threshold_SetUp_interface(int);
    void show_critic_message(void);
    bool show_data_registers();
    
#endif