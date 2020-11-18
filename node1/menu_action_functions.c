#include "menu_action_functions.h"
#include "menu.h"
#include "oled.h"
#include "fsm.h"
#include "can_driver.h"
#include "../common/can.h"
#include "../common/controller_select.h"
#include "../common/songs.h"
#include "../common/difficulty_select.h"


void start_new_game() {
    fsm_transition_to(STATE_PLAYING);
}


static void select_controller(CONTROLLER_SEL controller) {
    CAN_MESSAGE m = {
        .id = CONTROLLER_ID,
        .data_length = 1,
        .data = {controller}
    };

    can_send(&m);
}


void select_controller_slider() {
    select_controller(SLIDER_POS_CTRL);
    menu_go_to_parent();
}


void select_controller_joystick() {
    select_controller(JOYSTICK_SPEED_CTRL);
    menu_go_to_parent();
}


void select_controller_microbit() {
    select_controller(MICROBIT_SPEED_CTRL);
    menu_go_to_parent();
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
    CAN_MESSAGE stop_message = {
        .id = MUSIC_SONG_ID,
        .data_length = 1,
        .data = {STOP}
    };
    can_send(&stop_message);   

    CAN_MESSAGE song_message = {
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
    CAN_MESSAGE stop_message = {
        .id = MUSIC_SONG_ID,
        .data_length = 1,
        .data = {STOP}
    };

    can_send(&stop_message);   
    menu_go_to_parent();
}


static void select_difficulty(DIFFICULTY diff) {
    CAN_MESSAGE difficulty_message = {
        .id = GAME_DIFFICULTY_ID,
        .data_length = 1,
        .data = {diff}
    };
    can_send(&difficulty_message);
}


void set_difficulty_hard() {
    select_difficulty(HARD);
    menu_go_to_parent();
}


void set_difficulty_extreme() {
    select_difficulty(EXTREME);
    menu_go_to_parent();
}


void set_difficulty_impossible() {
    select_difficulty(IMPOSSIBLE);
    menu_go_to_parent();
}