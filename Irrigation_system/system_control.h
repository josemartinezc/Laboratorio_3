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


#include "../mcc_generated_files/rtcc.h"
#include "../periferics/sensor.h"
#include <stdio.h>

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

typedef struct{
    uint32_t ID;
    uint8_t position;
    uint8_t humidity_;
    SENSOR_STATE status;
} plant_t ;

extern plant_t plant;

void plant_init();
uint8_t get_irrigation_low_threshold();
uint8_t get_irrigation_high_threshold(); 
void get_real_time_IS (bcdTime_t*);

void system_control_menu(void);

void hour_SetUp();
bool ID_SetUp();
bool Telephone_SetUp();

void RGB_humidity_state(uint8_t);
void irrigation(SENSOR_STATE);
void send_critic_message(SENSOR_STATE, char*);

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
