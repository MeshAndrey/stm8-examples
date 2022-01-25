/*
    this example shows basics of uart receiving -
    
 */

#include <stdint.h>
#include <stm8s.h>


inline void init_gpio(void)
{
    // LED GPIO
    SetBit(GPIOB->DDR, 5); // set direction as output
    SetBit(GPIOB->ODR, 5); // set output 1 
    SetBit(GPIOB->CR1, 5); // init as push-pull

    // UART GPIO
    ClrBit(GPIOD->DDR, 6); // Rx
    SetBit(GPIOD->DDR, 5); // Tx
    ClrBit(GPIOD->CR1, 6); // alternate-function
}

inline void init_uart1(void)
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
    SetBit(UART1->CR2, 5); // Receiver interrupt enable
    SetBit(UART1->CR2, 2); // Receiver enable
}

void uart_rx_handler(void) __interrupt(18)
{   
    if (!(ValBit(UART1->SR, 5)))
        return;

    uint8_t received_value = UART1->DR;

    if (received_value == '1')
        SetBit(GPIOB->ODR, 5);    
    else if (received_value == '0')
        ChgBit(GPIOB->ODR, 5);
    else
    {
        // for error handling	
    }
}

void main(void)
{
    init_gpio();
    init_uart1();

    rim(); // enable interrupts
    
    while(1)
    {
       
    }
}
