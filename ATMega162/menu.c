#include "menu.h"
#include "oled.h"
#include <stdlib.h>
#include <avr/interrupt.h>


#define MAIN_MENU_LENGTH 3


menu_node_t* main_menu;
menu_node_t* settings_menu;
menu_node_t* highscore_menu;


void menu_init() {
    main_menu = malloc(sizeof(menu_node_t));
    settings_menu = malloc(sizeof(menu_node_t));

    main_menu->length = MAIN_MENU_LENGTH;
    main_menu->content = malloc(sizeof(char*) * main_menu->length);
    
    main_menu->content[0] = "New game";
    main_menu->content[1] = "Settings";
    main_menu->content[2] = "Quit";

    main_menu->children = settings_menu;
    settings_menu->parent = main_menu;
}


// void menu_free() {
//     free(main_menu->content);
//     free(main_menu);

//     free(settings_menu->content);
//     free(settings_menu);

//     free(highscore_menu->content);
//     free(highscore_menu);
// }


void menu_print(font_type_t type) {
    char* content[3] = {"New game", "Settings", "Quit"};

    for (int i = 0; i < main_menu->length; i++) {
        oled_set_pos(2*i + 1, 8);
        oled_print_string(main_menu->content[i], type);
        //printf("%s", *main_menu.content[i]);
    }
}