/*
Demonstrates and tests Timer Driver only 

*/


/*
        stateless implementation
        TO TEST NEXT 
        - does ISR in driver code work with test_flag and TEST_BIT? 
        - does ISR work with cusotm state 
        - does init_timer() (library) work? 
        - test check_bit_and_clear_if_set()

        */

/*----- Includes -----*/

//#include <avr/io.h>
//#include <avr/interrupt.h>
#include "../lib/libs/timer/timer_library.h"
// #include "../lib/AVR_drivers/timer/AVR_timer_driver.h"
//#include <util/delay.h>


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

    // reset_timer(0); 
    init_timer(0, CTC_MODE, 17, 0); 
    // init_timer_driver(0, CTC_MODE, 17, 0); 
    // test_flag = 0x00; 
    //TCCR0A |= _BV(WGM01);    // Set up 8-bit timer in CTC mod
    //TCCR0B = 0x05;          // clkio/1024 prescaler
    //TIMSK0 |= _BV(OCIE0A); // interrupt? 
    //OCR0A = 0xE6;           //Makes timer run at ~17Hz


    DDRD |= _BV(DDD7); // toggle mode to output 
    PORTD |= _BV(PD7); // set to logic HIGH
    sei(); 
    
    while (1)
    {
        /* code */

       // _delay_ms(500); 

        
        //if (bit_is_set(test_flag, TEST_BIT)){
        //    PORTD ^= _BV(PD7); 
        //    test_flag &= ~_BV(TEST_BIT); 

        //}

	
        if (check_bit_and_clear_if_set(0, TIMER_FLAG_CMP_A)){
            PORTD ^= _BV(PD7); 
        }
    }
    
}
