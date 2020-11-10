#ifndef TIMER_H
#define TIMER_H


#include <stdint.h>


void _delay_us(uint16_t us);


void SysTick_init_us(int period);


void timer_delay_us(int us);


#endif