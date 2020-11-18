/**
 * @file 
 * @brief Module for music functionality
 */


#ifndef NODE2_MUSIC_DRIVER_H
#define NODE2_MUSIC_DRIVER_H


#include "../common/songs.h"


/**
 * @brief Plays a song @c song through a PWM signal fed to a buzzer.
 */
void music_play(SONG song);


#endif