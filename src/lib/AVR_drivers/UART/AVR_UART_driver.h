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


#define MAX_AVR_UARTS 1


// Modes
typedef enum UART_mode {RX_ONLY, TX_ONLY, FULL_DUPLEX, NONE} UART_mode; 

typedef enum UART_conf {STANDARD_8N1, STANDARD_8E1, STANDARD_8O1, LISTEN_8N1} UART_conf; 


// UART state struct  
typedef struct {
    UART_mode mode; 
    UART_conf conf; 
    volatile uint8_t flag; 
    // volatile uint8_t queue[UART_BUFFER_SIZE]; 
} UART_state_struct; 

/*  Global Vars  */
UART_state_struct * UNIVERSAL_UART_STATE[MAX_AVR_UARTS]; 


// NOTES: ARCHITECTURALLY IT MAKES SENSE TO ENCAPSULATE THESE IN THE STATE STRUCT
// HOWEVER THE STATE ACCESS API IS KINDA CLUNKY, IT MAKES THE MOST SENSE TO DIRECTLY 
// INTERACT WITH THESE VARS AS OPPOSED TO THROUGH AN ARR OF PTRS BASED HEAVY API 

volatile uint8_t data_TX_buffer[UART_BUFFER_SIZE]; 
volatile uint8_t data_RX_buffer[UART_BUFFER_SIZE]; 
volatile uint8_t TX_pointer;
volatile uint8_t RX_pointer; 
/*  Constants  */


/*  Function declarations  */


// UART inits
void init_UART_raw(uint8_t control_mode, uint8_t interrupt_setting, uint8_t baud_register); 

void init_UART_driver(UART_mode mode, UART_conf conf, uint32_t UART_baud); 

uint8_t get_byte_UART_driver(); 
void set_byte_UART_driver(uint8_t data); 

void wait_till_UART_ready_to_send(); 

uint8_t check_bit_and_clear_if_set_UART(uint8_t bit_to_check); 


#endif