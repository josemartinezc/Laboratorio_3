/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "data_register.h"
#include "../utils/utils.h"


//VARIABLES
historic_data data_buffer[REGISTER_CAPACITY];


void data_save(void){
    static REGISTER_SYSTEM_STATE state_register_system=INITIALIZE;
    static uint8_t i, j;         
    static ut_tmrDelay_t timer;
    
    switch(state_register_system){
        case INITIALIZE:
            i=0;
            j=0;
            timer.state=0;
            state_register_system=WAIT;
            break;

        case WAIT:
            if(UT_delayDs(&timer, 600)==true){
                i++;
                if(i>=PERIOD_DATA_SAVING_MIN){
                    j++;
                    if (j>=PERIOD_DATA_SAVING_HOURS){
                        state_register_system=SAVE;
                    }
                    else{
                        state_register_system=WAIT;
                    }
                }
                else{
                    timer.state=0;
                }
            }
            break;
            
        case SAVE:
            save_register();
            state_register_system=INITIALIZE;
            break;
    }
    
}

void save_register(void) {
    static register_number=0;
    uint8_t trama[110];
    
    RTCC_TimeGet(&data_buffer[register_number].hour_and_date); 
    data_buffer[register_number].status=humidity_state_function();
    if(false_frame_maker(trama)==true){
        GPS_getPosition(&data_buffer[register_number].position, trama);
    }
    else{
        data_buffer[register_number].position.latitude=0;
        data_buffer[register_number].position.longitude=0;
    }
    if(register_number<REGISTER_CAPACITY){
        register_number++;
    }
    else{
        register_number=0;
    }
}



