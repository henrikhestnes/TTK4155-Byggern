#ifndef MENU_H
#define MENU_H


#include "oled.h"


typedef struct menu_node{
    char** content;
    //menu_node* children;
    //menu_node* parent;
    int length;
} menu_node;


void menu_init(void);


void menu_print(font_type type);

#endif
