#ifndef SLIDER_H
#define SLIDER_H


#include <stdint.h>


#define LEFT_OFFSET 14
#define RIGHT_OFFSET 15
#define SLIDER_MAX_VALUE 100


/**
 * @brief Data structure to be used to represent 
 * the position of the two sliders.
 */
typedef struct {
    int left;
    int right;
} slider_t;


/**
 * @brief Scales an output from the analog measurement to the range
 * [0, @p max].
 * 
 * @param value Measurement value to be scaled.
 * @param offset The measurement's offset from the middle of the
 * interval when the slider is centered.
 * @param max The maximum value the scaled output can have.
 * 
 * @return The scaled value as an integer. 
 */
int slider_scale_value(uint8_t value, int offset, int max);


/**
 * @brief Reads the slider positions through the ADC. Uses
 * @c slider_scale_value() to scale the reading to the desired
 * interval.
 * 
 * @return The scaled slider positions.
 */
slider_t slider_pos_read(void);


void slider_send_pos_to_can(void);


#endif