/**
 * @file 
 * @brief Main program of node 2
 */


// #include <stdio.h>
// #include <stdarg.h>
// #include <unistd.h>
#include "uart_and_printf/uart.h"
#include "uart_and_printf/printf-stdarg.h"
#include "can/can_controller.h"
#include "sam/sam3x/include/sam.h"

#include "game.h"
#include "fsm.h"


int main()
{
    SystemInit();
    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    configure_uart();
    can_init_def_tx_rx_mb(ATSAM_CAN_BR);
    //can_init(ATSAM_CAN_BR, 1, 3);
    game_init();

    fsm_transition_to(MENU);
    while (1);

    return 0;
}