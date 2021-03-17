#ifndef AVR_TIMER_H
#define AVR_TIMER_H

#include <avr/io.h>
#include <AVR_drivers/interrupt.h>
#include <stdlib.h>
#include <inttypes.h>


/*  Defines  */

// Modes

typedef enum OUTPUT_MODE {CTC_MODE, NORMAL_MODE, NONE} OUTPUT_MODE; 

typedef struct {
    short timer0_in_use;
    OUTPUT_MODE timer0_mode; 
    short timer1_in_use;  
    OUTPUT_MODE timer1_mode; 
} AVR_TIMER_STATE_STRUCT; 


/*  Global Vars  */

extern AVR_TIMER_STATE_STRUCT AVR_TIMER_STATE = {
    0, NONE, 0, NONE
} // set by driver, checked by library

/*  Constants  */

/*  Function declarations  */

void init_timer_0_raw(int8_t mode, int8_t prescaler, int8_t period);

void init_timer_0_processed(); // what's this one? 

void init_timer_0_enums(OUTPUT_MODE mode, int16_t frequency_1); 



void init_timer_1_raw(); 

void init_timer_1_processed(); 

void init_timer_1_enums(); 




#endif