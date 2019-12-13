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

#ifndef _SIM_IS_TASKS_H    /* Guard against multiple inclusion */
#define _SIM_IS_TASKS_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdint.h>
    

typedef enum{
    WAIT_TEL,
    NET,
    PIN,
    COMPANY,
    SET_PIN,
    END_PIN,
    END_TEL,
}sim_card_state_t;

extern bool available_SIM_card;

bool Init_SIMCard(void);
bool send_text_message(uint8_t *p_message, uint8_t *p_telephone_num);
bool config_SIM_UI();


#endif /* _EXAMPLE_FILE_NAME_H */












/* *****************************************************************************
 End of File
 */
