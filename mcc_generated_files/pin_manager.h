/**
  PIN MANAGER Generated Driver File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for PIN MANAGER.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.145.0
        Device            :  PIC32MM0256GPM064
    The generated drivers are tested against the following:
        Compiler          :  XC32 v2.20
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

#ifndef _PIN_MANAGER_H
#define _PIN_MANAGER_H
/**
    Section: Includes
*/
#include <xc.h>
#include <stdbool.h>
/**
    Section: Device Pin Macros
*/
/**
  @Summary
    Sets the GPIO pin, RA0, high using LATA0.

  @Description
    Sets the GPIO pin, RA0, high using LATA0.

  @Preconditions
    The RA0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA0 high (1)
    PWR_KEY_SetHigh();
    </code>

*/
#define PWR_KEY_SetHigh()          ( LATASET = (1 << 0) )
/**
  @Summary
    Sets the GPIO pin, RA0, low using LATA0.

  @Description
    Sets the GPIO pin, RA0, low using LATA0.

  @Preconditions
    The RA0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA0 low (0)
    PWR_KEY_SetLow();
    </code>

*/
#define PWR_KEY_SetLow()           ( LATACLR = (1 << 0) )

/**
  @Summary
    Sets a value to the GPIO pin.

  @Description
    Sets or Resets the GPIO pin, RA0, low or high using LATA0.

  @Preconditions
    The RA0 must be set to an output.

  @Returns
    None.

  @Param
    bool value; : value to be set to the GPIO pin.

  @Example
    <code>
    // Set RA0 to low.
    PWR_KEY_SetValue(false);
    </code>

*/
inline static void PWR_KEY_SetValue(bool value)
{
  if(value)
  {
    PWR_KEY_SetHigh();
  }
  else
  {
    PWR_KEY_SetLow();
  }
}

/**
  @Summary
    Toggles the GPIO pin, RA0, using LATA0.

  @Description
    Toggles the GPIO pin, RA0, using LATA0.

  @Preconditions
    The RA0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA0
    PWR_KEY_Toggle();
    </code>

*/
#define PWR_KEY_Toggle()           ( LATAINV = (1 << 0) )
/**
  @Summary
    Reads the value of the GPIO pin, RA0.

  @Description
    Reads the value of the GPIO pin, RA0.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA0
    postValue = PWR_KEY_GetValue();
    </code>

*/
#define PWR_KEY_GetValue()         PORTAbits.RA0
/**
  @Summary
    Configures the GPIO pin, RA0, as an input.

  @Description
    Configures the GPIO pin, RA0, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA0 as an input
    PWR_KEY_SetDigitalInput();
    </code>

*/
#define PWR_KEY_SetDigitalInput()   ( TRISASET = (1 << 0) )
/**
  @Summary
    Configures the GPIO pin, RA0, as an output.

  @Description
    Configures the GPIO pin, RA0, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA0 as an output
    PWR_KEY_SetDigitalOutput();
    </code>

*/
#define PWR_KEY_SetDigitalOutput()   ( TRISACLR = (1 << 0) )
/**
  @Summary
    Sets the GPIO pin, RA1, high using LATA1.

  @Description
    Sets the GPIO pin, RA1, high using LATA1.

  @Preconditions
    The RA1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA1 high (1)
    RESET_SetHigh();
    </code>

*/
#define RESET_SetHigh()          ( LATASET = (1 << 1) )
/**
  @Summary
    Sets the GPIO pin, RA1, low using LATA1.

  @Description
    Sets the GPIO pin, RA1, low using LATA1.

  @Preconditions
    The RA1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA1 low (0)
    RESET_SetLow();
    </code>

*/
#define RESET_SetLow()           ( LATACLR = (1 << 1) )

/**
  @Summary
    Sets a value to the GPIO pin.

  @Description
    Sets or Resets the GPIO pin, RA1, low or high using LATA1.

  @Preconditions
    The RA1 must be set to an output.

  @Returns
    None.

  @Param
    bool value; : value to be set to the GPIO pin.

  @Example
    <code>
    // Set RA1 to low.
    RESET_SetValue(false);
    </code>

*/
inline static void RESET_SetValue(bool value)
{
  if(value)
  {
    RESET_SetHigh();
  }
  else
  {
    RESET_SetLow();
  }
}

