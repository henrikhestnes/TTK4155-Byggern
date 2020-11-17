/**
 * @file 
 * @brief Module for SysTick timer delay
 */


#ifndef TIMER_H
#define TIMER_H


#include <stdint.h>

/**
 * @brief Delays execution of code using SysTicks
 * 
 * @param us Length of delay in us 
 */
void _delay_us(uint16_t us);


/**
 * @brief Delays execution of code using SysTicks
 * 
 * @param ms Length of delay in ms 
 */
void _delay_ms(uint16_t ms);


#endif