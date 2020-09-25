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
    const char* const* content;
    struct menu** children;
    struct menu* parent;
    int length;
} menu_t;


void menu_init(void);


// void menu_free(void);


void menu_add_submenu(menu_t* parent, int length);


void menu_add_submenu_content(menu_t* submenu, const char* const * content, int content_length);


void menu_print(font_type_t type);


void menu_set_state();


#endif
