#include "timer_library.h"

/*
universal timer init function that does all the checking for you - lots of conditionals ahead!

*/
void init_timer(short timer_num, timer_output_mode mode, uint16_t frequency_1, uint16_t frequency_2){
    switch (MCU)
    {
    case AVR:
        if (timer_num>MAX_AVR_TIMERS || timer_num < 0){
            // add in compile error? #error you cannot init this timer for AVR, it doens't exist 
        } else {
            // proceed with init, catch errors

            timer_state_struct timer_state = get_state_timer(UNIVERSAL_TIMER_STATE[timer_num]); 
            if (timer_state != NONE) {
                // begin by resetting the timer and then init, or #error timer already in use
            } else {
                init_timer(timer_num, mode, frequency_1, frequency_2)
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