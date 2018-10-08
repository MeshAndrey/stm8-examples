;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.5.0 #9253 (Mar 24 2016) (Linux)
; This file was generated Thu Oct  4 23:28:10 2018
;--------------------------------------------------------
	.module main
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _TIM1_Update
	.globl _init_tim1
	.globl _init_clk
	.globl _init_gpio
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area INITIALIZED
;--------------------------------------------------------
; Stack segment in internal ram 
;--------------------------------------------------------
	.area	SSEG
__start__stack:
	.ds	1

;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area DABS (ABS)
;--------------------------------------------------------
; interrupt vector 
;--------------------------------------------------------
	.area HOME
__interrupt_vect:
	int s_GSINIT ;reset
	int 0x0000 ;trap
	int 0x0000 ;int0
	int 0x0000 ;int1
	int 0x0000 ;int2
	int 0x0000 ;int3
	int 0x0000 ;int4
	int 0x0000 ;int5
	int 0x0000 ;int6
	int 0x0000 ;int7
	int 0x0000 ;int8
	int 0x0000 ;int9
	int 0x0000 ;int10
	int _TIM1_Update ;int11
	int 0x0000 ;int12
	int 0x0000 ;int13
	int 0x0000 ;int14
	int 0x0000 ;int15
	int 0x0000 ;int16
	int 0x0000 ;int17
	int 0x0000 ;int18
	int 0x0000 ;int19
	int 0x0000 ;int20
	int 0x0000 ;int21
	int 0x0000 ;int22
	int 0x0000 ;int23
	int 0x0000 ;int24
	int 0x0000 ;int25
	int 0x0000 ;int26
	int 0x0000 ;int27
	int 0x0000 ;int28
	int 0x0000 ;int29
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area GSINIT
__sdcc_gs_init_startup:
__sdcc_init_data:
; stm8_genXINIT() start
	ldw x, #l_DATA
	jreq	00002$
00001$:
	clr (s_DATA - 1, x)
	decw x
	jrne	00001$
00002$:
	ldw	x, #l_INITIALIZER
	jreq	00004$
00003$:
	ld	a, (s_INITIALIZER - 1, x)
	ld	(s_INITIALIZED - 1, x), a
	decw	x
	jrne	00003$
00004$:
; stm8_genXINIT() end
	.area GSFINAL
	jp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME
	.area HOME
__sdcc_program_startup:
	jp	_main
;	return from main will return to caller
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CODE
;	src/main.c: 78: void init_gpio(void)
;	-----------------------------------------
;	 function init_gpio
;	-----------------------------------------
_init_gpio:
;	src/main.c: 80: GPIOD->DDR |= (1 << 2);    /*set direction as output*/
	ldw	x, #0x5011
	ld	a, (x)
	or	a, #0x04
	ld	(x), a
;	src/main.c: 81: GPIOD->ODR |= (1 << 2);    /*set output 1 */
	ldw	x, #0x500f
	ld	a, (x)
	or	a, #0x04
	ld	(x), a
;	src/main.c: 82: GPIOD->CR1 |= (1 << 2);    /*init as push-pull*/
	ldw	x, #0x5012
	ld	a, (x)
	or	a, #0x04
	ld	(x), a
	ret
;	src/main.c: 85: void init_clk(void)
;	-----------------------------------------
;	 function init_clk
;	-----------------------------------------
_init_clk:
;	src/main.c: 87: CLK->ICKR = 0;    // Reser HSI
	mov	0x50c0+0, #0x00
;	src/main.c: 88: CLK->ICKR = 0x01; // Enable HSI
	mov	0x50c0+0, #0x01
;	src/main.c: 89: CLK->ECKR = 0x00; // Reset HSE
	mov	0x50c1+0, #0x00
;	src/main.c: 91: while((CLK->ICKR & (1 << 1)) == 0)
00101$:
	ldw	x, #0x50c0
	ld	a, (x)
	bcp	a, #0x02
	jrne	00103$
;	src/main.c: 93: __asm__("nop");   // Waiting for HSIRDY (High speed internal oscillator ready) 
	nop
	jra	00101$
00103$:
;	src/main.c: 97: CLK->PCKENR1 |= (1 << 7); // Enable TIM1
	bset	0x50c7, #7
	ret
;	src/main.c: 100: void init_tim1(void)
;	-----------------------------------------
;	 function init_tim1
;	-----------------------------------------
_init_tim1:
;	src/main.c: 102: TIM1->CR1  &= ~(1 << 4); // Counter used as up-counter
	ldw	x, #0x5250
	ld	a, (x)
	and	a, #0xef
	ld	(x), a
;	src/main.c: 104: TIM1->PSCRH = 0x07; // High bits of 2000d in prescaler
	mov	0x5260+0, #0x07
;	src/main.c: 105: TIM1->PSCRL = 0xD0; // Low  bits of 2000d in prescaler
	mov	0x5261+0, #0xd0
;	src/main.c: 107: TIM1->ARRH  = 0x03; // high bits of 1000d in auto-reload register
	mov	0x5262+0, #0x03
;	src/main.c: 108: TIM1->ARRL  = 0xE8; // low  bits of 1000d in auto-reload register
	mov	0x5263+0, #0xe8
;	src/main.c: 110: TIM1->IER  |= 0x01; // Enable interrupt
	bset	0x5254, #0
;	src/main.c: 111: TIM1->CR1  |= 0x01; // Counter enabled
	bset	0x5250, #0
	ret
;	src/main.c: 114: void TIM1_Update(void) __interrupt(11)
;	-----------------------------------------
;	 function TIM1_Update
;	-----------------------------------------
_TIM1_Update:
;	src/main.c: 116: TIM1->SR1 &= 0x00;
	ldw	x, #0x5255
	ld	a, (x)
	mov	0x5255+0, #0x00
;	src/main.c: 118: if (GPIOD->ODR & (1 << 2))
	ldw	x, #0x500f
	ld	a, (x)
	bcp	a, #0x04
	jreq	00102$
;	src/main.c: 119: GPIOD->ODR &= ~(1 << 2);
	ldw	x, #0x500f
	ld	a, (x)
	and	a, #0xfb
	ld	(x), a
	jra	00104$
00102$:
;	src/main.c: 121: GPIOD->ODR |= (1 << 2);
	ldw	x, #0x500f
	ld	a, (x)
	or	a, #0x04
	ld	(x), a
00104$:
	iret
;	src/main.c: 124: int main(void)
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
;	src/main.c: 126: init_clk();
	call	_init_clk
;	src/main.c: 128: init_tim1();
	call	_init_tim1
;	src/main.c: 130: init_gpio();
	call	_init_gpio
;	src/main.c: 132: __asm__("rim"); // enable interrupts
	rim
;	src/main.c: 134: GPIOD->ODR |= (1 << 2);
	ldw	x, #0x500f
	ld	a, (x)
	or	a, #0x04
	ld	(x), a
;	src/main.c: 136: while(1)
00102$:
	jra	00102$
	ret
	.area CODE
	.area INITIALIZER
	.area CABS (ABS)
