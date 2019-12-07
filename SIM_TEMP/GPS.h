/* ************************************************************************** */
/** GPS

  @Company
    Ucudal

  @File Name
    GPS.h

  @Summary
    Contains the structures and functions to obtain information from GPS frames obtained via SIM808 module
 */
/* ************************************************************************** */

#ifndef GPS_H
#define	GPS_H

/*******************************************************************************/    
/************************* INCLUDED FILES **************************************/    
/*******************************************************************************/    
#include <stdint.h>
#include <time.h>
#include <stdbool.h>

#include "../utils/utils.h"

/*******************************************************************************/    
/************************* CONSTANTS *******************************************/    
/*******************************************************************************/       
#define GPS_EARTH_RADIUS        6371

#define GPS_RMC_COMMA_LEN       1
#define GPS_RMC_RUN_LEN         1
#define GPS_RMC_FIX_LEN         1
#define GPS_RMC_UTC_LEN         18
#define GPS_RMC_LAT_LEN         10
#define GPS_RMC_LON_LEN         11

#define GPS_LAT_DIR_SOUTH       'S'
#define GPS_LAT_DIR_NORTH       'N'
#define GPS_LON_DIR_WEST        'W'
#define GPS_LAT_DIR_EAST        'E'
        
/*******************************************************************************/    
/************************* DATA TYPES ******************************************/    
/*******************************************************************************/       
typedef struct
{
	double latitude;                                                      
	double longitude;
}GPSPosition_t;

/*******************************************************************************/    
/************************* INTERFACE FUNCTIONS *********************************/    
/*******************************************************************************/     
 
/**
    @Function
        void GPS_getPosition( GPSPosition_t *p_pos, uint8_t *p_sentence )      
      
    @Summary
        Fills the position structure with POSITION information from the GPS frame received.
    
    @Parameters
        @Param GPSPosition_t *p_pos Pointer to structure where information will be stored 
        @Param uint8_t *p_sentence Pointer to string with GPS frame
    
    @Returns
        None
    
    @Remarks
        String must start after +CGNSINF: 
 **/ 
void GPS_getPosition( GPSPosition_t *p_pos, uint8_t *p_sentence );


/**
    @Function
        void GPS_getUTC(struct tm *p_newtime, uint8_t *p_sentence)    
      
    @Summary
        Fills the time structure with TIME information from the GPS frame received.
    
    @Parameters
        @Param GPSPosition_t *p_newTime Pointer to structure where information will be stored 
        @Param uint8_t *p_sentence Pointer to string with GPS frame
    
    @Returns
        None
    
    @Remarks
        String must start after +CGNSINF:
 **/
void GPS_getUTC(struct tm *p_newtime, uint8_t *p_sentence);

/**
    @Function
        double GPS_getGroundDistance( GPSPosition_t *a, GPSPosition_t *b ) 
      
    @Summary
        Calculates ground distance(in km) between to geographical points. (Uses spherical earth model)
    
    @Parameters
        @Param GPSPosition_t *a Pointer to the first point 
        @Param GPSPosition_t *b Pointer to the second point
    
    @Returns
        double Distance in km between 2 points passed as parameters
    
    @Remarks
        None
 **/
double GPS_getGroundDistance( GPSPosition_t *a, GPSPosition_t *b );

/*
 
  @Function
        void false_frame_maker(char *p_frame) 
      
    @Summary
        Genera una trama falsa
    
    @Parameters
        @Param char *p_frame // es un puntero a donde se quiere guardar la trama generada
    
*/

void get_google_link(GPSPosition_t position, uint8_t* p_gps_link ); 

void order_trama(uint8_t* p_full_trama);

bool false_frame_maker(char *p_frame);

TRI_STATUS Recibo_OK (uint8_t wait_delay);

bool get_trama (char*);

bool check_envio (void);

bool send_message (char*);

#endif	/* GPS_H */



