#include "uart.h"
#include <avr/io.h>


void UART_init(unsigned int ubrr) {
    // set baudrate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    // enable reciever and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // set frame format
    UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00);
}


void UART_transmit(unsigned char data){
    // wait for empty buffer
    while (!(UCSR0A & (1 << UDRE0)));

    // write to data register
    UDR0 = data;
}


unsigned char UART_recieve() {
    // wait for completed recieve
    while (!(UCSR0A & (1 << RXC0)));

    // read data register
    return UDR0;
}


void UART_link_printf() {    
    fdevopen(&UART_transmit, &UART_recieve);
}