#ifndef OLED_H
#define OLED_H

#include <stdint.h>

void oled_init();

void oled_command(uint8_t command);

void oled_data(uint8_t data);

#endif