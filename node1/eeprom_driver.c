#include "eeprom_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>


void eeprom_write(unsigned int address, unsigned char data){
    // wait for completion of previous write
    while (EECR & (1<<EEWE));
    
    // set up address and data register
    EEAR = address;
    EEDR = data;

    // disable interrupts
    cli();

    // make it possible to write to eeprom by setting EEWE
    EECR |= (1 << EEMWE);

    // start eeprom write by setting EEWE
    EECR |= (1 << EEWE);

    // enable interrupts
    sei();
}


unsigned char eeprom_read(unsigned int address){
    // wait for completion of previous write
    while(EECR & (1 << EEWE));

    // set up adress register
    EEAR = address;

    // disable interrupts
    cli();

    // start eeprom read by writing EERE
    EECR |= (1 << EERE);

    // enable interrupts
    sei();

    //return data from data register
    return EEDR;
}
