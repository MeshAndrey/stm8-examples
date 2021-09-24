/* PB5 - LED */

#include <stdint.h>
#include <stm8s.h>

inline void init_tim2(void)
{
    CLK->PCKENR1 |= CLK_PCKENR1_TIM2; // Enable TIM2

    TIM2->CR1 |= TIM2_CR1_ARPE; // 

    TIM2->PSCR = 1; // 

    TIM2->ARRH  = 0x03; // high bits of 1000d in auto-reload register
    TIM2->ARRL  = 0xE8; // low  bits of 1000d in auto-reload register

    TIM2->CCMR1 |= (1 << 6) | (1 << 5) //| (1 << 4) // PWM mode 1
	                    | (1 << 3); // Output compare 1 Preload enable

    TIM2->CCR1H = 0x00;  // high bits of 500d in Capture/compare register
    TIM2->CCR1L = 0x2F;  // low  bits of 500d in Capture/compare register

    TIM2->CCER1 |= 1;

    TIM2->CR1 |= TIM2_CR1_CEN; // Counter enabled
}

int main(void)
{
    init_tim2();

    while(1)
    {

    }
}

