#ifndef MENU_H
#define MENU_H

#include "oled.h"


typedef struct menu_node {
    struct menu* parent_menu;
    struct menu* own_menu;
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


menu_node_t* menu_new_node(menu_t* parent_menu, menu_t* own_menu, menu_t* child_menu, void (*action_function)());


void menu_print();


void go_to_child();


void go_to_parent();


void menu_run();


// void menu_write_to_sram();


#endif
