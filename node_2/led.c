#include "led.h"
#include "sam.h"
#include <stdint.h>


#define LED_D1 PIO_PA19 
#define LED_D2 PIO_PA20 


void led_set() {
    PIOA->PIO_PER |= (LED_D1 | LED_D2);
    PIOA->PIO_OER |= (LED_D1 | LED_D2);
    PIOA->PIO_SODR |= (LED_D1 | LED_D2);
}