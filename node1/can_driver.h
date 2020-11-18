/**
 * @file
 * @brief Module for sending and receiving data over the CAN bus. 
 */


#ifndef NODE1_CAN_H
#define NODE1_CAN_H


#include "mcp2515_driver.h"
#include "../common/can.h"
#include <stdint.h>


/**
 * @brief Data structure to be used for messages sent
 * using the CAN interface.
 */



/**
 * @brief Initiates the CAN interface, by setting the MCP2515
 * to the desired mode, and enabling interrupt on message reception.
 *
 * @param mode Mode MCP2515 is being set to.
 */
void can_init(uint8_t mode);


/**
 * @brief Transmits a message of type @c CAN_MESSAGE using the
 * CAN interface. Uses transmit buffer @c TXB0.
 *
 * @param message Pointer to the message being sent.
 */
void can_send(CAN_MESSAGE* message);


/**
 * @brief Recieves a message of type @c CAN_MESSAGE using the
 * CAN interface. Uses recieve buffer @c RXB0 or @c RBX1, depending
 * on the interrupt flag register of the MCP2515.
 * 
 * @param message Pointer to the message being recieved to.
 * 
 * @return 0 on success, 1 on failure.
 */
int can_recieve(CAN_MESSAGE* message);


#endif
