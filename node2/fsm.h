#ifndef NODE2_FSM_H
#define NODE2_FSM_H


enum FSM_STATE {
    INIT,
    MENU,
    PLAYING,
    POSTGAME
};


extern enum FSM_STATE fsm_current_state;


void fsm_transition_to(enum FSM_STATE state);


#endif