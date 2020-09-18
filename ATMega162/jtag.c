#include "jtag.h"

void JTAG_test_PA0() {
    DDRC = (1<<PC2);

    while(1) {
        PORTC |= (1 << PC2);
        _delay_ms(1000);
        PORTC &= ~(1 << PC2);
        _delay_ms(1000);
    }
}