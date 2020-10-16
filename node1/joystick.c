#include "joystick.h"
#include "adc.h"
#include "can_driver.h"
#include <math.h>


#define X_CHANNEL           0
#define Y_CHANNEL           1
#define DIRECTION_TRESHOLD  50

#define X_OFFSET    26
#define Y_OFFSET    28
#define MAX_VALUE   100
#define MIN_VALUE  -100


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
    pos_t pos;
    pos.x = adc_read(X_CHANNEL);
    pos.y = adc_read(Y_CHANNEL);

    return pos;
}


pos_t joystick_scaled_pos_read(void){
    pos_t pos;
    pos.x = adc_read(X_CHANNEL);
    pos.y = adc_read(Y_CHANNEL);

    pos.x = joystick_scale_value(pos.x, X_OFFSET, MAX_VALUE, MIN_VALUE);
    pos.y = joystick_scale_value(pos.y, Y_OFFSET, MAX_VALUE, MIN_VALUE);

    return pos;
}


dir_t joystick_get_dir(){    
    pos_t pos = joystick_pos_read();

    if (pos.x > DIRECTION_TRESHOLD && abs(pos.y) < abs(pos.x)){
        return RIGHT;
    }

    else if (pos.x < -DIRECTION_TRESHOLD && abs(pos.y) < abs(pos.x)){
        return LEFT;
    }

    else if (pos.y > DIRECTION_TRESHOLD && abs(pos.x) <= abs(pos.y)){
        return UP;
    }

    else if (pos.y < -DIRECTION_TRESHOLD && abs(pos.x) <= abs(pos.y)){
        return DOWN;
    }

    else if (abs(pos.x) < 10 && abs(pos.y) < 10){
        return CENTER;
    }   

    else {
        return NEUTRAL;
    }
}


void joystick_send_pos_to_can() {
    pos_t pos = joystick_pos_read();

    message_t pos_message = {
        .id = 1,
        .length = 2,
        .data = {pos.x, pos.y}
    };

    can_transmit(&pos_message);
}