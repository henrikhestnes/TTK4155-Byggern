#include "fsm.h"
#include "motor.h"


void fsm_transition_to(enum FSM_STATE state) {
    switch (state) {
        case MENU:
        {
            printf("Transitioning to MENU");
            fsm_current_state = MENU;
            break;
        }
        case PLAYING:
        {
            printf("Transitioning to PLAYING");
            motor_enable();
            fsm_current_state = PLAYING;
            break;
        }
        case POSTGAME: 
        {
            printf("Transitioning to POSTGAME");
            motor_disable();
            fsm_current_state = POSTGAME;
            break;
        }
        default:
            break;
    }
}