#include "user_input.h"
#include "../node1/user_input.h"
#include "sam/sam3x/include/sam.h"

#define A8          27
#define A9          2
#define A10         3

#define MB_LEFT_PIN    A8
#define MB_RIGHT_PIN   A9
#define MB_BUTTON_PIN  A10

#define BUTTON_PRESSED      1
#define BUTTON_NOT_PRESSED  0


int joystick_scale_x(uint8_t value) {
    int x = (int) (value - 128)*(JOYSTICK_MAX - JOYSTICK_MIN)/256;

    // regresion to scale x values to interval [-100, 100]
    x = (int) (7.7E-5*x*x*x + 6.6E-4*x*x + 0.23*x - 6.6);
    return x;
}


int joystick_scale_y(uint8_t value) {
    int y = (int) (value - 128)*(JOYSTICK_MAX - JOYSTICK_MIN)/256;

    // regresion to scale y values to interval [-100, 100]
    y = (int) (7.6E-5*y*y*y + 9E-4*y*y + 0.24*y - 9.1);
    return y;
}


int slider_scale_right(uint8_t value) {
    // scale to values in interval [0, SLIDER_MAX]
    int scaled_value = (int)(value*SLIDER_MAX/256);

    // correct offset and nonlinear scaling
    // based on measurements we assume positive offset
    if (scaled_value > SLIDER_MAX / 2 + SLIDER_RIGHT_OFFSET) {
        scaled_value -= (int)(SLIDER_RIGHT_OFFSET*(SLIDER_MAX - scaled_value)/(SLIDER_MAX / 2 - SLIDER_RIGHT_OFFSET));
    }
    else
    {
        scaled_value -= (int)(SLIDER_RIGHT_OFFSET*scaled_value/(SLIDER_MAX / 2 + SLIDER_RIGHT_OFFSET));
    }

    return scaled_value;
}


int slider_scale_left(uint8_t value) {
    // scale to values in interval [0, SLIDER_MAX]
    int scaled_value = (int)(value*SLIDER_MAX/256);

    // correct offset and nonlinear scaling
    // based on measurements we assume positive offset
    if (scaled_value > SLIDER_MAX / 2 + SLIDER_LEFT_OFFSET) {
        scaled_value -= (int)(SLIDER_LEFT_OFFSET*(SLIDER_MAX - scaled_value)/(SLIDER_MAX / 2 - SLIDER_LEFT_OFFSET));
    }
    else
    {
        scaled_value -= (int)(SLIDER_LEFT_OFFSET*scaled_value/(SLIDER_MAX / 2 + SLIDER_LEFT_OFFSET));
    }

    return scaled_value;
}


void microbit_user_input_init(){
    // enables the PIO to control the corresponding pins
    PIOA->PIO_PER |= (1 << MB_LEFT_PIN);
    PIOA->PIO_PER |= (1 << MB_RIGHT_PIN);
    PIOA->PIO_PER |= (1 << MB_BUTTON_PIN);

    PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_PIOA << PMC_PCR_PID_Pos);
    PMC->PMC_PCER0 |= 1 << (ID_PIOA);
}


const acc_dir_t user_input_microbit_get_dir(){
    char left_dir   = (PIOA->PIO_PDSR & (1 << MB_LEFT_PIN));
    char right_dir  = (PIOA->PIO_PDSR & (1 << MB_RIGHT_PIN));

    if(left_dir == 0 && right_dir == 0){
        return ACC_MIDDLE;
    }
    else if(left_dir == (1 << MB_LEFT_PIN)){
        return ACC_LEFT;
    }
    else{
        return ACC_RIGHT;
    }
    return ACC_MIDDLE;
}


const char user_input_microbit_button_pressed(){
    if((PIOA->PIO_PDSR & (1 << MB_BUTTON_PIN)) == (1 << MB_BUTTON_PIN)){
        return BUTTON_PRESSED;
    }
    return BUTTON_NOT_PRESSED;
}
