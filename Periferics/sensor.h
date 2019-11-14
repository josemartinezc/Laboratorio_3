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
   
void sensor();
void threshold_SetUp();
void analog_scale_to_cb(); //funcion que linealiza los valores de 0-1024 a 0-60. Debuelve un int entre 0 y 60
    
#endif /* _EXAMPLE_FILE_NAME_H */
    
/* *****************************************************************************
 End of File
 */
