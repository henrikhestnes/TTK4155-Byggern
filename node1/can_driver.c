#include "can_driver.h"
#include <avr/io.h>


static char recieved_flag = 0;


static void interrupt_can_recieve_init() {
    // set INT0 as input
    DDRD &= ~(1 << PD2);

    // enable INT0 interrupt vector
    GICR |= (1 << INT0);

    // interrupt on falling edge
    MCUCR |= (1 << ISC01);
    MCUCR &= ~(1 << ISC00);
}


void can_init(uint8_t mode) {
    mcp2515_init();
    mcp2515_set_mode(mode);

    // recieve all messages
    mcp2515_write(MCP_RXB0CTRL, MCP_RXM1 | MCP_RXM0);

    // enable interrupt generation for successful reception
    mcp2515_bit_modify(MCP_CANINTE, MCP_RX1IF | MCP_RX0IF, 0xFF);
    interrupt_can_recieve_init();
}


void can_send(CAN_MESSAGE* message) {
    // write to buffers
    mcp2515_write(MCP_TXB0SIDH, message->id / 8);
    mcp2515_write(MCP_TXB0SIDL, (message->id % 8) << 5);
    mcp2515_write(MCP_TXB0DLC, message->data_length);

    for (int m = 0; m < message->data_length; m++) {
        mcp2515_write(MCP_TXB0D0 + m, message->data[m]);
    }

    mcp2515_request_to_send();
}


int can_recieve(CAN_MESSAGE* message) {
    if (mcp2515_read(MCP_CANINTF) & MCP_RX0IF) {
        // read from buffers, shift to combine high and low bits
        uint8_t id_low_bits = mcp2515_read(MCP_RXB0SIDL);
        uint8_t id_high_bits = mcp2515_read(MCP_RXB0SIDH);
        message->id = (id_low_bits >> 5) + (id_high_bits << 3);

        message->data_length = mcp2515_read(MCP_RXB0DLC);

        for (int m = 0; m < message->data_length; m++) {
            message->data[m] = mcp2515_read(MCP_RXB0D0 + m);
        }
    }

    else if (mcp2515_read(MCP_CANINTF) & MCP_RX1IF) {
        // read from buffers, shift to combine high and low bits
        uint8_t id_low_bits = mcp2515_read(MCP_RXB1SIDL);
        uint8_t id_high_bits = mcp2515_read(MCP_RXB1SIDH);
        message->id = (id_low_bits >> 5) + (id_high_bits << 3);

        message->data_length = mcp2515_read(MCP_RXB1DLC);

        for (int m = 0; m < message->data_length; m++) {
            message->data[m] = mcp2515_read(MCP_RXB1D0 + m);
        }
    }  

    else {
        return 1;
    }

    return 0;
}    