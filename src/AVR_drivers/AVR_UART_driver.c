#include "AVR_UART_driver.h"



/*
initializes UART
*/

void init_UART(int32_t UART_baud, short recieve, short transmit){
    
    // enable LIN and UART, then enable UART, respectively
    LINCR |= _BV(LENA) |= _BV(LCMD2);  

    if (recieve){
        // enable RX
        LINCR |= _BV(LCMD1); 
        // enable RX interrupt
        LINENIR |= _BV(LENRXOK); // how to use this interrupt now? whats the vector name / where to find?  

    }

    if (transmit){
        // enable TX 
        LINCR |= _BV(LMCD0); 
        // enable TX interrupt
        LINENIR |= _BV(LENTXOK); // how to use this interrupt now? whats the vector name / where to find?  

    }

    // setup baudrate pg 183
    // LDIV[11..0] = (FCLK / LBT[5..0] * UART_baud)-1; // setup baud rate, pg 183 - is this access of bits within register ok? 
    LINBRR = 0x0C; 

    
}


// ISR handle
ISR(LIN_TC_VECT){ // should this be USART_RX_VECT ? 
    handle_UART_interrupt(); 
}