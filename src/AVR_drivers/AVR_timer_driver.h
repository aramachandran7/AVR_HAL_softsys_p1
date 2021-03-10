#ifndef AVR_TIMER_H
#define AVR_TIMER_H

#include <avr/io.h>
#include <AVR_drivers/interrupt.h>
#include <stdlib.h>
#include <inttypes.h>


/*  Defines  */

// Modes
// TODO: how shd we define different modes of timer operation 
#define CTC_MODE (short) 1 
#define NORMAL_MODE (short) 0 


/*  Constants  */
#define FCLK int32_t 4000000


/*  Function declarations  */

void init_timer_0(short output_mode, int16_t frequency_1, int16_t frequency_2); 

void init_timer_1(); 





#endif