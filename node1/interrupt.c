#include "interrupt.h"
#include <avr/interrupt.h>
#include <avr/io.h>


void interrupt_joystick_init() {
    cli();

    // set INT1 as input
    DDRD &= ~(1 << PD3);

    // enable INT1 interrupt vector
    GICR |= (1 << INT1);

    // interrupt on falling edge
    MCUCR |= (1 << ISC11);
    MCUCR &= ~(1 << ISC10);

    sei();
}


void interrupt_oled_timer_init(){
    cli();

    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;

    // set compare match register for 60 hz
    OCR1A = 39;

    // turn on CTC mode
    TCCR1B |= (1 << WGM12);

    // set prescaler 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);

    // enable timer compare interrupt
    TIMSK |= (1 << OCIE1A);

    sei();
}


void interrupt_can_recieve_init() {
    cli();

    // set INT0 as input
    DDRD &= ~(1 << PD2);

    // enable INT0 interrupt vector
    GICR |= (1 << INT0);

    // interrupt on falling edge
    MCUCR |= (1 << ISC01);
    MCUCR &= ~(1 << ISC00);

    sei();
}


void interrupt_enable_oled_timer() {
    cli();

    TIMSK |= (1 << OCIE1A);

    sei();
}

void interrupt_disable_oled_timer() {
    cli();

    TIMSK &= ~(1 << OCIE1A);

    sei();
}


ISR(BADISR_vect){}