#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>

<<<<<<< HEAD
/**
 * @brief Enum that describes the tilting of the accelerometer.
 */
=======
>>>>>>> master

typedef enum{
    middle,
    left,
    right
} dir_t;

<<<<<<< HEAD
/**
 * @brief Set the pins(0-2) on the microbit to output.
 */
=======
>>>>>>> master

void controller_init_pins(void);


<<<<<<< HEAD
/**
 * @brief Read the accelerometer values in X, Y, and Z directions.
 *
 * @param x_pt Pointer to x-value from accelerometer of type int16_t.
 *
 * @return left if the accelerometer is tilted left;
 *  right if the accelerometer is tilted right;
 *  middle if the accelerometer is horizontal.
 */

const dir_t controller_get_dir(const int16_t* x_pt);


/**
 * @brief Set the pins(0-1) high, depending on dir. 
 *
 * @param dir Pointer to dir of type dir_t.
 */

void controller_set_pin_high(dir_t* dir);


/**
 * @brief Send dir from node 3.
 *
 * @param x_pt Pointer to x-value from accelerometer of type int16_t
 */

void controller_send_dir(int16_t* x_pt);


/**
 * @brief Read the accelerometer values in X, Y, and Z directions.
 */

=======
const dir_t controller_get_dir(const int16_t* x_pt);


void controller_set_pin_high(dir_t* dir);


void controller_send_dir(int16_t* x_pt);


>>>>>>> master
void controller_send_button_pressed(void);


#endif
