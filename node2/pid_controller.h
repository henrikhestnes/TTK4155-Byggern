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
    double T;
    int max_u;
} PID_DATA_t;


int pid_controller(PID_DATA_t* PID, int ref, int current_value);


#endif