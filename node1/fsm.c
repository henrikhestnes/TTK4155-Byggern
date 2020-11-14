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


void fsm_set_state(enum FSM_STATE state) {
    current_state = state;
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

            current_state = PLAYING;
            break;
        }
        case GAME_OVER: 
        {
            user_input_timer_disable();
            oled_clear();
            oled_print_game_over_screen(0);

            current_state = GAME_OVER;
            break;
        }
        case IDLE:
        {   
            user_input_timer_disable();
            oled_clear();
            oled_print_quit_screen();
            
            current_state = IDLE;
            break;
        }
        default:
            break;
    }

    _delay_ms(10);
   fsm_transmit_state(state);
}


