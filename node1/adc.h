/**
 * @file
 * @brief Module for converting analog input signals to digital signals. 
 */


#ifndef NODE1_ADC_H
#define NODE1_ADC_H


#include <stdint.h>


/**
 * @brief Configurates the external clock signal delivered from
 * the ATMega162 to the ADC. Sets the frequency to half the
 * frequency of the CPU interal clock.
 */
void adc_config_clock(void); 


/**
 * @brief Initiates the ADC by configuring the external clock.
 */
void adc_init(void);


/**
 * @brief Reads the output data from the ADC conversion. Starts the
 * conversion by writing to the ADC address space, and reads serially
 * until data from channel @p channel is read.
 * 
 * @param channel The analog channel to be read from
 * 
 * @return The output data from the conversion of channel @p channel.
 */
uint8_t adc_read(uint8_t channel);


#endif