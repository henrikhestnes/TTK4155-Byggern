/**
 * @file 
 * @brief Module for solenoid functionality
 */


#ifndef NODE2_SOLENOID_H
#define NODE2_SOLENOID_H


/**
 * @brief Initiates the solenoid by setting pin A0
 * on the shield as output, active low
 */
void solenoid_init(void);


/**
 * @brief Makes solenoid shoot once if button is pressed
 * 
 * @param button_pressed 1 if button pressed, 0 otherwise 
 */
void solenoid_run_button(int button_pressed);


#endif
