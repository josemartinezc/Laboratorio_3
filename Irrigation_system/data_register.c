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
static uint8_t register_number=0;
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
            state_register_system=WAIT_;
            break;

        case WAIT_:
            if(UT_delayDs(&timer, 600)==true){
                i++;
                if(i>=PERIOD_DATA_SAVING_MIN){
                    j++;
                    if (j>=PERIOD_DATA_SAVING_HOURS){
                        state_register_system=SAVE;
                    }
                    else{
                        state_register_system=WAIT_;
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

//me quede acaaaaaaaaaaaaaaaaaaa


bool get_register(char* p_data_register){
    static SENDING_DATA_STATE data_left=INIT_DATA;
    static uint8_t pending_data;
    
    switch(data_left){
        case INIT_DATA:
            if(register_number==0){
                p_data_register="no hay datos a enviar";
                return true;
            }
            else{
                pending_data=register_number--;
                data_left=DATA_PENDING;
            }
            break;
        case DATA_PENDING:
            
            break;
        case EMPTY:
            break;
    }
}

void save_register(void) {
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



