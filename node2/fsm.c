#include "fsm.h"
#include "motor.h"
#include "game.h"


void fsm_transition_to(enum FSM_STATE state) {
    switch (state) {
        case MENU:
        {
            fsm_current_state = MENU;
            printf("Transitioning to MENU");
            break;
        }
        case PLAYING:
        {
            motor_enable();
            game_timer_enable();
            fsm_current_state = PLAYING;
            printf("Transitioning to PLAYING");
            break;
        }
        case POSTGAME: 
        {
            motor_disable();
            game_timer_disable();
            fsm_current_state = POSTGAME;
            printf("Transitioning to POSTGAME");
            break;
        }
        default:
            break;
    }
}