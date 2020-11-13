#ifndef NODE2_USER_INPUT
#define NODE2_USER_INPUT


#include <stdint.h>
#include "../node3/source/controller.h"


int joystick_scale_x(uint8_t value);


int joystick_scale_y(uint8_t value);


int slider_scale_right(uint8_t value);


int slider_scale_left(uint8_t value);


void microbit_user_input_init(void);


acc_dir_t acc_get_dir();


#endif
