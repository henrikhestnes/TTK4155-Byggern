#include <stdio.h>
#include <stdarg.h>
#include "uart_and_printf/uart.h"
#include "uart_and_printf/printf-stdarg.h"
#include "can/can_controller.h"
#include "can/can_interrupt.h"


#define CAN_JOYSTICK 1

#include "sam.h"
#include "led.h"

#include <unistd.h>


int main()
{
    SystemInit();

    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    // UART
        configure_uart();
        printf("Hello World\n\r");

    // CAN
        can_init_def_tx_rx_mb(ATSAM_CAN_BR);


    // TESTING
        CAN_MESSAGE object = {
            3,
            4,
            "heii"
        };

        while (1) {
            printf("transmit buffer 0: %d \r\n", can_send(&object, 0));
        }

}