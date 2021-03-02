#include "AVR_timer_driver.h"

/* 
Page 88
Init timer0 to trigger desired output_mode at desired frequency
Code currently only supports CTC and normal mode
frequency_1 is primary, how do we set freuqency_2 as optional / default? 
*/
void init_timer_0(int output_mode, int16_t frequency_1, int16_t frequency_2){
    int prescaler; 

    switch(output_mode){
        case CTC_MODE: 
            TCCR0A = _BV(WGM01); // set timer0 into CTC mode
            break; 
        case NORMAL_MODE: 
            break; // no sets required 
        default: 
            // Don't do anything
            break;
    }
    
    // setup prescaler
    if (frequency<(1024/255)){
        printf("you're out of luck"); 
    }
    if (frequency< (FCLK/1024)){
        prescaler = 1024; 
        TCCR0B = 0x05;          // clkio/1024 prescaler
    } else if (frequency < FCLK/256){
        prescaler = 256; 
        TCCR0B = 0b100;          // clkio/256 prescaler
    } else if (frequency<FCLK/64){
        prescaler = 64; 
        TCCR0B = 0b011;          // clkio/64 prescaler
    } else if (frequency< FCLK/8){
        prescaler = 8; 
        TCCR0B = 0b001;          // clkio/8 prescaler
    } else {
        prescaler = 1; 
        TCCR0B = 0b000;          // no prescaler
    }

    TIMSK0 |= _BV(OCIE0A); 
    OCR0A = (uint8_t)FCLK/prescaler/frequency_1; 

    // setup for frequency_2 
    if (frequency_2){
        // setup interrupt
        TIMSK0 |= _BV(OCIE0B); 
        // setup value 
        OCR0A = (uint8_t)FCLK/prescaler/frequency_2; 
        // OCR0B = ; 
    }
}