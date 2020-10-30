#ifndef PID_H
#define PID_H

#include <stdint.h>

/**
 * @brief Data structure to be used to represent 
 * the PI-regulator parameters
 */
typedef struct {
    int k_p;
    int k_i;
    int sum_error;
    //max_error;
    //max_sum_error;
} PI_data_t;


void pi_controller(PI_data_t* PI, int T);


#endif