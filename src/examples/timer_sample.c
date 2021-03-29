/*
Demonstrates Timer veritcal 

*/




/*----- Includes -----*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "../lib/libs/timer/timer_library.h"
// #include "can_api.h"
// #include "spi.h"

// CONFIG
mcu_type MCU = ATMEGA16M1; 


/*----- Macro Definitions -----*/
/*----- Global Variables -----*/
uint16_t freq_timer_1 = 100; 
uint16_t freq_timer_2 = 1000; 

/*----- Interrupt(s) -----*/
/*----- Functions -----*/

/*----- MAIN -----*/

int main(void){
    /*----- INITS -----*/
    init_timer(0, CTC_MODE, freq_timer_1, 0); 
    
    while (1)
    {
        /* code */
        if (check_bit_and_flip_if_1(0, TIMER_FLAG_CMP_A)){
            // set timer 1
            init_timer(1, CTC_MODE, freq_timer_2, 0); 
            if (freq_timer_2==100){
                freq_timer_2 = 1000; 
            } else {
                freq_timer_2 -= 100; 
            }
        // if (check_bit_and_flip_if_1(0, TIMER_FLAG_CMP_A)){
        //     // flash LED
        // }
        }
    }
    
}