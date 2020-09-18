#include "jtag.h"
#include "uart.h"
#include "xmem.h"
#include "sram_test.h"
#include "adc.h"
#include "joystick.h"
#include "slider.h"


#define FOSC 4915200
#define BAUD 9600
#define UBRR FOSC / 16 / BAUD - 1


int main() {
    xmem_init();
    UART_init(UBRR);
    UART_link_printf();

    // SRAM_test();

    adc_init();

    // test reading from adc
    while (1) {
        pos_t pos = joystick_pos_read();
        dir_t dir = joystick_get_dir(pos);
        slider_t slider = slider_pos_read();

        printf("(x,y) = (%d, %d). Direction = %d (LS,RS)=(%d,%d)\r\n", pos.x, pos.y, dir, slider.left, slider.right);
        _delay_ms(500);
    }

    return 0;
}