/*
Demonstrates and tests Timer Driver only 

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
volatile uint8_t test_flag; 
#define TEST_BIT 0
/*----- Interrupt(s) -----*/
/*----- Functions -----*/

/*----- MAIN -----*/


ISR(TIMER0_COMPA_vect){
    // flip state bit 
    test_flag |= _BV(TEST_BIT);
    //PORTD ^= _BV(PD7); 
}

int main(void){
    /*----- INITS -----*/
    // init_timer(0, CTC_MODE, freq_timer_1, 0); 

    // reset_timer(0); 
    init_timer_driver(0, CTC_MODE, 17, 0); 
    test_flag = 0x00; 
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

        /*
        stateless implementation 
        - does ISR work? 
        - does init_timer_driver() work? 
        - to try:  
            shift down to timer raw
            comment out ISR() and implement in this file
            write everything in this file, transition slowly to driver tools

        */
        if (bit_is_set(test_flag, TEST_BIT)){
            PORTD ^= _BV(PD7); 
            test_flag &= ~_BV(TEST_BIT); 

        }


        // if (check_bit_and_clear_if_set(0, TIMER_FLAG_CMP_A)){
        //     PORTD ^= _BV(PD7); 
        // }
    }
    
}
