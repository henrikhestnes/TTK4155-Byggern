#ifndef NODE2_FSM_H
#define NODE2_FSM_H


#include "../common/fsm_state.h"


extern enum FSM_STATE fsm_current_state;


void fsm_transition_to(enum FSM_STATE state);


#endif