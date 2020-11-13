#include "fsm.h"
#include "interrupt.h"
#include "oled.h"
#include "menu.h"
#include "can_driver.h"
#include "../common/can_id.h"
#include "user_input.h"

#define F_CPU 4.9152E6
#include <util/delay.h>



static enum FSM_STATE current_state = INIT;


static void fsm_transmit_state(enum FSM_STATE state) {
    message_t m = {.id = FSM_STATE_ID, .length = 1, .data = state};
    can_transmit(&m);
}


enum FSM_STATE fsm_get_state(void) {
    return current_state;
}


void fsm_transition_to(enum FSM_STATE state) {
    switch (state) {
        case MENU:
        {
            menu_timer_enable();
            current_state = MENU;
            break;
        }
        case PLAYING:
        {
            menu_timer_disable();
            user_input_timer_enable();

            oled_clear();
            oled_set_pos(1, 8);
            oled_print_string("PLAYING!");
            oled_set_pos(3, 8);
            oled_print_string("Quit the game");
            oled_set_pos(4, 8);
            oled_print_string("by pushing the");
            oled_set_pos(5, 8);
            oled_print_string("left button");

            current_state = PLAYING;
            break;
        }
        case POSTGAME: 
        {
            user_input_timer_disable();
            
            oled_clear();
            oled_set_pos(1, 8);
            oled_print_string("GAME ENDED!");
            oled_set_pos(3, 8);
            oled_print_string("Return to main");
            oled_set_pos(4, 8);
            oled_print_string("menu by pushing");
            oled_set_pos(5, 8);
            oled_print_string("the left button");

            current_state = POSTGAME;
            break;
        }
        default:
            break;
    }

    _delay_ms(10);
   fsm_transmit_state(state);
}


