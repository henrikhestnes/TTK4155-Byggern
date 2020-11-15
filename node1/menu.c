#include "menu.h"
#include "oled.h"
#include "fonts.h"
#include "sram.h"
#include "user_input.h"
#include "fsm.h"
#include "can_driver.h"
#include "highscore.h"
#include "menu_action_functions.h"
#include "../common/can_id.h"
#include "../common/controller_select.h"
#include "../common/songs.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>


#define F_CPU 4.9152E6
#include <util/delay.h>


#define MAIN_MENU_LENGTH        3
#define SETTINGS_MENU_LENGTH    3
#define HIGHSCORE_MENU_LENGTH   2
// #define CONTROLLER_MENU_LENGTH  4
// #define BRIGHTNESS_MENU_LENGTH  4
#define MUSIC_MENU_LENGTH       5


static menu_node_t* current;
static int state;


static char state_changed = 0;
static char joystick_pushed = 0;
static char joystick_centered = 1;


const char text_new_game[] PROGMEM = "New game";
const char text_settings[] PROGMEM = "Settings";
const char text_highscore[] PROGMEM = "Highscore";
PGM_P const content_main_menu[] PROGMEM = {text_new_game, text_settings, text_highscore};

const char text_difficulty[] PROGMEM = "Set difficulty";
// const char text_brightness[] PROGMEM = "Set brightness";
const char text_music[] PROGMEM = "Play music";
// const char text_controller[] PROGMEM = "Set controller";
const char text_return[] PROGMEM = "Return";
PGM_P const content_settings[] PROGMEM = {text_difficulty, text_music,text_return};

// const char text_brightness_high[] PROGMEM = "High contrast";
// const char text_brightness_medium[] PROGMEM = "Medium contrast";
// const char text_brightness_low[] PROGMEM = "Low contrast";
// PGM_P const content_brightness[] PROGMEM = {text_brightness_high, text_brightness_medium, text_brightness_low, text_return};

// const char text_slider_controller[] PROGMEM = "Slider";
// const char text_joystick_controller[] PROGMEM = "Joystick";
// const char text_microbit_controller[] PROGMEM = "Microbit";
// PGM_P const content_controller[] PROGMEM = {text_slider_controller, text_joystick_controller, text_microbit_controller, text_return};

const char text_song_mii_theme[] PROGMEM = "Mii Theme";
const char text_song_mario[] PROGMEM = "Super Mario";
const char text_song_harry_potter[] PROGMEM = "Harry Potter";
const char text_song_savage_love[] PROGMEM = "Savage Love";
PGM_P const content_music[] PROGMEM = {text_song_mii_theme, text_song_mario, text_song_harry_potter, text_song_savage_love, text_return};

const char text_reset[] PROGMEM = "Reset";
PGM_P const content_highscore[] PROGMEM = {text_reset, text_return};


void menu_go_to_child() {
    current = current->child_menu->head;
    state = 0;
}


void menu_go_to_parent() {
    current = current->parent_menu->head;
    state = 0;
}


void sram_write_char(char c, int line, int index, int inverted) {
    for (int i = 0; i < FONT_LENGTH; i++) {
        uint8_t column = pgm_read_byte(&(font8[c - ASCII_OFFSET][i]));
        if (inverted) {
            sram_write(~column, line*NUMBER_OF_COLUMNS + index*FONT_LENGTH + i);
        }
        else {
            sram_write(column, line*NUMBER_OF_COLUMNS + index*FONT_LENGTH + i);
        }
    } 
}


void sram_write_line(char* word, int line, int inverted) {
    int i = 0;
    while(word[i] != '\0') {
        sram_write_char(word[i], line, i, inverted);
        ++i;
    }

    while (i < NUMBER_OF_COLUMNS / FONT_LENGTH) {
        sram_write_char(' ', line, i, inverted);
        ++i;
    }
}


char is_in_highscore_menu() {
    return current->own_menu->text_display == content_highscore;
}


void highscore_menu_write_to_sram() {
    sram_write_line("\0", 0, 0);
    sram_write_line("Highscores:", 1, 0);

    uint16_t* highscores = highscore_get();
    for (int i = 0; i < HIGHSCORE_LIST_LENGTH; i++) {
        char string[16];
        sprintf(string, "   %d. %d", i + 1, highscores[i]);
        sram_write_line(string, i + 2, 0);
    }

    sram_write_line("\0", 5, 0);
    
    char word[16];
    menu_t* current_menu = current->own_menu;
    for (int line = 0; line < HIGHSCORE_MENU_LENGTH; line++) {
        strcpy_P(word, (PGM_P) pgm_read_word(&(current_menu->text_display[line])));
        if (line == state) {
            sram_write_line(word, line + 6, 1);
        }
        else {
            sram_write_line(word, line + 6, 0);
        }
    }
    
    sram_write_line("\0", 8, 0);
}


