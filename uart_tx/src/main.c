/*
    this example shows basics of uart transmitting -
    global variable "counter" is incrementing and sending to uart every second 
    (by tim1 & it's interrupt)
 */

#include <stdint.h>
#include <stm8s.h>

volatile uint8_t counter = 0;

void init_gpio(void)
{
    ClrBit(GPIOD->DDR, 6); // Rx
    SetBit(GPIOD->DDR, 5); // Tx
    ClrBit(GPIOD->CR1, 6); // alternate-function
}

void init_uart1(void)
{
    SetBit(CLK->PCKENR1, 3); // enable uart1 clock 
    ClrBit(UART1->CR3, 5);
    ClrBit(UART1->CR3, 4); // 1 stop-bit

    // Selecting baud rate
    // UART_DIV = f_cpu / baud_rate = 2 000 000 / 9600 = 208d = 0xD0;
    // then this number is using in BRR1 & BRR2 registers
    // ! how to split bits look to Reference Manual !
    // UART1->BRR2 |= 0x00; - useless operation - reset value is 0x00
    UART1->BRR1 = 0x0D;
    SetBit(UART1->CR2, 3); // enable uart
}

void init_tim1(void)
{
    SetBit(CLK->PCKENR1, 7); // Enable TIM1 clock
    TIM1->CR1 &= ~TIM1_CR1_DIR; // Counter used as up-counter

    TIM1->PSCRH = 0x07; // High bits of 2000d in prescaler
    TIM1->PSCRL = 0xD0; // Low  bits of 2000d in prescaler

    TIM1->ARRH  = 0x03; // high bits of 1000d in auto-reload register
    TIM1->ARRL  = 0xE8; // low  bits of 1000d in auto-reload register

    TIM1->IER  |= TIM1_IER_UIE; // Enable interrupt
    TIM1->CR1  |= TIM1_CR1_CEN; // Counter enabled
}

void uart_tx_byte(uint8_t data) // send byte
{
    while(!ValBit(UART1->SR, 7));

    UART1->DR = data;
}

void TIM1_Update(void) __interrupt(11)
{   
    TIM1->SR1 &= ~TIM1_SR1_UIF;

    uart_tx_byte(0x30 + counter / 100);
    uart_tx_byte(0x30 + (counter % 100) / 10);
    uart_tx_byte(0x30 + counter % 10);
    uart_tx_byte('\r');
    uart_tx_byte('\n');
    counter++;
}

void main(void)
{
    init_gpio();
    init_uart1();
    init_tim1();

    rim(); // enable interrupts
    
    uart_tx_byte(0xFF);

    while(1)
    {
       
    }
}