/**
  @Summary
    Toggles the GPIO pin, RA1, using LATA1.

  @Description
    Toggles the GPIO pin, RA1, using LATA1.

  @Preconditions
    The RA1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA1
    RESET_Toggle();
    </code>

*/
#define RESET_Toggle()           ( LATAINV = (1 << 1) )
/**
  @Summary
    Reads the value of the GPIO pin, RA1.

  @Description
    Reads the value of the GPIO pin, RA1.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA1
    postValue = RESET_GetValue();
    </code>

*/
#define RESET_GetValue()         PORTAbits.RA1
/**
  @Summary
    Configures the GPIO pin, RA1, as an input.

  @Description
    Configures the GPIO pin, RA1, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA1 as an input
    RESET_SetDigitalInput();
    </code>

*/
#define RESET_SetDigitalInput()   ( TRISASET = (1 << 1) )
/**
  @Summary
    Configures the GPIO pin, RA1, as an output.

  @Description
    Configures the GPIO pin, RA1, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA1 as an output
    RESET_SetDigitalOutput();
    </code>

*/
#define RESET_SetDigitalOutput()   ( TRISACLR = (1 << 1) )
/**
  @Summary
    Sets the GPIO pin, RA10, high using LATA10.

  @Description
    Sets the GPIO pin, RA10, high using LATA10.

  @Preconditions
    The RA10 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA10 high (1)
    LED_CTRL_SetHigh();
    </code>

*/
#define LED_CTRL_SetHigh()          ( LATASET = (1 << 10) )
/**
  @Summary
    Sets the GPIO pin, RA10, low using LATA10.

  @Description
    Sets the GPIO pin, RA10, low using LATA10.

  @Preconditions
    The RA10 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA10 low (0)
    LED_CTRL_SetLow();
    </code>

*/
#define LED_CTRL_SetLow()           ( LATACLR = (1 << 10) )

/**
  @Summary
    Sets a value to the GPIO pin.

  @Description
    Sets or Resets the GPIO pin, RA10, low or high using LATA10.

  @Preconditions
    The RA10 must be set to an output.

  @Returns
    None.

  @Param
    bool value; : value to be set to the GPIO pin.

  @Example
    <code>
    // Set RA10 to low.
    LED_CTRL_SetValue(false);
    </code>

*/
inline static void LED_CTRL_SetValue(bool value)
{
  if(value)
  {
    LED_CTRL_SetHigh();
  }
  else
  {
    LED_CTRL_SetLow();
  }
}

/**
  @Summary
    Toggles the GPIO pin, RA10, using LATA10.

  @Description
    Toggles the GPIO pin, RA10, using LATA10.

  @Preconditions
    The RA10 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA10
    LED_CTRL_Toggle();
    </code>

*/
#define LED_CTRL_Toggle()           ( LATAINV = (1 << 10) )
/**
  @Summary
    Reads the value of the GPIO pin, RA10.

  @Description
    Reads the value of the GPIO pin, RA10.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA10
    postValue = LED_CTRL_GetValue();
    </code>

*/
#define LED_CTRL_GetValue()         PORTAbits.RA10
/**
  @Summary
    Configures the GPIO pin, RA10, as an input.

  @Description
    Configures the GPIO pin, RA10, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA10 as an input
    LED_CTRL_SetDigitalInput();
    </code>

*/
#define LED_CTRL_SetDigitalInput()   ( TRISASET = (1 << 10) )
/**
  @Summary
    Configures the GPIO pin, RA10, as an output.

  @Description
    Configures the GPIO pin, RA10, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA10 as an output
    LED_CTRL_SetDigitalOutput();
    </code>

*/
#define LED_CTRL_SetDigitalOutput()   ( TRISACLR = (1 << 10) )
/**
  @Summary
    Sets the GPIO pin, RA11, high using LATA11.

  @Description
    Sets the GPIO pin, RA11, high using LATA11.

  @Preconditions
    The RA11 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA11 high (1)
    STATUS_SetHigh();
    </code>

*/
#define STATUS_SetHigh()          ( LATASET = (1 << 11) )
/**
  @Summary
    Sets the GPIO pin, RA11, low using LATA11.

  @Description
    Sets the GPIO pin, RA11, low using LATA11.

  @Preconditions
    The RA11 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA11 low (0)
    STATUS_SetLow();
    </code>

*/
#define STATUS_SetLow()           ( LATACLR = (1 << 11) )

/**
  @Summary
    Sets a value to the GPIO pin.

  @Description
    Sets or Resets the GPIO pin, RA11, low or high using LATA11.

  @Preconditions
    The RA11 must be set to an output.

  @Returns
    None.

  @Param
    bool value; : value to be set to the GPIO pin.

  @Example
    <code>
    // Set RA11 to low.
    STATUS_SetValue(false);
    </code>

*/
inline static void STATUS_SetValue(bool value)
{
  if(value)
  {
    STATUS_SetHigh();
  }
  else
  {
    STATUS_SetLow();
  }
}