void menu_write_to_sram() { 
    char word[16];
    menu_t* current_menu = current->own_menu;

    // reserve top line
    sram_write_line("\0", 0, 0);

    for (int line = 0; line < NUMBER_OF_PAGES; line++) {
        if (line < current_menu->length) {
            strcpy_P(word, (PGM_P) pgm_read_word(&(current_menu->text_display[line])));
            if (line == state) {
                sram_write_line(word, line + 1, 1);
            }
            else {
                sram_write_line(word, line + 1, 0);
            }
        }
        else {
            sram_write_line("\0", line + 1, 0);
        }

    }
}


void menu_timer_init() {
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;

    // set compare match register for 30 hz
    OCR1A = 159;

    // set to CTC mode
    TCCR1B |= (1 << WGM12);

    // set prescaler 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);

    // enable timer compare interrupt
    TIMSK |= (1 << OCIE1A);
}


void menu_timer_enable() {
    cli();

    TIMSK |= (1 << OCIE1A);

    sei();
}


void menu_timer_disable() {
    cli();

    TIMSK &= ~(1 << OCIE1A);

    sei();
}


void menu_init() {
    menu_t* main_menu = menu_new(content_main_menu, MAIN_MENU_LENGTH);
    menu_t* settings_menu = menu_new(content_settings, SETTINGS_MENU_LENGTH);
    menu_t* highscore_menu = menu_new(content_highscore, HIGHSCORE_MENU_LENGTH);
    // menu_t* controller_menu = menu_new(content_controller, CONTROLLER_MENU_LENGTH);
    // menu_t* brightness_menu = menu_new(content_brightness, BRIGHTNESS_MENU_LENGTH);
    menu_t* music_menu = menu_new(content_music, MUSIC_MENU_LENGTH);

    // main menu linked list
    menu_node_t* new_game_node = menu_new_node(NULL, main_menu, NULL, start_new_game);
    menu_node_t* settings_node = menu_new_node(NULL, main_menu, settings_menu, menu_go_to_child);
    menu_node_t* highscore_node = menu_new_node(NULL, main_menu, highscore_menu, menu_go_to_child);

    menu_link_nodes(new_game_node, settings_node);
    menu_link_nodes(settings_node, highscore_node);
    menu_link_nodes(highscore_node, new_game_node);

    main_menu->head = new_game_node;

    // settings menu linked list
    menu_node_t* difficulty_node = menu_new_node(main_menu, settings_menu, NULL, NULL);
    // menu_node_t* brightness_node = menu_new_node(main_menu, settings_menu, brightness_menu, menu_go_to_child);
    menu_node_t* music_node = menu_new_node(main_menu, settings_menu, music_menu, menu_go_to_child);
    // menu_node_t* controller_node = menu_new_node(main_menu, settings_menu, controller_menu, menu_go_to_child);
    menu_node_t* settings_return_node = menu_new_node(main_menu, settings_menu, NULL, menu_go_to_parent);

    menu_link_nodes(difficulty_node, music_node);
    menu_link_nodes(music_node, settings_return_node);
    menu_link_nodes(settings_return_node, difficulty_node);

    settings_menu->head = difficulty_node;

    // highscore menu linked list
    menu_node_t* reset_node = menu_new_node(main_menu, highscore_menu, NULL, highscore_reset);
    menu_node_t* highscore_return_node = menu_new_node(main_menu, highscore_menu, NULL, menu_go_to_parent);

    menu_link_nodes(reset_node, highscore_return_node);
    menu_link_nodes(highscore_return_node, reset_node);

    highscore_menu->head = reset_node;

    // brightness menu linked list
    // menu_node_t* high_node = menu_new_node(settings_menu, brightness_menu, NULL, set_high_oled_brightness);
    // menu_node_t* medium_node = menu_new_node(settings_menu, brightness_menu, NULL, set_medium_oled_brightness);
    // menu_node_t* low_node = menu_new_node(settings_menu, brightness_menu, NULL, set_low_oled_brightness);
    // menu_node_t* brightness_return_node = menu_new_node(settings_menu, brightness_menu, NULL, menu_go_to_parent);

    // menu_link_nodes(high_node, medium_node);
    // menu_link_nodes(medium_node, low_node);
    // menu_link_nodes(low_node, brightness_return_node);
    // menu_link_nodes(brightness_return_node, high_node);

    // brightness_menu->head = high_node;

    // music menu linked list
    menu_node_t* mii_theme_node = menu_new_node(settings_menu, music_menu, NULL, select_song_mii_theme);
    menu_node_t* mario_node = menu_new_node(settings_menu, music_menu, NULL, select_song_mario);
    menu_node_t* harry_potter_node = menu_new_node(settings_menu, music_menu, NULL, select_song_harry_potter);
    menu_node_t* savage_love_node = menu_new_node(settings_menu, music_menu, NULL, select_song_savage_love);
    menu_node_t* music_return_node = menu_new_node(settings_menu, music_menu, NULL, stop_music);

    menu_link_nodes(mii_theme_node, mario_node);
    menu_link_nodes(mario_node, harry_potter_node);
    menu_link_nodes(harry_potter_node, savage_love_node);
    menu_link_nodes(savage_love_node, music_return_node);
    menu_link_nodes(music_return_node, mii_theme_node);

    music_menu->head = mii_theme_node;

    // controller menu linked list
    // menu_node_t* slider_node = menu_new_node(settings_menu, controller_menu, NULL, select_controller_slider);
    // menu_node_t* joystick_node = menu_new_node(settings_menu, controller_menu, NULL, select_controller_joystick);
    // menu_node_t* microbit_node = menu_new_node(settings_menu, controller_menu, NULL, select_controller_microbit);
    // menu_node_t* controller_return_node = menu_new_node(settings_menu, controller_menu, NULL, menu_go_to_parent);

    // menu_link_nodes(slider_node, joystick_node);
    // menu_link_nodes(joystick_node, microbit_node);
    // menu_link_nodes(microbit_node, controller_return_node);
    // menu_link_nodes(controller_return_node, slider_node);

    // controller_menu->head = slider_node;

    // init the current state node
    current = new_game_node;
    state = 0;
    oled_clear();
    menu_write_to_sram();
    menu_timer_init();
}


