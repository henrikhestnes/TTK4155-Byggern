#include "interrupt.h"
#include <avr/io.h>


void interrupt_init() {
    // enable INT1 interrupt vector
    GICR |= (1 << INT1);

    // interrupt on falling edge
    MCUCR |= (1 << ISC11);
    MCUCR &= ~(1 << ISC10);

    // set INT1 as input
    DDRD &= ~(1 << PD3);
}