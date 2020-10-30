#ifndef MOTOR_H
#define MOTOR_H


#define DIR         PIO_PD10
#define EN          PIO_PD9
#define SEL         PIO_PD2
#define NOT_RST     PIO_PD1
#define NOT_OE      PIO_PD0

#define DO0         PIO_PC1
#define DO1         PIO_PC2
#define DO2         PIO_PC3
#define DO3         PIO_PC4
#define DO4         PIO_PC5
#define DO5         PIO_PC6
#define DO6         PIO_PC7
#define DO7         PIO_PC8



void motor_init(void);


void motor_set_speed(void);


void motor_read_encoder(void);


#endif