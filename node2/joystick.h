#ifndef JOYSTICK_H
#define JOYSTICK_H


#include <stdint.h>


/**
 * @brief Data structure to be used to represent the joystick position.
 */
typedef struct {
    int x;
    int y;
} pos_t;


/**
 * @brief Scales an output from the analog measurement to the range
 * [ @p min, @p max ].
 * 
 * @param value Measurement value to be scaled.
 * @param offset The measurement's offset from the origo when the
 * joystick is in a neutral position.
 * @param max The maximum value the scaled output can have.
 * @param min The minimum value the scaled output can have.
 * 
 * @return The scaled value as an integer. 
 */
int joystick_scale_value(uint8_t value, int offset, int max, int min);


int joystick_pos_recieve(pos_t* pos);


#endif