#include "menu.h"
#include "oled.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>


#define MAIN_MENU_LENGTH 4


menu_t* menu;
menu_state_t state;


const char text_new_game[] PROGMEM = "New game";
const char text_settings[] PROGMEM = "Settings";
const char text_highscore[] PROGMEM = "Highscore";
const char text_quit[] PROGMEM = "Quit";


PGM_P const content_main_menu[] PROGMEM = {text_new_game, text_settings, text_highscore, text_quit};


void menu_init() {
    // initiate main menu
    menu = malloc(sizeof(menu_t));
    menu->length = MAIN_MENU_LENGTH;
    menu->parent = NULL;
    menu->content = content_main_menu;

    // add submenus
    // menu->children[0] = NULL;
    // menu->children[1] = malloc(sizeof(menu_t));
    // menu->children[2] = malloc(sizeof(menu_t));
    // menu->children[3] = NULL;
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
    char word[10];

    for (int i = 0; i < menu->length; i++) {
        strcpy_P(word, (PGM_P)pgm_read_word(&(menu->content[i])));

        oled_set_pos(i + 1, 8);
        oled_print_string(word, type);
    }    
}


ISR(INT1_vect) {
    oled_clear();
    oled_set_pos(1, 0);
    oled_print_string("Sug meg", LARGE);
}