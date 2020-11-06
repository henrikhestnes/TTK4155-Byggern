#ifndef CAN_H
#define CAN_H


#include <stdint.h>


/**
 * @brief Data structure to be used for messages sent
 * using the CAN interface.
 */
typedef struct {
    uint16_t id;
    char length;
    char data[8];
} message_t;


typedef enum {
    USER_INPUT = 1
} CAN_MESSAGE_ID;


/**
 * @brief Initiates the CAN interface, by setting the MCP2515
 * to the desired mode, and enabling interrupt on message reception.
 * 
 * @param mode Mode MCP2515 is set to.
 * 
 * @return 0 on success, 1 if the MCP2515 actions cause error. 
 */
int can_init(uint8_t mode);


/**
 * @brief Transmits a message of type @c message_t using the 
 * CAN interface. Uses transmit buffer @c TXB0.
 * 
 * @param message Pointer to the message being sent.
 */
void can_transmit(message_t* message);


/**
 * @brief Recieves a message of type @c message_t using the 
 * CAN interface. Uses recieve buffer @c RXB0 or @c RBX1, depending
 * on the interrupt flag register of the MCP2515.
 */
message_t can_recieve();


/**
 * @brief Returns the flag signaling a successfully recieved message.
 * 
 * @return 0 if there are no pending recieved messages, 1 if there is 
 * a recieved message to be read.
 */
char can_get_recieved_flag();


#endif