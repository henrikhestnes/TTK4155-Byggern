#ifndef PID_H
#define PID_H

#include <stdint.h>

/**
 * @brief Data structure to be used to represent 
 * the PI-regulator parameters
 */
typedef struct {
    int K_p;
    int K_i;
    int sum_error;
    double T;
    int max_u;
} PI_data_t;


int pi_controller(PI_data_t* PI, int ref, int current_value);


#endif