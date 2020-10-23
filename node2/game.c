#include "game.h"
#include "adc.h"
#include <stdint.h>


static unsigned int score;
static unsigned int counting_flag;


void game_init() {
    score = 0;
}


void game_count_score() {
    uint16_t ir_level = adc_read();

    if ((ir_level < IR_TRESHOLD) && !counting_flag) {
        ++score;
        counting_flag = 1;
    }

    else if (ir_level > IR_TRESHOLD) {
        counting_flag = 0;
    }

    printf("Current score: %d \r\n", score);
}