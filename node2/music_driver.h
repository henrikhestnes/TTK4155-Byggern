#ifndef MUSIC_DRIVER_H
#define MUSIC_DRIVER_H

typedef enum {
    MII_THEME,
    MARIO,
    SIMPSON
} SONG;


void music_buzz(int freq, int length);


void music_play(SONG song);


#endif