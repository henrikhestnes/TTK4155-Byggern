#include "jtag.h"

#include <avr/io.h>

#define F_CPU 4.9152E6
#include <util/delay.h>

void JTAG_test_PA0() {
    DDRA = 1;

    while(1) {
        PORTA |= (1 << PA0);
        _delay_ms(1000);
        PORTA &= ~(1 << PA0);
        _delay_ms(1000);
    }
}