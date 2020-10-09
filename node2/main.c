#include <stdio.h>
#include <stdarg.h>
#include "uart_and_printf/uart.h"
#include "uart_and_printf/printf-stdarg.h"
#include "can/can_controller.h"
#include "can/can_interrupt.h"


#include "sam.h"
#include "led.h"



int main()
{
    SystemInit();

    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    configure_uart();
    printf("Hello World\n\r");

    uint32_t can_br = can_get_br();
    can_init_def_tx_rx_mb(can_br)

    while (1)
    {
        led_set();
    }
    
}