#ifndef ENV_CONSTANTS_H
#define ENV_CONSTANTS_H

/*
to be imported by the every example file and used 

*/

/*  Defines  */
#define FCLK (uint32_t) 4000000
#define UART_BUFFER_SIZE (uint16_t) 256

typedef enum mcu_type { STM, ATMEGA16M1, SOFTWARE } mcu_type; 

/*  THESE MUST BE SET IN MAIN FIRMWARE FILE  */

extern mcu_type MCU; 


#endif