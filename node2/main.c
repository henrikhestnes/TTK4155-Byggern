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
            1,
            4,
            "heii"
        };

        while (1) {
            // char can_sr = CAN0->CAN_SR; 
            // CAN_MESSAGE message = {
            //     0,
            //     0,
            //     ""
            // };

            // if(can_sr & CAN_SR_MB1) {
			//     can_receive(&message, 1);
		    // }
            // else if(can_sr & CAN_SR_MB2) {
            //     can_receive(&message, 2);
            // }

            // printf("message id: %d\n\r", message.id);
            // printf("message data length: %d\n\r", message.data_length);
            // printf("message data: %s\n\r", message.data); 
        }

}