/**
 * @file
 * @brief Main program of node 1. 
 */


#include "uart.h"
#include "sram.h"
#include "user_input.h"
#include "oled.h"
#include "menu.h"
#include "can_driver.h"
#include "highscore.h"
#include "fsm.h"
#include "../common/can.h"

#include <avr/interrupt.h>

#define F_CPU 4.9152E6
#include <util/delay.h> 


#define BAUD 9600
#define UBRR F_CPU / 16 / BAUD - 1
#define NUMBER_OF_LIVES 3


int main() {
    cli();

    uart_init(UBRR);
    sram_init();
    user_input_init();
    user_input_timer_disable();
    oled_init();
    menu_init();
    can_init(MODE_NORMAL);
    highscore_init();

    sei();

    fsm_transition_to(STATE_MENU);
    while (1) {
    FSM_STATE state = fsm_get_state();
        switch (state) {
            case STATE_MENU:
            {
                menu_run();
                break;
            }
            case STATE_PLAYING:
            {   
                unsigned int lives_left = fsm_get_lives_left();
                if (lives_left) {
                    oled_print_playing_screen(lives_left, NUMBER_OF_LIVES);
                }
                else {
                    fsm_transition_to(STATE_GAME_OVER);
                }

                if (user_input_buttons().left) {
                    oled_clear();
                    oled_print_quit_screen();
                    fsm_transition_to(STATE_IDLE);
                    _delay_ms(1000);
                }

                break;
            }
            case STATE_GAME_OVER:
            {  
                // wait for score message reception
                _delay_ms(100);
                highscore_update();
                fsm_transition_to(STATE_IDLE);
                break;
            }
            case STATE_IDLE:
            {   
                if (user_input_buttons().left) {
                    fsm_transition_to(STATE_MENU);
                }
            }
            default:
                break;
        }
    }

    return 0;
}


ISR(INT0_vect) {
    CAN_MESSAGE m;
    can_recieve(&m);

    switch (m.id) {
        case GAME_LIVES_LEFT_ID: 
        {
            fsm_set_lives_left(m.data[0]);
            break;
        }
        case GAME_SCORE_ID:
        {
            uint8_t msb = m.data[0];
            uint8_t lsb = m.data[1];
            int score = (msb << 8) + lsb;
            highscore_set_new_score(score);

            uint16_t* highscores = highscore_get();
            char new_highscore = score > highscores[0];
            oled_print_game_over_screen(score, new_highscore);
            break;
        }
        default:
            break;
    }
    
    mcp2515_bit_modify(MCP_CANINTF, MCP_RX0IF | MCP_RX1IF, 0);
}


ISR(TIMER1_COMPA_vect) {
    oled_print_from_sram();
}


ISR(TIMER3_COMPA_vect) {
    user_input_transmit();
}


ISR(BADISR_vect){}