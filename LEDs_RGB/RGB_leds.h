/* ************************************************************************** */
/** WS2812

  @Company
    BQN

  @File Name
    WS2812.h

  @Summary
    Declaraciones para el manejo de los leds WS2812.

  @Description
    Contiene la estructura que almacena los datos RGB de un led y la declaración
    de la función de escritura en el led.
 */
/* ************************************************************************** */

#ifndef _WS2812_H    /* Guard against multiple inclusion */
#define _WS2812_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <stdint.h>

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************

/** ws2812_t

  @Summary
    Estructura que contiene el valor para un led WS2812

  @Description
    Estructura que contiene el valor para un led WS2812
    <p>
    Contiene 3 bytes con el valor RGB de cada led.
    <p>

  @Remarks
    None
 */
typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
}ws2812_t;

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */
#define CANTIDAD_LEDS 8

static ws2812_t tira_leds[CANTIDAD_LEDS];

extern const ws2812_t WHITE;
extern const ws2812_t RED;
extern const ws2812_t YELLOW;
extern const ws2812_t GREEN;
extern const ws2812_t BLUE;
extern const ws2812_t BLACK;

// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/**
  @Function
    void WS2812_send( ws2812_t* p_led );

  @Summary
    Transmite un valor rgb a un led.

  @Description
    Transmite un valor rgb a un led.

  @Precondition
    None

  @Parameters
    @param p_led Puntero a la estrucutra que contiene los valores para configurar un led individual.


  @Returns
    void

  @Remarks
    None.
 */
void WS2812_send( ws2812_t *p_leds, uint8_t p_length );
void RGBs_SetDown(void);

#endif /* _WS2812_H */

/* *****************************************************************************
 End of File
 */
