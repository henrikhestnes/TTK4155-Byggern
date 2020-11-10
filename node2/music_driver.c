#include "music_driver.h"
#include "music_metadata.h"
#include "pwm.h"
#include "timer.h"

#define F_CPU 84000000

void music_set_tone(int freq){
    pwm_set_frequency(freq, CHANNEL_PIN44);
    pwm_set_duty_cycle(0.5, CHANNEL_PIN44);
}


void music_buzz(int freq, int length){
    music_set_tone(freq);
    for(int i = 0; i < length; ++i){
        _delay_us(100);
    }
}


void music_play(SONG song){
    int size = 0;
    int note_duration = 0;
    int note_pause = 0;

    switch(song){
        case MII_THEME:{
            size = sizeof(mii_theme_notes)/sizeof(int);
            for(int current_note = 0; current_note < size; current_note++){
                note_duration = 1000 / mii_theme_notes[current_note];
                music_buzz(mii_theme_notes[current_note], note_duration);

                note_pause = note_duration * 1.5;
                for(int i = 1; i < note_pause; ++i){
                    _delay_us(1000);
                }
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