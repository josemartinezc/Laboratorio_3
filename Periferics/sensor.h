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

#ifndef _SENSOR_H    /* Guard against multiple inclusion */
#define _SENSOR_H

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <xc.h>

#define MAX_CB_VALUE 60
#define MIN_CB_VALUE 0


typedef enum{
    RED_LOW,
    RED_HIGH,
    YELLOW_LOW,
    YELLOW_HIGH,
    GREEN_,
}SENSOR_STATE;

typedef enum{
    RY_max,
    YG_max,
    YG_min,
    RY_min,
}threshold_limits;
   
//static bool critic_humidity; //si es true, es porque la humedad esta en anillo rojo
//static bool irrigation_on; //prende el riego 
//static bool irrigation_off;//apaga el riego


bool threshold_SetUp_tasks(uint8_t);
void threshold__default_SetUp();
uint16_t analog_conversion_to_cb(); //funcion que linealiza los valores de 0-1024 a 0-60. Debuelve un int entre 0 y 60
void analog_scale_to_cb_array(char*);
int humidity_state_function(void);


#endif /* _EXAMPLE_FILE_NAME_H */
    
/* *****************************************************************************
 End of File
 */
