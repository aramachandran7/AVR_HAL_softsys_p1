#include "AVR_timer_driver.h"



/* 
Page 85-93 of Atmega datasheet 
Code currently only supports CTC and normal mode
*/

/*
ASSUSMES: 
That user will always use frequency 1, but not frequency 2
*/

/*
Reset timer registers, ' 'effectively turn off'
*/
void reset_timer(short timer_num){
    uint8_t zero = 0x00; 
    uint16_t zero_16 = 0x00; 
    switch (timer_num)
    {
    case 0:
        TCCR0A &= ~_BV(WGM01); // set timer mode of operation
        TCCR0B = 0b000; // set prescaler 
        TIMSK0 &= ~_BV(OCIE0A); 
        TIMSK1 &= ~_BV(OCIE0B); // enables timer 0 interrupts
        OCR0A = zero; // set period for A, 8 bits
        OCR0B = zero; // set period for B, 8 bits
        break;
    case 1: 

        TCCR1A &= ~_BV(WGM11); // set timer mode of operation
        TCCR1B = 0b000; // set prescaler 
        TIMSK1 &= ~_BV(OCIE1A); 
        TIMSK1 &= ~_BV(OCIE1B); // enables timer 0 interrupts
        OCR1A = zero_16; // set period for A, 16 bits
        OCR1B = zero_16; // set period for B, 16 bits
        break;    
    default:
        break;
    }
}


/*
Raw init fn where user passes in individual register values, from datasheet to init
*/
void init_timer_raw(short timer_num, uint8_t mode, uint8_t prescaler, uint8_t interrupt_mask, uint16_t period_1, uint16_t period_2){
    switch (timer_num)
    {
    case 0:
        // uint8_t period_1_8_bit = (uint8_t) period_1; 
        // uint8_t period_2_8_bit = (uint8_t) period_2; 
        TCCR0A |= mode; // set timer mode of operation
        TCCR0B = prescaler; // set prescaler 
        TIMSK0 |= interrupt_mask; // enables timer 0 interrupts
        OCR0A = (uint8_t) period_1; // set period for A, 8 bits
        OCR0B = (uint8_t) period_2; // set period for B, 8 bits
        break;
    case 1: 
        TCCR1A |= mode; // set timer mode of operation
        TCCR1B = prescaler; // set prescaler 
        TIMSK1 |= interrupt_mask; // enables timer 0 interrupts
        OCR1A = period_1; // set period for A, 16 bits
        OCR1B = period_2; // set period for B, 16 bits
        break;    
    default:
        break;
    }

}


/*
Manipulate and access timer state
*/
void set_state_timer(timer_state_struct * timer_state, timer_output_mode new_mode, uint8_t new_flag){
    (*timer_state).timer_mode = new_mode; 
    (*timer_state).timer_flag = new_flag; 
}


/*
defualt init timer 0 with as many enums as possible
*/
void init_timer_driver(short timer_num, timer_output_mode mode, uint16_t frequency_1, uint16_t frequency_2){
    
    int16_t prescaler_val; // helper var
    // vars to pass into raw function TODO: types? 
    uint8_t pass_mode = 0x00; 
    uint8_t prescaler; 
    uint8_t interrupt_mask = 0b000; 
    uint16_t period_1 = 0x00; 
    uint16_t period_2 = 0x00; 

    switch (timer_num)
    {
    case 0:
        // setup case 0 specific registers 
        switch(mode){
            case CTC_MODE: 
                pass_mode = _BV(WGM01); // set timer0 into CTC mode
                interrupt_mask |= _BV(OCIE0A); 
                break; 
            case NORMAL_MODE: 
                pass_mode = 0x00; 
                interrupt_mask |= _BV(OCIE1A); 
                break; // reset
            default: 
                // Don't do anything
                break;
        }
        break;
    case 1: 
        // setup case 1 specific registers
        switch(mode){
            case CTC_MODE: 
                pass_mode = _BV(WGM11); // set timer0 into CTC mode
                interrupt_mask |= _BV(OCIE1A); 
                break; 
            case NORMAL_MODE: 
                pass_mode = 0x00; 
                interrupt_mask |= _BV(OCIE1A); 
                break; // reset
            default: 
                // Don't do anything
                break;
        }
    default:
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

    period_1 = (uint16_t)(FCLK/prescaler_val/frequency_1); 

    if (frequency_2){
        if (timer_num== 1){
            interrupt_mask |= _BV(OCIE0B); 
        }
        interrupt_mask |= _BV(OCIE1B); 
        period_2 = (uint16_t)(FCLK/prescaler_val/frequency_1);
    }

    init_timer_raw(timer_num, pass_mode, prescaler, interrupt_mask, period_1, period_2); 
    set_state_timer(UNIVERSAL_TIMER_STATE[0],CTC_MODE,0x00); 

}




// returns entire state.
timer_state_struct get_state_timer(timer_state_struct * timer_state){
    return (*timer_state); // TODO: how do we return a copy that can't be edited? 
}

/*
Public State API
FOR INTERRUPT HANDLING in superloop: 
- allows you to check bit at a certian position within a flag within an AVR timer state struct 
- if 1, returns 1 and flips bit back to 0. If 0, returns 0. 
*/
uint8_t check_bit_and_flip_if_1(short timer_num, uint8_t bit_to_check){
    // access bit 
    timer_state_struct * timer_state = UNIVERSAL_TIMER_STATE[timer_num]; 
    
    if (bit_is_set((*timer_state).timer_flag, bit_to_check)){
        // flip bit now
        (*timer_state).timer_flag &= ~_BV(bit_to_check); 
        return 1; 
    } else {
        return 0; 
    }
}

/*
Public State API
For Checking mode 
*/
timer_output_mode get_mode_timer(timer_state_struct * timer_state){
    return (*timer_state).timer_mode; // TODO: how do we return a copy that can't be edited? 
}

/*
Interrupt handlers to flip global bits 
*/
ISR(TIMER0_COMPA_vect){
    // flip state bit 
    timer_state_struct current_state = get_state_timer(UNIVERSAL_TIMER_STATE[0]); 
    uint8_t new_flag = current_state.timer_flag |= _BV(TIMER_FLAG_CMP_A); 
    set_state_timer(UNIVERSAL_TIMER_STATE[0], current_state.timer_mode, new_flag); 
}

ISR(TIMER0_COMPB_vect){
    // flip global bit
    timer_state_struct current_state = get_state_timer(UNIVERSAL_TIMER_STATE[0]); 
    uint8_t new_flag = current_state.timer_flag |= _BV(TIMER_FLAG_CMP_B); 
    set_state_timer(UNIVERSAL_TIMER_STATE[0], current_state.timer_mode, new_flag); 
}

ISR(TIMER1_COMPA_vect){
    // flip global bit
    timer_state_struct current_state = get_state_timer(UNIVERSAL_TIMER_STATE[1]); 
    uint8_t new_flag = current_state.timer_flag |= _BV(TIMER_FLAG_CMP_A); 
    set_state_timer(UNIVERSAL_TIMER_STATE[0], current_state.timer_mode, new_flag); 
}

ISR(TIMER1_COMPB_vect){
    // flip global bit
    timer_state_struct current_state = get_state_timer(UNIVERSAL_TIMER_STATE[1]); 
    uint8_t new_flag = current_state.timer_flag |= _BV(TIMER_FLAG_CMP_B); 
    set_state_timer(UNIVERSAL_TIMER_STATE[0], current_state.timer_mode, new_flag); 
}

// void init_timer_0_processed(){} // what's this one? --> intermediate setting
