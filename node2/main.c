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


#define CAN_JOYSTICK 1


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
    enum FSM_STATE state = fsm_get_state();
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
                int score = game_get_score();
                uint8_t msb = (score & 0xFF00) >> 8;
                uint8_t lsb = (score & 0x00FF);

                CAN_MESSAGE m = {
                    .id = GAME_SCORE_ID,
                    .data_length = 2,
                    .data = {msb, lsb}
                };

                can_send(&m, 0);

                fsm_transition_to(IDLE);
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
        // PIOA->PIO_PER |= PIO_PA23;
        // PIOA->PIO_OER |= PIO_PA23;

        // music_play(GAME_OVER_THEME);

        // while (1) {
        //     // solenoid_shoot();
        //     // timer_delay_us(1000000);

        //     // slider_t slider_pos = {0, 0};
        //     // if (!slider_pos_recieve(&slider_pos)) {
        //     //     printf("(left, right) = (%d, %d) \r\n", slider_pos.left, slider_pos.right);
        //     // }
        //     // motor_run_slider(slider_pos.right);

        //     // servo_set_position();

        //     // game_count_score();


        //     // int button_status = 0;
        //     // if (!(buttons_status_recieve(&button_status))) {
        //     //     printf("button status = %d \r\n", button_status);
        //     // }

        //     // pos_t pos = {0,0};
        //     // if (!(joystick_pos_recieve(&pos))) {
        //     //     printf("(x,y) = (%d,%d) \r\n", pos.x, pos.y);
        //     // }
        // }

//     return 0;
}