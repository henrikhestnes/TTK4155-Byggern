/**
 * @file 
 * @brief Module for microbit functionality
 */


#ifndef NODE2_MICROBIT_H
#define NODE2_MICROBIT_H


#include "../node3/source/controller.h"


/**
 * @brief Initializes the microbit by enabling the PIO 
 * to control the corresponding pins.
 */
void microbit_init();


/**
 * @brief Returns the microbit accelerometer output
 *
 * @return Returns either ACC_LEFT, ACC_MIDDLE, ACC_RIGHT
 */
const ACC_DIR microbit_dir();


/**
 * @brief Returns the microbit left button output
 *
 * @return Returns 1 if pressed, 0 otherwise
 */
const char microbit_button();


#endif