#include "mcp2515_driver.h"
#include <avr/io.h> 

#define F_CPU 16000000
#include <util/delay.h> 


void clear_cs(void) {
    PORTB &= ~(1 << CAN_CS);
}


void set_cs(void) {
    PORTB |= (1 << CAN_CS);
}


void mcp2515_init() {
    spi_init();
    mcp2515_reset();

    _delay_ms(3);

    uint8_t value = mcp2515_read(MCP_CANSTAT);
    if ((value & MODE_MASK) != MODE_CONFIG) {
        printf("ERROR: MCP2515 not in configuration mode after reset. \r\n");
    }

    // set CAN bitrate
    uint8_t BRP = F_CPU / (2 * NUMBER_OF_TQ * BAUDRATE);

    mcp2515_write(MCP_CNF1, SJW4 | (BRP - 1));
    mcp2515_write(MCP_CNF2, BTLMODE | SAMPLE_3X | ((PS1 - 1) << 3) | (PROPAG - 1));
    mcp2515_write(MCP_CNF3, WAKFIL_DISABLE | (PS2 - 1));
}    


uint8_t mcp2515_read(uint8_t address) {
    uint8_t data;

    clear_cs();
    spi_write(MCP_READ);
    spi_write(address);
    data = spi_read();
    set_cs();

    return data;
}


uint8_t mcp2515_write(uint8_t address, uint8_t data) {
    clear_cs();
    spi_write(MCP_WRITE);
    spi_write(address);
    spi_write(data);
    set_cs();
}


void mcp2515_request_to_send() {
    clear_cs();
    spi_write(MCP_RTS_TX0);
    set_cs();
}


uint8_t mcp2515_read_status() {
    uint8_t status;

    clear_cs();
    spi_write(MCP_READ_STATUS);
    status = spi_read();
    set_cs();

    return status;
}


void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {
    clear_cs();
    spi_write(MCP_BITMOD);
    spi_write(address);
    spi_write(mask);
    spi_write(data);
    set_cs();
}


void mcp2515_reset() {
    clear_cs();
    spi_write(MCP_RESET);
    set_cs();
}


int mcp2515_set_mode(uint8_t mode) {
    // write mode
    mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, mode);

    // verify new mode
    uint8_t new_mode = mcp2515_read(MCP_CANSTAT);
    if ((new_mode & MODE_MASK) != mode) {
        printf("ERROR: failed to set mode. \r \n");
        return 1;
    }

    return 0;
}