/*
Demonstrates and tests Timer Driver only 

*/




/*----- Includes -----*/


#include "../lib/libs/timer/timer_library.h"
// #include "../lib/AVR_drivers/timer/AVR_timer_driver.h"
// #include <util/delay.h>


/*----- CONFIG -----*/
mcu_type MCU = ATMEGA16M1; 


/*----- Macro Definitions -----*/
/*----- Global Variables -----*/
// uint16_t freq_timer_1 = 30; 
// uint16_t freq_timer_2 = 1000; 

/*----- Interrupt(s) -----*/
/*----- Functions -----*/

/*----- MAIN -----*/

int main(void){
    /*----- INITS -----*/
    // init_timer(0, CTC_MODE, freq_timer_1, 0); 

    // reset_timer(0); 
    // init_timer_driver(0, CTC_MODE, 10, 0)


    DDRD |= _BV(DDD7); // toggle mode to output 
    PORTD |= _BV(PD7); // set to logic HIGH
    
    
    while (1)
    {
        /* code */

        PORTD ^= _BV(PD7); 
        _delay_ms(500); 


        // if (check_bit_and_clear_if_set(0, TIMER_FLAG_CMP_A)){
        //     PORTD ^= _BV(PD7); 
        // }
    }
    
}