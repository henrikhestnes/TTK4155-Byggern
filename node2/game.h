#ifndef GAME_H
#define GAME_H


void game_init(void);


void game_set_controller(unsigned int controller);


void game_count_score(void);


void game_set_user_data(char* data);


void game_timer_enable();


void game_timer_disable();


#endif
