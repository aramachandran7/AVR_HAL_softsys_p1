#ifndef UART_LIB_H
#define UART_LIB_H

/*
platform agnostic code 
*/
#include "../../AVR_drivers/UART/AVR_UART_driver.h"
#include "../examples/ENV_CONSTANTS.h"
// need custom preprocessor includes

/*  Defines  */


/*  Constants  */

/*  Function declarations  */
void init_UART(UART_mode mode, UART_conf conf, uint32_t UART_baud, uint8_t UART_num); 

void recv_UART_to_buffer(uint8_t UART_num); 
void send_UART_from_buffer(uint8_t UART_num); 
void send_blocking_UART(); 
#endif