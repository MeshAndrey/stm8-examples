/*
    D2 && D4 - LED
 */

#include <stdint.h>

#define GPIOD_BaseAddress       0x00500F
#define GPIOD ((GPIO_TypeDef *) GPIOD_BaseAddress)

#define CLK_BaseAddress         0x0050C0
#define CLK   ((CLK_TypeDef *)  CLK_BaseAddress)

volatile uint32_t time = 1000000;

typedef struct GPIO_struct
{
   volatile uint8_t ODR; /*!< Output Data Register     */
   volatile uint8_t IDR; /*!< Input Data Register      */
   volatile uint8_t DDR; /*!< Data Direction Register  */
   volatile uint8_t CR1; /*!< Configuration Register 1 */
   volatile uint8_t CR2; /*!< Configuration Register 2 */
}
GPIO_TypeDef;

typedef struct CLK_struct
{
   volatile  uint8_t  CLK_ICKR;     /* Internal clock control register         */
   volatile  uint8_t  CLK_ECKR;     /* External clock control register         */
   volatile  uint8_t  RESERVED;
   volatile  uint8_t  CLK_CMSR;     /* Clock master status register            */
   volatile  uint8_t  CLK_SWR;      /* Clock master switch register            */
   volatile  uint8_t  CLK_SWCR;     /* Clock switch control register           */
   volatile  uint8_t  CLK_CKDIVR;   /* Clock divider register                  */
   volatile  uint8_t  CLK_PCKENR1;  /* Peripheral clock gating register 1      */
   volatile  uint8_t  CLK_CSSR;     /* Clock security system register          */
   volatile  uint8_t  CLK_CCOR;     /* Configurable clock control register     */
   volatile uint16_t  CLK_PCKENR2;  /* Peripheral clock gating register 2      */
   volatile  uint8_t  CLK_HSITRIMR; /* HSI clock calibration trimming register */
   volatile  uint8_t  CLK_SWIMCCR;  /* SWIM clock control register             */
}
CLK_TypeDef;


void delay(uint32_t time)
{
    while(time--);
}

void init_gpio(void)
{
    GPIOD->DDR |= (1 << 4) | (1 << 2);    /* set direction as output */
    GPIOD->ODR |= (1 << 4) | (1 << 2);    /* set output 1            */
    GPIOD->CR1 |= (1 << 4) | (1 << 2);    /* init as push-pull       */
}

void init_clk_hsi(void) /* set clk to 16 MHz */
{
    CLK->CLK_CKDIVR &= ~((1 << 4) | (1 << 3));     /* set HSIDIV bits to 0 */
    CLK->CLK_CKDIVR &= ~((1 << 2) | (1 << 1) | 1); /* set CPUDIV bits to 0 */
}

void main(void)
{
    init_gpio();
    init_clk_hsi();

    while(1)
    {
        GPIOD->ODR |= (1 << 4) | (1 << 2);
        delay(time);
        
        GPIOD->ODR &= ~((1 << 4) | (1 << 2));
        delay(time);
    }
}