/**
  @Summary
    Toggles the GPIO pin, RA11, using LATA11.

  @Description
    Toggles the GPIO pin, RA11, using LATA11.

  @Preconditions
    The RA11 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA11
    STATUS_Toggle();
    </code>

*/
#define STATUS_Toggle()           ( LATAINV = (1 << 11) )
/**
  @Summary
    Reads the value of the GPIO pin, RA11.

  @Description
    Reads the value of the GPIO pin, RA11.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA11
    postValue = STATUS_GetValue();
    </code>

*/
#define STATUS_GetValue()         PORTAbits.RA11
/**
  @Summary
    Configures the GPIO pin, RA11, as an input.

  @Description
    Configures the GPIO pin, RA11, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA11 as an input
    STATUS_SetDigitalInput();
    </code>

*/
#define STATUS_SetDigitalInput()   ( TRISASET = (1 << 11) )
/**
  @Summary
    Configures the GPIO pin, RA11, as an output.

  @Description
    Configures the GPIO pin, RA11, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA11 as an output
    STATUS_SetDigitalOutput();
    </code>

*/
#define STATUS_SetDigitalOutput()   ( TRISACLR = (1 << 11) )
/**
  @Summary
    Sets the GPIO pin, RA13, high using LATA13.

  @Description
    Sets the GPIO pin, RA13, high using LATA13.

  @Preconditions
    The RA13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA13 high (1)
    BTN3_SetHigh();
    </code>

*/
#define BTN3_SetHigh()          ( LATASET = (1 << 13) )
/**
  @Summary
    Sets the GPIO pin, RA13, low using LATA13.

  @Description
    Sets the GPIO pin, RA13, low using LATA13.

  @Preconditions
    The RA13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA13 low (0)
    BTN3_SetLow();
    </code>

*/
#define BTN3_SetLow()           ( LATACLR = (1 << 13) )

/**
  @Summary
    Sets a value to the GPIO pin.

  @Description
    Sets or Resets the GPIO pin, RA13, low or high using LATA13.

  @Preconditions
    The RA13 must be set to an output.

  @Returns
    None.

  @Param
    bool value; : value to be set to the GPIO pin.

  @Example
    <code>
    // Set RA13 to low.
    BTN3_SetValue(false);
    </code>

*/
inline static void BTN3_SetValue(bool value)
{
  if(value)
  {
    BTN3_SetHigh();
  }
  else
  {
    BTN3_SetLow();
  }
}

/**
  @Summary
    Toggles the GPIO pin, RA13, using LATA13.

  @Description
    Toggles the GPIO pin, RA13, using LATA13.

  @Preconditions
    The RA13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA13
    BTN3_Toggle();
    </code>

*/
#define BTN3_Toggle()           ( LATAINV = (1 << 13) )
/**
  @Summary
    Reads the value of the GPIO pin, RA13.

  @Description
    Reads the value of the GPIO pin, RA13.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA13
    postValue = BTN3_GetValue();
    </code>

*/
#define BTN3_GetValue()         PORTAbits.RA13
/**
  @Summary
    Configures the GPIO pin, RA13, as an input.

  @Description
    Configures the GPIO pin, RA13, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA13 as an input
    BTN3_SetDigitalInput();
    </code>

*/
#define BTN3_SetDigitalInput()   ( TRISASET = (1 << 13) )
/**
  @Summary
    Configures the GPIO pin, RA13, as an output.

  @Description
    Configures the GPIO pin, RA13, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA13 as an output
    BTN3_SetDigitalOutput();
    </code>

*/
#define BTN3_SetDigitalOutput()   ( TRISACLR = (1 << 13) )
/**
  @Summary
    Sets the GPIO pin, RA7, high using LATA7.

  @Description
    Sets the GPIO pin, RA7, high using LATA7.

  @Preconditions
    The RA7 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA7 high (1)
    LEDA_SetHigh();
    </code>

*/
#define LEDA_SetHigh()          ( LATASET = (1 << 7) )
/**
  @Summary
    Sets the GPIO pin, RA7, low using LATA7.

  @Description
    Sets the GPIO pin, RA7, low using LATA7.

  @Preconditions
    The RA7 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA7 low (0)
    LEDA_SetLow();
    </code>

*/
#define LEDA_SetLow()           ( LATACLR = (1 << 7) )

