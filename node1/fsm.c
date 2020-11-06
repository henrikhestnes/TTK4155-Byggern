#include "fsm.h"
#include "interrupt.h"
#include "oled.h"
#include "can_driver.h"

#define F_CPU 4.9152E6
#include <util/delay.h>


void fsm_transition_to(enum FSM_STATE state) {
    switch (state) {
        case MENU:
        {
            interrupt_enable_oled_timer();
            fsm_current_state = MENU;
            break;
        }
        case PLAYING:
        {
            interrupt_disable_oled_timer();

            oled_clear();
            oled_set_pos(1, 8);
            oled_print_string("PLAYING!");
            oled_set_pos(3, 8);
            oled_print_string("Quit the game");
            oled_set_pos(4, 8);
            oled_print_string("by pushing the");
            oled_set_pos(5, 8);
            oled_print_string("left button");

            fsm_current_state = PLAYING;
            break;
        }
        case POSTGAME: 
        {
            oled_clear();
            oled_set_pos(1, 8);
            oled_print_string("GAME ENDED!");
            oled_set_pos(3, 8);
            oled_print_string("Return to main");
            oled_set_pos(4, 8);
            oled_print_string("menu by pushing");
            oled_set_pos(5, 8);
            oled_print_string("the left button");

            fsm_current_state = POSTGAME;
            break;
        }
        default:
            break;
    }

    _delay_ms(10);
    message_t m = {.id = 2, .length = 1, .data = state};
    can_transmit(&m);
}