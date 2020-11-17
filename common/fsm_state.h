/**
 * @file 
 * @brief Enumeration for FSM states common for node 1 and 2.
 */



#ifndef COMMON_FSM_STATE_H
#define COMMON_FSM_STATE_H


typedef enum {
    INIT,
    MENU,
    PLAYING,
    GAME_OVER,
    IDLE
} FSM_STATE;


#endif