#include "oled.h"


void oled_init(){
    oled_command(0xae);
    oled_command(0xa1);
    oled_command(0xda);
    oled_command(0x12);
    oled_command(0xc8);
    oled_command(0xa8);
    oled_command(0x3f);
    oled_command(0xd5);
    oled_command(0x80);
    oled_command(0x81);
    oled_command(0x50);
    oled_command(0xd9);
    oled_command(0x21);
    oled_command(0x20);
    oled_command(0x02);
    oled_command(0xdb);
    oled_command(0x30);
    oled_command(0xad);
    oled_command(0x00);
    oled_command(0xa4);
    oled_command(0xa6);
    oled_command(0xaf);
}

void oled_command(uint8_t command){
    volatile char* address = (char*) 0x1000;
    address[0]=command;
}

void oled_data(uint8_t data){
    volatile char* address = (char*) 0x1200;
    address[0]=data;
}
