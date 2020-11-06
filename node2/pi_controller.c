#include "pi_controller.h"


int pi_controller(PI_data_t* PI, int ref, int current_value) {
    int error = ref - current_value;
    PI->sum_error += error;

    int u = PI->K_p * error + PI->T * PI->K_i * PI->sum_error;

    if (u > PI->max_u) {
        u = PI->max_u;
    }
    else if (u < -PI->max_u) {
        u = -PI->max_u;
    }

    return u;
}