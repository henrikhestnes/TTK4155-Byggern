#include "timer.h"
#include "sam/sam3x/include/sam.h"
#include "sam/interrupt.h"
#include <time.h>


#define TC0_CLK0    84E6 / 2
#define TC1_CLK0    84E6 / 128
#define FREQ        100


void timer_init() {
    // initiate TC0 channel 0
    // enable clock for TC0:    DIV = 0 (clk = MCK), CMD = 0 (read), PID = 27 (TC0)
    PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_TC0 << PMC_PCR_PID_Pos);
    PMC->PMC_PCER0 |= 1 << (ID_TC0);

    // enable timer counter channel
    TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;

    // set clock to MCK/2 = 42 MHz, capture mode with reset trigger on compare match with RC
    TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_CPCTRG;

    // set match frequency to 100 Hz
    TC0->TC_CHANNEL[0].TC_RC = TC0_CLK0 / FREQ;

    // enable RC compare match interrupt
    TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;

    // enable NVIC interrupt
    NVIC_EnableIRQ(ID_TC0);

    // TESTING FREQUENCY
    PIOA->PIO_PER |= PIO_PA16;
    PIOA->PIO_OER |= PIO_PA16;



    // initiate TC1 channel 0
    // enable clock for TC1:    DIV = 0 (clk = MCK), CMD = 0 (read), PID = 28 (TC1)
    // PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_TC1 << PMC_PCR_PID_Pos);
    // PMC->PMC_PCER0 |= 1 << (ID_TC1);

    // // enable timer counter channel
    // TC1->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN;

    // // set clock to MCK/128 = 656250 Hz, capture mode
    // TC1->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK4; 
}


void timer_delay_ms(int ms) {
    TC1->TC_CHANNEL[0].TC_CCR |= TC_CCR_SWTRG;
    while (TC1->TC_CHANNEL[0].TC_CV < TC1_CLK0 * ms * 1e-3) {
        printf("counter value: %d \n\r", TC1->TC_CHANNEL[0].TC_CV);
    }
    TC1->TC_CHANNEL[0].TC_CCR &= ~TC_CCR_SWTRG;
}


void TC0_Handler(void) {
    // toggle pin PA16
    if (PIOA->PIO_ODSR & PIO_PA16) {
        PIOA->PIO_CODR = PIO_PA16;
    }
    else {
        PIOA->PIO_SODR = PIO_PA16;
    }

    // clear interrupt flag
    TC0->TC_CHANNEL[0].TC_SR;
}