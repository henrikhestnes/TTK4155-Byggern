#ifndef UART_H
#define UART_H

#include <avr/io.h>


void UART_init(unsigned int ubrr);

void UART_transmit(unsigned char data);

unsigned char UART_recieve();

void UART_link_printf();

#endif