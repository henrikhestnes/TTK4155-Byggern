#ifndef GAME_H
#define GAME_H


#include "../common/controller_select.h"


void game_init(void);


int game_count_fails(void);


void game_get_user_data(char* data);


void game_set_controller(enum CONTROLLER_SEL controller);


void game_timer_enable();


void game_timer_disable();


int game_get_score();


void game_reset_score();


#endif
