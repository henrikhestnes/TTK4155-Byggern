#ifndef DAC_H
#define DAC_H


#include <stdint.h>


void dac_init(void);


void dac_write(uint16_t data);


#endif