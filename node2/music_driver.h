#ifndef MUSIC_DRIVER_H
#define MUSIC_DRIVER_H

typedef enum {
    MII_THEME,
    MARIO,
    SAVAGE_LOVE,
    HARRY_POTTER,
    GAME_OVER_SOUND
} SONG;


void music_play(SONG song);


#endif