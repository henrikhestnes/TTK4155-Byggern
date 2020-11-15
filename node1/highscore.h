#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <stdint.h>



void highscore_init();


void highscore_update();


uint16_t* highscore_get();


void highscore_reset();


void highscore_set_new_score(uint16_t score);


#endif