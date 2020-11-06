#include "uart.h"
#include "sram.h"
#include "adc.h"
//#include "joystick.h"
//#include "slider.h"
//#include "buttons.h"
#include "user_input.h"
#include "oled.h"
#include "menu.h"
#include "interrupt.h"
#include "spi_driver.h"
#include "mcp2515_driver.h"
#include "can_driver.h"
#include "fsm.h"
#include <avr/interrupt.h>


#define F_CPU 4.9152E6
#include <util/delay.h> 


#define FOSC 4915200
#define BAUD 9600
#define UBRR FOSC / 16 / BAUD - 1

#define CAN_JOYSTICK 1


enum FSM_STATE fsm_current_state = INIT;


int main() {
    // UART
        UART_init(UBRR);
        UART_link_printf();

    // SRAM
        sram_init();
        sram_test();

    // ADC
        adc_init();

    // OLED
        oled_init();

    // Menu
        menu_init(); 

    // CAN
        can_init(MODE_NORMAL);

    // BUTTONS
        buttons_init();

    // INTERRUPT
        interrupt_joystick_init();
        interrupt_oled_timer_init();
        interrupt_can_recieve_init();

    // Testing
        DDRB |= (1 >> PB3);

        while (1){
            user_input_transmit();

            // if (can_get_recieve_flag()) {
            //     message_t message = can_recieve();
            //     printf("message id: %d\n\r", message.id);
            //     printf("message data length: %d\n\r", message.length);
            //     printf("message data: %s\n\r", message.data);
            // }

            // menu_run();
        }


    // switch (fsm_current_state) {
    //     case MENU:
    //         menu_run();
    //         break;
        
    //     case PLAYING:
    //         slider_send_pos_to_can();
    //         joystick_send_pos_to_can();
    //         buttons_send_status_to_can();
    //         break;

    //     default:
    //         break;
    // }


    return 0;
}


ISR(INT0_vect) {
    message_t message = can_recieve();

    if (message.id == 1) {

    }
    else if (message.id == 2) {
        
    }

    mcp2515_bit_modify(MCP_CANINTF, MCP_RX0IF | MCP_RX1IF, 0);
}

