/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.145.0
        Device            :  PIC32MM0256GPM064
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36b
        MPLAB 	          :  MPLAB X v5.25
*/

/*
    (c) 2019 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include <stdbool.h>
#include <xc.h> 
#include "utils/utils.h"
#include "Periferics/UI.h"
#include "Periferics/leds.h"
#include "LEDs_RGB/RGB_leds.h"
#include "Irrigation_system/UI_IS.h"
#include "Irrigation_system/system_control.h"
#include "Periferics/sensor.h"
#include "mcc_generated_files/mcc.h"


/*
                         Main application
 */

int main(void)
{   
    static uint8_t ini[16];
    bool ini_SIM808=false;
    bool ini_GPS=false;
    bool get_trama_f=false;
    bool hour_set_up=false;
    uint8_t trama[128];
    
    SYSTEM_Initialize();
    
    LEDA_SetLow();
    LEDB_SetLow();
    RGBs_SetDown();
    threshold__default_SetUp();  //define los umbrales por defecto, definida en sensor.c
    plant_init();
    
    PWR_KEY_SetDigitalInput();
    STATUS_SetDigitalInput();
    RESET_SetHigh();
    RESET_SetDigitalOutput();
    
    
    while(1){
        if(ini_SIM808==false){
            ini_SIM808=Initialize_SIM808();
        }
        else{
            if(ini_GPS==false){            
                ini_GPS=Initialize_GPS();
            }
            else{
                if(hour_set_up==false);
                hour_set_up=hour_SetUp();
            }
        }
        led_sequence();
        data_save();
        interface_IS();
        system_control_menu();
        UI_tasks();
    }
}

            
/*
 End of File
*/