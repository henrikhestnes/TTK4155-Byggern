#ifndef MENU_ACTION_FUNCTIONS
#define MENU_ACTION_FUNCTIONS


/**
 * @brief Starts a new game by transitioning the FSM to state
 * PLAYING.
 */
void start_new_game();


/**
 * @brief Selects the slider position controller.
 */
void select_controller_slider();


/**
 * @brief Selects the joystick speed controller.
 */
void select_controller_joystick();


/**
 * @brief Selects the microbit speed controller.
 */
void select_controller_microbit();


/**
 * @brief Selects the OLED screen brightness to high.
 */
void set_high_oled_brightness();


/**
 * @brief Selects the OLED screen brightness to medium.
 */
void set_medium_oled_brightness();


/**
 * @brief Selects the OLED screen brightness to low.
 */
void set_low_oled_brightness();


/**
 * @brief Plays the song "Mii Theme".
 */
void select_song_mii_theme();


/**
 * @brief Plays the song "Super Mario Bros Theme".
 */
void select_song_mario();


/**
 * @brief Plays the song "Hedwigs Theme" from Harry Potter.
 */
void select_song_harry_potter();


/**
 * @brief Plays the song "Savage Love".
 */
void select_song_savage_love();


/**
 * @brief Stops any playing music and returns to the main menu.
 */
void stop_music();


void set_difficulty_hard();


void set_difficulty_extreme();


void set_difficulty_impossible();


#endif