/*
    D2 && D4 - LED
 */

#include <stdint.h>

#define GPIOD_BaseAddress       0x00500F
#define GPIOD ((GPIO_TypeDef *) GPIOD_BaseAddress)

typedef struct GPIO_struct
{
   volatile uint8_t ODR; /*!< Output Data Register */
   volatile uint8_t IDR; /*!< Input Data Register */
   volatile uint8_t DDR; /*!< Data Direction Register */
   volatile uint8_t CR1; /*!< Configuration Register 1 */
   volatile uint8_t CR2; /*!< Configuration Register 2 */
}
GPIO_TypeDef;

void delay(uint32_t time)
{
    while(time--);
}

void init_gpio(void)
{
    GPIOD->DDR |= (1 << 4) | (1 << 2);    /*set direction as output*/
    GPIOD->ODR |= (1 << 4) | (1 << 2);    /*set output 1 */
    GPIOD->CR1 |= (1 << 4) | (1 << 2);    /*init as push-pull*/
}

void main(void)
{
    init_gpio();

    while(1)
    {
        GPIOD->ODR |= (1 << 4) | (1 << 2);
        delay(100000UL);
        
        GPIOD->ODR &= ~((1 << 4) | (1 << 2));
        delay(100000UL);
    }
}
