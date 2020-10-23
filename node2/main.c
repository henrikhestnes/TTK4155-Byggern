#include <stdio.h>
#include <stdarg.h>
#include "uart_and_printf/uart.h"
#include "uart_and_printf/printf-stdarg.h"
#include "can/can_controller.h"
#include "can/can_interrupt.h"


#include "sam.h"
#include "led.h"
#include "joystick.h"
#include "pwm.h"


#include <unistd.h>


#define CAN_JOYSTICK 1


int main()
{
    SystemInit();

    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    // UART
        configure_uart();
        printf("Hello World\n\r");

    // CAN
        can_init_def_tx_rx_mb(ATSAM_CAN_BR);

    // PWM
        pwm_init();


    // TESTING
        CAN_MESSAGE pos_message;

        while (1) {
            pos_t pos = joystick_pos_recieve();
            printf("(x,y) = (%d,%d) \r\n", pos.x, pos.y);
            
        }

}