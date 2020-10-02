#include "spi_driver.h"
#include <avr/io.h>


#define WRITE_INSTR 0b00000010
#define READ_INSTR  0b00000011


void spi_init(void){
    // Set SS, MOSI and SCK output, all others input
    DDRB = (1 << PB4) | (1 << PB5) | (1 << PB7);

    // Enable SPI, set to master, set SPI mode 0, set SCK rate to F_osc / 2
    SPCR = (1 << SPE) | (1 << MSTR);
    SPSR |= (1 << SPI2X);
}


void spi_write(uint8_t data){
    // Start transmission 
    SPDR = data;
    
    // Wait for transmission comlpete
    while(!(SPSR & (1 << SPIF)));
}


uint8_t spi_read() {
    // Transmission of dummy byte
    spi_write(0);

    return SPDR;
}
