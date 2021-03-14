#ifndef AVR_UART_H
#define AVR_UART_H

#include <avr/io.h>
#include <AVR_drivers/interrupt.h>
#include <stdlib.h>
#include <inttypes.h>


/*  Defines  */

// Modes
// #define 


/*  Constants  */
#define FCLK int32_t 4000000


/*  Function declarations  */

void init_UART(int32_t UART_baud, short recieve, short transmit); 

void handle_UART_interrupt(); 



#endif