#include "timer_library.h"

/*
universal timer init function that does all the checking for you - lots of conditionals ahead!

*/
void init_timer(short timer_num, TIMER_OUTPUT_MODE mode, int16_t frequency_1, int16_t frequency_2){
    switch (MCU)
    {
    case AVR:
        if (timer_num>MAX_AVR_TIMERS || timer_num < 0){
            // add in compile error? #error you cannot init this timer for AVR, it doens't exist 
        } else {
            // proceed with init, catch errors
            switch (timer_num)
            {
            case 0:
                // timer 0
                TIMER_STATE_STRUCT timer_0_state = get_state_timer(universal_timer_state[0]); 
                
                if (timer_0_state.timer_mode != NONE){
                    // begin by resetting the timer and then init, or #error timer already in use
                } else {
                    init_timer_0(mode, frequency_1, frequency_2)
                }
                break;
            case 1: 
                // timer 1

                break; 
            default:
                break;
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