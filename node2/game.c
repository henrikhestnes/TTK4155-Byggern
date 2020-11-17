#include "game.h"
#include "adc.h"
#include "motor.h"
#include "servo_driver.h"
#include "solenoid.h"
#include "pid_controller.h"
#include "user_input_scaling.h"
#include "can/can_controller.h"
#include "microbit.h"
#include "sam/sam3x/include/sam.h"
#include "../common/can_id.h"

#include <stdint.h>


#define F_CPU               84E6
#define TC0_CLK0            F_CPU / 2

#define IR_TRESHOLD         1000
#define NUMBER_OF_LIVES     3

#define K_P_HARD            35
#define K_I_HARD            20
#define K_D_HARD            1
#define K_P_EXTREME         20
#define K_I_EXTREME         10
#define K_D_EXTREME         1
#define K_P_IMPOSSIBLE      10
#define K_I_IMPOSSIBLE      5
#define K_D_IMPOSSIBLE      1

#define T                   1.0 / MOTOR_TIMER_FREQ
#define MAX_MOTOR_SPEED     0x4FF

#define IRQ_TC0_priority    2


static unsigned int score;
static unsigned int lives_left;
static unsigned int counting_flag;
static CONTROLLER_SEL controller_select = SLIDER_POS_CTRL;


static struct user_input_data {
    int joystick_x;
    int joystick_y;
    int slider_left;
    int slider_right;
    int button_left;
    int button_right;
} user_data;


void game_timer_init() {
    // initiate TC0 channel 0
    // enable clock for TC0:    DIV = 0 (clk = MCK), CMD = 0 (read), PID = 27 (TC0)
    PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_TC0 << PMC_PCR_PID_Pos);
    PMC->PMC_PCER0 |= 1 << (ID_TC0);

    // disable timer counter channel
    TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKDIS;

    // set clock to MCK/2 = 42 MHz, capture mode with reset trigger on compare match with RC
    TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_CPCTRG;

    // set match frequency to 50 Hz
    TC0->TC_CHANNEL[0].TC_RC = TC0_CLK0 / MOTOR_TIMER_FREQ;

    // enable RC compare match interrupt
    TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;

    // enable NVIC interrupt
    NVIC_EnableIRQ(ID_TC0);
    NVIC_SetPriority(TC0_IRQn, IRQ_TC0_priority);
}


void game_init() {
    score = 0;
    lives_left = NUMBER_OF_LIVES;
    game_timer_init();
    pid_controller_init(K_P_HARD, K_I_HARD, K_D_HARD, T, MAX_MOTOR_SPEED);
}


int game_count_fails() {

    uint16_t ir_level = adc_read();

    if ((ir_level < IR_TRESHOLD) && !counting_flag) {
        --lives_left;
        counting_flag = 1;
        return 1;
    }

    else if (ir_level > IR_TRESHOLD) {
        counting_flag = 0;
    }

    return 0;
}


void game_set_controller(CONTROLLER_SEL controller){
    controller_select = controller;
    printf("New controller: %d \n\r", controller);
}


void game_set_difficulty(DIFFICULTY difficulty) {
    switch (difficulty)
    {
    case HARD:
    {
        pid_controller_set_parameters(K_P_HARD, K_I_HARD, K_D_HARD);
        printf("New parameters: \n\r K_p = %d \n\r K_i = %d \n\r K_d = %d \n\n\r", K_P_HARD, K_I_HARD, K_D_HARD);
        break;
    }
    case EXTREME:
    {
        pid_controller_set_parameters(K_P_EXTREME, K_I_EXTREME, K_D_EXTREME);
        printf("New parameters: \n\r K_p = %d \n\r K_i = %d \n\r K_d = %d \n\n\r", K_P_EXTREME, K_I_EXTREME, K_D_EXTREME);
        break;
    }
    case IMPOSSIBLE:
    {
        pid_controller_set_parameters(K_P_IMPOSSIBLE, K_I_IMPOSSIBLE, K_D_IMPOSSIBLE);
        printf("New parameters: \n\r K_p = %d \n\r K_i = %d \n\r K_d = %d \n\n\r", K_P_IMPOSSIBLE, K_I_IMPOSSIBLE, K_D_IMPOSSIBLE);
        break;
    }
    default:
        break;
    }

    
}


void game_set_user_data(char* data) {
    user_data.joystick_x = joystick_scale_x(data[0]);
    user_data.joystick_y = joystick_scale_y(data[1]);
    user_data.slider_left = slider_scale_left(data[2]);
    user_data.slider_right = slider_scale_right(data[3]);
    user_data.button_left = data[4];
    user_data.button_right = data[5];
}


static void game_run() {
    // motor_run_slider(user_data.slider_right);
    // servo_set_position(user_data.joystick_x);
    // solenoid_run_button(user_data.button_right);

    switch (controller_select) {
        case SLIDER_POS_CTRL:
        {
            motor_run_slider(user_data.slider_right);
            servo_set_position(user_data.joystick_x);
            solenoid_run_button(user_data.button_right);
            break;
        }
        case JOYSTICK_SPEED_CTRL:
        {   
            motor_run_joystick(user_data.joystick_x);
            servo_set_position(2*(user_data.slider_right - 50));
            solenoid_run_button(user_data.button_right);
            break;
        }
        case MICROBIT_SPEED_CTRL:
        {
            motor_run_microbit();
            servo_set_position(user_data.joystick_x);
            solenoid_run_button(microbit_button());
        }
        default:
            break;
    }
    

    if (game_count_fails()) {
        printf("Lives left: %d \n\r", lives_left);

        CAN_MESSAGE m = {
            .id = GAME_LIVES_LEFT_ID,
            .data_length = 1,
            .data = lives_left
        };

        can_send(&m, 0);
    }

    ++score;
}


void game_timer_enable(){
    TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
}


void game_timer_disable(){
    TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKDIS;
}


int game_get_score() {
    return score;
}


void game_reset_score() {
    score = 0;
}


void game_reset_lives_left() {
    lives_left = INITIAL_LIVES;
}


void TC0_Handler(void) {
    game_run();

    // clear interrupt flag
    TC0->TC_CHANNEL[0].TC_SR;
}
