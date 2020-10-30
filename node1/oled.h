#ifndef OLED_H
#define OLED_H


#include <stdint.h>


#define NUMBER_OF_PAGES 8


/**
 * @brief Initiates the OLED, and clears the screen using @c oled_clear().
 */
void oled_init();


/**
 * @brief Writes a command to the OLED, by writing to its command memory space.
 * 
 * @param command Command to be written to the OLED.
 */
void oled_write_command(uint8_t command);


/**
 * @brief Writes data to the OLED screen, by writing to its data memory space.
 * The data is printed in the current position.
 * 
 * @param data Data to be printed on the OLED screen.
 */
void oled_write_data(uint8_t data);


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
 * @brief Prints the bitwise inversion of a character @p c to the 
 * OLED screen in the position pointed to by the page and column pointers. 
 * Uses the large font given in @c fonts.h.
 * 
 * @param c Character to be inverted and printed to the OLED screen.
 */
void oled_print_inverted_char(char c);


/**
 * @brief Prints the bitwise inversion of a string @p string to the 
 * OLED screen in the position pointed to by the page and column pointers,
 * by using @c oled_print_inverted_char().
 * 
 * @param string String to be inverted and printed to the OLED screen.
 */
void oled_print_inverted_string(const char* string);


// void oled_print_from_sram();


#endif