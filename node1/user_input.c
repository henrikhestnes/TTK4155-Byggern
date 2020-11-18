#include "user_input.h"
#include "adc.h"
#include "can_driver.h"
#include "../common/can.h"
#include "../common/user_input.h"
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>


#define X_CHANNEL               0
#define Y_CHANNEL               1
#define RIGHT_SLIDER_CHANNEL    2
#define LEFT_SLIDER_CHANNEL     3
#define DIRECTION_TRESHOLD      50
#define CENTER_TRESHOLD         10
#define RIGHT_BUTTON_PIN        PB1
#define LEFT_BUTTON_PIN         PB2
#define JOYSTICK_BUTTON_PIN     PD3

#define CLKSEL_OFF_MASK         0xF8
#define CLKSEL_PRESCALER_1024   ((1 << CS32) | (1 << CS30))


static void interrupt_can_timer_init() {
    TCCR3A = 0;
    TCCR3B = 0;
    TCNT3 = 0;

    // set compare match register for 10 Hz
    OCR3A = 479;

    // set to CTC mode
    TCCR3B |= (1 << WGM32);

    // set prescaler 1024
    TCCR3B |= CLKSEL_PRESCALER_1024;

    // enable timer compare interrupt
    ETIMSK |= (1 << OCIE3A);
}


void user_input_init() {
    adc_init();

    // set button pins to input
    DDRB &= ~(1 << RIGHT_BUTTON_PIN) & ~(1 << LEFT_BUTTON_PIN);
    DDRD &= ~(1 << JOYSTICK_BUTTON_PIN);

    interrupt_can_timer_init();
}


JOYSTICK_POS user_input_joystick_pos() {
    JOYSTICK_POS pos;
    pos.x = adc_read(X_CHANNEL);
    pos.y = adc_read(Y_CHANNEL);

    return pos;
}


int joystick_scale_value(uint8_t value, int offset) {
    // scale to values in interval [JOYSTICK_MIN, JOYSTICK_MAX]
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


JOYSTICK_DIR user_input_joystick_dir(void) {
    JOYSTICK_POS pos = user_input_joystick_pos();
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

    else if (abs(pos.x) < CENTER_TRESHOLD && abs(pos.y) < CENTER_TRESHOLD) {
        return CENTER;
    }

    else {
        return NEUTRAL;
    }
}


SLIDER_POS user_input_slider_pos(void) {
    SLIDER_POS slider;
    slider.left = adc_read(LEFT_SLIDER_CHANNEL);
    slider.right = adc_read(RIGHT_SLIDER_CHANNEL);

    return slider;
}


BUTTONS user_input_buttons(void) {
    BUTTONS status = {0, 0, 0};

    status.right = (PINB & (1 << RIGHT_BUTTON_PIN)) >> RIGHT_BUTTON_PIN;
    status.left = (PINB & (1 << LEFT_BUTTON_PIN)) >> LEFT_BUTTON_PIN;
    status.joystick = !((PIND & (1 << JOYSTICK_BUTTON_PIN)) >> JOYSTICK_BUTTON_PIN);

    return status;
}


void user_input_transmit() {
    JOYSTICK_POS joystick = user_input_joystick_pos();
    SLIDER_POS slider = user_input_slider_pos();
    BUTTONS button = user_input_buttons();

    CAN_MESSAGE m = {
        .id = USER_INPUT_ID,
        .data_length = 6,
        .data = {joystick.x, joystick.y, slider.left, slider.right, button.left, button.right}
    };

    can_send(&m);
}


void user_input_timer_enable() {
    cli();

    TCCR3B |= CLKSEL_PRESCALER_1024;

    sei();
}


void user_input_timer_disable() {
    cli();

    TCCR3B &= CLKSEL_OFF_MASK;

    sei();
}