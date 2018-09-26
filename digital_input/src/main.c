/*
    D2 && D4 - LED
    D1 && D3 - Buttons
 */

#include <stdint.h>

#define GPIOC_BaseAddress       0x00500A
#define GPIOC ((GPIO_TypeDef *) GPIOC_BaseAddress)

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
    GPIOD->DDR |= (1 << 4) | (1 << 2);    /*set direction as output for D4 & D2*/    
    GPIOD->CR1 |= (1 << 4) | (1 << 2);    /*init as push-pull*/
    //GPIOD->ODR |= (1 << 4) | (1 << 2);    /*set output 1 */

    GPIOC->DDR &= ~((1 << 6) | (1 << 7)); /*set direction as input for D1 & D3*/
    GPIOC->CR1 &= ~((1 << 6) | (1 << 7)); /*Floating without interrupt*/
    GPIOC->CR2 &= ~((1 << 6) | (1 << 7));

}

void main(void)
{
    init_gpio();

    while(1)
    {
        if (GPIOC->IDR & (1 << 6))
            GPIOD->ODR |= (1 << 2);
        else 
            GPIOD->ODR &= ~(1 << 2);

        if (GPIOC->IDR & (1 << 7))
            GPIOD->ODR |= (1 << 4);
        else 
            GPIOD->ODR &= ~(1 << 4);
    }
}
