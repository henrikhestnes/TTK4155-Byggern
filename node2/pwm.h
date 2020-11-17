/**
 * @file 
 * @brief Module for PWM-signal functionality
 */


#ifndef PWM_H
#define PWM_H


#define CHANNEL_PIN44 6
#define CHANNEL_PIN45 5

/**
 * @brief Initializes PWM-signal, pin 44
 * set to a period of 20 ms to use for setting servo
 * position, pin 45 to initially not have a pulse 
 * to play music later
 */
void pwm_init(void);


/**
 * @brief Sets duty-cycle of PWM-signal
 * 
 * @param duty_cycle Desired duty-cycle
 * @param channel Which channel to set duty-cycle
 */
void pwm_set_duty_cycle(float duty_cycle, unsigned int channel);


/**
 * @brief Sets frequency of PWM-signal
 * 
 * @param freq Desired frequence
 * @param channel Which channel to set frequency
 */
void pwm_set_frequency(int freq, unsigned int channel);


#endif