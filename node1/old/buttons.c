#include "buttons.h"
#include "can_driver.h"
#include <avr/io.h>


#define RIGHT_BUTTON_PIN PB1
#define LEFT_BUTTON_PIN PB2


void buttons_init(void) {
    // set button pins to input
    DDRB &= ~(1 << RIGHT_BUTTON_PIN) & ~(1 << LEFT_BUTTON_PIN);
}


button_t button_status_read() {
    button_t status = {0, 0};

    status.right = (PINB & (1 << RIGHT_BUTTON_PIN)) >> RIGHT_BUTTON_PIN;
    status.left = (PINB & (1 << LEFT_BUTTON_PIN)) >> LEFT_BUTTON_PIN;

    return status;
}


void buttons_send_status_to_can(void) {
    button_t status = button_status_read();

    message_t buttons_message = {
        .id = 4,
        .length = 2,
        .data = {status.left, status.right}
    };

    can_transmit(&buttons_message);
}