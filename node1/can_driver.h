#ifndef CAN_H
#define CAN_H


#include <stdint.h>


/**
 * @brief Data structure to be used for messages sent
 * using the CAN interface.
 */
typedef struct {
    uint16_t id;
    char data_length;
    char data[8];
} message_t;


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
void can_send(message_t* message);


/**
 * @brief Recieves a message of type @c message_t using the
 * CAN interface. Uses recieve buffer @c RXB0 or @c RBX1, depending
 * on the interrupt flag register of the MCP2515.
 * 
 * @param message Pointer to the message being recieved to.
 * 
 * @return 0 on success, 1 on failure.
 */
int can_recieve(message_t* message);


#endif
