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
#include <string.h>

#include "data_register.h"
#include "system_control.h"
#include "../utils/utils.h"


//VARIABLES
static bool empty_buffer=true;
static uint8_t register_number=0;
historic_data data_buffer[REGISTER_CAPACITY];

bool get_empty_buffer_value(){
    return empty_buffer;
}

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
            if(save_register()==true){
                if(empty_buffer==true){
                    empty_buffer=false;
                }
                state_register_system=INITIALIZE;
            }
            break;
    }   
}



bool get_register(historic_data* p_data_register){
    static int8_t data_to_send=0;
    
    if(empty_buffer==true){
        return true;
    }
    else{ 
        memcpy(p_data_register, &data_buffer[data_to_send],sizeof(data_buffer[data_to_send]));
        data_to_send++;
        if(data_to_send<(register_number-1)){
            return false;
        }
        else{
            data_to_send=0;
            return true;
        }
    }
}

bool save_register(void) {
    static data_tasks_state saving_state=SAVE_DATA;
    uint8_t trama[128];
    TRI_STATUS trama_status;
    
    switch(saving_state){
        case SAVE_DATA:
            data_buffer[register_number].event_number=register_number;
            RTCC_TimeGet(&(data_buffer[register_number].hour_and_date)); 
            data_buffer[register_number].status=humidity_state_function();
            saving_state=WAIT_DATA;
        case WAIT_DATA:
            trama_status=get_trama(trama);
            //if(false_frame_maker(trama)==true){
            if(trama_status==DONE){
                GPS_getPosition(&data_buffer[register_number].position, trama);
                saving_state=END_DATA;
            }
            else if(trama_status==ERROR){
                data_buffer[register_number].position.latitude=0;
                data_buffer[register_number].position.longitude=0;
                saving_state=END_DATA;
            }
            return false;
            break;
        case END_DATA:
            if(register_number<REGISTER_CAPACITY){
                register_number++;
            }
            else{
                register_number=0;
            }
            saving_state=SAVE_DATA;
            return true;
            break;
    }
}       


