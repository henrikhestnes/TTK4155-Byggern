#include "adc.h"
#include <avr/io.h>

#define F_CPU 4.9152E6
#include <util/delay.h>


#define BASE_ADDRESS_ADC 0x1400
#define NUMBER_OF_CHANNELS 4


void adc_config_clock(void) {
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

    // frequency set to 0.5 x F_CPU
    OCR0 = 0;
}


void adc_init(void) {
    adc_config_clock();
}


uint8_t adc_read(uint8_t channel){
    // initiate conversion by setting writing to the ADC address space
    volatile char* ext_mem = (char *) BASE_ADDRESS_ADC;
    ext_mem[0] = 0;

    // wait for end of conversion
    _delay_ms(9*NUMBER_OF_CHANNELS*2 / F_CPU);

    // read desired channel
    uint8_t data;

    for (int i = 0; i <= channel; ++i) {
        data = ext_mem[0];
    }
    
    return data;
}