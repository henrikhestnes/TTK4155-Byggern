#ifndef XMEM_H
#define XMEM_H

#include <avr/io.h>
#include <stdint.h>

void xmem_init(void);

void xmem_write(uint8_t data, uint16_t addr);

uint8_t xmem_read(uint16_t addr);

#endif