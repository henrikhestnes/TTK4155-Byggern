#include "menu.h"
#include "oled.h"
#include "fonts.h"
#include "sram.h"
#include "user_input.h"
#include "highscore.h"
#include "menu_action_functions.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>


#define MAIN_MENU_LENGTH        4
#define SETTINGS_MENU_LENGTH    4
#define HIGHSCORE_MENU_LENGTH   2
#define MUSIC_MENU_LENGTH       5
#define BRIGHTNESS_MENU_LENGTH  4
#define CONTROLLER_MENU_LENGTH  4
#define DIFFICULTY_MENU_LENGTH  4


typedef void (*action_function)();


static menu_t* current;
static uint8_t state;


static char state_changed = 0;
static char joystick_pushed = 0;
static char joystick_centered = 1;


const char text_new_game[] PROGMEM = "New game";
const char text_settings[] PROGMEM = "Settings";
const char text_highscore[] PROGMEM = "Highscore";
const char text_music[] PROGMEM = "Play music";
PGM_P const content_main_menu[] PROGMEM = {text_new_game, text_settings, text_highscore, text_music};

const char text_difficulty[] PROGMEM = "Set difficulty";
const char text_brightness[] PROGMEM = "Set brightness";
const char text_controller[] PROGMEM = "Set controller";
const char text_return[] PROGMEM = "Return";
PGM_P const content_settings[] PROGMEM = {text_difficulty, text_brightness, text_controller, text_return};

const char text_song_mii_theme[] PROGMEM = "Mii Theme";
const char text_song_mario[] PROGMEM = "Super Mario";
const char text_song_harry_potter[] PROGMEM = "Harry Potter";
const char text_song_savage_love[] PROGMEM = "Savage Love";
PGM_P const content_music[] PROGMEM = {text_song_mii_theme, text_song_mario, text_song_harry_potter, text_song_savage_love, text_return};

const char text_reset[] PROGMEM = "Reset";
PGM_P const content_highscore[] PROGMEM = {text_reset, text_return};

const char text_brightness_high[] PROGMEM = "High contrast";
const char text_brightness_medium[] PROGMEM = "Medium contrast";
const char text_brightness_low[] PROGMEM = "Low contrast";
PGM_P const content_brightness[] PROGMEM = {text_brightness_high, text_brightness_medium, text_brightness_low, text_return};

const char text_slider_controller[] PROGMEM = "Slider";
const char text_joystick_controller[] PROGMEM = "Joystick";
const char text_microbit_controller[] PROGMEM = "Microbit";
PGM_P const content_controller[] PROGMEM = {text_slider_controller, text_joystick_controller, text_microbit_controller, text_return};

const char text_difficulty_hard[] PROGMEM = "Hard";
const char text_difficulty_extreme[] PROGMEM = "Extreme";
const char text_difficulty_impossible[] PROGMEM = "Impossible";
PGM_P const content_difficulty[] PROGMEM = {text_difficulty_hard, text_difficulty_extreme, text_difficulty_impossible, text_return};


