#include "menu_action_functions.h"
#include "menu.h"
#include "oled.h"
#include "fsm.h"
#include "can_driver.h"
#include "../common/can_id.h"
#include "../common/controller_select.h"
#include "../common/songs.h"


void start_new_game() {
    fsm_transition_to(PLAYING);
}


void select_controller_slider() {
    message_t m = {
        .id = CONTROLLER_ID,
        .length = 1,
        .data = {SLIDER_POS_CTRL}
    };

    can_transmit(&m);
    menu_go_to_parent();
}


void select_controller_joystick() {
    message_t m = {
        .id = CONTROLLER_ID,
        .length = 1,
        .data = {JOYSTICK_SPEED_CTRL}
    };

    can_transmit(&m);
    menu_go_to_parent();
}


void select_controller_microbit() {
    message_t m = {
        .id = CONTROLLER_ID,
        .length = 1,
        .data = {MICROBIT_SPEED_CTRL}
    };

    can_transmit(&m);
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


void select_song_mii_theme() {
    message_t stop_message = {
        .id = MUSIC_SONG_ID,
        .length = 1,
        .data = {STOP}
    };
    can_transmit(&stop_message);

    message_t m = {
        .id = MUSIC_SONG_ID,
        .length = 1,
        .data = {MII_THEME}
    };
    can_transmit(&m);
}


void select_song_mario() {
    message_t stop_message = {
        .id = MUSIC_SONG_ID,
        .length = 1,
        .data = {STOP}
    };
    can_transmit(&stop_message);

    message_t m = {
        .id = MUSIC_SONG_ID,
        .length = 1,
        .data = {MARIO}
    };
    can_transmit(&m);
}


void select_song_harry_potter() {
    message_t stop_message = {
        .id = MUSIC_SONG_ID,
        .length = 1,
        .data = {STOP}
    };
    can_transmit(&stop_message);

    message_t m = {
        .id = MUSIC_SONG_ID,
        .length = 1,
        .data = {HARRY_POTTER}
    };
    can_transmit(&m);
}


void select_song_savage_love() {
    message_t stop_message = {
        .id = MUSIC_SONG_ID,
        .length = 1,
        .data = {STOP}
    };
    can_transmit(&stop_message);

    message_t m = {
        .id = MUSIC_SONG_ID,
        .length = 1,
        .data = {SAVAGE_LOVE}
    };
    can_transmit(&m);
}


void stop_music() {
    message_t stop_message = {
        .id = MUSIC_SONG_ID,
        .length = 1,
        .data = {STOP}
    };

    can_transmit(&stop_message);   
    menu_go_to_parent();
}