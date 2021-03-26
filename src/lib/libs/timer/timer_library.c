#include "timer_library.h"

/*
universal timer init function that does all the checking for you - lots of conditionals ahead!

*/
void init_timer(short timer_num, timer_output_mode mode, uint16_t frequency_1, uint16_t frequency_2){
    switch (MCU)
    {
    case ATMEGA16M1:
        if (timer_num>MAX_AVR_TIMERS || timer_num < 0){
            // add in compile error? Why is this legal? 
            
        } else {
            // proceed with init, catch errors
            timer_output_mode current_mode = get_mode_timer(UNIVERSAL_TIMER_STATE[timer_num]); 
            if (current_mode != NONE) {
                // begin by resetting the timer and then init, or #error timer already in use
                reset_timer(timer_num); 
                init_timer(timer_num, mode, frequency_1, frequency_2); 
            } else {
                init_timer(timer_num, mode, frequency_1, frequency_2); 
            }
        }

        break;
    case STM:
        break;
    case SOFTWARE:
        break;
    default:
        break;
    }
}