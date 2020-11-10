// #include "interrupt.h"
// #include <avr/interrupt.h>
// #include <avr/io.h>


// void interrupt_joystick_init() {
//     cli();

//     // set INT1 as input
//     DDRD &= ~(1 << PD3);

//     // enable INT1 interrupt vector
//     GICR |= (1 << INT1);

//     // interrupt on falling edge
//     MCUCR |= (1 << ISC11);
//     MCUCR &= ~(1 << ISC10);

//     sei();
// }


// void interrupt_oled_timer_init() {
//     cli();

//     TCCR1A = 0;
//     TCCR1B = 0;
//     TCNT1 = 0;

//     // set compare match register for 60 hz
//     OCR1A = 39;

//     // set to CTC mode
//     TCCR1B |= (1 << WGM12);

//     // set prescaler 1024
//     TCCR1B |= (1 << CS12) | (1 << CS10);

//     // enable timer compare interrupt
//     TIMSK |= (1 << OCIE1A);

//     sei();
// }


// void interrupt_can_timer_init() {
//     cli();

//     TCCR3A = 0;
//     TCCR3B = 0;
//     TCNT3 = 0;

//     // set compare match register for 10 Hz
//     OCR3A = 239;

//     // set to CTC mode
//     TCCR3B |= (1 << WGM32);

//     // set prescaler 1024
//     TCCR3B |= (1 << CS32) | (1 << CS30);

//     // enable timer compare interrupt
//     ETIMSK |= (1 << OCIE3A);

//     sei();
// }


// void interrupt_can_recieve_init() {
//     cli();

//     // set INT0 as input
//     DDRD &= ~(1 << PD2);

//     // enable INT0 interrupt vector
//     GICR |= (1 << INT0);

//     // interrupt on falling edge
//     MCUCR |= (1 << ISC01);
//     MCUCR &= ~(1 << ISC00);

//     sei();
// }


// void interrupt_enable_oled_timer() {
//     cli();

//     TIMSK |= (1 << OCIE1A);

//     sei();
// }

// void interrupt_disable_oled_timer() {
//     cli();

//     TIMSK &= ~(1 << OCIE1A);

//     sei();
// }


// ISR(BADISR_vect){}