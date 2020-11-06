#include "servo_driver.h"
#include "pwm.h"


#define PERIOD              20E-3
#define MIN_DUTY_CYCLE      0.9E-3 / PERIOD
#define MAX_DUTY_CYCLE      2.1E-3 / PERIOD
#define X_MIN               -100
#define X_MAX               100

#define GAIN                (MAX_DUTY_CYCLE - MIN_DUTY_CYCLE) / (X_MIN - X_MAX)
#define OFFSET              MAX_DUTY_CYCLE - X_MIN * GAIN


void servo_init() {
    pwm_init();
}


void servo_set_position(int x) {
    float duty_cycle = GAIN * x + OFFSET;
    pwm_set_duty_cycle(duty_cycle, CHANNEL_PIN45);
}