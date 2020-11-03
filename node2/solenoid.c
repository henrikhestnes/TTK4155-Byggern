#include "solenoid.h"
#include "sam/sam3x/include/sam.h"
#include "timer.h"


void solenoid_init(void) {
    // enable A0 pin on shield as output, active low
    PIOA->PIO_PER |= PIO_PA16;
    PIOA->PIO_OER |= PIO_PA16;
    PIOA->PIO_SODR |= PIO_PA16;
}


void solenoid_shoot(void) {
    // set a pulse on A0
    PIOA->PIO_CODR |= PIO_PA16;
    timer_delay_us(200000);
    PIOA->PIO_SODR |= PIO_PA16;
}