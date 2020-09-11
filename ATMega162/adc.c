#include "adc.h"
#include "utilities.h"

#define BASE_ADDRESS_ADC 0xAFF

void adc_init(void){
    // set PB0 to output PWM timer signal
    DDRB |= 1;

    // set to CTC mode
    TCCR0 |= (1 << WGM01);
    TCCR0 &= ~(1 << WGM00);
    
    // set PWM toggle on match with internal clock
    TCCR0 &= ~(1 << COM01);
    TCCR0 |= (1 << COM00);

    // set PWM signal to match with internal clock, no prescale
    TCCR0 &= ~(1 << CS02);
    TCCR0 &= ~(1 << CS01);
    TCCR0 |= (1 << CS00);

    // frequency set to 0.5 x FOSC
    OCR0 = 0;
}

uint8_t adc_read(uint8_t channel){
//    volatile uint8_t *ext_mem = BASE_ADDRESS_ADC;
//    uint8_t channel = *ext_mem;
}

void adc_calibrate(){

}

pos_t pos_read(void){

}