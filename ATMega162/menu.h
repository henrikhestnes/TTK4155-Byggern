#ifndef MENU_H
#define MENU_H

#include "oled.h"


typedef struct menu_node {
    struct menu* parent_menu;
    struct menu* child_menu;
    struct menu_node* next;
    struct menu_node* prev;
    void (*action_function)();
} menu_node_t;


typedef struct menu {
    const char* const* text_display;
    int length;
    struct menu_node* head;
} menu_t;


void menu_link_nodes(menu_node_t* first, menu_node_t* second);


void menu_init();


menu_t* menu_new(const char* const* text_display, int length);


menu_node_t* menu_new_node(menu_t* parent_menu, menu_t* child_menu, void (*action_function)());


void menu_print(font_type_t type);


void go_to_child();


void go_to_parent();

void menu_run();


// typedef enum {
//     MAIN_MENU_NEW_GAME,
//     MAIN_MENU_HIGHSCORE,
//     MAIN_MENU_SETTINGS,
//     MAIN_MENU_QUIT,
//     HIGHSCORE_RESET,
//     HIGHSCORE_RETURN,
//     SETTINGS_BACKGROUND_MUSIC,
//     SETTINGS_SET_DIFFICULTY,
//     SETTINGS_RETURN
// } menu_state_t;


// typedef struct menu {
//     const char* const* content;
//     struct menu** children;
//     struct menu* parent;
//     int length;
// } menu_t;


// void menu_init(void);


// void menu_add_submenu(menu_t* parent, int length);


// void menu_add_submenu_content(menu_t* submenu, const char* const * content, int content_length);


// void menu_print(font_type_t type);


// void menu_run();


#endif
