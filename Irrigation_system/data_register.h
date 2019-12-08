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

#ifndef _DATA_REGISTER_H    /* Guard against multiple inclusion */
#define _DATA_REGISTER_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <time.h>
#include <stdint.h>

#include "../mcc_generated_files/rtcc.h"
#include "../periferics/sensor.h"
#include "../SIM_TEMP/GPS.h"

#define REGISTER_CAPACITY 30
#define PERIOD_DATA_SAVING_HOURS 0 //in hours
#define PERIOD_DATA_SAVING_MIN 1 //in minutes


typedef struct{
    bcdTime_t hour_and_date;
    SENSOR_STATE status;
    GPSPosition_t position;
    uint8_t event_number;
} historic_data;

typedef enum{
    INITIALIZE,
    WAIT_,
    SAVE,        
}REGISTER_SYSTEM_STATE;

bool get_empty_buffer_value();
void data_save(void);
bool save_register(void);
uint8_t get_register_number();
bool get_register(historic_data*);

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
