#ifndef PWM_H
#define PWM_H


#define CHANNEL_PIN44 6
#define CHANNEL_PIN45 5


void pwm_init(void);


void pwm_set_duty_cycle(float duty_cycle, unsigned int channel);


#endif