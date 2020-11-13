#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>


/**
 * @brief Enum that describes the tilting of the accelerometer.
 */

typedef enum{
    middle,
    left,
    right
} acc_dir_t;


/**
 * @brief Set the pins(0-2) on the microbit to output.
 */

void controller_init_pins(void);


/**
 * @brief Read the accelerometer values in X, Y, and Z directions.
 *
 * @param x_pt Pointer to x-value from accelerometer of type int16_t.
 *
 * @return left if the accelerometer is tilted left;
 *  right if the accelerometer is tilted right;
 *  middle if the accelerometer is horizontal.
 */

const acc_dir_t controller_get_dir(const int16_t* x_pt);


/**
 * @brief Set the pins(0-1) high, depending on dir.
 *
 * @param dir Pointer to dir of type dir_t.
 */

void controller_set_pin_high(acc_dir_t* dir);


/**
 * @brief Send dir from node 3.
 *
 * @param x_pt Pointer to x-value from accelerometer of type int16_t
 */

void controller_send_dir(int16_t* x_pt);


/**
 * @brief Set pin high while button B is pressed.
 */

void controller_send_button_pressed(void);


#endif
