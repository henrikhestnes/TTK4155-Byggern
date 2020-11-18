/**
 * @file 
 * @brief Module for PID controller functionality
 */


#ifndef NODE2_PID_H
#define NODE2_PID_H

#include <stdint.h>

/**
 * @brief Data structure to be used to represent 
 * the PI-regulator parameters
 */
typedef struct {
    float K_p;
    float K_i;
    float K_d;
    int sum_error;
    int prev_error;
    float T;
    int max_u;
} PID_DATA;


/**
 * @brief Initializes PID-controller
 * 
 * @param k_p Desired K_P gain
 * @param k_i Desired K_I gain
 * @param k_d Desired K_D gain
 * @param timestep Timestep of how often measurements are updated
 * @param max_u Maximum u allowed 
 */
void pid_controller_init(float k_p, float k_i, float k_d, float timestep, int max_u);


/**
 * @brief Sets parameters of PID-controller
 * 
 * @param k_p Desired K_P gain
 * @param k_i Desired K_I gain
 * @param k_d Desired K_D gain 
 */
void pid_controller_set_parameters(float k_p, float k_i, float k_d);


/**
 * @brief Resets sum_error and prev_error to zero
 */
void pid_controller_reset_errors();


/**
 * @brief Initializes PID-controller
 * 
 * @param ref Desired position
 * @param current_value Current position
 *
 * @return Input to motor
 */
int pid_controller(int ref, int current_value);


#endif