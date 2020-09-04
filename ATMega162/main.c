#include "jtag.h"
#include "uart.h"
#include "xmem.h"
#include "sram_test.h"

#define FOSC 4915200
#define BAUD 9600
#define UBRR FOSC / 16 / BAUD - 1

int main() {
    UART_init(UBRR);
    xmem_init();

    // link printf() to UART by sending one character to the MCU
    UART_link_printf();
    
    SRAM_test();

    // while(1){
    //     printf("Magnus er søt \t");
    //     int i = 14;
    //     printf("%d", i);
    //     _delay_ms(1000);
    // }

    uint8_t data = 42;
    volatile char *ext_mem = (char *) 0x1400;

    while(1) {
        ext_mem[0] = data;
    }
    
    return 0;
}