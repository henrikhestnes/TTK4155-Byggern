#include "menu_action_functions.h"
#include "menu.h"
#include "oled.h"
#include "fsm.h"
#include "can_driver.h"
#include "../common/can_id.h"
#include "../common/controller_select.h"
#include "../common/songs.h"
#include "../common/difficulty_select.h"


void start_new_game() {
    fsm_transition_to(PLAYING);
}


static void select_controller(CONTROLLER_SEL controller) {
    message_t m = {
        .id = CONTROLLER_ID,
        .data_length = 1,
        .data = {controller}
    };

    can_send(&m);
    menu_go_to_parent();
}


void select_controller_slider() {
    select_controller(SLIDER_POS_CTRL);
}


void select_controller_joystick() {
    select_controller(JOYSTICK_SPEED_CTRL);
}


void select_controller_microbit() {
    select_controller(MICROBIT_SPEED_CTRL);
}


void set_high_oled_brightness() {
    oled_set_brightness(0xff);
    menu_go_to_parent();
}


void set_medium_oled_brightness() {
    oled_set_brightness(0x7f);
    menu_go_to_parent();
}


void set_low_oled_brightness() {
    oled_set_brightness(0x0f);
    menu_go_to_parent();
}


static void select_song(SONG song) {
    message_t stop_message = {
        .id = MUSIC_SONG_ID,
        .data_length = 1,
        .data = {STOP}
    };
    can_send(&stop_message);   

    message_t song_message = {
        .id = MUSIC_SONG_ID,
        .data_length = 1,
        .data = {song}
    };
    can_send(&song_message);
}


void select_song_mii_theme() {
    select_song(MII_THEME);
}


void select_song_mario() {
    select_song(MARIO);
}


void select_song_harry_potter() {
    select_song(HARRY_POTTER);
}


void select_song_savage_love() {
    select_song(SAVAGE_LOVE);
}


void stop_music() {
    message_t stop_message = {
        .id = MUSIC_SONG_ID,
        .data_length = 1,
        .data = {STOP}
    };

    can_send(&stop_message);   
    menu_go_to_parent();
}


static void select_difficulty(DIFFICULTY diff) {
    message_t difficulty_message = {
        .id = GAME_DIFFICULTY_ID,
        .data_length = 1,
        .data = {diff}
    };
    can_send(&difficulty_message);
    menu_go_to_parent();
}


void set_difficulty_hard() {
    select_difficulty(HARD);
}


void set_difficulty_extreme() {
    select_difficulty(EXTREME);
}


void set_difficulty_impossible() {
    select_difficulty(IMPOSSIBLE);
}