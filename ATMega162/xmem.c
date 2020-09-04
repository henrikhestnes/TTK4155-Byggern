#include "xmem.h"
#define BASE_ADDRESS_XMEM 0x1800

void xmem_init(void){
    MCUCR |= (1 << SRE);
    SFIOR |= (1 << XMM2);
}

void xmem_write(uint8_t data, uint16_t addr){
    volatile char *ext_mem = (char *) BASE_ADDRESS_XMEM;
    ext_mem[addr] = data;
}

uint8_t xmem_read(uint16_t addr){
    volatile char *ext_mem = (char *) BASE_ADDRESS_XMEM;
    uint8_t ret_val = ext_mem[addr];
    return ret_val;
}                    