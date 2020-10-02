#ifndef SPI_H
#define SPI_H


#include <stdint.h>


void spi_init(void);


void spi_write(char data);


uint8_t spi_read();


#endif