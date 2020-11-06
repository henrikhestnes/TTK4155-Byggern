#include "fsm.h"
#include "interrupt.h"


void fsm_transition_to(enum FSM_STATE state) {
    switch (state) {
        case MENU:
            interrupt_enable_oled_timer();
            fsm_current_state = MENU;
            break;
        
        case PLAYING:
            interrupt_disable_oled_timer();
            fsm_current_state = PLAYING;
            break;

        default:
            break;
    }
}