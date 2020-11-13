#include "solenoid.h"
#include "sam/sam3x/include/sam.h"
#include "timer.h"


static int shooting_flag = 0;


void solenoid_init(void) {
    // enable A0 pin on shield as output, active low
    PIOA->PIO_PER |= PIO_PA16;
    PIOA->PIO_OER |= PIO_PA16;
    PIOA->PIO_SODR |= PIO_PA16;
}


void solenoid_run_button(int button_pressed) {
    if (button_pressed && !shooting_flag) {
        shooting_flag = 1;
        // set a pulse on A0
        PIOA->PIO_CODR |= PIO_PA16;
        _delay_ms(100);
        PIOA->PIO_SODR |= PIO_PA16;
    }

    else if (!button_pressed) {
        shooting_flag = 0;
    }
}
