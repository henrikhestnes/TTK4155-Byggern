#include "fsm.h"
#include "oled.h"
#include "menu.h"
#include "can_driver.h"
#include "highscore.h"
#include "user_input.h"
#include "../common/can.h"

#define F_CPU 4.9152E6
#include <util/delay.h>


static FSM_STATE current_state = STATE_INIT;
static unsigned int lives_left;


static void fsm_transmit_state(FSM_STATE state) {
    CAN_MESSAGE m = {
        .id = FSM_STATE_ID, 
        .data_length = 1, 
        .data = state};
    can_send(&m);
}


FSM_STATE fsm_get_state() {
    return current_state;
}


unsigned int fsm_get_lives_left() {
    return lives_left;
}


void fsm_set_lives_left(unsigned int lives) {
    lives_left = lives;
}


void fsm_transition_to(FSM_STATE state) {
    switch (state) {
        case STATE_MENU:
        {
            menu_timer_enable();
            current_state = STATE_MENU;
            break;
        }
        case STATE_PLAYING:
        {
            menu_timer_disable();
            user_input_timer_enable();
            oled_clear();

            current_state = STATE_PLAYING;
            break;
        }
        case STATE_GAME_OVER: 
        {
            user_input_timer_disable();

            current_state = STATE_GAME_OVER;
            break;
        }
        case STATE_IDLE:
        {   
            user_input_timer_disable();

            current_state = STATE_IDLE;
            break;
        }
        default:
            break;
    }

    _delay_ms(10);
   fsm_transmit_state(state);
}


