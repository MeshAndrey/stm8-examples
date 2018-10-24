/*
    this example shows basics of uart transmitting -
    global varieble "counter" is incrementing and sending to uart every second 
    (by tim1 & it's interrupt)
 */

#include <stdint.h>
#include <stdio.h>

#define TIM1_BaseAddress        0x005250
#define TIM1  ((TIM1_TypeDef *) TIM1_BaseAddress)

#define CLK_BaseAddress         0x0050C0
#define CLK   ((CLK_TypeDef *)  CLK_BaseAddress)

#define GPIOC_BaseAddress       0x00500A
#define GPIOC ((GPIO_TypeDef *) GPIOC_BaseAddress)

#define GPIOD_BaseAddress       0x00500F
#define GPIOD ((GPIO_TypeDef *) GPIOD_BaseAddress)

#define UART1_BaseAddress       0x005230
#define UART1 ((UART_TypeDef *) UART1_BaseAddress)

#define BUFFER 16

volatile uint8_t counter = 0;
volatile char text[BUFFER];

typedef struct CLK_struct
{
    volatile  uint8_t      ICKR; /* Internal clock control register         */
    volatile  uint8_t      ECKR; /* External clock control register         */
    volatile  uint8_t  RESERVED;
    volatile  uint8_t      CMSR; /* Clock master status register            */
    volatile  uint8_t       SWR; /* Clock master switch register            */
    volatile  uint8_t      SWCR; /* Clock switch control register           */
    volatile  uint8_t    CKDIVR; /* Clock divider register                  */
    volatile  uint8_t   PCKENR1; /* Peripheral clock gating register 1      */
    volatile  uint8_t      CSSR; /* Clock security system register          */
    volatile  uint8_t      CCOR; /* Configurable clock control register     */
    volatile uint16_t   PCKENR2; /* Peripheral clock gating register 2      */
    volatile  uint8_t  HSITRIMR; /* HSI clock calibration trimming register */
    volatile  uint8_t   SWIMCCR; /* SWIM clock control register             */
}
CLK_TypeDef;

typedef struct GPIO_struct
{
    volatile uint8_t ODR; /*!< Output Data Register     */
    volatile uint8_t IDR; /*!< Input Data Register      */
    volatile uint8_t DDR; /*!< Data Direction Register  */
    volatile uint8_t CR1; /*!< Configuration Register 1 */
    volatile uint8_t CR2; /*!< Configuration Register 2 */
}
GPIO_TypeDef;

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

typedef struct UART_struct
{
    volatile uint8_t   SR; /*!< Status Register      */
    volatile uint8_t   DR; /*!< Data Register        */
    volatile uint8_t BRR1; /*!< Baud rate register 1 */
    volatile uint8_t BRR2; /*!< Baud rate register 2 */
    volatile uint8_t  CR1; /*!< Control register 1   */
    volatile uint8_t  CR2; /*!< Control register 2   */
    volatile uint8_t  CR3; /*!< Control register 3   */
    volatile uint8_t  CR4; /*!< Control register 4   */
    volatile uint8_t  CR5; /*!< Control register 5   */
    volatile uint8_t  GTR; /*!< Guard time register  */
    volatile uint8_t PSCR; /*!< Prescaler register   */
}
UART_TypeDef;

void init_gpio(void)
{
    GPIOD->DDR &= ~(1 << 6); // Rx
    GPIOD->DDR |=  (1 << 5); // Tx

    GPIOD->CR1 &= ~(1 << 6); // alternate-function
}

void init_clk(void) /* */
{

    CLK->ICKR = 0;    // Reset HSI
    CLK->ICKR = 0x01; // Enable HSI
    CLK->ECKR = 0x00; // Reset HSE

    while((CLK->ICKR & (1 << 1)) == 0)
    {
        __asm__("nop");   // Waiting for HSIRDY (High speed internal oscillator ready) 
                          // bit is set by hardware
    }

    CLK->PCKENR1 |= (1 << 3); // enable uart 1
    CLK->PCKENR1 |= (1 << 7); // Enable TIM1    
}

void init_uart1(void)
{
    UART1->CR2 |= (1 << 3); // enable uart
    UART1->CR3 &= ~(1 << 5 | 1 << 4); // 1 stop-bit

    // Selecting baud rate
    // UART_DIV = f_cpu / baud_rate = 2 000 000 / 9600 = 208d = 0xD0;
    // then this number is using in BRR1 & BRR2 registers
    // ! how to split bits look to Reference Manual !
    UART1->BRR2 |= 0x00;
    UART1->BRR1 |= 0x0D;
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
    TIM1->SR1 &= 0x00;

    sprintf(text, "%d\r\n", counter);
    printf(text);
    
    counter++;    
}

void putchar(char c) //send char to uart
{
    while(!(UART1->SR & (1 << 7))); // wait for data register of uart1 is empty
    UART1->DR = c;
}

// next two function are alternative of printf()
// void uart_tx_byte(unsigned char data) // send byte
// {
//     while(!(UART1->SR & (1 << 7)));

//     UART1->DR = data;
// }
 
// // send array of data
// void uart_tx_data(unsigned char * data, unsigned char len)
// {
//     while(len--)
//     {
//         uart_tx_byte(*data++);
//     }
// }

void main(void)
{
    init_gpio();
    init_clk();
    init_uart1();
    init_tim1();

    __asm__("rim"); // enable interrupts
    
    // uart_tx_data("Hello, world!\r\n", 15);
    while(1)
    {
       
    }
}
