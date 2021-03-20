#ifndef AVR_TIMER_H
#define AVR_TIMER_H

#include <avr/io.h>
#include <AVR_drivers/interrupt.h>
#include <stdlib.h>
#include <inttypes.h>
#include "ENV_CONSTANTS.h"


/*  Defines  */

// bits references within timer state
#define T0_A_BIT 0 
#define T0_B_BIT 1
#define T1_A_BIT 2 
#define T1_B_BIT 3 

#define MAX_AVR_TIMERS 3

// Modes --> move to supporting fast PWM and phase correct PWM modes later on

typedef enum TIMER_OUTPUT_MODE {CTC_MODE, NORMAL_MODE, NONE} TIMER_OUTPUT_MODE; 




// universal timer state struct 
typedef struct {
    TIMER_OUTPUT_MODE timer_mode; 
    uint8_t timer_flag; 
} TIMER_STATE_STRUCT; 


/*  Global Vars  */

// create array of struct pointers to hold universal timer state
TIMER_STATE_STRUCT * universal_timer_state[MAX_AVR_TIMERS]; // filled with void pointers by defualt 


/*  Constants  */

/*  Function declarations  */

// timer 0 inits
void init_timer_0_raw(int8_t mode, int8_t prescaler, int8_t interrupt_mask, int8_t period_1, int8_t period_2); 

// void init_timer_0_processed(); // what's this one? 

void init_timer_0(TIMER_OUTPUT_MODE mode, int16_t frequency_1, int16_t frequency_2); 

// timer 1 inits
void init_timer_1_raw(int8_t mode, int8_t prescaler, int8_t interrupt_mask, int8_t period_1, int8_t period_2); 

// void init_timer_1_processed(); 

void init_timer_1(TIMER_OUTPUT_MODE mode, int16_t frequency_1, int16_t frequency_2); 

// state management
static void set_state_timer(TIMER_STATE_STRUCT * timer_state, TIMER_OUTPUT_MODE new_mode, uint8_t new_flag); 

TIMER_STATE_STRUCT get_state_timer(TIMER_STATE_STRUCT * timer_state); 





#endif