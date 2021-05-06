#include "AVR_UART_driver.h"

/*
initializes UART
*/

void init_UART_raw(uint8_t control_mode, uint8_t interrupt_setting, uint8_t baud_register){
    // set registers
    LINCR |= control_mode; 
    LINENIR |= interrupt_setting; 
    LINBRR |= baud_register; 
}

/*
Manipulate and access timer state
*/
void init_state_UART(UART_state_struct * UART_state, UART_mode new_mode, UART_conf new_conf, uint8_t new_flag){
    // INIT STATE VARS
    (*UART_state).mode = new_mode; 
    (*UART_state).conf = new_conf;
    (*UART_state).flag = new_flag;
    // INIT RELEVANT GLOBALS
    // data_TX_buffer[UART_BUFFER_SIZE] = {0}; // don't think we need to declare? 
    // data_RX_buffer[UART_BUFFER_SIZE] = {0};
    TX_pointer = 0;
    RX_pointer = 0;
}


void init_UART_driver(UART_mode mode, UART_conf conf, uint32_t UART_baud){

    uint8_t control_mode = 0x00; // mode register, passed into LINCR
    uint8_t interrupt_setting = 0x00; // for linenir
    uint8_t buad_rate_register = 0x00; 


    switch (mode)
    {
    case FULL_DUPLEX:
        /* code */
        control_mode |= _BV(LENA); 
        control_mode |= _BV(LCMD0); 
        control_mode |= _BV(LCMD1);  
        control_mode |= _BV(LCMD2); 
        interrupt_setting |= _BV(LENTXOK); 
        interrupt_setting |= _BV(LENRXOK); 
        break;
    case RX_ONLY: 
        control_mode |= _BV(LENA); 
        control_mode |= _BV(LCMD0);  
        control_mode |= _BV(LCMD2); 
        interrupt_setting |= _BV(LENRXOK); 
        break;
    case TX_ONLY: 
        control_mode |= _BV(LENA); 
        control_mode |= _BV(LCMD1);  
        control_mode |= _BV(LCMD2); 
        interrupt_setting |= _BV(LENTXOK); 
        break; 
    default:
        break;
    }

    switch (conf)
    {
    case STANDARD_8N1:
        control_mode &= ~_BV(LCONF1); 
        control_mode &= ~_BV(LCONF0); // set both to 0
        break;
    case STANDARD_8E1: 
        control_mode |= _BV(LCONF0); 
        break; 
    case STANDARD_8O1: 
        control_mode |= _BV(LCONF1); 
        break; 
    case LISTEN_8N1: 
        control_mode |= _BV(LCONF0); 
        control_mode |= _BV(LCONF1); 
        break; 
    default:
        break;
    }

    buad_rate_register = (uint8_t) (FCLK / ((uint32_t)(UART_baud * 32)) - 1 ); // assumes default value of 32 for LINBTR register | page 183 & 195
    // TODO: THIS LINE IS HIGHLY SUS 

    init_state_UART(UNIVERSAL_UART_STATE[0], mode, conf, 0x00); 
    init_UART_raw(control_mode, interrupt_setting, buad_rate_register); 

}


/* 
Low Level API
*/
uint8_t get_byte_UART_driver(){
    int8_t data = LINDAT;  
    LINDAT &= 0xff; // clear data!  
    return data; 
} 

void set_byte_UART_driver(uint8_t data) {
    // LINDAT &= 0xff; 
    LINDAT = data; 
}

// BLOCKING - loops till ready to send
void wait_till_UART_ready_to_send(){
    loop_until_bit_is_clear(LINSIR, LBUSY);
}

// private state API
void set_flag(UART_state_struct * state, uint8_t bit_to_check){
    (*state).flag |= _BV(bit_to_check); 
}
void clear_flag(UART_state_struct * state, uint8_t bit_to_check){
    (*state).flag &= ~_BV(bit_to_check); 
}



// Fuck this convoluted public state API jesus
// tho I like the premise 
uint8_t check_bit_and_clear_if_set_UART(uint8_t bit_to_check){
    UART_state_struct * UART_state = UNIVERSAL_UART_STATE[0]; // 0 always, but in the future should be variablized

    if(bit_is_set((*UART_state).flag, bit_to_check)){
        // clear it, return 1
        clear_flag(UART_state, bit_to_check); 
        return 1; 
    } else {
        return 0; 
    }
}



// ISR handling

ISR(LIN_TC_vect){
    // state is ideally chip agnostic, even though we're literally duplicating bits argh 
    if (bit_is_set(LINSIR, LTXOK)){ // TX 
        set_flag(UNIVERSAL_UART_STATE[0], UART_TX_SENT); 
        LINSIR &= ~_BV(LTXOK); // clear actual register 
    } 
    if (bit_is_set(LINSIR, LRXOK)){ // RX 
        set_flag(UNIVERSAL_UART_STATE[0], UART_RX_RCVD); 
        LINSIR &= ~_BV(LRXOK); // clear register
    }
}
