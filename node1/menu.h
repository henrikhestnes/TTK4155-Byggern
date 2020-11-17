/**
 * @file
 * @brief Module for the menu system. 
 */


#ifndef MENU_H
#define MENU_H


#include <stdint.h>


#define MAX_SUBMENU_NUMBER 5


/**
 * @brief Data structure to represent a menu. Points to 
 * the text display of the menu, and menus above and below in the structure.
 * Also points to an array of functions to be called when the option is selected.
 */
typedef struct menu {
    const char* const* text_display;
    uint8_t length;
    struct menu* parent;
    struct menu* submenus[MAX_SUBMENU_NUMBER];
    void (*action_functions[])();
} MENU;


/**
 * @brief Initiates the menu by creating all submenus, with 
 * their respective linked lists of nodes. Clears the OLED screen
 * and writes the main menu to the SRAM. 
 */
void menu_init();


/**
 * @brief Navigates the menu, depending on the joystick direction. 
 */
void menu_run();


/**
 * @brief Enables the timer which prints the menu to the OLED screen.
 */
void menu_timer_enable();


/**
 * @brief Disables the timer which prints the menu to the OLED screen.
 */
void menu_timer_disable();


/**
 * @brief Navigates to the menu above the current menu.
 */ 
void menu_go_to_parent();


/**
 * @brief Navigates to the submenu below the current menu.
 */
void menu_go_to_child();


#endif
