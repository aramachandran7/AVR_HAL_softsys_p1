#include "AVR_ADC_driver.h"


/*
This funciton can be called any number of times to init the AVR ADC (and reinit / change settings)
TODO: add more operating modes? 
*/
void init_ADC(int16_t frequency){
    // enable ADC bit 
    ADCSRA |= _BV(ADEN); 

    // enable internal reference voltage pg 212 TODO: not sure why we do this 
    AREFEN &= _BV(AREFEN); 

    // set prescaler to 32, for desired frequency - do we want to handle custom frequency + custom prescalers? 
    ADCSRA |= _BV(ADPS2) |= _BV(ADSP0); 

    // setup internal reference
    ADMUX |= _BV(REFS0); 

}


int16_t single_read_ADC(int8_t ADC_channel){
    // perform a single conversion from select ADC channel

    // clear mux select value, and set ADC_channel appropriately
	ADMUX = _BV(REFS0);
    ADMUX |= _BV(ADC_channel); 

    // start conversion 
    ADCSRA |= _BV(ADSC); 

    // blocking loop until conversion is complete, where ADSC bit will be cleared
	loop_until_bit_is_clear(ADCSRA, ADSC);

    uint16_t ADC_result = ADC; // TODO: does this automatically get bits stored in ADCH and ADCL registers? 

    return ADC_result; 
    
}