static void menu_timer_init() {
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


void menu_go_to_parent() {
    current = current->parent;
    state = 0;
}


void menu_go_to_child() {
    current = current->submenus[state];
    state = 0;
}


static menu_t* menu_new(const char* const* text_display, uint8_t length, menu_t* parent) {
    menu_t* menu = malloc(sizeof(menu_t) + length * sizeof(action_function) + MAX_SUBMENU_NUMBER * sizeof(menu_t*));

    // check for successful allocation
    if (menu) {
        menu->text_display = text_display;
        menu->length = length;
        menu->parent = parent;

        for (uint8_t i = 0; i < length; ++i) {
            menu->submenus[i] = NULL;
            menu->action_functions[i] = NULL;
        }

        return menu;
    }

    else { 
        return NULL;
    }
}


static void menu_config_node(menu_t* menu, uint8_t node, menu_t* submenu, action_function func) {
    menu->submenus[node] = submenu;
    menu->action_functions[node] = func;
}


static menu_t* menu_allocate() {
    // dynamically allocate menus
    menu_t* main_menu = menu_new(content_main_menu, MAIN_MENU_LENGTH, NULL);
    menu_t* settings_menu = menu_new(content_settings, SETTINGS_MENU_LENGTH, main_menu);
    menu_t* highscore_menu = menu_new(content_highscore, HIGHSCORE_MENU_LENGTH, main_menu);
    menu_t* music_menu = menu_new(content_music, MUSIC_MENU_LENGTH, main_menu);
    menu_t* controller_menu = menu_new(content_controller, CONTROLLER_MENU_LENGTH, settings_menu);
    menu_t* brightness_menu = menu_new(content_brightness, BRIGHTNESS_MENU_LENGTH, settings_menu);
    menu_t* difficulty_menu = menu_new(content_difficulty, DIFFICULTY_MENU_LENGTH, settings_menu);
    
    // configure main menu
    menu_config_node(main_menu, 0, NULL, start_new_game);
    menu_config_node(main_menu, 1, settings_menu, menu_go_to_child);
    menu_config_node(main_menu, 2, highscore_menu, menu_go_to_child);
    menu_config_node(main_menu, 3, music_menu, menu_go_to_child);

    // configure settings menu
    menu_config_node(settings_menu, 0, difficulty_menu, menu_go_to_child);
    menu_config_node(settings_menu, 1, brightness_menu, menu_go_to_child);
    menu_config_node(settings_menu, 2, controller_menu, menu_go_to_child);
    menu_config_node(settings_menu, 3, NULL, menu_go_to_parent);

    // configure highscore menu
    menu_config_node(highscore_menu, 0, NULL, highscore_reset);
    menu_config_node(highscore_menu, 1, NULL, menu_go_to_parent);

    // configure music menu
    menu_config_node(music_menu, 0, NULL, select_song_mii_theme);
    menu_config_node(music_menu, 1, NULL, select_song_mario);
    menu_config_node(music_menu, 2, NULL, select_song_harry_potter);
    menu_config_node(music_menu, 3, NULL, select_song_savage_love);
    menu_config_node(music_menu, 4, NULL, stop_music);

    // configure brightness menu
    menu_config_node(brightness_menu, 0, NULL, set_high_oled_brightness);
    menu_config_node(brightness_menu, 1, NULL, set_medium_oled_brightness);
    menu_config_node(brightness_menu, 2, NULL, set_low_oled_brightness);
    menu_config_node(brightness_menu, 3, NULL, menu_go_to_parent);

    // configure controller select menu
    menu_config_node(controller_menu, 0, NULL, select_controller_slider);
    menu_config_node(controller_menu, 1, NULL, select_controller_joystick);
    menu_config_node(controller_menu, 2, NULL, select_controller_microbit);
    menu_config_node(controller_menu, 3, NULL, menu_go_to_parent);

    // configure difficulty menu
    menu_config_node(difficulty_menu, 0, NULL, set_difficulty_hard);
    menu_config_node(difficulty_menu, 1, NULL, set_difficulty_extreme);
    menu_config_node(difficulty_menu, 2, NULL, set_difficulty_impossible);
    menu_config_node(difficulty_menu, 3, NULL, menu_go_to_parent);

    return main_menu;
}


static char is_in_highscore_menu() {
    return current->text_display == content_highscore;
}


static void sram_write_char(char* c, uint8_t line, uint8_t index, uint8_t inverted) {
    for (uint8_t i = 0; i < FONT_LENGTH; ++i) {
        uint8_t column = pgm_read_byte(&(font8[*c - ASCII_OFFSET][i]));
        if (inverted) {
            sram_write(~column, line*NUMBER_OF_COLUMNS + index*FONT_LENGTH + i);
        }
        else {
            sram_write(column, line*NUMBER_OF_COLUMNS + index*FONT_LENGTH + i);
        }
    } 
}


static void sram_write_line(char* word, uint8_t line, uint8_t inverted) {
    uint8_t i = 0;
    while(word[i] != '\0') {
        sram_write_char(&word[i], line, i, inverted);
        ++i;
    }

    while (i < NUMBER_OF_COLUMNS / FONT_LENGTH) {
        char c = ' ';
        sram_write_char(&c, line, i, inverted);
        ++i;
    }
}


static void menu_write_to_sram() { 
    // reserve top line
    sram_write_line("\0", 0, 0);

    // write the current menu text display
    char word[16];
    for (uint8_t line = 0; line < NUMBER_OF_PAGES; line++) {
        if (line < current->length) {
            strcpy_P(word, (PGM_P) pgm_read_word(&(current->text_display[line])));
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


static void highscore_menu_write_to_sram() {
    // reserve top line, write title
    sram_write_line("\0", 0, 0);
    sram_write_line("Highscores:", 1, 0);

    // write current highscores
    uint16_t* highscores = highscore_get();
    for (uint8_t i = 0; i < HIGHSCORE_LIST_LENGTH; ++i) {
        char string[16];
        sprintf(string, "   %d. %d", i + 1, highscores[i]);
        sram_write_line(string, i + 2, 0);
    }

    // reserve line
    sram_write_line("\0", 5, 0);
    
    // write highscore menu text display
    char word[16];
    for (uint8_t line = 0; line < HIGHSCORE_MENU_LENGTH; line++) {
        strcpy_P(word, (PGM_P) pgm_read_word(&(current->text_display[line])));
        if (line == state) {
            sram_write_line(word, line + 6, 1);
        }
        else {
            sram_write_line(word, line + 6, 0);
        }
    }
    
    // reserve bottom line
    sram_write_line("\0", 8, 0);
}


void menu_init() {
    current = menu_allocate();
    state = 0;
    oled_clear();
    menu_write_to_sram();
    menu_timer_init();
}


void menu_run() {
    char joystick_button = user_input_buttons().joystick;
    if (joystick_button && !joystick_pushed) {
        joystick_pushed = 1;

        if (current->action_functions[state]) {
            current->action_functions[state]();
            state_changed = 1;
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

            if (state == 0) {
                state = current->length - 1;
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

            if (state == current->length - 1) {
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
            break;

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