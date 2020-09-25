#include "oled.h"
#include "fonts.h"


#define ASCII_OFFSET 32


const int FONT_LENGTH[3] = {8, 5, 4};


void oled_init(){
    oled_write_command(0xae);
    oled_write_command(0xa1);
    oled_write_command(0xda);
    oled_write_command(0x12);
    oled_write_command(0xc8);
    oled_write_command(0xa8);
    oled_write_command(0x3f);
    oled_write_command(0xd5);
    oled_write_command(0x80);
    oled_write_command(0x81);
    oled_write_command(0x50);
    oled_write_command(0xd9);
    oled_write_command(0x21);
    oled_write_command(0x20);
    oled_write_command(0x02);
    oled_write_command(0xdb);
    oled_write_command(0x30);
    oled_write_command(0xad);
    oled_write_command(0x00);
    oled_write_command(0xa4);
    oled_write_command(0xa6);
    oled_write_command(0xaf);
    oled_clear();
}


void oled_write_command(uint8_t command){
    volatile char* address = (char*) 0x1000;
    address[0] = command;
}


void oled_write_data(uint8_t data){
    volatile char* address = (char*) 0x1200;
    address[0] = data;
}


void oled_go_to_line(int line){
    if (0 <= line && line <=7) {
        oled_write_command(0xB0 + line);
    }
}


void oled_go_to_col(int col){
    if (0 <= col && col <= 127) {
        // set lower 4 bits
        oled_write_command(0x00 + (col & 0x0F));

        // set upper 4 bits
        oled_write_command(0x10 + ((col & 0xF0) >> 4));
    }
}


void oled_set_pos(int line, int col) {
    oled_go_to_line(line);
    oled_go_to_col(col);
}


void oled_clear() {
    for (int page = 0; page <= 7; page++) {
        oled_set_pos(page, 0);
        for (int col = 0; col <= 127; col++) {
            oled_write_data(0);
        }
    }
}


void oled_print_char(char c, font_type_t type) {
    if (' ' <= c && c <= '~') {
        switch (type) {
            case LARGE:
                for (int i = 0; i < FONT_LENGTH[LARGE]; i++) {
                    uint8_t character = pgm_read_byte(&(font8[c - ASCII_OFFSET][i]));
                    oled_write_data(character);
                }
                break;

            case NORMAL:
                for (int i = 0; i < FONT_LENGTH[NORMAL]; i++) {
                    uint8_t character = pgm_read_byte(&(font5[c - ASCII_OFFSET][i]));
                    oled_write_data(character);
                }
                break;

            case SMALL:
                for (int i = 0; i < FONT_LENGTH[SMALL]; i++) {
                    uint8_t character = pgm_read_byte(&(font4[c - ASCII_OFFSET][i]));
                    oled_write_data(character);
                }
                break;

            default:
                break;
        }
    }  
}


void oled_print_string(const char* string, font_type_t type) {
    int i = 0;
    while (string[i] != '\0') {
        oled_print_char(string[i], type);
        ++i;
    }
}


void oled_draw_arrow() {
    oled_write_data(0b00011000);
    oled_write_data(0b00011000);
    oled_write_data(0b01111110);
    oled_write_data(0b00111100);
    oled_write_data(0b00011000);
}

