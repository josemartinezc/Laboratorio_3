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
#include "mcc_generated_files/mcc.h"
#include "Platform/HardwareProfile.h"

#define ARRAY_SIZE 10
int exampleData;
char exampleArray[ARRAY_SIZE];
int boton2;
int boton3;


int main( void ){
    //declaro entradas y salidas
    LEDA_SetDigitalOutput();
    LEDB_SetDigitalOutput();
    BTN2_SetDigitalInput();
    BTN3_SetDigitalInput();       
   
    //botones con pull down
    BTN2_SetPullDown();
    BTN3_SetPullDown();
    
    //inicializo leds
    LEDA_SetLow();
    LEDB_SetLow();
    
    uint32_t ptimer = 0;
    while(1){
        //obtengo valores de hardware
        //boton2 = BTN2_getValue();
        //UT_delay();
        //boton3 = BTN3_getValue();
        //UT_delay();
        
        //if (boton2 == 1) 
            //LEDA_SetHigh();
          //LEDA_Toggle();
          
        
        //else
        //LEDA_SetLow();
       
        //if (boton3 == 1) 
            //LEDB_SetHigh();
            //LEDB_Toggle();
        //UT_delay();
    
        //else
        //LEDB_SetLow();
        
        switch (UT_delayDs(ptimer,400))
           case (true):
               
               LEDA_Toggle();
               
            UT_delayDs (ptimer, 400);
           case (false):
            LEDA_SetLow();
            UT_delayDs (p, 800);
        
/**
 End of File
*/