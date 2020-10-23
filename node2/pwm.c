#include "pwm.h"
#include "sam/sam3x/include/sam.h"


#define MCK         84E6

#define PERIOD_A    20E-3
#define DIVA        84
#define CLK_A       1E6
#define CPRDA       (int) (PERIOD_A * MCK / DIVA)

#define PERIOD_B    20E-3
#define DIVB        84
#define CLK_B       1E6
#define CPRDB       (int) (PERIOD_B * MCK / DIVB)


void pwm_init() {
    // enable peripheral function B for PIN44 and PIN45
    PIOC->PIO_ABSR |= PIO_PC19B_PWMH5 | PIO_PC18B_PWMH6;

    // disable PIO from controlling PIN44 and PIN45
    PIOC->PIO_PDR |= PIO_PC18B_PWMH6 | PIO_PC19B_PWMH5;

    // enable clock for PWM:    DIV = 0 (clk = MCK), CMD = 0 (read), PID = 36 (PWM)
    PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_PWM << PMC_PCR_PID_Pos);
    PMC->PMC_PCER1 |= 1 << (ID_PWM - 32);

    // enable PWM channels
    PWM->PWM_ENA = PWM_ENA_CHID5 | PWM_ENA_CHID6;

    // set PWM clocks to 1 MHz
    PWM->PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(DIVA);
    PWM->PWM_CLK |= PWM_CLK_PREB(0) | PWM_CLK_DIVB(DIVB);

    // assign clocks to respective channels: clock A for channel 5 (PIN44), clock B for channel 6 (PIN45)
    // waveform set to be left-aligned
    PWM->PWM_CH_NUM[5].PWM_CMR = PWM_CMR_CPRE_CLKA;
    PWM->PWM_CH_NUM[6].PWM_CMR = PWM_CMR_CPRE_CLKB;
    
    // set period to 20 ms, giving a frequency of 50 Hz
    PWM->PWM_CH_NUM[5].PWM_CPRD = PWM_CPRD_CPRD(CPRDA);
    PWM->PWM_CH_NUM[6].PWM_CPRD = PWM_CPRD_CPRD(CPRDB);
    
    // set duty cycles
    pwm_set_duty_cycle(0.5, CHANNEL_PIN44);
    pwm_set_duty_cycle(0.5, CHANNEL_PIN45);
}


void pwm_set_duty_cycle(float duty_cycle, unsigned int channel) {
    if ((duty_cycle < 0) || (duty_cycle > 1)) {
        return;
    }

    int CDTY = 0;

    if (channel == 5) {
        CDTY = (int) (PERIOD_A * (1 - duty_cycle) * CLK_A);
    }

    if (channel == 6) {
        CDTY = (int) (PERIOD_B * (1 - duty_cycle) * CLK_B);
    }

    PWM->PWM_CH_NUM[channel].PWM_CDTY = PWM_CDTY_CDTY(CDTY);
}