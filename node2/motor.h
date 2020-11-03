#ifndef MOTOR_H
#define MOTOR_H


#include <stdint.h>


#define DIR         PIO_PD10
#define EN          PIO_PD9
#define SEL         PIO_PD2
#define NOT_RST     PIO_PD1
#define NOT_OE      PIO_PD0

#define DO0_IDX     1


void motor_init(void);


void motor_run_slider(void);


int motor_read_encoder(void);


#endif