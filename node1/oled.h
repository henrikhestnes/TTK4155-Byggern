/**
 * @file
 * @brief Module for controlling and printing to the OLED screen. 
 */


#ifndef NODE1_OLED_H
#define NODE1_OLED_H


#include <stdint.h>


#define NUMBER_OF_PAGES     8
#define NUMBER_OF_COLUMNS   128
#define ASCII_OFFSET        32
#define FONT_LENGTH         8


/**
 * @brief Initiates the OLED, and clears the screen using @c oled_clear().
 */
void oled_init();


/**
 * @brief Updates the OLED page pointer. Does nothing if @p line
 * is outside the interval [0,7].
 * 
 * @param line New value of the OLED page pointer.
 */
void oled_go_to_line(int line);


/**
 * @brief Updates the OLED column pointer. Does nothing if @p line
 * is outside the interval [0,127].
 * 
 * @param col New value of the OLED column pointer.
 */
void oled_go_to_col(int col);


/**
 * @brief Updates the position pointed to by the page og column poiniters,
 * by using @c oled_go_to_line() and @c oled_go_to_col().
 * 
 * @param line New value of the OLED page pointer.
 * @param col New value of the OLED column pointer.
 */
void oled_set_pos(int line, int col);


/**
 * @brief Clears the OLED screen.
 */
void oled_clear(void); 


/**
 * @brief Prints a character @p c to the OLED screen in the position pointed 
 * to by the page and column pointers. Uses the large font given in
 * @c fonts.h.
 * 
 * @param c Character to be printed to the OLED screen.
 */
void oled_print_char(char c);


/**
 * @brief Prints a character @p string to the OLED screen in the position pointed 
 * to by the page and column pointers, by using @c oled_print_char().
 * 
 * @param string String to be printed to the OLED screen.
 */
void oled_print_string(const char* string);


/**
 * @brief Prints an integer @p number to the OLED screen in the position pointed 
 * to by the page and column pointers, by using @c oled_print_string().
 * 
 * @param number Integer to be printed to the OLED screen.
 */
void oled_print_int(uint16_t number);


/**
 * @brief Prints the playing screen, showing lives left as filled hearts,
 * and lives lost as empty hearts.
 * 
 * @param lives_left Amount of filled hearts.
 * @param max_lives Number of hearts on screen.
 */
void oled_print_playing_screen(int lives_left, int max_lives);


/**
 * @brief Prints the quit screen.
 */
void oled_print_quit_screen(void);


/**
 * @brief Prints the game over screen, which displays @p score.
 * 
 * @param score Score to be displayed.
 * @param new_highscore If 1, player is congratulated with achieving a new highscore.
 */
void oled_print_game_over_screen(int score, char new_highscore);


/**
 * @brief Prints the first 1024 bytes of the SRAM memory to the OLED screen.
 */
void oled_print_from_sram();


/**
 * @brief Adjusts the brightness of the OLED screen.
 * 
 * @param brightness Desired brightness.
 */
void oled_set_brightness(uint8_t brightness);


#endif