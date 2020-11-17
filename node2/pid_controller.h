#ifndef PID_H
#define PID_H

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
} PID_DATA_t;


void pid_controller_init(float k_p, float k_i, float k_d, float timestep, int max_u);


void pid_controller_set_parameters(float k_p, float k_i, float k_d);


void pid_controller_reset_errors();


int pid_controller(int ref, int current_value);


#endif