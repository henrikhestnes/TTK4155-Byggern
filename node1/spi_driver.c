#include "spi_driver.h"
#include <avr/io.h>


void spi_init(void){
    // set SS, MOSI and SCK output, all others input
    DDRB |= (1 << PB4) | (1 << PB5) | (1 << PB7);
    DDRB &= ~(1 << PB1) & ~(1 << PB2) & ~(1 << PB3) & ~(1 << PB6);

    // enable SPI, set to master, set SPI mode 0, set SCK rate to F_osc / 16
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);

    // set SS
    PORTB |= (1 << PB4);
}


void spi_write(char data){
    // start transmission 
    SPDR = data;
    
    // wait for comlpeted transmission
    while(!(SPSR & (1 << SPIF)));
}


uint8_t spi_read() {
    // transmission of dummy byte
    spi_write(0);

    return SPDR;
}
