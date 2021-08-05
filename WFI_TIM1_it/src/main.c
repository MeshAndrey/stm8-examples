/* PB5 - LED */

#include <stdint.h>
#include <stm8s.h>

void init_gpio(void)
{
    SetBit(GPIOB->DDR, 5); /* set direction as output */
    SetBit(GPIOB->ODR, 5); /* set output 1 */
    SetBit(GPIOB->CR1, 5); /* init as push-pull */
}

void init_tim1(void)
{
    CLK->PCKENR1 |= CLK_PCKENR1_TIM1; // Enable TIM1

    TIM1->CR1 &= ~TIM1_CR1_DIR; // Counter used as up-counter

    TIM1->PSCRH = 0x07; // High bits of 2000d in prescaler
    TIM1->PSCRL = 0xD0; // Low  bits of 2000d in prescaler

    TIM1->ARRH  = 0x03; // high bits of 1000d in auto-reload register
    TIM1->ARRL  = 0xE8; // low  bits of 1000d in auto-reload register

    TIM1->IER |= TIM1_IER_UIE; // Enable interrupt
    TIM1->CR1 |= TIM1_CR1_CEN; // Counter enabled
}

void TIM1_Update(void) __interrupt(11)
{
    TIM1->SR1 &= ~TIM1_SR1_UIF;
}

int main(void)
{
    init_tim1();

    init_gpio();

    rim(); // enable interrupts

    SetBit(GPIOB->ODR, 5);

    while(1)
    {
        wfi(); // enable sleep mode
        ChgBit(GPIOB->ODR, 5);
    }
}

