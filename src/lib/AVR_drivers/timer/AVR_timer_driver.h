#ifndef AVR_TIMER_H
#define AVR_TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <inttypes.h>
#include "../../ENV_CONSTANTS.h"


/*  Defines  */

// bits references within timer state
#define TIMER_FLAG_CMP_A 0 
#define TIMER_FLAG_CMP_B 1

#define MAX_AVR_TIMERS 2

// Modes --> move to supporting fast PWM and phase correct PWM modes later on

typedef enum timer_output_mode {CTC_MODE, NORMAL_MODE, NO_TIMER} timer_output_mode; 


// universal timer state struct 
typedef struct {
    timer_output_mode timer_mode; 
    volatile uint8_t timer_flag; 
} timer_state_struct; 


/*  Global Vars  */

// create array of struct pointers to hold universal timer state
timer_state_struct * UNIVERSAL_TIMER_STATE[MAX_AVR_TIMERS]; // filled with void pointers by defualt 


/*  Constants  */

/*  Function declarations  */

// timer reset
void reset_timer(short timer_num); 

// timer inits
void init_timer_raw(short timer_num, uint8_t mode, uint8_t prescaler, uint8_t interrupt_mask, uint16_t period_1, uint16_t period_2); 

void init_timer_driver(short timer_num, timer_output_mode mode, uint16_t frequency_1, uint16_t frequency_2); 


// state management
// by not exposing set_state_timer() we prevent libraries / higher level code from changing state
// static void set_state_timer(TIMER_STATE_STRUCT * timer_state, TIMER_OUTPUT_MODE new_mode, uint8_t new_flag); 
// static void set_state_timer(timer_state_struct * timer_state, timer_output_mode new_mode, uint8_t new_flag); 

// timer_state_struct get_state_timer(timer_state_struct * timer_state); 

// uint8_t check_bit_and_flip_if_1(timer_state_struct * timer_state, uint8_t bit_to_check); 
uint8_t check_bit_and_clear_if_set(short timer_num, uint8_t bit_to_check); 

timer_output_mode get_mode_timer(timer_state_struct * timer_state); 




#endif
