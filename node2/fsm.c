#include "fsm.h"
#include "motor.h"
#include "game.h"


static enum FSM_STATE current_state = INIT;


enum FSM_STATE fsm_get_state() {
    return current_state;
}


void fsm_transition_to(enum FSM_STATE state) {
    switch (state) {
        case MENU:
        {
            current_state = MENU;
            printf("Transitioning to MENU");
            break;
        }
        case PLAYING:
        {
            motor_enable();
            game_timer_enable();
            current_state = PLAYING;
            printf("Transitioning to PLAYING");
            break;
        }
        case GAME_OVER: 
        {
            current_state = GAME_OVER;
            printf("Transitioning to GAME_OVER");
            break;
        }
        case IDLE:
        {
            motor_disable();
            game_timer_disable();
            current_state = IDLE;
            printf("Transitioning to IDLE");
        }
        default:
            break;
    }
}