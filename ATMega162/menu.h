#ifndef MENU_H
#define MENU_H


#include "oled.h"


typedef enum {
    MAIN_MENU_NEW_GAME,
    MAIN_MENU_HIGHSCORE,
    MAIN_MENU_SETTINGS,
    MAIN_MENU_QUIT,
    HIGHSCORE_RESET,
    HIGHSCORE_RETURN,
    SETTINGS_BACKGROUND_MUSIC,
    SETTINGS_SET_DIFFICULTY,
    SETTINGS_RETURN
} menu_state_t;


typedef struct menu {
    const char** content;
    struct menu** children;
    struct menu* parent;
    int length;
} menu_t;


void menu_init(void);


// void menu_free(void);


void menu_set_state(menu_state_t state);


void menu_print(font_type_t type);


void action_function(int state);


#endif
