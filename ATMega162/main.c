#include "jtag.h"
#include "uart.h"
#include "xmem.h"
#include "sram_test.h"
#include "adc.h"
#include "joystick.h"
#include "slider.h"
#include "oled.h"


#define FOSC 4915200
#define BAUD 9600
#define UBRR FOSC / 16 / BAUD - 1


int main() {
    xmem_init();
    // UART_init(UBRR);
    // UART_link_printf();

    oled_init();
    //SRAM_test();

    //adc_init();
    //volatile char* ext_mem = (char*) 0x1000;

    oled_command(0xA5);
    // test reading from adc
    while (1) {

        
        
        //ext_mem[0]=0xA5;
        
        // pos_t pos = joystick_pos_read();
        // dir_t dir = joystick_get_dir(pos);
        // slider_t slider = slider_pos_read();
        //JTAG_test_PA0();

        // printf("(x,y) = (%d, %d). Direction = %d (LS,RS)=(%d,%d)\r\n", pos.x, pos.y, dir, slider.left, slider.right);
        //_delay_ms(500);
        
    }

    return 0;
}