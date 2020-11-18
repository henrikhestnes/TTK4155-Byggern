#include "microbit.h"
#include "sam/sam3x/include/sam.h"


#define MB_LEFT_PIN         PIO_PB17
#define MB_RIGHT_PIN        PIO_PB18
#define MB_BUTTON_PIN       PIO_PB19


void microbit_init() {
    // enables the PIO to control the corresponding pins
    PIOB->PIO_PER |= (MB_LEFT_PIN | MB_RIGHT_PIN | MB_BUTTON_PIN);

    PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_PIOB << PMC_PCR_PID_Pos);
    PMC->PMC_PCER0 |= 1 << (ID_PIOB);
}


const ACC_DIR microbit_dir() {
    if (PIOB->PIO_PDSR & MB_LEFT_PIN) {
        return ACC_LEFT;
    }
    else if (PIOB->PIO_PDSR & MB_RIGHT_PIN) {
        return ACC_RIGHT;
    }
    
    return ACC_MIDDLE;
}


const char microbit_button() {
    if (PIOB->PIO_PDSR & MB_BUTTON_PIN) {
        return 1;
    }
    return 0;
}

