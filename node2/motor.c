#include "motor.h"
#include "dac.h"
#include "joystick.h"
#include "sam/sam3x/include/sam.h"
#include "timer.h"
#include <math.h>


#define ENCODER_DATA_MASK   (0xFF << DO0_IDX)


void motor_init() {
    // initiate dac
    dac_init();

    // enable PIO pins to motor box as output
    PIOD->PIO_PER |= DIR | EN | SEL | NOT_RST | NOT_OE;
    PIOD->PIO_OER |= DIR | EN | SEL | NOT_RST | NOT_OE;

    // enable motor
    PIOD->PIO_SODR = EN | NOT_RST;

    
}


void motor_set_speed() {
    pos_t pos = {0, 0};
    if (!(joystick_pos_recieve(&pos))) {
        printf("recieved position \n\r");
        if (pos.x > 0) {
            printf("moving right, x = %d \n\r", pos.x);
            // moving right, set direction pin
            PIOD->PIO_SODR = DIR;
        }
        else {
            printf("moving left x = %d \n\r", pos.x);
            // moving left, clear direction pin
            PIOD->PIO_CODR = DIR;
        }
        
        // set motor speed
        uint16_t speed = (uint16_t) (0x4FF * abs(pos.x) / 100);
        printf("speed = %X \n\n\r", speed);
        dac_write(speed);
    }
}



uint32_t motor_read_encoder() {
  // Setting !OE low to enable output of encoder
  PIOD->PIO_SODR &= ~NOT_OE;

  // Setting SEL low to get high byte and extracting MSB
  PIOD->PIO_SODR &= ~SEL;
  // delay(20);
  uint32_t msb = (PIOC->PIO_ODSR & ENCODER_DATA_MASK) >> DO0_IDX;

  // Setting SEL high to get low byte and extracting LSB
  PIOD->PIO_SODR &= ~SEL;
  // delay(20);
  uint32_t lsb = (PIOC->PIO_ODSR & ENCODER_DATA_MASK) >> DO0_IDX;

  // Reset encoder
  PIOD->PIO_SODR &= ~NOT_RST;
  PIOD->PIO_SODR |= NOT_RST;

  // Disable output of encoder
  PIOD->PIO_SODR &= ~NOT_OE;

  // Combine LSB and MSB
  uint32_t encoder_data = (msb << 16) | lsb;
  return encoder_data;
}