#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include "uart_and_printf/uart.h"
#include "uart_and_printf/printf-stdarg.h"
#include "can/can_controller.h"
#include "can/can_interrupt.h"
#include "sam/sam3x/include/sam.h"


#include "led.h"
#include "joystick.h"
#include "slider.h"
#include "pwm.h"
#include "servo_driver.h"
#include "adc.h"
#include "game.h"
#include "motor.h"
#include "timer.h"
#include "solenoid.h"


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

    // SERVO
        servo_init();

    // ADC
        adc_init();

    // MOTOR
        motor_init();

    // TIMER
        timer_init();

    // SOLENOID
        solenoid_init();


    // TESTING
        // PIOA->PIO_PER |= PIO_PA23;
        // PIOA->PIO_OER |= PIO_PA23;

        while (1) {
            // solenoid_shoot();
            // timer_delay_us(1000000);

            // motor_run_slider();

            // servo_set_position();

            game_count_score();

            // pos_t pos = {0,0};
            // if (!(joystick_pos_recieve(&pos))) {
            //     printf("(x,y) = (%d,%d) \r\n", pos.x, pos.y);
            // }

            // slider_t slider_pos = {0, 0};
            // if (!slider_pos_recieve(&slider_pos)) {
            //     printf("(left, right) = (%d, %d) \r\n", slider_pos.left, slider_pos.right);
            // }
            
            // PIOA->PIO_SODR = PIO_PA23;
            // timer_delay_us(20);
            // PIOA->PIO_CODR = PIO_PA23;
            // timer_delay_us(20);
        }

}