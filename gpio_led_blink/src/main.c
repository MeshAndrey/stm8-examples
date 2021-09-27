/*
    PB5 - LED
 */
#include <stm8s.h>
#include <stdint.h>


inline void delay(uint32_t time)
{
    while(time--);
}

inline void init_gpio(void)
{
    SetBit(GPIOB->DDR, 5); // set direction as output
    SetBit(GPIOB->ODR, 5); // set output 1 
    SetBit(GPIOB->CR1, 5); // init as push-pull
}

void main(void)
{
    init_gpio();

    while(1)
    {
        ChgBit(GPIOB->ODR, 5);
        delay(100000UL);        
    }
}
