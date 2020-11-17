#ifndef DAC_H
#define DAC_H


/**
* @file
* @brief Module for dac-fuctionality
*/


#include <stdint.h>


/**
 * @brief Initiates the DAC by setting its mode and clock source,
 * choosing channel, and configuring its PMC settings.
 */
void dac_init(void);


/**
 * @brief Writes a value to be converted to an analog signal in the
 * DAC.
 *
 * @param data Data value to be converted to an analog signal.
 */
void dac_write(uint16_t data);


#endif
