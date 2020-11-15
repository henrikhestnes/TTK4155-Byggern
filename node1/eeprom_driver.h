#ifndef EEPROM_DRIVER_H
#define EEPROM_DRIVER_H


#define HIGHSCORE_BASE_ADDRESS 0;


void eeprom_write(unsigned int address, unsigned char data);


unsigned char eeprom_read(unsigned int address);


#endif