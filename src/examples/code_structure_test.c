
#include "../lib/libs/timer/timer_library.h"
#include "../lib/libs/UART/UART_library.h"


mcu_type MCU = ATMEGA16M1; 



volatile uint8_t read_ptr = 0; 
volatile uint8_t write_ptr = 0; 

/*
high level code structure
- consistent stream of UART input 
- processing involves encrpyting data 1 byte at a time
- UART output

To consider - concurrency issues regarding 

*/

uint8_t encrypt(uint8_t data){
    return (data * 2 - 1); 
}

void input(){
    recv_UART_to_buffer(0); 
}

void process(){
    // write from RX buffer into TX buffer 
    while (read_ptr != RX_pointer){
        // encrypt and write 
        data_TX_buffer[write_ptr] = encrypt(data_RX_buffer[read_ptr]); 

        // increment read and write ptr 
        read_ptr = (read_ptr + 1)% UART_BUFFER_SIZE; 
        write_ptr = (write_ptr + 1)% UART_BUFFER_SIZE; 
    }
}

void output(){
    // if TX is not ready to send, this passes through without doing anything - it doesn't block. 
    send_UART_from_buffer(0); 
}

int main(void){
    sei(); 
    init_UART(FULL_DUPLEX, STANDARD_8N1, 9600, 0); 

    while(1){ 
        // can be built into RTOS structure with proper concurrency protection   
        input(); 
        process(); 
        output(); 
    }
}