#ifndef SRAM_H
#define SRAM_H


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * @brief Initiates the external memory by enabling 
 * the required pins on the MCU.
 */
void sram_init(void);


/**
 * @brief Writes @p data to the address @p addr, defined
 * as offset from @c 0x1000.
 * 
 * @param data 8-bit value to be written to the external memory.
 * @param addr Offset from the base address @c 0x1800 in the external
 * memery address space.
 */
void sram_write(uint8_t data, uint16_t addr);


/**
 * @brief Reads from the address @p addr, defined as offset
 * from @c 0x1000.
 * 
 * @param addr Offset from the base address @c 0x1800 in the external
 * memery address space.
 * 
 * @return The 8-bit data at the address given på @p addr.
 */
uint8_t sram_read(uint16_t addr);


void sram_test(void);


#endif