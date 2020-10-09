#ifndef UART_H
#define UART_H


/**
 * @brief Initiates the UART module by enabling the necessary registers,
 * and setting baudrate and frame format.
 * 
 * @param ubrr Value used to compute baudrate.
 */
void UART_init(unsigned int ubrr);


/**
 * @brief Tranmits @p data to the MCU.
 * 
 * @param data 8-bit value to be tranmitted.
 */
void UART_transmit(unsigned char data);


/**
 * @brief Recieves data from the MCU.
 * 
 * @return 8-bit value recieved from the MCU.
 */
unsigned char UART_recieve();


/**
 * @brief Links the @c printf() function to the UART module. 
 */
void UART_link_printf();


#endif