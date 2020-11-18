/**
 * @file 
 * @brief Main program of node 2
 */


#include "uart_and_printf/uart.h"
#include "uart_and_printf/printf-stdarg.h"
#include "can/can_controller.h"
#include "sam/sam3x/include/sam.h"
#include "game.h"
#include "fsm.h"


int main()
{
    SystemInit();
    WDT->WDT_MR = WDT_MR_WDDIS; // Disable Watchdog Timer

    configure_uart();
    can_init_def_tx_rx_mb(ATSAM_CAN_BR);
    game_init();

    fsm_transition_to(STATE_MENU);
    while (1);

    return 0;
}


void TC0_Handler() {
    game_run();

    // clear interrupt flag
    TC0->TC_CHANNEL[0].TC_SR;
}