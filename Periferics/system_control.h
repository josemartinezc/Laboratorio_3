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

#ifndef _SYSTEM_CONTROL_H    /* Guard against multiple inclusion */
#define _SYSTEM_CONTROL_H


#include "sensor.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

typedef struct{
    uint8_t ID;
    uint8_t position;
    uint8_t humidity_;
    SENSOR_STATE status;
} plant_t ;

extern plant_t plant;

void system_control_menu(void);

void RGB_humidity_state(uint8_t);
 
bool ID_SetUp();
bool Telephone_SetUp();


#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
