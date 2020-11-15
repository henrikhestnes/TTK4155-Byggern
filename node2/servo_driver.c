#include "servo_driver.h"
#include "pwm.h"


#define PERIOD              20E-3
#define MIN_DUTY_CYCLE      1.0E-3 / PERIOD
#define MAX_DUTY_CYCLE      2.0E-3 / PERIOD
#define X_MIN               -100
#define X_MAX               100

#define GAIN                (MAX_DUTY_CYCLE - MIN_DUTY_CYCLE) / (X_MIN - X_MAX)
#define OFFSET              MAX_DUTY_CYCLE - X_MIN * GAIN


void servo_init() {
    pwm_init();
    servo_set_position(0);
}


void servo_set_position(int x) {
    float duty_cycle = GAIN * x + OFFSET;
    pwm_set_duty_cycle(duty_cycle, CHANNEL_PIN45);
}