#include "joystick.h"
#include "adc.h"
#include <math.h>


#define X_CHANNEL 0
#define Y_CHANNEL 1
#define DIRECTION_TRESHOLD 40

#define X_OFFSET 26
#define Y_OFFSET 28
#define MAX_VALUE 100
#define MIN_VALUE -100


int joystick_scale_value(uint8_t value, int offset, int max, int min) {
    // scale to values between min and max 
    int scaled_value = (int)(value - 128)*(max - min)/256;

    // correct offset and nonlinear scaling
    // based on measurements we assume positive offset
    if (scaled_value > offset) {
        scaled_value -= (int)(offset*(max - scaled_value)/(max - offset));
    }
    else
    {
        scaled_value -= (int)(offset*(min - scaled_value)/(min - offset));
    }

    return scaled_value;
}


pos_t joystick_pos_read(void){
    uint8_t x = adc_read(X_CHANNEL);
    uint8_t y = adc_read(Y_CHANNEL);

    pos_t pos;
    pos.x = joystick_scale_value(x, X_OFFSET, MAX_VALUE, MIN_VALUE);
    pos.y = joystick_scale_value(y, Y_OFFSET, MAX_VALUE, MIN_VALUE);

    return pos;
}


dir_t joystick_get_dir(pos_t pos){    
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