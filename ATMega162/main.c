#include "jtag.h"
#include "uart.h"
#include "xmem.h"
#include "sram_test.h"
#include "adc.h"
#include "joystick.h"
#include "slider.h"
#include "oled.h"
#include "menu.h"


#define FOSC 4915200
#define BAUD 9600
#define UBRR FOSC / 16 / BAUD - 1


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
        oled_set_pos(1, 0);
        oled_write_string("Lasse er lok", LARGE);

        _delay_ms(1000);

        oled_set_pos(1, 0);
        oled_write_string("Magnus er sot", LARGE);
    
    // Menu
        oled_clear();
        menu_init();
        menu_print(LARGE);

    // ADC test
        while (1) {
            // pos_t pos = joystick_pos_read();
            // dir_t dir = joystick_get_dir(pos);
            // slider_t slider = slider_pos_read();

            // printf("(x,y) = (%d, %d). Direction = %d (LS,RS)=(%d,%d)\r\n", pos.x, pos.y, dir, slider.left, slider.right);
            // _delay_ms(500);
            
        }

    return 0;
}