#include "jtag.h"
#include "uart.h"

#define FOSC 4915200
#define BAUD 9600
#define UBRR FOSC / 16 / BAUD - 1

int main() {
    // JTAG_test_PA0();
    UART_init(UBRR);

    // link printf() to UART by sending one character to the MCU
    UART_link_printf();

    printf("Onsdager er kult \n");

    int i = 14;
    printf("%d", i);
    
    
    return 0;
}