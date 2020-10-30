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
 * @brief Reads the joystick position through the ADC. Returns a position
 * with x and y values in the interval [0, 255].
 * 
 * @return The scaled joystick position.
 */
pos_t joystick_pos_read(void);


/**
 * @brief Reads the joystick position using @c joystick_pos_read(). Uses
 * @c joystick_scale_value() to scale the reading to the desired
 * interval.
 * 
 * @return The scaled joystick position.
 */
pos_t joystick_scaled_pos_read(void);


/**
 * @brief Calculates the joystick's direction from it's postiton. Reads
 * the joystick position using @c joystick_pos_read().
 * 
 * @return The direction the joystick is pointing.
 */
dir_t joystick_get_dir(void);


/**
 * @brief Reads the joystick position using @c joystick_pos_read(). Sends
 * this position to node 2 using the can interface. The can message
 * transmitted has @c id 1.
 */
void joystick_send_pos_to_can(void);


#endif