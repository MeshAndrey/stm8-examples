/*
 * In Single conversion mode, the ADC does one conversion on the channel 
 * selected by the CH[3:0] bits in the ADC_CSR register. 
 * This mode is started by setting the ADON bit in the ADC_CR1 register,
 * while the CONT bit is 0. Once the conversion is complete, the converted data
 * are stored in the ADC_DR register, the EOC (End of Conversion) flag is set 
 * and an interrupt is generated if the EOCIE bit is set.
 */

#include <stdint.h>
#include <stm8s.h>

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

void init_adc1(void)
{
    SetBit(CLK->PCKENR2, 3); // Enable ADC clock gating

    ADC1->CSR = 0x02; // Channel 2 - AIN2 - PC4
    SetBit(ADC1->CR2, 3); // Right data alignment
    // Right alignment (eight LSB bits are written in the ADC_DRL register
    // then the remaining MSB bits are written in the ADC_DH register). 
    // The reading order should be LSB first and then MSB.

    SetBit(ADC1->CR1, 0); // Enable ADC1
}

void uart_tx_byte(uint8_t data) // send byte
{
    while(!ValBit(UART1->SR, 7));

    UART1->DR = data;
}

void TIM1_Update(void) __interrupt(11)
{   
    TIM1->SR1 &= ~TIM1_SR1_UIF;
    
    uint16_t adc_result = 0; // will be from 0 to ((2^10) - 1) = 1023
    
    SetBit(ADC1->CR1, 0); // Start convertion

    while(!ValBit(ADC1->CSR, 7)); // wait until end of convertion 
    // do not use in real application in interrupt handler because of time delay
    // this is not energy efficient way 

    adc_result |= (uint16_t) ADC1->DRL;
    adc_result |= ((uint16_t)ADC1->DRH << 8);

    uart_tx_byte(0x30 +  adc_result / 1000); // first digit
    uart_tx_byte(0x30 + (adc_result % 1000) / 100);  // second     
    uart_tx_byte(0x30 + (adc_result % 100)  / 10); // third
    uart_tx_byte(0x30 +  adc_result % 10); // last one
    uart_tx_byte('\r');
    uart_tx_byte('\n');
}

void main(void)
{
    init_gpio();
    init_uart1();
    init_tim1();
    init_adc1();

    rim(); // enable interrupts

    while(1) {}
}
