/* PB5 - LED */

#include <stdint.h>
#include <stm8s.h>

inline void init_tim2(void)
{
    CLK->PCKENR1 |= CLK_PCKENR1_TIM2; // Enable TIM2

    TIM2->CR1 = TIM2_CR1_ARPE; // Enable Auto-Reload Preload // reset value = 0

    TIM2->PSCR = 1; // Set Prescaler Value (pow (2, 1) or (2 ^ 1))

    TIM2->ARRH = BYTE_1(1000); // high bits of 1000d in auto-reload register
    TIM2->ARRL = BYTE_0(1000); // low  bits of 1000d in auto-reload register

    TIM2->CCMR1 = (1 << 6) | (1 << 5)  //| (1 << 4) // PWM mode 1
	                   | (1 << 3); // Output compare 1 Preload enable

    //TIM2->CCR1H = 0x00;  // high bits of 500d in Capture/compare register
    TIM2->CCR1L = BYTE_0(500);  // low  bits of 500d in Capture/compare register

    TIM2->CCER1 = TIM2_CCER1_CC1E; // Set capture/compare output enable

    TIM2->CR1 |= TIM2_CR1_CEN; // Counter enabled
}

int main(void)
{
    init_tim2();

    while(1)
    {

    }
}

