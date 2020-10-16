#ifndef CAN_H
#define CAN_H


#include <stdint.h>


typedef struct {
    uint16_t id;
    char length;
    char data[8];
} message_t;


void can_init(uint8_t mode);


void can_transmit(message_t* message);


message_t can_recieve();


char can_get_recieve_flag();


#endif