#ifndef OLED_H
#define OLED_H


#include <stdint.h>


void oled_init();


void oled_write_command(uint8_t command);


void oled_write_data(uint8_t data);


void oled_set_pos(int page, int col);


void oled_clear(void); 


void oled_draw_arrow(void);


#endif