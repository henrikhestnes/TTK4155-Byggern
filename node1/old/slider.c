#include "slider.h"
#include "adc.h"
#include "can_driver.h"
#include <avr/io.h>


#define RIGHT_SLIDER_CHANNEL 2
#define LEFT_SLIDER_CHANNEL 3


int slider_scale_value(uint8_t value, int offset, int max) {
    // scale to values between 0 and max 
    int scaled_value = (int)(value*max/256);

    // correct offset and nonlinear scaling
    // based on measurements we assume positive offset
    if (scaled_value > max / 2 + offset) {
        scaled_value -= (int)(offset*(max - scaled_value)/(max / 2 - offset));
    }
    else
    {
        scaled_value -= (int)(offset*scaled_value/(max / 2 + offset));
    }

    return scaled_value;
}


slider_t slider_pos_read() {
    uint8_t left = adc_read(LEFT_SLIDER_CHANNEL);
    uint8_t right = adc_read(RIGHT_SLIDER_CHANNEL);

    slider_t slider;
    slider.left = slider_scale_value(left, LEFT_OFFSET, SLIDER_MAX_VALUE);
    slider.right = slider_scale_value(right, RIGHT_OFFSET, SLIDER_MAX_VALUE);

    return slider;
}


void slider_send_pos_to_can() {
  slider_t slider_pos = slider_pos_read();

  message_t slider_message = {
    .id = 3,
    .length = 2,
    .data = {slider_pos.left, slider_pos.right}
  };

  can_transmit(&slider_message);
}