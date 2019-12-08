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

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#include "telephone.h"
#include "GPS.h"


/*
bool Init_SIMCard(void){
    static sim_card_state_t state = NET;
    switch (state)
    {
        case NET:
        {
            UART1_WriteBuffer ("AT+CREG\r", strlen ("AT+CREG\r")); //consultar estado de la red
            if( UART1_ReceiveBufferIsEmpty() == false )
            {
                UART1_ReadBuffer ( RxBuffer , sizeof(RxBuffer)); 
                if (strstr(RxBuffer,"CREG: 0,1")!= NULL) // la red es GSM?
                {
                    memset (RxBuffer, 0, sizeof(RxBuffer));
                    state = PIN;
                }
            }
            break;
        } 
        case PIN:
        {
            UART1_WriteBuffer ("AT+CPIN?\r", strlen ("AT+CPIN?\r")); //tiene pin?
            if (Recibo_OK(1) == DONE)
            {
                state = COMPANY;
            }
            break;
        }
        case COMPANY:
        {
            UART1_WriteBuffer ("AT+COPS=1,2,\"74801\"\r", strlen ("AT+COPS=1,2,\"74801\"\r")); //Antel
            if ( Recibo_OK(1) == DONE)
            {
                state = NET;
                return true;
            }
            break;
        }
    }
    return false;
}

bool send_message (char *message[])
{
    static msg_stage_state_t stage = STG0;
    switch (stage)
    {
        case STG0:
        {
            UART1_WriteBuffer ("AT+CMGF=1\r", strlen ("AT+CMGF=1\r")); //seleccionar modo texto
            stage = STG1;
            break;
        }
        case STG1:
        {
            if( Recibo_OK(1) == DONE)
            {
                UART1_WriteBuffer ("AT+CMGS=\"098234059\"\r", strlen ("AT+CMGS=\"098234059\"\r"));
                stage = STG2;  
            }
            break;
            
        }
        case STG2:
        {
            if( Recibo_OK(1) == DONE)
            {
                UART1_Write(0x0D);
                stage = STG3;  
            }
            break;
        }
        case STG3:
        {
            if( Recibo_OK(1) == DONE)
            {
                UART1_WriteBuffer (*message, strlen (*message));
                stage = STG4;  
            }
            break;
        }
        case STG4:
        {
            if( Recibo_OK(1) == DONE)
            {
                UART1_Write(0x1A);
                stage = STG5;  
            }
            break;
        }
        case STG5:
        {
            if( Recibo_OK(1) == DONE)
            {
                stage = STG0;
                return true;
            }
        break; 
        }
    }
    return false;
}
*/
bool send_text_message(char *p_message){
    return false;
}



 
 