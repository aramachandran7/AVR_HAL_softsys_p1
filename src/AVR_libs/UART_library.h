#ifndef UART_LIB_H
#define UART_LIB_H

/*
platform agnostic code 
*/

#include "../examples/ENV_CONSTANTS.h"
// need custom preprocessor includes

/*  Defines  */
extern int8_t UART_TRANSMIT_DATA_BUFFER[256]; // define a buffer that will act  


// need to grab and check state from appropriate chip driver



/*  Constants  */

/*  Function declarations  */
void init_UART(); // init UART
void send_UART(); // send singular byte of data 
void serialize_UART_send(); 
#endif