/**
  @Summary
    Sets a value to the GPIO pin.

  @Description
    Sets or Resets the GPIO pin, RA7, low or high using LATA7.

  @Preconditions
    The RA7 must be set to an output.

  @Returns
    None.

  @Param
    bool value; : value to be set to the GPIO pin.

  @Example
    <code>
    // Set RA7 to low.
    LEDA_SetValue(false);
    </code>

*/
inline static void LEDA_SetValue(bool value)
{
  if(value)
  {
    LEDA_SetHigh();
  }
  else
  {
    LEDA_SetLow();
  }
}

/**
  @Summary
    Toggles the GPIO pin, RA7, using LATA7.

  @Description
    Toggles the GPIO pin, RA7, using LATA7.

  @Preconditions
    The RA7 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA7
    LEDA_Toggle();
    </code>

*/
#define LEDA_Toggle()           ( LATAINV = (1 << 7) )
/**
  @Summary
    Reads the value of the GPIO pin, RA7.

  @Description
    Reads the value of the GPIO pin, RA7.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA7
    postValue = LEDA_GetValue();
    </code>

*/
#define LEDA_GetValue()         PORTAbits.RA7
/**
  @Summary
    Configures the GPIO pin, RA7, as an input.

  @Description
    Configures the GPIO pin, RA7, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA7 as an input
    LEDA_SetDigitalInput();
    </code>

*/
#define LEDA_SetDigitalInput()   ( TRISASET = (1 << 7) )
/**
  @Summary
    Configures the GPIO pin, RA7, as an output.

  @Description
    Configures the GPIO pin, RA7, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA7 as an output
    LEDA_SetDigitalOutput();
    </code>

*/
#define LEDA_SetDigitalOutput()   ( TRISACLR = (1 << 7) )
/**
  @Summary
    Sets the GPIO pin, RB14, high using LATB14.

  @Description
    Sets the GPIO pin, RB14, high using LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB14 high (1)
    LEDB_SetHigh();
    </code>

*/
#define LEDB_SetHigh()          ( LATBSET = (1 << 14) )
/**
  @Summary
    Sets the GPIO pin, RB14, low using LATB14.

  @Description
    Sets the GPIO pin, RB14, low using LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB14 low (0)
    LEDB_SetLow();
    </code>

*/
#define LEDB_SetLow()           ( LATBCLR = (1 << 14) )

/**
  @Summary
    Sets a value to the GPIO pin.

  @Description
    Sets or Resets the GPIO pin, RB14, low or high using LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    bool value; : value to be set to the GPIO pin.

  @Example
    <code>
    // Set RB14 to low.
    LEDB_SetValue(false);
    </code>

*/
inline static void LEDB_SetValue(bool value)
{
  if(value)
  {
    LEDB_SetHigh();
  }
  else
  {
    LEDB_SetLow();
  }
}

/**
  @Summary
    Toggles the GPIO pin, RB14, using LATB14.

  @Description
    Toggles the GPIO pin, RB14, using LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB14
    LEDB_Toggle();
    </code>

*/
#define LEDB_Toggle()           ( LATBINV = (1 << 14) )
/**
  @Summary
    Reads the value of the GPIO pin, RB14.

  @Description
    Reads the value of the GPIO pin, RB14.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB14
    postValue = LEDB_GetValue();
    </code>

*/
#define LEDB_GetValue()         PORTBbits.RB14
/**
  @Summary
    Configures the GPIO pin, RB14, as an input.

  @Description
    Configures the GPIO pin, RB14, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB14 as an input
    LEDB_SetDigitalInput();
    </code>

*/
#define LEDB_SetDigitalInput()   ( TRISBSET = (1 << 14) )
/**
  @Summary
    Configures the GPIO pin, RB14, as an output.

  @Description
    Configures the GPIO pin, RB14, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB14 as an output
    LEDB_SetDigitalOutput();
    </code>

*/
#define LEDB_SetDigitalOutput()   ( TRISBCLR = (1 << 14) )
/**
  @Summary
    Sets the GPIO pin, RB15, high using LATB15.

  @Description
    Sets the GPIO pin, RB15, high using LATB15.

  @Preconditions
    The RB15 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB15 high (1)
    BTN2_SetHigh();
    </code>

*/
#define BTN2_SetHigh()          ( LATBSET = (1 << 15) )
/**
  @Summary
    Sets the GPIO pin, RB15, low using LATB15.

  @Description
    Sets the GPIO pin, RB15, low using LATB15.

  @Preconditions
    The RB15 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB15 low (0)
    BTN2_SetLow();
    </code>

*/
#define BTN2_SetLow()           ( LATBCLR = (1 << 15) )

