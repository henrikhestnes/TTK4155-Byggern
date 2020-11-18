/**
 * @file
 * @brief Module for running the system as a Finite State Machine. 
 */


#ifndef NODE1_FSM_H
#define NODE1_FSM_H


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


/**
 * @brief Returns the number of lives left in a game.
 * 
 * @return The number of lives left in a game.
 */
unsigned int fsm_get_lives_left(void);


/**
 * @brief Sets the number of lives left in a game.
 * 
 * @param lives_left The new number of lives left in a game.
 */
void fsm_set_lives_left(unsigned int lives);

#endif