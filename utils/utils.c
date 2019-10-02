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

#include "utils.h"
#include "../mcc_generated_files/tmr2.h"

void UT_delayDs ( int i ){
    int t;
    t = TMR2_SoftwareCounterGet ();
    while ( t < t + i);
    }

//uint8_t *var1, var2;
//uint8_t *var1, *var2; 
    
//bool UT_delayDs(ut_tmrDelay_t* p_timer, uint32_t p_ds)
//{
// 
//}



/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
int ExampleInterfaceFunction(int param1, int param2) {
    return 0;
}


/* *****************************************************************************
 End of File
 */
