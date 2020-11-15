#include "motor.h"
#include "dac.h"
// #include "../node1/user_input.h"
#include "timer.h"
#include "pid_controller.h"
#include "sam/sam3x/include/sam.h"
#include "sam/interrupt.h"
#include <math.h>
#include "user_input.h"


#define ENCODER_DATA_MASK   (0xFF << DO0_IDX)
#define MIN_ENCODER_VALUE   0
#define MAX_ENCODER_VALUE   8800
// REMOVE THIS WHEN WE HAVE FIXED ALL THE CODE :)
#define SLIDER_MAX          100


#define MICROBIT_CONTROLLER_MOTOR_SPEED 0x0FF


static int scale_encoder_value(int value) {
    return SLIDER_MAX * value / (MAX_ENCODER_VALUE - MIN_ENCODER_VALUE);
}


enum motor_direction {
   LEFT,
   RIGHT
};


static void motor_set_speed(int v) {
    dac_write(v);
}


static void motor_set_direction(enum motor_direction d) {
    if (d == LEFT) {
        PIOD->PIO_CODR = DIR;
    }
    else if (d == RIGHT) {
        PIOD->PIO_SODR = DIR;
    }
}


void motor_init() {
    // initiate dac
    dac_init();

    // enable PIOD pins to motor box as output
    PIOD->PIO_PER |= DIR | EN | SEL | NOT_RST | NOT_OE;
    PIOD->PIO_OER |= DIR | EN | SEL | NOT_RST | NOT_OE;

    // enable PIOC pins from motor encoder as input
    PIOC->PIO_PER |= ENCODER_DATA_MASK;
    PIOC->PIO_ODR |= ENCODER_DATA_MASK;

    // enable PIOC clock
    PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_PIOC << PMC_PCR_PID_Pos);
    PMC->PMC_PCER0 |= 1 << (ID_PIOC);

    // enable motor
    // PIOD->PIO_SODR = EN | NOT_RST;
}


void motor_disable() {
    motor_set_speed(0);
    PIOD->PIO_CODR = EN;
}


void motor_enable() {
    PIOD->PIO_SODR = EN;
    pid_controller_reset_errors();
}


int motor_read_encoder() {
    // Setting !OE low to enable output of encoder
    PIOD->PIO_CODR |= NOT_OE;

    // Setting SEL low to get high byte and extracting MSB
    PIOD->PIO_CODR |= SEL;
    _delay_us(20);
    uint8_t msb = (PIOC->PIO_PDSR & ENCODER_DATA_MASK) >> DO0_IDX;

    // Setting SEL high to get low byte and extracting LSB
    PIOD->PIO_SODR |= SEL;
    _delay_us(20);
    uint8_t lsb = (PIOC->PIO_PDSR & ENCODER_DATA_MASK) >> DO0_IDX;

    // Reset encoder
    PIOD->PIO_CODR |= NOT_RST;
    PIOD->PIO_SODR |= NOT_RST;

    // Disable output of encoder
    PIOD->PIO_SODR |= NOT_OE;

    // Combine LSB and MSB
    uint16_t encoder_data = ((msb << 8) | lsb);
    if (encoder_data & (1 << 15)) {
        return ((uint16_t) (~encoder_data) + 1);
    }
    return -encoder_data;
}


void motor_run_slider(int reference) {
    // pos_t pos = {0, 0};
    // if (!(joystick_pos_recieve(&pos))) {
    //     printf("recieved position \n\r");
    //     if (pos.x > 0) {
    //         printf("moving right, x = %d \n\r", pos.x);
    //         // moving right, set direction pin
    //         PIOD->PIO_SODR = DIR;
    //     }
    //     else {
    //         printf("moving left x = %d \n\r", pos.x);
    //         // moving left, clear direction pin
    //         PIOD->PIO_CODR = DIR;
    //     }

    //     // set motor speed
    //     uint16_t speed = (uint16_t) (0x4FF * abs(pos.x) / 100);
    //     printf("speed = %X \n\n\r", speed);
    //     dac_write(speed);
    // }

    int encoder_value = motor_read_encoder();
    int current_position = scale_encoder_value(encoder_value);
    //printf("reference: %d, \t\tcurrent position: %d \r\n", reference, current_position);
    int u = pid_controller(reference, current_position);
    //printf("pådrag: %d \r\n", u);

    if (u > 0) {
        motor_set_direction(RIGHT);
    }
    else {
        motor_set_direction(LEFT);
    }

    motor_set_speed(abs(u));
}


void motor_run_microbit(){
    acc_dir_t microbit_dir = user_input_microbit_dir();

    switch(microbit_dir){
        case(ACC_LEFT):
        {
            motor_set_direction(LEFT);
            motor_set_speed(MICROBIT_CONTROLLER_MOTOR_SPEED);
            break;
        }
        case(ACC_RIGHT):
        {
            motor_set_direction(RIGHT);
            motor_set_speed(MICROBIT_CONTROLLER_MOTOR_SPEED);
            break;
        }
        case(ACC_MIDDLE):
        {
            motor_set_speed(0);
            break;
        }
        default:
        {
            motor_set_speed(0);
            break;
        }
    }
}
