#include <stdint.h>

#define GPIOD_BaseAddress       0x00500F
#define GPIOD ((GPIO_TypeDef *) GPIOD_BaseAddress)

#define TIM1_BaseAddress        0x005250
#define TIM1  ((TIM1_TypeDef *) TIM1_BaseAddress)

#define CLK_BaseAddress         0x0050C0
#define CLK    ((CLK_TypeDef *) CLK_BaseAddress)

void init_gpio(void);
void clk_init(void);
void init_tim1(void);


typedef struct GPIO_struct
{
    volatile uint8_t ODR; /*!< Output Data Register     >!*/
    volatile uint8_t IDR; /*!< Input Data Register      >!*/
    volatile uint8_t DDR; /*!< Data Direction Register  >!*/
    volatile uint8_t CR1; /*!< Configuration Register 1 >!*/
    volatile uint8_t CR2; /*!< Configuration Register 2 >!*/
}
GPIO_TypeDef;

typedef struct CLK_struct
{
   volatile  uint8_t      ICKR;  /* Internal clock control register         */
   volatile  uint8_t      ECKR;  /* External clock control register         */
   volatile  uint8_t  RESERVED;
   volatile  uint8_t      CMSR;  /* Clock master status register            */
   volatile  uint8_t       SWR;  /* Clock master switch register            */
   volatile  uint8_t      SWCR;  /* Clock switch control register           */
   volatile  uint8_t    CKDIVR;  /* Clock divider register                  */
   volatile  uint8_t   PCKENR1;  /* Peripheral clock gating register 1      */
   volatile  uint8_t      CSSR;  /* Clock security system register          */
   volatile  uint8_t  CLK_CCOR;  /* Configurable clock control register     */
   volatile uint16_t   PCKENR2;  /* Peripheral clock gating register 2      */
   volatile  uint8_t  HSITRIMR;  /* HSI clock calibration trimming register */
   volatile  uint8_t   SWIMCCR;  /* SWIM clock control register             */
}
CLK_TypeDef;

typedef struct TIM1_struct
{
    volatile uint8_t   CR1; /*!< TIM1 control register 1                >!*/
    volatile uint8_t   CR2; /*!< TIM1 control register 2                >!*/
    volatile uint8_t  SMCR; /*!< TIM1 slave mode control register       >!*/
    volatile uint8_t   ETR; /*!< TIM1 external trigger register         >!*/
    volatile uint8_t   IER; /*!< TIM1 interrupt enable register         >!*/
    volatile uint8_t   SR1; /*!< TIM1 status register 1                 >!*/
    volatile uint8_t   SR2; /*!< TIM1 status register 2                 >!*/
    volatile uint8_t   EGR; /*!< TIM1 event generation register         >!*/
    volatile uint8_t CCMR1; /*!< TIM1 capture/compare mode register 1   >!*/
    volatile uint8_t CCMR2; /*!< TIM1 capture/compare mode register 2   >!*/
    volatile uint8_t CCMR3; /*!< TIM1 capture/compare mode register 3   >!*/
    volatile uint8_t CCMR4; /*!< TIM1 capture/compare mode register 4   >!*/
    volatile uint8_t CCER1; /*!< TIM1 capture/compare enable register 1 >!*/
    volatile uint8_t CCER2; /*!< TIM1 capture/compare enable register 2 >!*/
    volatile uint8_t CNTRH; /*!< TIM1 counter high                      >!*/
    volatile uint8_t CNTRL; /*!< TIM1 counter low                       >!*/
    volatile uint8_t PSCRH; /*!< TIM1 prescaler register high           >!*/
    volatile uint8_t PSCRL; /*!< TIM1 prescaler register low            >!*/
    volatile uint8_t  ARRH; /*!< TIM1 auto-reload register high         >!*/
    volatile uint8_t  ARRL; /*!< TIM1 auto-reload register low          >!*/
    volatile uint8_t   RCR; /*!< TIM1 repetition counter register       >!*/
    volatile uint8_t CCR1H; /*!< TIM1 capture/compare register 1 high   >!*/
    volatile uint8_t CCR1L; /*!< TIM1 capture/compare register 1 low    >!*/
    volatile uint8_t CCR2H; /*!< TIM1 capture/compare register 2 high   >!*/
    volatile uint8_t CCR2L; /*!< TIM1 capture/compare register 2 low    >!*/
    volatile uint8_t CCR3H; /*!< TIM1 capture/compare register 3 high   >!*/
    volatile uint8_t CCR3L; /*!< TIM1 capture/compare register 3 low    >!*/
    volatile uint8_t CCR4H; /*!< TIM1 capture/compare register 4 high   >!*/
    volatile uint8_t CCR4L; /*!< TIM1 capture/compare register 4 low    >!*/
    volatile uint8_t   BKR; /*!< TIM1 break register                    >!*/
    volatile uint8_t   DTR; /*!< TIM1 dead-time register                >!*/
    volatile uint8_t  OISR; /*!< TIM1 output idle state register        >!*/
}
TIM1_TypeDef;

int main(void)
{
    init_clk();

    init_tim1();

    init_gpio();

    //__asm("rim");   // enable interrupts

    while(1)
    {
        // GPIOD->ODR |= (1 << 4) | (1 << 2);
        // delay(100000UL);
        
        // GPIOD->ODR &= ~((1 << 4) | (1 << 2));
        // delay(100000UL);
    }
}

void init_gpio(void)
{
    GPIOD->DDR |= (1 << 2);    /*set direction as output*/
    GPIOD->ODR |= (1 << 2);    /*set output 1 */
    GPIOD->CR1 |= (1 << 2);    /*init as push-pull*/
}

void clk_init(void)
{
    CLK->ICKR = 0;    // Reser HSI
    CLK->ICKR = 0x01; // Enable HSI
    CLK->ECKR = 0x00; // Reset HSE

    while((CLK->ICKR & (1 << 1)) == 0)
    {
        __asm("nop"); // Waiting for HSIRDY (High speed internal oscillator ready) 
                          // bit is set by hardware
    }

    CLK->PCKENR1 |= (1 << 7); // Enable TIM1
}

void init_tim1(void)
{
    TIM1->CR1  &= ~(1 << 4); // Counter used as up-counter

    TIM1->PSCRH = 0x07; // High bits of 2000d in prescaler
    TIM1->PSCRL = 0xD0; // Low  bits of 2000d in prescaler

    TIM1->ARRH  = 0x03; // high bits of 1000d in auto-reload register
    TIM1->ARRL  = 0xE8; // low  bits of 1000d in auto-reload register

    TIM1->IER  |= 0x01; // Enable interrupt
    TIM1->CR1  |= 0x01; // Counter enabled
}

void TIM1_Update(void) __interrupt(11)
{
    if (GPIOD->ODR & (1 << 2))
        GPIOD->ODR &= ~(1 << 2);
    else
        GPIOD->ODR |= (1 << 2);
}


