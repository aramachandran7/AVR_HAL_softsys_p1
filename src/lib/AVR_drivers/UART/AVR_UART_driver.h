#ifndef AVR_UART_H
#define AVR_UART_H

/*
Baked in assumptions - 
    LIN is not supported by this library 
    if we were using LIN, this would be a shared UART + LIN library 
*/



#include <avr/io.h>
#include <AVR_drivers/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <inttypes.h>
#include "../../ENV_CONSTANTS.h"


/*  Defines  */

#define UART_RX_RCVD 0 
#define UART_TX_SENT 1 

#define UART_RX_MODE 2
#define UART_TX_MODE 3 // how to check mode 

#define MAX_AVR_UARTS 1


// Modes
typedef enum UART_mode {RX_ONLY, TX_ONLY, FULL_DUPLEX, NONE} UART_mode; 

typedef enum UART_conf {STANDARD_8N1, STANDARD_8E1, STANDARD_8O1, LISTEN_8N1} UART_conf; 


// UART state struct  
typedef struct {
    UART_mode mode; 
    UART_conf conf; 
    volatile uint8_t UART_flag; 
    volatile uint8_t data_buffer[UART_BUFFER_SIZE]; 
    volatile uint8_t data_byte_rcvd;
    volatile uint8_t data_byte_send; 
    // volatile uint8_t queue[UART_BUFFER_SIZE]; 
} UART_state_struct; 

/*  Global Vars  */
UART_state_struct * UNIVERSAL_UART_STATE[MAX_AVR_UARTS]; 

/*  Constants  */


/*  Function declarations  */


// UART inits
void init_UART_raw(int32_t UART_baud, short recieve, short transmit); 

void init_UART(UART_mode mode); 

// allow for setting and getting of UART byte 
int8_t get_byte(); // clear after? 

void set_byte(int8_t data); 

void handle_UART_interrupt(); 



#endif