#include "pid_controller.h"


static PID_DATA_t PID = {0, 0, 0, 0, 0, 0, 0};


void pid_controller_init(float k_p, float k_i, float k_d, float timestep, int max_u) {
    pid_controller_set_parameters(k_p, k_i, k_d);
    pid_controller_reset_errors();
    PID.T = timestep;
    PID.max_u = max_u;
}


void pid_controller_set_parameters(float k_p, float k_i, float k_d) {
    PID.K_p = k_p;
    PID.K_i = k_i;
    PID.K_d = k_d;
}


void pid_controller_reset_errors() {
    PID.sum_error = 0;
    PID.prev_error = 0;
}


int pid_controller(int ref, int current_value) {
    int error = ref - current_value;
    PID.sum_error += error;

    int u_p = PID.K_p * error;
    int u_i = PID.T * PID.K_i * PID.sum_error;
    int u_d = (PID.K_d / PID.T) * (error - PID.prev_error);
    int u = u_p + u_i + u_d;

    PID.prev_error = error;

    if (u > PID.max_u) {
        u = PID.max_u;
    }
    else if (u < -PID.max_u) {
        u = -PID.max_u;
    }

    return u;
}