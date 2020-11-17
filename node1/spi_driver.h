/**
 * @file
 * @brief Module for sending and receiving messages over the SPI bus. 
 */


#ifndef SPI_H
#define SPI_H


#include <stdint.h>


/**
 * @brief Initiates the SPI driver by configuring data directions,
 * and setting the ATMega162 to be master node.
 * 
 */
void spi_init(void);


/**
 * @brief Transmits a data byte to the slave on the SPI bus.
 * 
 * @param data Byte to be transmitted.
 */
void spi_write(char data);


/**
 * @brief Recieves a data byte from the slave the SPI bus.
 */
uint8_t spi_read();


#endif