#ifndef ADC_H
#define ADC_H

#include "xmem.h"
#include <avr/io.h>

typedef struct {
    uint8_t x;
    uint8_t y;
} pos_t;

void adc_init(void);

uint8_t adc_read(uint8_t channel);

void adc_calibrate();

pos_t pos_read(void);


#endif