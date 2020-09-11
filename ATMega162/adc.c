#include "adc.h"

#define BASE_ADDRESS_ADC 0x1400
#define NUMBER_OF_CHANNELS 2

#define X_CHANNEL 0
#define Y_CHANNEL 1
#define RIGHT_SLIDER_CHANNEL 2
#define LEFT_SLIDER_CHANNEL 3
#define RIGHT_BUTTON_PIN PB1
#define LEFT_BUTTON_PIN PB2


#define DIRECTION_TRESHOLD 40

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

    // frequency set to 0.5 x FOSC
    OCR0 = 0;
}


void adc_init(void){
    adc_config_clock();
}


uint8_t adc_read(uint8_t channel){
    // initiate conversion by setting writing to the ADC address space
    volatile char* ext_mem = BASE_ADDRESS_ADC;
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


void adc_calibrate(){

}


pos_t adc_pos_read(void){
    pos_t pos;
    uint8_t x = adc_read(X_CHANNEL);
    uint8_t y = adc_read(Y_CHANNEL);

    // scale to values between -100 and 100 
    int x_scaled = (int)(x - 128)*100/128;
    int y_scaled = (int)(y - 128)*100/128;

    pos.x = x_scaled;
    pos.y = y_scaled;

    return pos;
}


dir_t adc_get_dir(pos_t pos){    
    if(pos.x > DIRECTION_TRESHOLD && abs(pos.y) < abs(pos.x) ){
        return RIGHT;
    }
    if(pos.x < -DIRECTION_TRESHOLD && abs(pos.y) < abs(pos.x)){
        return LEFT;
    }
    if(pos.y > DIRECTION_TRESHOLD && abs(pos.x) <= abs(pos.y)){
        return UP;
    }
    if(pos.y < -DIRECTION_TRESHOLD && abs(pos.x) <= abs(pos.y)){
        return DOWN;
    }
    return NEUTRAL;
}


slider_t adc_get_slider(){
    slider_t slider;

    uint8_t left = adc_read(LEFT_SLIDER_CHANNEL);
    uint8_t right = adc_read(RIGHT_SLIDER_CHANNEL);

    // scale to values between 0 and 100
    int left_scaled = left*100/255;
    int right_scaled = right*100/255;

    slider.left = left_scaled;
    slider.right = right_scaled;

    return slider;
}


