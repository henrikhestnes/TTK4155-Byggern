#ifndef NODE1_USER_INPUT_H
#define NODE1_USER_INPUT_H


#include <stdint.h>



/**
 * @brief Data structure to be used to represent the joystick position.
 */
typedef struct {
    int x;
    int y;
} pos_t;


/**
 * @brief The different directions the joystick can point.
 */
typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    CENTER,
    NEUTRAL
} dir_t;


/**
 * @brief Data structure to be used to represent
 * the position of the two sliders.
 */
typedef struct {
    int left;
    int right;
} slider_t;


/**
 * @brief Data structure to be used to represent
 * the status of the three buttons.
 */
typedef struct {
    unsigned int left;
    unsigned int right;
    unsigned int joystick;
} button_t;


/**
 * @brief Initiates the user input modeule by initiating the ADC,
 * configuring input pins for the button, and setting up a timer
 * for timed transmissions.
 */
void user_input_init(void);


/**
 * @brief Reads the joystick position through the ADC. Returns a position
 * with x and y values in the interval [0, 255].
 *
 * @return The joystick position.
 */
pos_t user_input_joystick_pos(void);


/**
 * @brief Calculates the joystick's direction from it's postiton. Reads
 * the joystick position using @c joystick_pos_read().
 *
 * @return The direction the joystick is pointing.
 */
dir_t user_input_joystick_dir(void);


/**
 * @brief Reads the slider position through the ADC. Returns a position
 * for the left and right slider values in the interval [0, 255].
 *
 * @return The slider positions.
 */
slider_t user_input_slider_pos(void);


/**
 * @brief Reads the button statuses. Returns 1 if a button is pressed,
 * and 0 otherwise.
 *
 * @return The status of the left, right and joystick buttons.
 */
button_t user_input_buttons(void);


/**
 * @brief Transmits all the input data over the CAN bus. 
 */
void user_input_transmit(void);


/**
 * @brief Enables the timer which calls @c user_input_transmit() 
 * at a frequency of 10 Hz.
 */
void user_input_timer_enable();


/**
 * @brief Disables the timer which calls @c user_input_transmit().
 */
void user_input_timer_disable();


#endif
