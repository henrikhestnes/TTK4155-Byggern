/**
 * @file 
 * @brief Module for scaling user inputs
 */


#ifndef NODE2_USER_INPUT_SCALING
#define NODE2_USER_INPUT_SCALING


#include <stdint.h>


/**
 * @brief Scales x-value of joystick with regresion to interval [-100, 100]
 * 
 * @param value Joystick x-value in interval [0, 255]. 
 *
 * @return Scaled value
 */
int joystick_scale_x(uint8_t value);


/**
 * @brief Scales y-value of joystick with regresion to interval [-100, 100]
 * 
 * @param value Joystick y-value in interval [0, 255]. 
 *
 * @return Scaled value
 */
int joystick_scale_y(uint8_t value);


/**
 * @brief Scales right slider of multifunction board to interval [0, 100]
 * 
 * @param value Right slider value in interval [0, 255]. 
 *
 * @return Scaled value
 */
int slider_scale_right(uint8_t value);


/**
 * @brief Scales left slider of multifunction board to interval [0, 100]
 * 
 * @param value Left slider value in interval [0, 255]. 
 *
 * @return Scaled value
 */
int slider_scale_left(uint8_t value);


#endif
