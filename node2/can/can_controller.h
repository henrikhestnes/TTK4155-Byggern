/*
 * can_controller.h
 *
 * Author: Gustav O. Often and Eivind H. J�lsgard
 *
 * For use in TTK4155 Embedded and Industrial Computer Systems Design
 * NTNU - Norwegian University of Science and Technology
 *
 */ 


#ifndef CAN_CONTROLLER_H_
#define CAN_CONTROLLER_H_


#include <stdint.h>


// baudrate of 250 kbits/s, sjw = 4 TQ, propag = 2 TQ, phase1 = 6 TQ, phase2 = 7 TQ
#define ATSAM_CAN_BR 0x00143156
// #define ATSAM_CAN_BR 0x00290165


typedef struct can_message_t
{
	uint16_t id;
	char data_length;
	char data[8];
} CAN_MESSAGE;


uint8_t can_init_def_tx_rx_mb(uint32_t can_br);
uint8_t can_init(uint32_t can_br, uint8_t num_tx_mb, uint8_t num_rx_mb);

uint8_t can_send(CAN_MESSAGE* can_msg, uint8_t mailbox_id);
uint8_t can_receive(CAN_MESSAGE* can_msg, uint8_t mailbox_id);

#endif /* CAN_CONTROLLER_H_ */