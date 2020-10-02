#include "can_driver.h"
#include "mcp2515_driver.h"
#include "interrupt.h"


void can_init(void) {
    mcp2515_init();
    mcp2515_set_mode(MODE_LOOPBACK);

    // enable interrupt generation for successful reception
    // mcp2515_bit_modify(MCP_CANINTE, MCP_RX0IF, 0xFF);
}


void can_trancieve(message_t* message) {
    // write to buffers
    mcp2515_write(MCP_TXB0SIDH, message->id / 8);
    mcp2515_write(MCP_TXB0SIDL, (message->id % 8) << 5);
    mcp2515_write(MCP_TXB0DLC, message->length);

    for (int m = 0; m < message->length; m++) {
        mcp2515_write(MCP_TXB0D0 + m, message->data[m]);
    }

    // send message
    mcp2515_request_to_send();
}


message_t can_recieve() {
    message_t message = {};

    // read from buffers, shift to combine high and low bits
    message.id = mcp2515_read(MCP_RXB0SIDL) >> 5;
    message.id += mcp2515_read(MCP_RXB0SIDH) << 3;
    message.length = mcp2515_read(MCP_RXB0DLC);

    for (int m = 0; m < message.length; m++) {
        message.data[m] = mcp2515_read(MCP_RXB0D0 + m);
    }

    return message;    
}


// void ISR(INT0_vect) {
//     message_t message = can_recieve();
// }