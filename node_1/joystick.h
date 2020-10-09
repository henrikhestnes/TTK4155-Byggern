#ifndef JOYSTICK_H
#define JOYSTICK_H


#include <stdint.h>


/**
 * @brief The different directions the joystick can point.
 */
typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NEUTRAL,
    CENTER
} dir_t;


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


/**
 * @brief Reads the joystick position through the ADC. Uses
 * @c joystick_scale_value() to scale the reading to the desired
 * interval.
 * 
 * @return The scaled joystick position.
 */
pos_t joystick_pos_read(void);


/**
 * @brief Calculates the joystick's direction from it's postiton.
 * 
 * @return The direction the joystick is pointing when in position @p pos.
 */
dir_t joystick_get_dir(void);


#endif