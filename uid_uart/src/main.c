/*
    this example shows unique device ID through uart.
 */

#include <stdint.h>
#include <stm8s.h>

#define UID_BaseAddress      0x004865   // Base address of UID (refer to datasheet)
#define UID ((UID_TypeDef *) UID_BaseAddress)

#define UID_LENGTH_BIT       (96)
#define UID_LENGTH_BYTE      (UID_LENGTH_BIT / 8)

typedef struct UID_struct
{
    volatile uint16_t WAFER_X;
    volatile uint16_t WAFER_Y;
    volatile uint8_t  WAFER_NUMBER;
    volatile uint8_t  LOT_NUMBER[7];
}
UID_TypeDef;

void init_gpio(void)
{
    ClrBit(GPIOD->DDR, 6); // Rx
    SetBit(GPIOD->DDR, 5); // Tx
    ClrBit(GPIOD->CR1, 6); // alternate-function
}

void init_uart1(void)
{
    SetBit(CLK->PCKENR1, 3); // enable uart1 clock 
    SetBit(UART1->CR2, 3); // enable uart
    ClrBit(UART1->CR3, 5);
    ClrBit(UART1->CR3, 4); // 1 stop-bit

    // Selecting baud rate
    // UART_DIV = f_cpu / baud_rate = 2 000 000 / 9600 = 208d = 0xD0;
    // then this number is using in BRR1 & BRR2 registers
    // ! how to split bits look to Reference Manual !
    UART1->BRR2 |= 0x00;
    UART1->BRR1 |= 0x0D;
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

void uart_tx_array(uint8_t * array, uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        uart_tx_byte(0x30 + (array[i] / 100));        // send third digit of number as char
        uart_tx_byte(0x30 + ((array[i] % 100) / 10)); // send second
        uart_tx_byte(0x30 + (array[i] % 10));         // send first
	uart_tx_byte(' '); // send separator between bytes
    }
}

void TIM1_Update(void) __interrupt(11)
{   
    TIM1->SR1 &= ~TIM1_SR1_UIF;

    uart_tx_array((uint8_t*)UID, UID_LENGTH_BYTE);
    uart_tx_byte('\r');
    uart_tx_byte('\n');
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
