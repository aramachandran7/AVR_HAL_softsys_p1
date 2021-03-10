#ifndef AVR_ADC_H
#define AVR_ADC_H

#include <avr/io.h>
#include <AVR_drivers/interrupt.h>
#include <stdlib.h>
#include <inttypes.h>

/*  Defines  */

// ADC input register references - page 211
#define ADC0 0b00000
#define ADC1 0b00001
#define ADC2 0b00010
#define ADC3 0b00011
#define ADC4 0b00100
#define ADC5 0b00101
#define ADC6 0b00110
#define ADC7 0b00111
#define ADC8 0b01000
#define ADC9 0b01001
#define ADC10 0b01010



/*  Constants  */
#define FCLK int32_t 4000000
// #define ADC_CLK

/*  Function declarations  */
void init_ADC(); 

int16_t single_read_ADC(int8_t ADC_channel); 


#endif