/*
Demonstrates and tests Timer veritcal 

*/




/*----- Includes -----*/

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <util/delay.h>

#include "../lib/libs/timer/timer_library.h"
// #include "can_api.h"
// #include "spi.h"

/*----- CONFIG -----*/
mcu_type MCU = ATMEGA16M1; 


/*----- Macro Definitions -----*/
/*----- Global Variables -----*/
uint16_t freq_timer_0 = 17; 
uint16_t freq_timer_1 = 17; 
uint8_t counter = 0;
uint8_t flash_counter = 0; 
/*----- Interrupt(s) -----*/
/*----- Functions -----*/

/*----- MAIN -----*/

int main(void){
    /*----- INITS -----*/
    init_timer(0, CTC_MODE, freq_timer_0, 0); 
    init_timer(1, CTC_MODE, freq_timer_1, 0); 


    DDRD |= _BV(DDD7); // toggle mode to output 
    PORTD |= _BV(PD7); // set to logic HIGH

    DDRB |= _BV(DDB0); 
    PORTB |= _BV(PB0); 
    sei();

    while (1)
    {
        /* code */
        if (check_bit_and_clear_if_set(0, TIMER_FLAG_CMP_A)){
            PORTB ^= _BV(PB0);  
        }
        if (check_bit_and_clear_if_set(1, TIMER_FLAG_CMP_A)){
            // flash LED
            flash_counter = (flash_counter + 1) %10;  
        }
        if (flash_counter == 0) {
            PORTD ^= _BV(PD7); 
            // increment here 
        }
    }   
}
