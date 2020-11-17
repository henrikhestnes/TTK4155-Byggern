#include "user_input_scaling.h"
#include "../common/user_input.h"



int joystick_scale_x(uint8_t value) {
    int x = (int) (value - 128)*(JOYSTICK_MAX - JOYSTICK_MIN)/256;

    // regresion to scale x values to interval [-100, 100]
    x = (int) (7.7E-5*x*x*x + 6.6E-4*x*x + 0.23*x - 6.6);
    return x;
}


int joystick_scale_y(uint8_t value) {
    int y = (int) (value - 128)*(JOYSTICK_MAX - JOYSTICK_MIN)/256;

    // regresion to scale y values to interval [-100, 100]
    y = (int) (7.6E-5*y*y*y + 9E-4*y*y + 0.24*y - 9.1);
    return y;
}


int slider_scale_right(uint8_t value) {
    // scale to values in interval [0, SLIDER_MAX]
    int scaled_value = (int)(value*SLIDER_MAX/256);

    // correct offset and nonlinear scaling
    // based on measurements we assume positive offset
    if (scaled_value > SLIDER_MAX / 2 + SLIDER_RIGHT_OFFSET) {
        scaled_value -= (int)(SLIDER_RIGHT_OFFSET*(SLIDER_MAX - scaled_value)/(SLIDER_MAX / 2 - SLIDER_RIGHT_OFFSET));
    }
    else
    {
        scaled_value -= (int)(SLIDER_RIGHT_OFFSET*scaled_value/(SLIDER_MAX / 2 + SLIDER_RIGHT_OFFSET));
    }

    return scaled_value;
}


int slider_scale_left(uint8_t value) {
    // scale to values in interval [0, SLIDER_MAX]
    int scaled_value = (int)(value*SLIDER_MAX/256);

    // correct offset and nonlinear scaling
    // based on measurements we assume positive offset
    if (scaled_value > SLIDER_MAX / 2 + SLIDER_LEFT_OFFSET) {
        scaled_value -= (int)(SLIDER_LEFT_OFFSET*(SLIDER_MAX - scaled_value)/(SLIDER_MAX / 2 - SLIDER_LEFT_OFFSET));
    }
    else
    {
        scaled_value -= (int)(SLIDER_LEFT_OFFSET*scaled_value/(SLIDER_MAX / 2 + SLIDER_LEFT_OFFSET));
    }

    return scaled_value;
}
