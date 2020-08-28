#include "uart.h"
#include <avr/io.h>

#define F_CPU 4.9152E6
#define BAUD 9600
#include <util/delay.h>

void UART_init(unsigned int ubrr) {
    // set baudrate
    UCSR0A &= ~(1 << U2X0);
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    // enable reciever and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // set communication format
    UCSR0C = (1 << URSEL0) | (1 << USBS0) | (1 << UCSZ01);
}

void UART_transmit(unsigned char data){
    // wait for empty buffer
    while(!(UCSR0A & (1 << UDRE0)));

    // write to data register
    UDR0 = data;
}

unsigned char UART_recieve() {
    // wait for completed recieve
    while (!(UCSR0A & (1 << RXC0)));

    // read data register
    return UDR0;
}