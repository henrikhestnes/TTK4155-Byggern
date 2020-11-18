/**
 * @file 
 * @brief Enumeration for FSM states common for node 1 and 2.
 */


#ifndef COMMON_FSM_STATE_H
#define COMMON_FSM_STATE_H


typedef enum {
    STATE_INIT,
    STATE_MENU,
    STATE_PLAYING,
    STATE_GAME_OVER,
    STATE_IDLE
} FSM_STATE;


#endif