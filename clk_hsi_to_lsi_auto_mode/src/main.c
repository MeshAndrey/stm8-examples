#include <stdint.h>
#include <stm8s.h>
 
volatile uint32_t time = 200000;
 
void delay(uint32_t time)
{
    while(time--);
}
 
void init_gpio(void)
{
    SetBit(GPIOB->DDR, 5);    /* set direction as output */
    SetBit(GPIOB->CR1, 5);    /* init as push-pull       */
}

void config_option_bytes(void)
{
    // if Option bit LSI_EN is not set and NLSI_EN is set
    // option bytes are located in internal eeprom of device
    if (!ValBit(OPT->OPT3, 3) && ValBit(OPT->NOPT3, 3))
    {
        SetBit(OPT->OPT3, 3); // set LSI_EN option bit
	ClrBit(OPT->NOPT3, 3); // clear NLSI_EN option bit
    }
}

void init_clk_lsi(void)
{
    SetBit(CLK->ICKR, 3);  // LSIEN: Low speed internal RC oscillator enable
    ClrBit(CLK->SWCR, 3);  // clear SWIF flag
    // enable clock control interrupt
    SetBit(CLK->SWCR, 1);  // Set CLK_SWCR_SWEN bit
    SetBit(CLK->SWCR, 2);  // Set CLK_SWCR_SWIEN	
    // initiate automatic switch mode 
    // (only if LSI_EN option bit is set)
    CLK->SWR   = 0xD2;
}
 
void ClockControlerInterrupt (void) __interrupt(2) 
{
    ClrBit(CLK->SWCR, 3); // clear SWIF flag
}
 
void main(void)
{
    init_gpio();
    config_option_bytes();
 
    __asm__("rim"); // enable interrupts
 
    init_clk_lsi();
 
    while(1)
    {
        ChgBit(GPIOB->ODR, 5);
        delay(time);
    }
}
