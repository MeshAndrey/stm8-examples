/* PB5 - LED */

#include <stdint.h>
#include <stm8s.h>

inline void init_gpio(void)
{
    SetBit(GPIOB->DDR, 5); /* set direction as output */
    SetBit(GPIOB->ODR, 5); /* set output 1 */
    SetBit(GPIOB->CR1, 5); /* init as push-pull */
}

inline void init_tim1(void)
{
    CLK->PCKENR1 |= CLK_PCKENR1_TIM1; // Enable TIM1

    TIM1->CR1 &= ~TIM1_CR1_DIR; // Counter used as up-counter

    TIM1->PSCRH = BYTE_1(2000); // High bits of 2000d in prescaler
    TIM1->PSCRL = BYTE_0(2000); // Low  bits of 2000d in prescaler

    TIM1->ARRH  = BYTE_1(1000); // high bits of 1000d in auto-reload register
    TIM1->ARRL  = BYTE_0(1000); // low  bits of 1000d in auto-reload register

    TIM1->IER |= TIM1_IER_UIE; // Enable interrupt
    TIM1->CR1 |= TIM1_CR1_CEN; // Counter enabled
}

void TIM1_Update(void) __interrupt(11)
{
    TIM1->SR1 &= ~TIM1_SR1_UIF;

    ChgBit(GPIOB->ODR, 5);
}

int main(void)
{
    init_tim1();

    init_gpio();

    rim(); // enable interrupts

    SetBit(GPIOB->ODR, 5);

    while(1)
    {

    }
}

