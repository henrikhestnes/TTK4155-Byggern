#ifndef ADC_H
#define ADC_H

#include "xmem.h"
#include <avr/io.h>
#include <math.h>

#define F_CPU 4.9152E6
#include <util/delay.h>

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NEUTRAL
} dir_t;

typedef struct {
    int x;
    int y;
} pos_t;

typedef struct {
    int left;
    int right;
} slider_t;

void adc_config_clock(void); 

void adc_init(void);

uint8_t adc_read(uint8_t channel);

void adc_calibrate();

pos_t adc_pos_read(void);

dir_t adc_get_dir(pos_t pos);

slider_t adc_get_slider();

#endif