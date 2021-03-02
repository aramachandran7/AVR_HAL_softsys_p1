#ifndef AVR_TIMER_H
#define AVR_TIMER_H

#include <avr/io.h>
#include <AVR_drivers/interrupt.h>
#include <stdlib.h>
#include <inttypes.h>


/*  Defines  */
// how do they define different modes of timer operation 

#define CTC_MODE 1 
#define NORMAL_MODE 0 

#define FCLK int32_t 4000000


/*  Function declarations  */

void init_timer_0(); 
void init_timer_1(); 





#endif