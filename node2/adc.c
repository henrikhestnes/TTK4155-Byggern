#include "adc.h"
#include "sam/sam3x/include/sam.h"


// The ADC used is channel 0, which uses PIO pin PA2. 
// This is located at pin A7 on the shield.


void adc_init() {
    // set ADC mode:    12-bit resolution, free run mode, no clock prescaler
    ADC->ADC_MR = ADC_MR_FREERUN;

    // enable AD0 peripheral
    ADC->ADC_CHER = ADC_CHER_CH0;

    // enable clock for ADC:    DIV = 0 (clk = MCK), CMD = 0 (read), PID = 37 (ADC)
    PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_ADC << PMC_PCR_PID_Pos);
    PMC->PMC_PCER1 |= 1 << (ID_ADC - 32);

    // begin conversion
    ADC->ADC_CR = ADC_CR_START;
}


uint16_t adc_read() {
    return ADC->ADC_CDR[0];
}