/*
    PB5 - LED
 */

#include <stdint.h>
#include <stm8s.h>

void delay(uint32_t time)
{
    while(time--);
}

void init_gpio(void)
{
    SetBit(GPIOB->DDR, 5);    /* set direction as output */
    SetBit(GPIOB->ODR, 5);    /* set output 1            */
    SetBit(GPIOB->CR1, 5);    /* init as push-pull       */
}

void init_clk_hsi(void) /* set clk to 16 MHz */
{
    CLK->CKDIVR &= ~(CLK_CKDIVR_HSIDIV); /* set HSIDIV bits to 0 */
    CLK->CKDIVR &= ~(CLK_CKDIVR_CPUDIV); /* set CPUDIV bits to 0 */
}

void main(void)
{
    volatile uint32_t delay_time = 1000000;
    init_gpio();
    init_clk_hsi();

    while(1)
    {
        ChgBit(GPIOB->ODR, 5);
        delay(delay_time);
    }
}
