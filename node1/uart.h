/**
 * @file
 * @brief Module for sending and receiving messages through the UART. 
 */


#ifndef NODE1_UART_H
#define NODE1_UART_H


/**
 * @brief Initiates the uart module by enabling the necessary registers,
 * and setting baudrate and frame format.
 * 
 * @param ubrr Value used to compute baudrate.
 */
void uart_init(unsigned int ubrr);


/**
 * @brief Tranmits @p data to the MCU.
 * 
 * @param data 8-bit value to be tranmitted.
 */
void uart_transmit(unsigned char data);


/**
 * @brief Recieves data from the MCU.
 * 
 * @return 8-bit value recieved from the MCU.
 */
unsigned char uart_recieve();


/**
 * @brief Links the @c printf() function to the uart module. 
 */
void uart_link_printf();


#endif