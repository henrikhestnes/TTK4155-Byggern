
volatile uint32_t wait_ticks = 0;
#define F_CPU 84000000

void _delay_us(uint16_t us){
    wait_ticks = us;
    SysTick_init_us(1);
    while(wait_ticks !=0);
}

void SysTick_init_us(int period){
    //Set SysTick reload register with new SysTick period
    SysTick->LOAD = ((int)(period*10.5) & SysTick_LOAD_RELOAD_Msk)-1;

    //Reset SysTick counter value
    SysTick->VAL = 0;

    //Set SysTick interrupt priority
    NVIC_SetPriority(SysTick_IRQn, IRQ_prio_SysTick);

    //Enable SysTick interrupt and timer
    SysTick->CTRL = (0b0 << SysTick_CTRL_CLKSOURCE_Pos) & 
    SysTick_CTRL_CLKSOURCE_Msk | 
    (0b1 << SysTick_CTRL_TICKINT_Pos) &
    SysTick_CTRL_ENABLE_Msk |
    (0b1 << SysTick_CTRL_ENABLE_Pos) &
    SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void){
    if(wait_ticks!=0){
        wait_ticks--;
    }
    else{
        SysTick->CTRL = 0;
    }
}