#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>


typedef enum{
    middle,
    left,
    right
} dir_t;


void controller_init_pins(void);


const dir_t controller_get_dir(const int16_t* x_pt);


void controller_set_pin_high(dir_t* dir);


void controller_send_dir(int16_t* x_pt);


void controller_send_button_pressed(void);


#endif
