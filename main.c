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
#include "User Interface/UI.h"

#include "mcc_generated_files/mcc.h"


/*
                         Main application
 */
int main(void)
{   
    ut_tmrDelay_t timer;
    ut_tmrDelay_t *ptimer;
    uint8_t i=0; 
    ptimer = &timer;
    ptimer->state = 0;

    button2On=false;
    button3On=false;
    
    SYSTEM_Initialize();
    
    LEDA_SetLow();
    LEDB_SetLow();


    
    while (1)
    { 
        /*if(button3On==true){
            LEDA_SetHigh ();
            UT_delayDs (20);  
            LEDA_SetLow();
            button3On = false; 
        }*/
        
         if (UT_delayDs(ptimer,40) == true) {
            switch (i){
                case (0):
                    LEDA_SetHigh();
                    i++;
                    break;
                case (1):
                    LEDA_SetLow();
                    i++;
                    break;
                case (2):
                    i = 0;
                    break;
            }
        }
         if ((USBGetDeviceState() >= CONFIGURED_STATE)&&( USBIsDeviceSuspended()== false)){
             UI_menu();
         }
    }
}
/**
 End of File
*/