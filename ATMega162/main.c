#include "jtag.h"
#include "uart.h"

#define FOSC 4915200
#define BAUD 9600
#define UBRR FOSC / 16 / BAUD - 1

int main() {
    UART_init(UBRR);

    // link printf() to UART by sending one character to the MCU
    UART_link_printf();
    while(1){
        printf("Magnus er søt \t");
        int i = 14;
        printf("%d", i);
        _delay_ms(1000);
    }
    
    return 0;
}