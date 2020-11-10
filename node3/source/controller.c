#include "controller.h"
#include "gpio.h"
#include "button.h"

#define THRESHOLD  200

#define PIN_0   3
#define PIN_1   2
#define PIN_2   1


void controller_init_pins(){
    GPIO->PIN_CNF[PIN_0] = 1;
    GPIO->PIN_CNF[PIN_1] = 1;
    GPIO->PIN_CNF[PIN_2] = 1;
}


const dir_t controller_get_dir(const int16_t* x_pt){
    if(*x_pt > -THRESHOLD){
        return left;
    }
    if(*x_pt < THRESHOLD){
        return right;
    }
    else{
        return middle;
    }
}


void controller_set_pin_high(dir_t* dir){
    switch(*dir){
        case(left):
            GPIO->OUTSET = (1 << PIN_0);
            GPIO->OUTCLR = (1 << PIN_1);
            break;

        case(right):
            GPIO->OUTSET = (1 << PIN_1);
            GPIO->OUTCLR = (1 << PIN_0);
            break;

        case(middle):
            GPIO->OUTCLR = (1 << PIN_1);
            GPIO->OUTCLR = (1 << PIN_0);
            break;

    }
}


void controller_send_dir(int16_t* x_pt){

    dir_t dir = controller_get_dir(x_pt);

    controller_set_pin_high(&dir);
}


void controller_send_button_pressed(){
    if(button_b_pressed()){
        GPIO->OUTSET = (1 << PIN_2);
    }
    else{
        GPIO->OUTCLR = (1 << PIN_2);
    }
}
