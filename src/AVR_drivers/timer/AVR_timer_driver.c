#include "AVR_timer_driver.h"

/* 
Page 88
Init timer0 to trigger desired output_mode at desired frequency
Code currently only supports CTC and normal mode
frequency_1 is primary, how do we set freuqency_2 as optional / default? 
*/



/*
Raw init fn where user passes in individual register values, from datasheet to init
*/
void init_timer_0_raw(int8_t mode, int8_t prescaler, int8_t interrupt_mask, int8_t period_1, int8_t period_2){
    TCCR0A |= mode; // set timer mode of operation
    TCCR0B = prescaler; // set prescaler 
    TIMSK0 |= interrupt_mask; // enables timer 0 interrupts
    OCR0A = period_1; // set period for A
    OCR0B = period_2; // set period for B

}

/*
defualt init timer 0 with as many enums as possible
*/
void init_timer_0(TIMER_OUTPUT_MODE mode, int16_t frequency_1, int16_t frequency_2){
    
    int16_t prescaler_val; // helper var
    // vars to pass into raw function TODO: types? 
    int8_t pass_mode = 0x00; 
    int8_t prescaler; 
    int8_t interrupt_mask = 0b000; 
    int8_t period_1 = 0x00; 
    int8_t period_2 = 0x00; 
    
    switch(mode){
        case CTC_MODE: 
            pass_mode = _BV(WGM01); // set timer0 into CTC mode
            break; 
        case NORMAL_MODE: 
            pass_mode = 0x00; 
            break; // reset
        default: 
            // Don't do anything
            break;
    }

    if (frequency_1< (FCLK/1024)){ // these should be >> 3 right
        prescaler_val = 1024; 
        prescaler = 0x05;          // clkio/1024 prescaler
    } else if (frequency_1 < FCLK/256){
        prescaler_val = 256; 
        prescaler = 0b100;          // clkio/256 prescaler
    } else if (frequency_1<FCLK/64){
        prescaler_val = 64; 
        prescaler = 0b011;          // clkio/64 prescaler
    } else if (frequency_1< FCLK/8){
        prescaler_val = 8; 
        prescaler = 0b001;          // clkio/8 prescaler
    } else {
        prescaler_val = 1; 
        prescaler = 0b000;          // no prescaler
    }

    interrupt_mask |= _BV(OCIE0A); 
    period_1 = (int8_t)(FCLK/prescaler_val/frequency_1); 

    if (frequency_2){
        interrupt_mask |= _BV(OCIE0B); 
        period_2 = (int8_t)(FCLK/prescaler_val/frequency_1);
    }

    init_timer_0_raw(pass_mode, prescaler, interrupt_mask, period_1, period_2); 
    set_state_timer(universal_timer_state[0],CTC_MODE,0x00); 

}


/*
Manipulate and access timer state
*/

static void set_state_timer(TIMER_STATE_STRUCT * timer_state, TIMER_OUTPUT_MODE new_mode, uint8_t new_flag){
    (*timer_state).timer_mode = new_mode; 
    (*timer_state).timer_flag = new_flag; 
}

TIMER_STATE_STRUCT get_state_timer(TIMER_STATE_STRUCT * timer_state){
    return (*timer_state); // TODO: how do we return a copy that can't be edited? 
}

/*
Interrupt handlers to flip global bits 
*/
ISR(TIMER0_COMPA_vect){
    // flip state bit 
    TIMER_STATE_STRUCT current_state = get_state_timer(universal_timer_state[0]); 
    uint8_t new_flag = current_state.timer_flag |= _BV(T0_A_BIT); 
    set_state_timer(universal_timer_state[0], current_state.timer_mode, new_flag); 
}

ISR(TIMER0_COMPB_vect){
    // flip global bit
}

ISR(TIMER1_COMPA_vect){
    // flip global bit
}

ISR(TIMER1_COMPB_vect){
    // flip global bit

}

// void init_timer_0_processed(){} // what's this one? --> intermediate setting
