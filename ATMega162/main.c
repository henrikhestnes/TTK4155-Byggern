#include "jtag.h"
#include "uart.h"
#include "xmem.h"
#include "sram_test.h"
#include "adc.h"
#include "joystick.h"
#include "slider.h"
#include "oled.h"
#include "menu.h"
#include "interrupt.h"
#include <avr/interrupt.h>


#define FOSC 4915200
#define BAUD 9600
#define UBRR FOSC / 16 / BAUD - 1


int main() {
    // XMEM
        xmem_init();

    // INTERRUPT
        cli();
        interrupt_joystick_init();
        interrupt_oled_timer_init();
        sei();
        
    // UART
        UART_init(UBRR);
        UART_link_printf();

    // SRAM
        SRAM_test();

    // ADC
        adc_init();

    // OLED
        oled_init();
        oled_clear();

    // Menu
        // menu_init();    

    // ADC test
        while (1) {
            pos_t pos = joystick_pos_read();
            dir_t dir = joystick_get_dir();
            slider_t slider = slider_pos_read();
            printf("(x,y) = (%d, %d). Direction = %d (LS,RS)=(%d,%d)\r\n", pos.x, pos.y, dir, slider.left, slider.right);
            _delay_ms(500);

            // menu_run();
        }

    return 0;
}