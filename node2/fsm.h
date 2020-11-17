#ifndef NODE2_FSM_H
#define NODE2_FSM_H


/**
* @file
* @brief Module consisting of state-machine-functionality
*/


#include "../common/fsm_state.h"


/**
 * @brief Returns the current FSM state.
 *
 * @return The current FSM state, of data type @c FSM_STATE.
 */
FSM_STATE fsm_get_state();


/**
 * @brief Transitions the FSM to @c state by calling the state's
 * entry actions, and updating the current state.
 *
 * @param state The FSM state to be transitioned to, of data type @c FSM_STATE.
 */
void fsm_transition_to(FSM_STATE state);


#endif
