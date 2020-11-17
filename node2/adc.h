#ifndef ADC_H
#define ADC_H


/**
* @file
* @brief Module for adc-fuctionality
*/


#include <stdint.h>


/**
 * @brief Initiates the ADC by setting its mode and clock source,
 * and configuring its PMC settings.
 */
void adc_init(void);


/**
 * @brief Reads the ADC channel 0.
 *
 * @return The converted value at the ADC pin, with type @c uint16_t.
 */
uint16_t adc_read();


#endif
