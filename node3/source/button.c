#include "button.h"
#include "gpio.h"

#define BUTTON_A_PIN 17
#define BUTTON_B_PIN 26


void button_init(){
    GPIO->PIN_CNF[BUTTON_A_PIN] = 0;
    GPIO->PIN_CNF[BUTTON_B_PIN] = 0;
}


uint8_t button_a_pressed(){
    if (GPIO->IN & (1 << 17)){
      return 0;
    }
    return 1;
}


uint8_t button_b_pressed(){
    if (GPIO->IN & (1 << 26)){
      return 0;
    }
    return 1;
}
