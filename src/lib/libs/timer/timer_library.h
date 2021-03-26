#ifndef TIMER_LIB_H
#define TIMER_LIB_H

#include "../../ENV_CONSTANTS.h"
#include "../../AVR_drivers/timer/AVR_timer_driver.h"
// need custom preprocessor includes depending on the MCU var

/*  Defines  */


/*  Constants  */

/*  Function declarations  */
void init_timer(short timer_num, timer_output_mode mode, uint16_t frequency_1, uint16_t frequency_2); 

#endif