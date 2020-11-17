#include "highscore.h"
#include "eeprom_driver.h"


static uint16_t current_highscores[HIGHSCORE_LIST_LENGTH] = {0, 0, 0};
static uint16_t new_score = 0;


void highscore_init() {
    for (int i = 0; i < HIGHSCORE_LIST_LENGTH; ++i) {
        uint8_t score_lsb = eeprom_read(2*i);
        uint8_t score_msb = eeprom_read(2*i+1);

        current_highscores[i] = score_lsb + (score_msb << 8);
    }
}


static void highscore_write_to_eeprom() {
    for (int i = 0; i < HIGHSCORE_LIST_LENGTH; ++i) {
        uint8_t score_lsb = (current_highscores[i] & 0x00FF);
        eeprom_write(2*i, 0);
        eeprom_write(2*i, score_lsb);
        uint8_t score_msb = (current_highscores[i] & 0xFF00) >> 8;
        eeprom_write(2*i+1, 0);
        eeprom_write(2*i+1, score_msb);
    }
}


void highscore_update() {
    int highscore_changed = 1;
    if (new_score > current_highscores[0]) {
        current_highscores[2] = current_highscores[1];
        current_highscores[1] = current_highscores[0];
        current_highscores[0] = new_score;
    }
    else if (new_score > current_highscores[1]) {
        current_highscores[2] = current_highscores[1];
        current_highscores[1] = new_score;
    }
    else if(new_score > current_highscores[2]) {
        current_highscores[2] = new_score;
    }
    else {
        highscore_changed = 0;
    }

    if (highscore_changed) {
        highscore_write_to_eeprom();
    }
}


uint16_t* highscore_get() {
    return current_highscores;
} 


void highscore_reset() {
    for (int i = 0; i < HIGHSCORE_LIST_LENGTH; ++i) {
        current_highscores[i] = 0;
        eeprom_write(2*i, 0);
        eeprom_write(2*i+1, 0);
    }
}

void highscore_set_new_score(uint16_t score) {
    new_score = score;
}

