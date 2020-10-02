#ifndef CAN_H
#define CAN_H


#include <stdint.h>


typedef struct {
    unsigned int id;
    uint8_t length;
    uint8_t data[8];
} message_t;


void can_init(void);


void can_trancieve(message_t* message);


message_t can_recieve();


#endif