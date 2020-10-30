#include "pid.h"
#include "slider.h"

#define K_P 1
#define K_I 1


PI_data_t PI_data = {    
    K_P,
    K_I,
    0
};


void pi_controller(PI_data_t* PI, int T) {
    slider_t ref;
    slider_pos_recieve(&ref);

    int real_pos;
    //HER MÅ VI LESE ENKODEREN

    int error = ref.right - real_pos;
    PI->sum_error += error;

    int u = PI->k_p*error + T*PI->k_i*PI->sum_error;
}