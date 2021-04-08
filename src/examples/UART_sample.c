/*
Demonstrates and tests UART veritcal 

*/




/*----- Includes -----*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "../lib/libs/timer/timer_library.h"
#include "../lib/libs/UART/UART_library.h"
// #include "can_api.h"
// #include "spi.h"

/*----- CONFIG -----*/
mcu_type MCU = ATMEGA16M1; 


/*----- Macro Definitions -----*/
/*----- Global Variables -----*/
uint16_t freq_timer_1 = 20; 

/*----- Interrupt(s) -----*/
/*----- Functions -----*/

/*----- MAIN -----*/

int main(void){
    /*----- INITS -----*/
    init_timer(0, CTC_MODE, freq_timer_1, 0); 
    init_UART(FULL_DUPLEX, STANDARD_8N1, 9600, 0); 

    uint8_t increment_var = 0; 

    while (1)
    {
        /* code */
        send_UART_from_first_byte(0); 
        if (check_bit_and_clear_if_set(0, TIMER_FLAG_CMP_A)){
            increment_var = (increment_var + 1) % 255; 
            data_RX_buffer[0] = increment_var; 
        }

    }
    
}