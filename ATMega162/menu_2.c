// #include "menu.h"
// #include "oled.h"
// #include "joystick.h"
// #include <stdlib.h>
// #include <avr/interrupt.h>
// #include <avr/pgmspace.h>


// #define F_CPU 4.9152E6
// #include <util/delay.h> 


// #define MAIN_MENU_LENGTH 4
// #define SETTINGS_LENGTH 3
// #define HIGHSCORE_LENGTH 3


// menu_t* menu;
// menu_state_t state;


// // char one_scroll_per_joystick_move;


// char state_changed;


// const char text_new_game[] PROGMEM = "New game";
// const char text_settings[] PROGMEM = "Settings";
// const char text_highscore[] PROGMEM = "Highscore";
// const char text_quit[] PROGMEM = "Quit";
// PGM_P const content_main_menu[] PROGMEM = {text_new_game, text_settings, text_highscore, text_quit};

// const char text_difficulty[] PROGMEM = "Select difficulty";
// const char text_brightness[] PROGMEM = "Change brightness";
// const char text_music[] PROGMEM = "Select music";
// const char text_return[] PROGMEM = "Return";
// PGM_P const content_settings[] PROGMEM = {text_difficulty, text_brightness, text_music, text_return};

// const char text_reset[] PROGMEM = "Reset";
// PGM_P const content_highscore[] PROGMEM = {text_reset, text_return};


// void menu_init() {
//     // initiate main menu
//     menu = malloc(sizeof(menu_t));
//     menu->length = MAIN_MENU_LENGTH;
//     menu->parent = NULL;
//     menu->content = content_main_menu;


//     state = MAIN_MENU_NEW_GAME;
//     state_changed = 0;

//     // one_scroll_per_joystick_move = 1;

//     // add submenus
//     menu_add_submenu(menu, 4);
//     // new game
//     menu_add_submenu_content(menu->children[0], NULL, 0);
//     // highscore
//     menu_add_submenu_content(menu->children[1], content_highscore, 1);
//     // settings
//     menu_add_submenu_content(menu->children[2], content_settings, 3);
//     // quit
//     menu_add_submenu_content(menu->children[3], NULL, 0);


//     menu_print(LARGE);
// }


// void menu_add_submenu(menu_t* parent, int length) {
//     menu_t* submenu = malloc(sizeof(menu_t)*length);
//     submenu->parent = parent;
//     submenu->children = NULL;

//     parent->children = &submenu;
// }


// void menu_add_submenu_content(menu_t* submenu, const char* const* content, int content_length) {
//     submenu->length = content_length;
//     submenu->content = content;
// }


// void menu_print(font_type_t type) {
//     char word[20];
//     for(int i = 0; i<menu->length; i++){
//         strcpy_P(word, (PGM_P)pgm_read_word(&(menu->content[i])));
//         oled_set_pos(i+1,8);
//         if (i==state){
//             oled_print_inverted_string(word,LARGE);
//         }
//         else{
//             oled_print_string(word, LARGE);
//         }
//     }
// }
// //     char word[20];
// //     strcpy_P(word, (PGM_P)pgm_read_word(&(menu->content[0])));

// //     oled_set_pos(0,8);
// //     oled_print_inverted_string(word, type);

// //     for (int i = 1; i < menu->length; i++) {
// //         strcpy_P(word, (PGM_P)pgm_read_word(&(menu->content[i])));

// //         oled_set_pos(i, 8);
// //         oled_print_string(word, type);
// //     }    
// // }



// void menu_run(){
//     // switch (joystick_get_dir(joystick_pos_read())){
//     //     case UP:{
//     //         if (one_scroll_per_joystick_move){
//     //             if (state==0){
//     //                 state = menu->typedef struct {
//     //     const char* const text_display;
//     // }length-1;
//     //             }
//     //             else{
//     //                 state -=1;
//     //             }
//     //             one_scroll_per_joystick_move = 0;
//     //         }
//     //         break;
//     //     }
//     //     case DOWN:{
//     //         if (one_scroll_per_joystick_move){
//     //             if (state==menu->length-1){
//     //                 state=0;
//     //             }
//     //             else{
//     //                 state+=1;
//     //             }
//     //             one_scroll_per_joystick_move = 0;
//     //         }
//     //         break;
//     //     }
//     //     case CENTER:
//     //         one_scroll_per_joystick_move = 1;
//     //         break;
//     // }
    
    
//     switch (joystick_get_dir()) {
//         case UP:
//             if (state == 0) {
//                 state = menu->length - 1;
//             }
//             else {
//                 --state;
//             }
//             state_changed = 1;
//             break;

//         case DOWN:
//             if (state == menu->length - 1) {
//                 state = 0;
//             }
//             else{
//                 ++state;
//             }
//             state_changed = 1;
        
//         case CENTER:

//         default:
//             break;
//     }

//     _delay_ms(150);
// }


// ISR(INT1_vect) {

// }


// ISR(TIMER1_COMPA_vect){
//     if (!state_changed) {
//         return;
//     }

//     state_changed = 0;
//     menu_print(LARGE);
// }