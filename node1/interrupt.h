#ifndef INTERRUPT_H
#define INTERRUPT_H


/**
 * @brief Initiates the interrupt @c INT1, triggered 
 * on the falling edge of pin @c PD3.
 */
void interrupt_joystick_init();


/**
 * @brief Initiates a timer interrupt using @c TIMER1, 
 * which is triggered with a frequency of 60 Hz.
 */
void interrupt_oled_timer_init();


/**
 * @brief Initiates the interrupt @c INT0, triggered 
 * on the falling edge of pin @c PD2.
 */
void interrupt_can_recieve_init();


void interrupt_enable_oled_timer();


void interrupt_disable_oled_timer();


#endif