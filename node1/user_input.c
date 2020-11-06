#include "user_input.h"
#include "adc.h"
#include "can_driver.h"
#include <math.h>
#include <avr/io.h>


#define X_CHANNEL               0
#define Y_CHANNEL               1
#define RIGHT_SLIDER_CHANNEL    2
#define LEFT_SLIDER_CHANNEL     3
#define DIRECTION_TRESHOLD      50
#define RIGHT_BUTTON_PIN        PB1
#define LEFT_BUTTON_PIN         PB2



int joystick_scale_value(uint8_t value, int offset) {
    // scale to values between min and max 
    int scaled_value = (int)(value - 128)*(JOYSTICK_MAX - JOYSTICK_MIN)/256;

    // correct offset and nonlinear scaling
    // based on measurements we assume positive offset
    if (scaled_value > offset) {
        scaled_value -= (int)(offset*(JOYSTICK_MAX - scaled_value)/(JOYSTICK_MAX - offset));
    }
    else
    {
        scaled_value -= (int)(offset*(JOYSTICK_MIN - scaled_value)/(JOYSTICK_MIN - offset));
    }

    return scaled_value;
}


void user_input_init(void) {
    adc_init();

    // set button pins to input
    DDRB &= ~(1 << RIGHT_BUTTON_PIN) & ~(1 << LEFT_BUTTON_PIN);
}


pos_t user_input_joystick_pos(void) {
    pos_t pos;
    pos.x = adc_read(X_CHANNEL);
    pos.y = adc_read(Y_CHANNEL);

    return pos;
}


dir_t user_input_joystick_dir(void) {
    pos_t pos = user_input_joystick_pos();
    pos.x = joystick_scale_value(pos.x, JOYSTICK_X_OFFSET);
    pos.y = joystick_scale_value(pos.y, JOYSTICK_Y_OFFSET);

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

    else {
        return NEUTRAL;
    }
}


slider_t user_input_slider_pos(void) {
    slider_t slider;
    slider.left = adc_read(LEFT_SLIDER_CHANNEL);
    slider.right = adc_read(RIGHT_SLIDER_CHANNEL);

    return slider;
}


button_t user_input_buttons(void) {
    button_t status = {0, 0};

    status.right = (PINB & (1 << RIGHT_BUTTON_PIN)) >> RIGHT_BUTTON_PIN;
    status.left = (PINB & (1 << LEFT_BUTTON_PIN)) >> LEFT_BUTTON_PIN;

    return status;
}


void user_input_transmit() {
    pos_t joystick = user_input_joystick_pos();
    slider_t slider = user_input_slider_pos();
    button_t button = user_input_buttons();

    message_t m = {
        .id = USER_INPUT,
        .length = 6,
        .data = {joystick.x, joystick.y, slider.left, slider.right, button.left, button.right}
    };

    can_transmit(&m);
}
