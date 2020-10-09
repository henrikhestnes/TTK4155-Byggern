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


#define FOSC 4915200
#define BAUD 9600
#define UBRR FOSC / 16 / BAUD - 1


int main() {
    // INTERRUPT
        cli();
        interrupt_joystick_init();
        interrupt_oled_timer_init();

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
        // menu_init(); 

    // CAN
        can_init();
        message_t message = {
            1,
            6,
            "heiiii"
        };

        can_trancieve(&message);
        message_t recieved = can_recieve();
        printf("id: %d\r\n", recieved.id);
        printf("length: %d\r\n", recieved.length);
        printf("data: %s\r\n", recieved.data);

    // Enable interrupts
        sei();
        
    // Testing
        // while (1){

        //     // menu_run();
        // }
        

    return 0;
}