/**
  @Summary
    Sets a value to the GPIO pin.

  @Description
    Sets or Resets the GPIO pin, RB15, low or high using LATB15.

  @Preconditions
    The RB15 must be set to an output.

  @Returns
    None.

  @Param
    bool value; : value to be set to the GPIO pin.

  @Example
    <code>
    // Set RB15 to low.
    BTN2_SetValue(false);
    </code>

*/
inline static void BTN2_SetValue(bool value)
{
  if(value)
  {
    BTN2_SetHigh();
  }
  else
  {
    BTN2_SetLow();
  }
}

/**
  @Summary
    Toggles the GPIO pin, RB15, using LATB15.

  @Description
    Toggles the GPIO pin, RB15, using LATB15.

  @Preconditions
    The RB15 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB15
    BTN2_Toggle();
    </code>

*/
#define BTN2_Toggle()           ( LATBINV = (1 << 15) )
/**
  @Summary
    Reads the value of the GPIO pin, RB15.

  @Description
    Reads the value of the GPIO pin, RB15.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB15
    postValue = BTN2_GetValue();
    </code>

*/
#define BTN2_GetValue()         PORTBbits.RB15
/**
  @Summary
    Configures the GPIO pin, RB15, as an input.

  @Description
    Configures the GPIO pin, RB15, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB15 as an input
    BTN2_SetDigitalInput();
    </code>

*/
#define BTN2_SetDigitalInput()   ( TRISBSET = (1 << 15) )
/**
  @Summary
    Configures the GPIO pin, RB15, as an output.

  @Description
    Configures the GPIO pin, RB15, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB15 as an output
    BTN2_SetDigitalOutput();
    </code>

*/
#define BTN2_SetDigitalOutput()   ( TRISBCLR = (1 << 15) )
/**
  @Summary
    Sets the GPIO pin, RC5, high using LATC5.

  @Description
    Sets the GPIO pin, RC5, high using LATC5.

  @Preconditions
    The RC5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC5 high (1)
    POT_SetHigh();
    </code>

*/
#define POT_SetHigh()          ( LATCSET = (1 << 5) )
/**
  @Summary
    Sets the GPIO pin, RC5, low using LATC5.

  @Description
    Sets the GPIO pin, RC5, low using LATC5.

  @Preconditions
    The RC5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC5 low (0)
    POT_SetLow();
    </code>

*/
#define POT_SetLow()           ( LATCCLR = (1 << 5) )

/**
  @Summary
    Sets a value to the GPIO pin.

  @Description
    Sets or Resets the GPIO pin, RC5, low or high using LATC5.

  @Preconditions
    The RC5 must be set to an output.

  @Returns
    None.

  @Param
    bool value; : value to be set to the GPIO pin.

  @Example
    <code>
    // Set RC5 to low.
    POT_SetValue(false);
    </code>

*/
inline static void POT_SetValue(bool value)
{
  if(value)
  {
    POT_SetHigh();
  }
  else
  {
    POT_SetLow();
  }
}

/**
  @Summary
    Toggles the GPIO pin, RC5, using LATC5.

  @Description
    Toggles the GPIO pin, RC5, using LATC5.

  @Preconditions
    The RC5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RC5
    POT_Toggle();
    </code>

*/
#define POT_Toggle()           ( LATCINV = (1 << 5) )
/**
  @Summary
    Reads the value of the GPIO pin, RC5.

  @Description
    Reads the value of the GPIO pin, RC5.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RC5
    postValue = POT_GetValue();
    </code>

*/
#define POT_GetValue()         PORTCbits.RC5
/**
  @Summary
    Configures the GPIO pin, RC5, as an input.

  @Description
    Configures the GPIO pin, RC5, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC5 as an input
    POT_SetDigitalInput();
    </code>

*/
#define POT_SetDigitalInput()   ( TRISCSET = (1 << 5) )
/**
  @Summary
    Configures the GPIO pin, RC5, as an output.

  @Description
    Configures the GPIO pin, RC5, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC5 as an output
    POT_SetDigitalOutput();
    </code>

*/
#define POT_SetDigitalOutput()   ( TRISCCLR = (1 << 5) )

/**
    Section: Function Prototypes
*/
/**
  @Summary
    Configures the pin settings of the PIC32MM0256GPM064
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void SYSTEM_Initialize(void)
    {
        // Other initializers are called from this function
        PIN_MANAGER_Initialize();
    }
    </code>

*/
void PIN_MANAGER_Initialize (void);

#endif
