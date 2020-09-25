#ifndef OLED_H
#define OLED_H


#include <stdint.h>


typedef enum {
    LARGE,
    NORMAL,
    SMALL
} font_type_t;


void oled_init();


void oled_write_command(uint8_t command);


void oled_write_data(uint8_t data);


void oled_go_to_line(int line);


void oled_go_to_col(int col);


void oled_set_pos(int line, int col);


void oled_clear(void); 


void oled_print_char(char c, font_type_t type);


void oled_print_string(const char* string, font_type_t type);


void oled_print_inverted_char(char c, font_type_t type);


void oled_print_inverted_string(const char* string, font_type_t type);


void oled_draw_arrow(void);



#endif