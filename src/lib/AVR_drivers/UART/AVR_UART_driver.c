#include "AVR_UART_driver.h"



/*
initializes UART
*/

void init_UART_raw(uint8_t control_mode, uint8_t interrupt_setting, int32_t UART_baud){
    
    // enable LIN and UART, then enable UART, respectively
    LINCR |= control_mode; 
    LINENIR |= interrupt_setting; 

    // setup baudrate pg 183
    // LDIV[11..0] = (FCLK / LBT[5..0] * UART_baud)-1; // setup baud rate, pg 183 - is this access of bits within register ok? 
    LINBRR = 0x0C; 

    
}

void init_UART(UART_mode mode, UART_conf conf){
    uint8_t control_mode = 0x00; // mode register, passed into LINCR
    uint8_t interrupt_setting = 0x00; // for linenir



    switch (mode)
    {
    case FULL_DUPLEX:
        /* code */
        control_mode |= _BV(LENA) |= _BV(LCMD2) |= LMCD0 |= LMCD1;  
        interrupt_setting |= _BV(LENTXOK); 
        interrupt_setting |= _BV(LENRXOK); 
        break;
    case RX_ONLY: 
        control_mode |= _BV(LENA) |= _BV(LCMD2) |= LMCD0;  
        interrupt_setting |= _BV(LENRXOK); 
        break;
    case TX_ONLY: 
        control_mode |= _BV(LENA) |= _BV(LCMD2) |= LMCD1;  
        interrupt_setting |= _BV(LENTXOK); 
        break; 
    default:
        break;
    }

    switch (conf)
    {
    case STANDARD_8N1:
        control_mode &= ~_BV(LCONF1) &= ~_BV(LCONF0); // set both to 0
        break;
    case STANDARD_8E1: 
        control_mode |= _BV(LCONF0); 
        break; 
    case STANDARD_8O1: 
        control_mode |= _BV(LCONF1); 
        break; 
    case LISTEN_8N1: 
        control_mode |= _BV(LCONF1) |= _BV(LCONF2); 
        break; 
    default:
        break;
    }


    init_UART_raw(control_mode, interrupt_setting); 


}


// clear data! 
int8_t get_byte(){
    int8_t data = LINDAT;  
    LINDAT &= 0xff; 
    return data; 
} 

void set_byte(int8_t data) {
    // LINDAT &= 0xff; 
    LINDAT = data; 
}

// state update functions





// ISR handling
ISR(LIN_TC_VECT){ // should this be USART_RX_VECT ? 
    
}