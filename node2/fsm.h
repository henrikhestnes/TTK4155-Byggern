#ifndef NODE2_FSM_H
#define NODE2_FSM_H


#include "../common/fsm_state.h"


void fsm_transition_to(enum FSM_STATE state);


enum FSM_STATE fsm_get_state();


#endif