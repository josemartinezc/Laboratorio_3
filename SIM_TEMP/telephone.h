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
    NET,
    PIN,
    COMPANY,
}sim_card_state_t;

typedef enum{
   STG0,
   STG1,
   STG2,
   STG3,
   STG4,
   STG5,
}msg_stage_state_t;


bool Init_SIMCard (void);
bool send_text_message(char *p_message);


#endif /* _EXAMPLE_FILE_NAME_H */












/* *****************************************************************************
 End of File
 */
