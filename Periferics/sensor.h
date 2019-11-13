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

#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */


#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "../mcc_generated_files/rtcc.h"

#define MAX_CB_VALUE 60
#define MIN_CB_VALUE 0


typedef enum{
        RED_LOW,
        RED_HIGH,
        YELLOW_LOW,
        YELLOW_HIGH,
        GREEN,
    }SENSOR_STATE;
    
    //umbrales
    static uint8_t red_yellow_max;
    static uint8_t yellow_green_max;
    static uint8_t yellow_green_min;
    static uint8_t red_yellow_min;
    
    static uint8_t humidity_value;
    static SENSOR_STATE humidity_state; //indica el anillo en el que esta lo sensado en el potenciometro
    static bool critic_humidity; //si es true, es porque la humedad esta en anillo rojo
    static bool irrigation_on; //prende el riego 
    static bool irrigation_off;//apaga el riego
    
    
    void sensor();
    void threshold_SetUp();
    
/* *****************************************************************************
 End of File
 */
