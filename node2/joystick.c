#include "joystick.h"
#include "can/can_controller.h"


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


pos_t joystick_pos_recieve() {
    pos_t pos = {0,0};

    CAN_MESSAGE pos_message;
    if(!(can_receive(&pos_message, 0))) {
        if (pos_message.id == 1) {
            pos.x = joystick_scale_value(pos_message.data[0], X_OFFSET, MAX_VALUE, MIN_VALUE);
            pos.y = joystick_scale_value(pos_message.data[1], Y_OFFSET, MAX_VALUE, MIN_VALUE);
        }
    }

    return pos;
}