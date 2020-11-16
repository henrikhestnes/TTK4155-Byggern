#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include "uart_and_printf/uart.h"
#include "uart_and_printf/printf-stdarg.h"
#include "can/can_controller.h"
#include "can/can_interrupt.h"
#include "sam/sam3x/include/sam.h"
#include "../common/can_id.h"


#include "led.h"
#include "pwm.h"
#include "servo_driver.h"
#include "adc.h"
#include "dac.h"
#include "game.h"
#include "motor.h"
#include "timer.h"
#include "solenoid.h"
#include "fsm.h"
#include "music_driver.h"


int main()
{
    SystemInit();

    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    // UART
        configure_uart();
        printf("Hello World\n\r");

    // CAN
        can_init(ATSAM_CAN_BR, 1, 3);

    // ADC
        adc_init();

    // SERVO
        servo_init();

    // MOTOR
        motor_init();

    // GAME
        game_init();

    // SOLENOID
        solenoid_init();



    
    fsm_transition_to(MENU);
    while (1) {
    FSM_STATE state = fsm_get_state();
        switch(state) {
            case MENU:
            {
                break;
            }
            case PLAYING:
            {
                // count score and send to can
                break;
            }
            case GAME_OVER:
            {   
                break;
            }
            case IDLE:
            {
                break;
            }
            default:
                break;
        }
    }


    // TESTING
        // game_timer_enable();
        // motor_enable();

        // while (1) {
            
        // }

    return 0;
}