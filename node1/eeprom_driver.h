/**
 * @file
 * @brief Module for reading from and writing to the EEPROM of the ATMega162. 
 */


#ifndef NODE1_EEPROM_DRIVER_H
#define NODE1_EEPROM_DRIVER_H


/**
 * @brief Writes @c data to the EEPROM memory address @c address.
 *
 * @param address Memory address to be written to.
 * @param data Data to be written.
 */
void eeprom_write(unsigned int address, unsigned char data);


/**
 * @brief Reads a data byte from the EEPROM memory address @c address.
 *
 * @param address Memory address to be read from.
 * 
 * @return Data byte at memory address @c address.
 */
unsigned char eeprom_read(unsigned int address);


#endif