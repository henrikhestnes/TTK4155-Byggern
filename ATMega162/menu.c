#include "menu.h"
#include "oled.h"
#include "joystick.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>


#define F_CPU 4.9152E6
#include <util/delay.h> 


#define MAIN_MENU_LENGTH 4
#define SETTINGS_LENGTH 4
#define HIGHSCORE_LENGTH 3


static menu_node_t* current;
char state_changed;
int state;


const char text_new_game[] PROGMEM = "New game";
const char text_settings[] PROGMEM = "Settings";
const char text_highscore[] PROGMEM = "Highscore";
const char text_quit[] PROGMEM = "Quit";
PGM_P const content_main_menu[] PROGMEM = {text_new_game, text_settings, text_highscore, text_quit};

const char text_difficulty[] PROGMEM = "Select difficulty";
const char text_brightness[] PROGMEM = "Change brightness";
const char text_music[] PROGMEM = "Select music";
const char text_return[] PROGMEM = "Return";
PGM_P const content_settings[] PROGMEM = {text_difficulty, text_brightness, text_music, text_return};

const char text_reset[] PROGMEM = "Reset";
PGM_P const content_highscore[] PROGMEM = {text_highscore, text_reset, text_return};


void menu_init() {
    menu_t* main_menu = menu_new(content_main_menu, MAIN_MENU_LENGTH);
    menu_t* settings_menu = menu_new(content_settings, SETTINGS_LENGTH);
    menu_t* highscore_menu = menu_new(content_highscore, HIGHSCORE_LENGTH);

    // main menu linked list
    menu_node_t* new_game_node = menu_new_node(main_menu, NULL, NULL);
    menu_node_t* settings_node = menu_new_node(main_menu, settings_menu, go_to_child);
    menu_node_t* highscore_node = menu_new_node(main_menu, highscore_menu, go_to_child);
    menu_node_t* quit_node = menu_new_node(main_menu, NULL, NULL);

    menu_link_nodes(new_game_node, settings_node);
    menu_link_nodes(settings_node, highscore_node);
    menu_link_nodes(highscore_node, quit_node);
    menu_link_nodes(quit_node, new_game_node);

    main_menu->head = new_game_node;

    // settings menu linked list
    menu_node_t* difficulty_node = menu_new_node(settings_menu, NULL, NULL);
    menu_node_t* brightness_node = menu_new_node(settings_menu, NULL, NULL);
    menu_node_t* music_node = menu_new_node(settings_menu, NULL, NULL);
    menu_node_t* settings_return_node = menu_new_node(settings_menu, NULL, go_to_parent);

    menu_link_nodes(difficulty_node, brightness_node);
    menu_link_nodes(brightness_node, music_node);
    menu_link_nodes(music_node, settings_return_node);
    menu_link_nodes(settings_return_node, difficulty_node);

    settings_menu->head = difficulty_node;

    // highscore menu linked list
    menu_node_t* reset_node = menu_new_node(highscore_menu, NULL, NULL);
    menu_node_t* highscore_return_node = menu_new_node(highscore_menu, NULL, go_to_parent);

    menu_link_nodes(reset_node, highscore_return_node);

    highscore_menu->head = reset_node;

    // init the current state node
    current = new_game_node;
    state = 0;
    menu_print(LARGE);
}


menu_t* menu_new(const char* const* text_display, int length) {
    menu_t* menu = malloc(sizeof(menu_t));
    menu->text_display = text_display;
    menu->length = length;
    menu->head = NULL;

    return menu;
}


menu_node_t* menu_new_node(menu_t* parent_menu, menu_t* child_menu, void (*action_function)()) {
    menu_node_t* node = malloc(sizeof(menu_node_t));
    node->child_menu = child_menu;
    node->parent_menu = parent_menu;
    node->action_function = action_function;

    node->next = NULL;
    node->prev = NULL;

    return node;
}


void menu_print(font_type_t type) {
    char word[20];
    menu_t* current_menu = current->parent_menu;

    for (int i = 0; i < current_menu->length; i++){
        strcpy_P(word, (PGM_P)pgm_read_word(&(current_menu->text_display[i])));
        oled_set_pos(i+1, 8);
        if (i == state){
            oled_print_inverted_string(word,LARGE);
        }
        else{
            oled_print_string(word, LARGE);
        }
    }
}


void menu_link_nodes(menu_node_t* first, menu_node_t* second) {
    first->next = second;
    second->prev = first;
}


void menu_run() {
    switch (joystick_get_dir()) {
        case UP:
            if (state == 0) {
                state = current->parent_menu->length - 1;
            }
            else {
                --state;
            }
            state_changed = 1;
            break;

        case DOWN:
            if (state == current->parent_menu->length - 1) {
                state = 0;
            }
            else{
                ++state;
            }
            state_changed = 1;
        
        case CENTER:

        default:
            break;
    }

    _delay_ms(150);
}


void go_to_child() {
    current = current->child_menu->head;
    state = 0;
}


void go_to_parent() {
    current = current->parent_menu->head;
    state = 0;
}


ISR(INT1_vect) {
    if (current->action_function) {
        current->action_function();
    }
}


ISR(TIMER1_COMPA_vect){
    if (!state_changed) {
        return;
    }

    state_changed = 0;
    menu_print(LARGE);
}