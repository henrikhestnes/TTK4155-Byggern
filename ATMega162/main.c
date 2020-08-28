#include "jtag.h"
#include "uart.h"

#define FOSC 4915200
#define BAUD 9600
#define UBRR FOSC / 16 / BAUD - 1

int main() {
    // JTAG_test_PA0();
    UART_init(UBRR);
    
    while(1) {
        unsigned char c = UART_recieve();
        UART_transmit(c);
    }
    
    return 0;
}