#include "UART_library.h"


/*
Generic UART init function
*/
void init_UART(UART_mode mode, UART_conf conf, uint32_t UART_baud, uint8_t UART_num){
    switch (MCU)
    {
    case ATMEGA16M1:
        // reset code 
        init_UART_driver(mode, conf, UART_baud); 
        break;
    case STM: 
        break;
    case SOFTWARE: 
        break;
    default:
        break;
    }

}

/*
Call these functions from directly within the superloop - they check the appropriate flags 
and send or write to every item in the appropriate buffer. 
They basically allow for data serialization 
These functions should also work nicely within an indiviudal RTOS thread too!
*/

void send_UART_from_buffer(uint8_t UART_num){
    // TODO: implement chip checking
    if (check_bit_and_clear_if_set_UART(UART_TX_SENT)){
        // increment TX Buffer and send next byte 
        set_byte_UART_driver(data_TX_buffer[TX_pointer]); 
        TX_pointer = (TX_pointer + 1) % UART_BUFFER_SIZE; 
    }
}

void send_UART_from_first_byte(uint8_t UART_num){
    if (check_bit_and_clear_if_set_UART(UART_TX_SENT)){
        // write to TX buffer from first byte
        get_byte_UART_driver(data_TX_buffer[0]); 
    }
}


void recv_UART_to_buffer(uint8_t UART_num){
    // TODO: implement chip checking
    if (check_bit_and_clear_if_set_UART(UART_RX_RCVD)){
        // increment RX Buffer and write into RX buffer from next byte
        data_RX_buffer[RX_pointer] = get_byte_UART_driver(); 
        RX_pointer = (RX_pointer + 1) % UART_BUFFER_SIZE; 
    }
}

void recv_UART_to_first_byte(uint8_t UART_num){
    if (check_bit_and_clear_if_set_UART(UART_RX_RCVD)){
        // write into RX buffer from first byte
        data_RX_buffer[0] = get_byte_UART_driver(); 
    }
}


// send from the start of buffer, to a certain point, in a blocking manner 
void send_blocking_UART(uint8_t data_length){
    // either move through entire buffer or char or until queue is empty 

    if (data_length>UART_BUFFER_SIZE){
        // huh
    } else {
        for (TX_pointer=0; TX_pointer < data_length; TX_pointer ++){
            uint8_t data = data_TX_buffer[TX_pointer]; 
            set_byte_UART_driver(data); 
            wait_till_UART_ready_to_send(); 
        }
    }
}

void println_UART(char * starting_char, uint8_t data_len){ // straight from log_uart.c, handy tho 
    // Send our data
    for (int i=0; i < data_len; i++) {
        wait_till_UART_ready_to_send();
        set_byte_UART_driver((uint8_t) starting_char[i]);
    }

    // Send a newline
    wait_till_UART_ready_to_send(); 
    set_byte_UART_driver(0xa);

    // Send a return-carriage
    wait_till_UART_ready_to_send(); 
    set_byte_UART_driver(0xd);
}