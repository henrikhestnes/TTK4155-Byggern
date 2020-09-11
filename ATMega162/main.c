#include "jtag.h"
#include "uart.h"
#include "xmem.h"
#include "sram_test.h"
#include "adc.h"

#define FOSC 4915200
//#define FOSC 8000000
#define BAUD 9600
#define UBRR FOSC / 16 / BAUD - 1

int main() {
    UART_init(UBRR);
    //xmem_init();
    adc_init();

    // link printf() to UART by sending one character to the MCU
    //UART_link_printf();
    
    //SRAM_test();

    //while(1){
    //    printf("Magnus er søt \t");
    //    int i = 14;
    //    printf("%d", i);
    //    _delay_ms(1000);
    //}

    //DDRB = 1;
    //while (1) {
    //    PORTB |= (1 << PB0);
    //    _delay_ms(1000);
    //    PORTB &= ~(1 << PB0);
    //    _delay_ms(1000);
    //}

  
    return 0;
}