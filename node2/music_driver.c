#include "music_driver.h"
#include "music_metadata.h"
#include "pwm.h"
#include "timer.h"

#define F_CPU 84000000


#define TEMPO 114


void music_set_tone(int freq){
    pwm_set_frequency(freq, CHANNEL_PIN44);
    pwm_set_duty_cycle(0.5, CHANNEL_PIN44);
}


void music_buzz(int freq, int duration){
    music_set_tone(freq);
    _delay_ms(duration);
}


void music_play(SONG song){
    int size = 0;
    int divider = 0;
    int note_duration = 0;
    int note_pause = 0;

    // duration of a whole note in milliseconds
    int wholenote = 240000 / TEMPO;

    switch(song){
        case MII_THEME:{
            size = sizeof(mii_theme_notes)/sizeof(int);
            for(int current_note = 0; current_note < size; current_note += 2){
                divider = mii_theme_notes[current_note + 1];
                if (divider < 0) { 
                    // quarter note
                    note_duration = -1.5 * wholenote / divider;
                }
                else {
                    // regular note
                    note_duration = wholenote / divider;
                }
                music_buzz(mii_theme_notes[current_note], 0.9*note_duration);

                note_pause = 0.1*note_duration;
                music_buzz(0, note_pause);
            }
            break;
        }

        case MARIO:{
            break;
        }

        case SIMPSON:{
            break;
        }
    }
    music_buzz(0,0);
}