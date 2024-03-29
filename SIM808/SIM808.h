/* ************************************************************************** */
/* SIM808

  @Company
    Ucudal

  @File Name
    SIM808.h

  @Summary
    Macros for SIM808.c

 */
/* ************************************************************************** */

#ifndef SIM808_H    
#define SIM808_H

/*******************************************************************************/    
/************************* INCLUDED FILES **************************************/    
/*******************************************************************************/    
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "../utils/utils.h"

/*******************************************************************************/    
/************************* CONSTANTS *******************************************/    
/*******************************************************************************/


/*******************************************************************************/    
/************************* DATA TYPES ******************************************/    
/*******************************************************************************/       

typedef enum{
   STG0,
   STG1,
   STG2,
   STG3,
   STG4,
   STG5,
   STG6,
   STG7,
}stage_state_t;

typedef enum {
    INITi,
    WAITi,
} st_inicializacion_SIM808;

/*******************************************************************************/    
/******************************* FUNCTIONS ****************************************/    
/*******************************************************************************/ 
TRI_STATUS wait_usart_answer(uint8_t *p_answer, uint8_t delay); 
bool espero_OK ();
 void init_punteros();
 void Leer_Buffer_debug ();

 
 
#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */

