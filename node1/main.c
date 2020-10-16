#include "uart.h"
#include "xmem.h"
#include "sram_test.h"
#include "adc.h"
#include "joystick.h"
#include "slider.h"
#include "oled.h"
#include "menu.h"
#include "interrupt.h"
#include "spi_driver.h"
#include "mcp2515_driver.h"
#include "can_driver.h"
#include <avr/interrupt.h>


#define F_CPU 4.9152E6
#include <util/delay.h> 


#define FOSC 4915200
#define BAUD 9600
#define UBRR FOSC / 16 / BAUD - 1

#define CAN_JOYSTICK 1


int main() {
    // XMEM
        xmem_init();
        
    // UART
        UART_init(UBRR);
        UART_link_printf();

    // SRAM
        SRAM_test();

    // ADC
        adc_init();

    // OLED
        oled_init();

    // Menu
        menu_init(); 

    // CAN
        can_init(MODE_NORMAL);

    // INTERRUPT
        interrupt_joystick_init();
        interrupt_oled_timer_init();
        interrupt_can_recieve_init();
        
    // Testing
        // message_t object_1 = {
        //     1,
        //     4,
        //     "heii"
        // };

        // message_t object_2 = {
        //     2,
        //     5,
        //     "yiiha"
        // };

        
        while (1){
            // can_transmit(&object_1);
            // _delay_ms(100);
            // can_transmit(&object_2);
            // _delay_ms(100);
            if (can_get_recieve_flag()) {
                message_t message = can_recieve();
                printf("message id: %d\n\r", message.id);
                printf("message data length: %d\n\r", message.length);
                printf("message data: %s\n\r", message.data);
            }
        }


    return 0;
}