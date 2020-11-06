#ifndef NODE1_FSM_H
#define NODE1_FSM_H


enum FSM_STATE {
    INIT,
    MENU,
    PLAYING,
};


extern enum FSM_STATE fsm_current_state;


void fsm_transition_to(enum FSM_STATE state);


#endif