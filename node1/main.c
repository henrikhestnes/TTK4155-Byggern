#include "uart.h"
#include "sram.h"
#include "adc.h"
#include "user_input.h"
#include "oled.h"
#include "menu.h"
#include "interrupt.h"
#include "spi_driver.h"
#include "mcp2515_driver.h"
#include "can_driver.h"
#include "fsm.h"
#include "highscore.h"
#include "../common/can_id.h"
#include <avr/interrupt.h>


#define F_CPU 4.9152E6
#include <util/delay.h> 

#define BAUD 9600
#define UBRR F_CPU / 16 / BAUD - 1


int main() {
        cli();

    // UART
        UART_init(UBRR);
        UART_link_printf();

    // SRAM
        sram_init();
        sram_test();

    // USER INPUT
        user_input_init();
        user_input_timer_disable();

    // OLED
        oled_init();

    // Menu
        menu_init();
        menu_timer_disable();

    // CAN
        can_init(MODE_NORMAL);

    // Highscore
        highscore_init();

        sei();

    // Testing
        // while (1) {
        //     user_input_transmit();

        //     if (can_get_recieve_flag()) {
        //         message_t message = can_recieve();
        //         printf("message id: %d\n\r", message.id);
        //         printf("message data length: %d\n\r", message.length);
        //         printf("message data: %s\n\r", message.data);
        //     }

        //     menu_run();
        // }


    // Real code :DDD
    fsm_transition_to(MENU);
    
    while (1) {
    enum FSM_STATE state = fsm_get_state();
        switch (state) {
            case MENU:
            {
                menu_run();
                break;
            }
            case PLAYING:
            {   
                unsigned int lives_left = fsm_get_lives_left();
                if (lives_left) {
                    oled_print_playing_screen(lives_left);
                }
                else {
                    fsm_transition_to(GAME_OVER);
                }

                if (user_input_buttons().left) {
                    oled_clear();
                    oled_print_quit_screen();
                    fsm_transition_to(IDLE);
                    _delay_ms(1000);
                }

                break;
            }
            case GAME_OVER:
            {
                _delay_ms(100);
                fsm_transition_to(IDLE);
                break;
            }
            case IDLE:
            {   
                if (user_input_buttons().left) {
                    fsm_transition_to(MENU);
                }
            }
            default:
                break;
        }
    }

    return 0;
}


ISR(INT0_vect) {
    message_t m = can_recieve();

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


ISR(TIMER3_COMPA_vect) {
    cli();

    user_input_transmit();

    sei();
}


ISR(BADISR_vect){}