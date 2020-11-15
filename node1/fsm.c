#include "fsm.h"
#include "interrupt.h"
#include "oled.h"
#include "menu.h"
#include "can_driver.h"
#include "highscore.h"
#include "../common/can_id.h"
#include "user_input.h"

#define F_CPU 4.9152E6
#include <util/delay.h>


static enum FSM_STATE current_state = INIT;
static unsigned int lives_left;


static void fsm_transmit_state(enum FSM_STATE state) {
    message_t m = {.id = FSM_STATE_ID, .length = 1, .data = state};
    can_transmit(&m);
}


enum FSM_STATE fsm_get_state(void) {
    return current_state;
}


unsigned int fsm_get_lives_left() {
    return lives_left;
}


void fsm_set_lives_left(unsigned int lives) {
    lives_left = lives;
}


void fsm_transition_to(enum FSM_STATE state) {
    switch (state) {
        case MENU:
        {
            menu_timer_enable();
            current_state = MENU;
            printf("Transitioning to MENU \n\r");
            break;
        }
        case PLAYING:
        {
            menu_timer_disable();
            user_input_timer_enable();
            oled_clear();

            current_state = PLAYING;
            printf("Transitioning to PLAYING \n\r");
            break;
        }
        case GAME_OVER: 
        {
            user_input_timer_disable();
            oled_clear();

            current_state = GAME_OVER;
            printf("Transitioning to GAME_OVER \n\r");
            break;
        }
        case IDLE:
        {   
            user_input_timer_disable();
            highscore_update();

            current_state = IDLE;
            printf("Transitioning to IDLE \n\r");
            break;
        }
        default:
            break;
    }

    _delay_ms(10);
   fsm_transmit_state(state);
}