menu_t* menu_new(const char* const* text_display, int length) {
    menu_t* menu = malloc(sizeof(menu_t));
    menu->text_display = text_display;
    menu->length = length;
    menu->head = NULL;

    return menu;
}


menu_node_t* menu_new_node(menu_t* parent_menu, menu_t* own_menu, menu_t* child_menu, void (*action_function)()) {
    menu_node_t* node = malloc(sizeof(menu_node_t));
    if (!node) {
        printf("FAILED TO ALLOCATE");
    }
    node->parent_menu = parent_menu;
    node->own_menu = own_menu;
    node->child_menu = child_menu;
    node->action_function = action_function;

    node->next = NULL;
    node->prev = NULL;

    return node;
}


void menu_link_nodes(menu_node_t* first, menu_node_t* second) {
    first->next = second;
    second->prev = first;
}


void menu_run() {
    int joystick_button = user_input_buttons().joystick;
    if (joystick_button && !joystick_pushed) {
        joystick_pushed = 1;
        if (current->action_function) {
            current->action_function();
        }
    }
    else if (!joystick_button) {
        joystick_pushed = 0;
    }

    switch (user_input_joystick_dir()) {
        case UP:
            if (!joystick_centered) {
                break;
            }

            current = current->prev;

            if (state == 0) {
                state = current->own_menu->length - 1;
            }
            else {
                --state;
            }

            state_changed = 1;
            joystick_centered = 0;
            break;

        case DOWN:
            if (!joystick_centered) {
                break;
            }

            current = current->next;

            if (state == current->own_menu->length - 1) {
                state = 0;
            }
            else {
                ++state;
            }

            state_changed = 1;
            joystick_centered = 0;
            break;

        case CENTER:
            joystick_centered = 1;

        default:
            break;
    }
    

    if (state_changed) {
        if (is_in_highscore_menu()) {
            highscore_menu_write_to_sram();
        }
        else {
            menu_write_to_sram();
        }
    }
}


ISR(TIMER1_COMPA_vect) {
    oled_print_from_sram();
}


ISR(INT1_vect) {
    if (current->action_function) {
        current->action_function();
    }
}


// void menu_print() {
//     oled_clear();
//     char word[20];
//     menu_t* current_menu = current->own_menu;

//     for (int i = 0; i < current_menu->length; i++) {
//         strcpy_P(word, (PGM_P)pgm_read_word(&(current_menu->text_display[i])));
//         oled_set_pos(i+1, 8);
//         if (i == state) {
//             oled_print_inverted_string(word);
//         }
//         else {
//             oled_print_string(word);
//         }
//     }
// }



// void settings_menu() {
//     menu_init_settings();
//     menu_run();
// }


// void main_menu() {
//     menu_init_main();
//     menu_run();
// }