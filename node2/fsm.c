#include "fsm.h"
#include "motor.h"
#include "game.h"
#include "can/can_controller.h"
#include "../common/can.h"


static FSM_STATE current_state = INIT;


FSM_STATE fsm_get_state() {
    return current_state;
}


void fsm_transition_to(FSM_STATE state) {
    switch (state) {
        case MENU:
        {
            // reset number of lives
            game_reset_lives_left();
            CAN_MESSAGE m = {
                .id = GAME_LIVES_LEFT_ID,
                .data_length = 1,
                .data = INITIAL_LIVES
            };
            can_send(&m, 0);

            current_state = MENU;
            printf("Transitioning to MENU \n\r");
            break;
        }
        case PLAYING:
        {   
            motor_enable();
            game_timer_enable();
            current_state = PLAYING;
            printf("Transitioning to PLAYING \n\r");
            break;
        }
        case GAME_OVER: 
        {
            int score = game_get_score();
            uint8_t msb = (score & 0xFF00) >> 8;
            uint8_t lsb = (score & 0x00FF);

            CAN_MESSAGE m = {
                .id = GAME_SCORE_ID,
                .data_length = 2,
                .data = {msb, lsb}
            };
            can_send(&m, 0);

            current_state = GAME_OVER;
            printf("Transitioning to GAME_OVER \n\r");
            break;
        }
        case IDLE:
        {
            motor_disable();
            game_timer_disable();
            game_reset_score();
            current_state = IDLE;
            printf("Transitioning to IDLE \n\r");
        }
        default:
            break;
    }
}