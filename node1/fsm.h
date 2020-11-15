#ifndef NODE1_FSM_H
#define NODE1_FSM_H


#include "../common/fsm_state.h"


enum FSM_STATE fsm_get_state(void);


void fsm_set_state(enum FSM_STATE state);


void fsm_transition_to(enum FSM_STATE state);


unsigned int fsm_get_lives_left();


void fsm_set_lives_left(unsigned int lives);

#endif