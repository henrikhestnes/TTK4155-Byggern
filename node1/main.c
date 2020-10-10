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
        menu_init(); 

    // CAN
        can_init();

    // Enable interrupts
        sei();
        
    // Testing
        message_t object = {
            7,
            6,
            "heiiii"
        };

        // can_trancieve(&object);
        // can_trancieve(&object);
        // printf("id: %d\r\n", object.id);
        // printf("length: %d\r\n", object.length);
        // printf("data: %s\r\n", object.data);

        while (1){
            menu_run();
        }
        

    return 0;
}