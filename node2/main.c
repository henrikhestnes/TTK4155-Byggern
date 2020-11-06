#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include "uart_and_printf/uart.h"
#include "uart_and_printf/printf-stdarg.h"
#include "can/can_controller.h"
#include "can/can_interrupt.h"
#include "sam/sam3x/include/sam.h"


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

#define CAN_JOYSTICK 1


enum FSM_STATE fsm_current_state = INIT;


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

    // TIMER
        timer_init();

    // SOLENOID
        solenoid_init();


    fsm_current_state = MENU;
    while (1) {
        switch(fsm_current_state) {
            case MENU:
            {
                break;
            }
            case PLAYING:
            {
                // count score and send to can
                break;
            }
            case POSTGAME:
            {
                dac_write(0);
                break;
            }
            default:
                break;
        }
    }


    // TESTING
        // PIOA->PIO_PER |= PIO_PA23;
        // PIOA->PIO_OER |= PIO_PA23;

        // while (1) {
        //     solenoid_shoot();
        //     timer_delay_us(1000000);

        //     slider_t slider_pos = {0, 0};
        //     if (!slider_pos_recieve(&slider_pos)) {
        //         printf("(left, right) = (%d, %d) \r\n", slider_pos.left, slider_pos.right);
        //     }
        //     motor_run_slider(slider_pos.right);

        //     servo_set_position();

        //     game_count_score();


        //     int button_status = 0;
        //     if (!(buttons_status_recieve(&button_status))) {
        //         printf("button status = %d \r\n", button_status);
        //     }

        //     pos_t pos = {0,0};
        //     if (!(joystick_pos_recieve(&pos))) {
        //         printf("(x,y) = (%d,%d) \r\n", pos.x, pos.y);
        //     }
            
        //     PIOA->PIO_SODR = PIO_PA23;
        //     timer_delay_us(20);
        //     PIOA->PIO_CODR = PIO_PA23;
        //     timer_delay_us(20);
        // }

}