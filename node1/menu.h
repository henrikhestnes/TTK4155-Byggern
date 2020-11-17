#ifndef MENU_H
#define MENU_H

#include "oled.h"

/**
 * @brief Data structure to represent a node in the menu. Points to 
 * the text displays of owm menu, and menus above and below in the structure.
 * Points to the next and previous node in the linked list of nodes.
 * Also points to a function which is called when the node is selected
 * when the joystick button is pressed. 
 */
// typedef struct menu_node {
//     struct menu* parent_menu;
//     struct menu* own_menu;
//     struct menu* child_menu;
//     struct menu_node* next;
//     struct menu_node* prev;
//     void (*action_function)();
// } menu_node_t;


/**
 * @brief Data structure to represent a menu or submenu. Points to a text display
 * to be printed to the OLED screen. Also points to the first node in the linked list
 * of nodes in the menu.
 */
// typedef struct menu {
//     const char* const* text_display;
//     int length;
//     struct menu_node* head;
// } menu_t;


/**
 * @brief Links two menu nodes in a linked list. 
 */
// void menu_link_nodes(menu_node_t* first, menu_node_t* second);


/**
 * @brief Initiates the menu by creating all submenus, with 
 * their respective linked lists of nodes. Clears the OLED screen
 * and prints the main menu. 
 */
void menu_init();


/**
 * @brief Creates a new menu object.
 * 
 * @param text_display Text display of the new menu object.
 * @param length Amount of nodes in the linked list of nodes beloning to the menu.
 * 
 * @return A pointer to the new menu object. 
 */
// menu_t* menu_new(const char* const* text_display, int length);


/**
 * @brief Creates a new menu node object. 
 * 
 * @param parent_menu Pointer to the parent of the menu the node is part of.
 * @param own_menu Pointer to the menu the node is part of.
 * @param child_menu Pointer to the submenu the node is parent of.
 * @param action_function The function to be called when the node is selected.
 * 
 * @return A pointer to the new menu node object. 
 */
// menu_node_t* menu_new_node(menu_t* parent_menu, menu_t* own_menu, menu_t* child_menu, void (*action_function)());


/**
 * @brief Prints the text display of the menu the current selected node is part of.
 */
void menu_print();


/**
 * @brief Navigates the menu, depending on the joystick direction. 
 */
void menu_run();


void menu_timer_enable();


void menu_timer_disable();


// menu_node_t* menu_get_current();


void menu_go_to_parent();


void menu_go_to_child();

#endif
