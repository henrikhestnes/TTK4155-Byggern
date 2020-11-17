#include "oled.h"
#include "sram.h"
#include "fonts.h"


static void oled_write_command(uint8_t command){
    volatile char* address = (char*) 0x1000;
    address[0] = command;
}


static void oled_write_data(uint8_t data){
    volatile char* address = (char*) 0x1200;
    address[0] = data;
}


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


void oled_print_char(char c) {
    if (' ' <= c && c <= '~') {
        for (int i = 0; i < FONT_LENGTH; i++) {
            uint8_t character = pgm_read_byte(&(font8[c - ASCII_OFFSET][i]));
            oled_write_data(character);
        }
    }
}


void oled_print_string(const char* string) {
    int i = 0;
    while (string[i] != '\0') {
        oled_print_char(string[i]);
        ++i;
    }
}


void oled_print_int(uint16_t number) {
    char string[6];
    sprintf(string, "%d", number);
    oled_print_string(string);
}


static void oled_print_heart(char filled) {
    if (filled) {
        oled_write_data(0b00001110);
        oled_write_data(0b00011111);
        oled_write_data(0b00111111);
        oled_write_data(0b01111111);
        oled_write_data(0b11111110);
        oled_write_data(0b01111111);
        oled_write_data(0b00111111);
        oled_write_data(0b00011111);
        oled_write_data(0b00001110);
    }
    else {
        oled_write_data(0b00001110);
        oled_write_data(0b00010001);
        oled_write_data(0b00100001);
        oled_write_data(0b01000001);
        oled_write_data(0b10000010);
        oled_write_data(0b01000001);
        oled_write_data(0b00100001);
        oled_write_data(0b00010001);
        oled_write_data(0b00001110);
    }
}


void oled_print_lives(int lives_left, int max_lives) {
    for (int i = 0; i < lives_left; ++i) {
        oled_print_heart(1);
        oled_print_char(' ');
    }
    for (int i = 0; i < (max_lives - lives_left); ++i) {
        oled_print_heart(0);
        oled_print_char(' ');
    }
}


void oled_print_playing_screen(int lives_left, int max_lives) {
    oled_set_pos(1, 8);
    oled_print_string("Lives left:");
    oled_set_pos(3, 30);
    oled_print_lives(lives_left, max_lives);
    oled_set_pos(5, 8);
    oled_print_string("Quit the game");
    oled_set_pos(6, 8);
    oled_print_string("by pushing the");
    oled_set_pos(7, 8);
    oled_print_string("left button");
}


void oled_print_quit_screen() {
    oled_clear();

    oled_set_pos(1, 8);
    oled_print_string("GAME QUIT!");
    oled_set_pos(3, 8);
    oled_print_string("Return to main");
    oled_set_pos(4, 8);
    oled_print_string("menu by pushing");
    oled_set_pos(5, 8);
    oled_print_string("the left button");
}


void oled_print_game_over_screen(int score, char new_highscore) {
    oled_clear();

    oled_set_pos(1, 8);
    if (new_highscore) {
        oled_print_string("NEW HIGHSCORE!!");
    }
    else
    {
        oled_print_string("GAME OVER!");
    }
    
    oled_set_pos(2, 8);
    oled_print_string("Score: ");
    oled_print_int(score);
    oled_set_pos(4, 8);
    oled_print_string("Return to main");
    oled_set_pos(5, 8);
    oled_print_string("menu by pushing");
    oled_set_pos(6, 8);
    oled_print_string("the left button");
}


void oled_print_from_sram() {
    for (uint8_t line = 0; line < NUMBER_OF_PAGES; ++line){
        oled_set_pos(line, 0);
        for (uint8_t col = 0; col < NUMBER_OF_COLUMNS; ++col){
            oled_write_data(sram_read(line*NUMBER_OF_COLUMNS + col));
        }
    }
}


void oled_set_brightness(uint8_t brightness) {
    oled_write_command(0x81);
    oled_write_command(brightness);
}