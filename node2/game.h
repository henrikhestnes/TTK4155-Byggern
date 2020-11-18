#ifndef NODE2_GAME_H
#define NODE2_GAME_H


/**
* @file
* @brief Module for game-fuctionality
*/


#include "../common/controller_select.h"
#include "../common/difficulty_select.h"


#define INITIAL_LIVES       3


/**
 * @brief Initiates the game by resetting the score and lives left,
 * enabling the timer for timed updating of the game signals, and
 * initiating the PID controller for the motor.
 */
void game_init(void);


/**
 * @brief Checks if the IR beam is disrupted by the ball. Decreases the
 * number of lives left if this is the case.
 *
 * @return 1 if the IR beam is disrupted, 0 if not.
 */
int game_count_fails(void);


/**
 * @brief Updates the user input data.
 *
 * @param data An array with new user input data, in the order
 * {joystick.x, joystick.y, slider.right, slider.left, buttons.left, buttons.right}.
 */
void game_set_user_data(char* data);


/**
 * @brief Selects the controller to be used in the game.
 *
 * @param controller The controller option of data type @c CONTROLLER_SEL
 * to be used in the game.
 */
void game_set_controller(CONTROLLER_SEL controller);


/**
 * @brief Selects the difficulty to be used in the game.
 *
 * @param controller The difficulty option of data type @c DIFFICULTY
 * to be used in the game.
 */
void game_set_difficulty(DIFFICULTY difficulty);


/**
 * @brief Enables the timer which runs the game.
 */
void game_timer_enable();


/**
 * @brief Disables the timer which runs the game.
 */
void game_timer_disable();


/**
 * @brief Returns the score of a game, which is
 * increased by 50 every seconds.
 *
 * @return The score of a game.
 */
int game_get_score();


/**
 * @brief Resets the score of a game.
 */
void game_reset_score();


/**
 * @brief Resets the number of lives left in a game.
 */
void game_reset_lives_left();


#endif
