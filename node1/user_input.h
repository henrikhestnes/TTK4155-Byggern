#ifndef NODE1_USER_INPUT_H
#define NODE1_USER_INPUT_H


#include <stdint.h>


#define JOYSTICK_X_OFFSET       26
#define JOYSTICK_Y_OFFSET       28
#define JOYSTICK_MAX            100
#define JOYSTICK_MIN           -100

#define SLIDER_LEFT_OFFSET      14
#define SLIDER_RIGHT_OFFSET     15
#define SLIDER_MAX              100
#define SLIDER_MIN              0


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


typedef struct {
    int left;
    int right;
} button_t;


void user_input_init(void);


/**
 * @brief Reads the joystick position through the ADC. Returns a position
 * with x and y values in the interval [0, 255].
 *
 * @return The scaled joystick position.
 */
pos_t user_input_joystick_pos(void);



/**
 * @brief Calculates the joystick's direction from it's postiton. Reads
 * the joystick position using @c joystick_pos_read().
 *
 * @return The direction the joystick is pointing.
 */
dir_t user_input_joystick_dir(void);


slider_t user_input_slider_pos(void);


button_t user_input_buttons(void);


void user_input_transmit(void);


void user_input_timer_enable();


void user_input_timer_disable();


void user_input_select_controller_microbit(void);


void user_input_select_controller_joystick(void);


#endif
