#ifndef NODE2_USER_INPUT
#define NODE2_USER_INPUT


#include <stdint.h>
#include "../node3/source/controller.h"


int joystick_scale_x(uint8_t value);


int joystick_scale_y(uint8_t value);


int slider_scale_right(uint8_t value);


int slider_scale_left(uint8_t value);


void user_input_microbit_init(void);


const acc_dir_t user_input_microbit_dir();


const char user_input_microbit_button();


#endif
