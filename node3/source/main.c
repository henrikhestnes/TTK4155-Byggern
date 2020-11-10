#include "accelerometer.h"
#include "button.h"
#include "controller.h"
#include <stdint.h>

int main(){
    button_init();
    accelerometer_init();
    controller_init_pins();

    int16_t x, y, z;

    while(1){
        accelerometer_read(&x, &y, &z);
        controller_send_dir(&x);
        controller_send_button_pressed();
    }

    return 0;
}
