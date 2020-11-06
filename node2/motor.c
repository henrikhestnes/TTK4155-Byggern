#include "motor.h"
#include "dac.h"
#include "slider.h"
#include "timer.h"
#include "pi_controller.h"
#include "sam/sam3x/include/sam.h"
#include "sam/interrupt.h"
#include <math.h>


#define ENCODER_DATA_MASK   (0xFF << DO0_IDX)

#define K_P                 30
#define K_I                 6
#define T                   1.0 / 50
#define MAX_SPEED           0x4FF

#define MIN_ENCODER_VALUE   0
#define MAX_ENCODER_VALUE   8800


static int encoder_value = 0;
int scaled_encoder_value() {
    return SLIDER_MAX_VALUE * encoder_value / (MAX_ENCODER_VALUE - MIN_ENCODER_VALUE);
}

static PI_data_t PI = {    
    K_P,
    K_I,
    0,
    T,
    MAX_SPEED
};





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
    PIOD->PIO_SODR = EN | NOT_RST;
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
   
    int current_position = scaled_encoder_value();
    // printf("reference: %d, \t\tcurrent position: %d \r\n", reference, current_position);
    int u = pi_controller(&PI, reference, current_position);
    // printf("pådrag: %d \r\n", u);

    if (u > 0) {
        // moving right, set direction pin
        PIOD->PIO_SODR = DIR;
    }
    else {
        // moving left, clear direction pin
        PIOD->PIO_CODR = DIR;
    }

    // set motor speed
    dac_write(abs(u));
}


int motor_read_encoder() {
    // Setting !OE low to enable output of encoder
    PIOD->PIO_CODR |= NOT_OE;

    // Setting SEL low to get high byte and extracting MSB
    PIOD->PIO_CODR |= SEL;
    timer_delay_us(20);
    uint8_t msb = (PIOC->PIO_PDSR & ENCODER_DATA_MASK) >> DO0_IDX;

    // Setting SEL high to get low byte and extracting LSB
    PIOD->PIO_SODR |= SEL;
    timer_delay_us(20);
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


void TC0_Handler(void) {
    encoder_value = motor_read_encoder();

    // clear interrupt flag
    TC0->TC_CHANNEL[0].TC_SR;
}