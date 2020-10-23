#include "joystick.h"
#include "can/can_controller.h"


#define X_OFFSET    26
#define Y_OFFSET    28
#define MAX_VALUE   100
#define MIN_VALUE  -100


int joystick_scale_x(uint8_t value, int max, int min) {
    int x = (int) (value - 128)*(max - min)/256;

    // regresion to scale x values
    x = (int) (7.7E-5*x*x*x + 6.6E-4*x*x + 0.23*x - 6.6);
    return x;
}


int joystick_scale_y(uint8_t value, int max, int min) {
    int y = (int) (value - 128)*(max - min)/256;

    // regresion to scale y values
    y = (int) (7.6E-5*y*y*y + 9E-4*y*y + 0.24*y - 9.1);
    return y;
}


int joystick_pos_recieve(pos_t* pos) {
    CAN_MESSAGE pos_message;
    if(!(can_receive(&pos_message, 0))) {
        if (pos_message.id == 1) {
            pos->x = joystick_scale_x(pos_message.data[0], MAX_VALUE, MIN_VALUE);
            pos->y = joystick_scale_y(pos_message.data[1], MAX_VALUE, MIN_VALUE);

            return 0;
        }
    }

    return 1;
}