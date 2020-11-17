/*
 * interrupt.c
 *
 * Author: Gustav O. Often and Eivind H. J�lsgard
 *
 * For use in TTK4155 Embedded and Industrial Computer Systems Design
 * NTNU - Norwegian University of Science and Technology
 *
 */

#include "can_interrupt.h"
#include "can_controller.h"
#include "../uart_and_printf/printf-stdarg.h"
#include "../sam/sam3x/include/sam.h"

#include "../game.h"
#include "../fsm.h"
#include "../music_driver.h"
#include "../../common/can.h"

#include <stdio.h>


#define DEBUG_INTERRUPT 0

/**
 * \brief CAN0 Interrupt handler for RX, TX and bus error interrupts
 *
 * \param void
 *
 * \retval
 */
void CAN0_Handler( void )
{
	if(DEBUG_INTERRUPT)printf("CAN0 interrupt\n\r");
	char can_sr = CAN0->CAN_SR;

	//RX interrupt
	if(can_sr & (CAN_SR_MB1 | CAN_SR_MB2)) // Mailbox 1 and 2 specified for receiving
	{
		CAN_MESSAGE message;
		if(can_sr & CAN_SR_MB1)  // Mailbox 1 event
		{
			can_receive(&message, 1);
		}
		else if(can_sr & CAN_SR_MB2) // Mailbox 2 event
		{
			can_receive(&message, 2);
		}
		else
		{
			printf("CAN0 message arrived in non-used mailbox\n\r");
		}


        switch(message.id) {
            case USER_INPUT_ID:
            {
                game_set_user_data(message.data);
                break;
            }
            case FSM_STATE_ID:
            {
                fsm_transition_to(message.data[0]);
                break;
            }
			case CONTROLLER_ID:
            {
				game_set_controller(message.data[0]);
				break;
            }
            case MUSIC_SONG_ID:
            {
                music_play(message.data[0]);
				break;
            }
			case GAME_DIFFICULTY_ID:
			{
				game_set_difficulty(message.data[0]);
				break;
			}
            default:
                break;
        }


		if(DEBUG_INTERRUPT)printf("message id: %d\n\r", message.id);
		if(DEBUG_INTERRUPT)printf("message data length: %d\n\r", message.data_length);
		for (int i = 0; i < message.data_length; i++)
		{
			if(DEBUG_INTERRUPT)printf("%d ", message.data[i]);
		}

		if(DEBUG_INTERRUPT)printf("\n\n\r");
	}

	if(can_sr & CAN_SR_MB0)
	{
		if(DEBUG_INTERRUPT) printf("CAN0 MB0 ready to send \n\r");

	//Disable interrupt
		CAN0->CAN_IDR = CAN_IER_MB0;

	}

	if(can_sr & CAN_SR_ERRP)
	{
		if(DEBUG_INTERRUPT)printf("CAN0 ERRP error\n\r");

	}
	if(can_sr & CAN_SR_TOVF)
	{
		if(DEBUG_INTERRUPT)printf("CAN0 timer overflow\n\r");

	}

	NVIC_ClearPendingIRQ(ID_CAN0);
	//sei();*/
}
