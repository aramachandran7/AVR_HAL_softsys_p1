#include "AVR_timer_driver.h"

/* 
Page 88
Init timer0 to trigger desired output_mode at desired frequency
Code currently only supports CTC and normal mode
frequency_1 is primary, how do we set freuqency_2 as optional / default? 
*/



/*
Raw init fn where user passes in individual register values, from datasheet to init

*/
void init_timer_0_raw(int8_t mode, int8_t prescaler, int8_t period){
    // set output mode based on desired input 
    TCCR0A = _BV(mode); // TODO: mode is |=, precompiled TCCR0A
    // cleanest way to flip more than 1 optional bits to enable other modes?
    // what about flipping no bits at all (normal mode in this case?)


    // prescaler + frequency setting
    TCCR0B = prescaler; 
    TIMSK0 |= _BV(OCIE0A); // flips timer0 Compare Match A interrupt 
    OCR0A = period; 

    // what about compare match B interrupt - how do we give them the option? 


}



void init_timer_0_processed(){

} // what's this one? --> intermediate


// TODO: default no enums, keep it short for default 
void init_timer_0_enums(OUTPUT_MODE mode, int16_t frequency_1){
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



    if (frequency_1< (FCLK/1024)){ // these should be >> 3 right
        prescaler = 1024; 
        TCCR0B = 0x05;          // clkio/1024 prescaler
    } else if (frequency_1 < FCLK/256){
        prescaler = 256; 
        TCCR0B = 0b100;          // clkio/256 prescaler
    } else if (frequency_1<FCLK/64){
        prescaler = 64; 
        TCCR0B = 0b011;          // clkio/64 prescaler
    } else if (frequency_1< FCLK/8){
        prescaler = 8; 
        TCCR0B = 0b001;          // clkio/8 prescaler
    } else {
        prescaler = 1; 
        TCCR0B = 0b000;          // no prescaler
    }

    TIMSK0 |= _BV(OCIE0A); 
    OCR0A = (uint8_t)(FCLK/prescaler/frequency_1); 



}


// void init_timer_0(OUTPUT_MODE mode, int16_t frequency_1, int16_t frequency_2){
//     int prescaler; 

//     switch(output_mode){
//         case CTC_MODE: 
//             TCCR0A = _BV(WGM01); // set timer0 into CTC mode
//             break; 
//         case NORMAL_MODE: 
//             break; // no sets required 
//         default: 
//             // Don't do anything
//             break;
//     }
    
//     // setup prescaler
//     if (frequency_1<(1024/255)){
//         printf("you're out of luck"); // how to handle errors like this 
//     }
//     if (frequency_1< (FCLK/1024)){ // these should be >> 3 right
//         prescaler = 1024; 
//         TCCR0B = 0x05;          // clkio/1024 prescaler
//     } else if (frequency_1 < FCLK/256){
//         prescaler = 256; 
//         TCCR0B = 0b100;          // clkio/256 prescaler
//     } else if (frequency_1<FCLK/64){
//         prescaler = 64; 
//         TCCR0B = 0b011;          // clkio/64 prescaler
//     } else if (frequency_1< FCLK/8){
//         prescaler = 8; 
//         TCCR0B = 0b001;          // clkio/8 prescaler
//     } else {
//         prescaler = 1; 
//         TCCR0B = 0b000;          // no prescaler
//     }

//     TIMSK0 |= _BV(OCIE0A); 
//     OCR0A = (uint8_t)(FCLK/prescaler/frequency_1); 

//     // setup for frequency_2 
//     if (frequency_2){
//         // setup interrupt
//         TIMSK0 |= _BV(OCIE0B); 
//         // setup value 
//         OCR0A = (uint8_t)(FCLK/prescaler/frequency_2); 
//         // OCR0B = ; 
//     }
// }
