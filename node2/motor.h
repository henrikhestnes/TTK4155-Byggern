/**
 * @file 
 * @brief Module for motor functionality
 */


#ifndef NODE2_MOTOR_H
#define NODE2_MOTOR_H


#include "microbit.h"
#include <stdint.h>


#define DIR         PIO_PD10
#define EN          PIO_PD9
#define SEL         PIO_PD2
#define NOT_RST     PIO_PD1
#define NOT_OE      PIO_PD0

#define DO0_IDX     1

#define MOTOR_TIMER_FREQ    50


/**
 * @brief Initiates the motor by initiating the DAC, and enabling
 * the pins and clock used by the motor.
 */
void motor_init(void);


/**
 * @brief Disables the motor. Sets the speed to 0.
 */
void motor_disable(void);


/**
 * @brief Enables the motor. Resets the PID errors.
 */
void motor_enable(void);


/**
 * @brief Reads the motor encoder.
 * 
 * @return The read encoder value.
 */
int motor_read_encoder(void);


/**
 * @brief Uses the PID controller to drive the motor, by comparing
 * the encoder measurement to the input @c reference. 
 * 
 * @param reference The reference value input to the PID controller.
 */
void motor_run_slider(int reference);


/**
 * @brief Drives the motor speed, by comparing
 * the encoder measurement to the input @c reference. 
 * 
 * @param joystick_value The reference value joystick position.
 */
void motor_run_joystick(int joystick_value);



/**
 * @brief Drives the motor by reading the accelerometer output
 * from the microbit.
 * 
 * @param direction The direction the microbit is tilted. Varies between left, 
 * right, and neutral.
 */
void motor_run_microbit(ACC_DIR direction); 


/**
 * @brief Set the motor speed when controlling with the microbit.
 * 
 * @param speed Desired motor speed.
 */
void motor_set_microbit_speed(uint16_t speed);


#endif