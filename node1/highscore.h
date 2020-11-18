/**
 * @file
 * @brief Module for saving and updating highscores in the non-volatile EEPROM.
 */


#ifndef NODE1_HIGHSCORE_H
#define NODE1_HIGHSCORE_H


#include <stdint.h>


#define HIGHSCORE_LIST_LENGTH 3


/**
 * @brief Initiates the highscore by reading the highscore table
 * from the EEPROM memory.
 */
void highscore_init(void);


/**
 * @brief Updates the highscore, by comparing any new set scores
 * to the highscore table.
 */
void highscore_update(void);


/**
 * @brief Returns the highscore table.
 * 
 * @return The highscore table, as an array with three elements of
 * type @c uint16_t.
 */
uint16_t* highscore_get(void);


/**
 * @brief Resets the highscore table, setting all highscores to 0.
 */
void highscore_reset(void);


/**
 * @brief Sets a new score, which is compared to the highscore table
 * when @c highscore_update() is called.
 */
void highscore_set_new_score(uint16_t score);


#endif