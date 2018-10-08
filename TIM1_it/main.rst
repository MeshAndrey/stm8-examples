                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 3.5.0 #9253 (Mar 24 2016) (Linux)
                                      4 ; This file was generated Thu Oct  4 23:28:10 2018
                                      5 ;--------------------------------------------------------
                                      6 	.module main
                                      7 	.optsdcc -mstm8
                                      8 	
                                      9 ;--------------------------------------------------------
                                     10 ; Public variables in this module
                                     11 ;--------------------------------------------------------
                                     12 	.globl _main
                                     13 	.globl _TIM1_Update
                                     14 	.globl _init_tim1
                                     15 	.globl _init_clk
                                     16 	.globl _init_gpio
                                     17 ;--------------------------------------------------------
                                     18 ; ram data
                                     19 ;--------------------------------------------------------
                                     20 	.area DATA
                                     21 ;--------------------------------------------------------
                                     22 ; ram data
                                     23 ;--------------------------------------------------------
                                     24 	.area INITIALIZED
                                     25 ;--------------------------------------------------------
                                     26 ; Stack segment in internal ram 
                                     27 ;--------------------------------------------------------
                                     28 	.area	SSEG
      000001                         29 __start__stack:
      000001                         30 	.ds	1
                                     31 
                                     32 ;--------------------------------------------------------
                                     33 ; absolute external ram data
                                     34 ;--------------------------------------------------------
                                     35 	.area DABS (ABS)
                                     36 ;--------------------------------------------------------
                                     37 ; interrupt vector 
                                     38 ;--------------------------------------------------------
                                     39 	.area HOME
      008000                         40 __interrupt_vect:
      008000 82 00 80 83             41 	int s_GSINIT ;reset
      008004 82 00 00 00             42 	int 0x0000 ;trap
      008008 82 00 00 00             43 	int 0x0000 ;int0
      00800C 82 00 00 00             44 	int 0x0000 ;int1
      008010 82 00 00 00             45 	int 0x0000 ;int2
      008014 82 00 00 00             46 	int 0x0000 ;int3
      008018 82 00 00 00             47 	int 0x0000 ;int4
      00801C 82 00 00 00             48 	int 0x0000 ;int5
      008020 82 00 00 00             49 	int 0x0000 ;int6
      008024 82 00 00 00             50 	int 0x0000 ;int7
      008028 82 00 00 00             51 	int 0x0000 ;int8
      00802C 82 00 00 00             52 	int 0x0000 ;int9
      008030 82 00 00 00             53 	int 0x0000 ;int10
      008034 82 00 80 F2             54 	int _TIM1_Update ;int11
      008038 82 00 00 00             55 	int 0x0000 ;int12
      00803C 82 00 00 00             56 	int 0x0000 ;int13
      008040 82 00 00 00             57 	int 0x0000 ;int14
      008044 82 00 00 00             58 	int 0x0000 ;int15
      008048 82 00 00 00             59 	int 0x0000 ;int16
      00804C 82 00 00 00             60 	int 0x0000 ;int17
      008050 82 00 00 00             61 	int 0x0000 ;int18
      008054 82 00 00 00             62 	int 0x0000 ;int19
      008058 82 00 00 00             63 	int 0x0000 ;int20
      00805C 82 00 00 00             64 	int 0x0000 ;int21
      008060 82 00 00 00             65 	int 0x0000 ;int22
      008064 82 00 00 00             66 	int 0x0000 ;int23
      008068 82 00 00 00             67 	int 0x0000 ;int24
      00806C 82 00 00 00             68 	int 0x0000 ;int25
      008070 82 00 00 00             69 	int 0x0000 ;int26
      008074 82 00 00 00             70 	int 0x0000 ;int27
      008078 82 00 00 00             71 	int 0x0000 ;int28
      00807C 82 00 00 00             72 	int 0x0000 ;int29
                                     73 ;--------------------------------------------------------
                                     74 ; global & static initialisations
                                     75 ;--------------------------------------------------------
                                     76 	.area HOME
                                     77 	.area GSINIT
                                     78 	.area GSFINAL
                                     79 	.area GSINIT
      008083                         80 __sdcc_gs_init_startup:
      008083                         81 __sdcc_init_data:
                                     82 ; stm8_genXINIT() start
      008083 AE 00 00         [ 2]   83 	ldw x, #l_DATA
      008086 27 07            [ 1]   84 	jreq	00002$
      008088                         85 00001$:
      008088 72 4F 00 00      [ 1]   86 	clr (s_DATA - 1, x)
      00808C 5A               [ 2]   87 	decw x
      00808D 26 F9            [ 1]   88 	jrne	00001$
      00808F                         89 00002$:
      00808F AE 00 00         [ 2]   90 	ldw	x, #l_INITIALIZER
      008092 27 09            [ 1]   91 	jreq	00004$
      008094                         92 00003$:
      008094 D6 81 26         [ 1]   93 	ld	a, (s_INITIALIZER - 1, x)
      008097 D7 00 00         [ 1]   94 	ld	(s_INITIALIZED - 1, x), a
      00809A 5A               [ 2]   95 	decw	x
      00809B 26 F7            [ 1]   96 	jrne	00003$
      00809D                         97 00004$:
                                     98 ; stm8_genXINIT() end
                                     99 	.area GSFINAL
      00809D CC 80 80         [ 2]  100 	jp	__sdcc_program_startup
                                    101 ;--------------------------------------------------------
                                    102 ; Home
                                    103 ;--------------------------------------------------------
                                    104 	.area HOME
                                    105 	.area HOME
      008080                        106 __sdcc_program_startup:
      008080 CC 81 13         [ 2]  107 	jp	_main
                                    108 ;	return from main will return to caller
                                    109 ;--------------------------------------------------------
                                    110 ; code
                                    111 ;--------------------------------------------------------
                                    112 	.area CODE
                                    113 ;	src/main.c: 78: void init_gpio(void)
                                    114 ;	-----------------------------------------
                                    115 ;	 function init_gpio
                                    116 ;	-----------------------------------------
      0080A0                        117 _init_gpio:
                                    118 ;	src/main.c: 80: GPIOD->DDR |= (1 << 2);    /*set direction as output*/
      0080A0 AE 50 11         [ 2]  119 	ldw	x, #0x5011
      0080A3 F6               [ 1]  120 	ld	a, (x)
      0080A4 AA 04            [ 1]  121 	or	a, #0x04
      0080A6 F7               [ 1]  122 	ld	(x), a
                                    123 ;	src/main.c: 81: GPIOD->ODR |= (1 << 2);    /*set output 1 */
      0080A7 AE 50 0F         [ 2]  124 	ldw	x, #0x500f
      0080AA F6               [ 1]  125 	ld	a, (x)
      0080AB AA 04            [ 1]  126 	or	a, #0x04
      0080AD F7               [ 1]  127 	ld	(x), a
                                    128 ;	src/main.c: 82: GPIOD->CR1 |= (1 << 2);    /*init as push-pull*/
      0080AE AE 50 12         [ 2]  129 	ldw	x, #0x5012
      0080B1 F6               [ 1]  130 	ld	a, (x)
      0080B2 AA 04            [ 1]  131 	or	a, #0x04
      0080B4 F7               [ 1]  132 	ld	(x), a
      0080B5 81               [ 4]  133 	ret
                                    134 ;	src/main.c: 85: void init_clk(void)
                                    135 ;	-----------------------------------------
                                    136 ;	 function init_clk
                                    137 ;	-----------------------------------------
      0080B6                        138 _init_clk:
                                    139 ;	src/main.c: 87: CLK->ICKR = 0;    // Reser HSI
      0080B6 35 00 50 C0      [ 1]  140 	mov	0x50c0+0, #0x00
                                    141 ;	src/main.c: 88: CLK->ICKR = 0x01; // Enable HSI
      0080BA 35 01 50 C0      [ 1]  142 	mov	0x50c0+0, #0x01
                                    143 ;	src/main.c: 89: CLK->ECKR = 0x00; // Reset HSE
      0080BE 35 00 50 C1      [ 1]  144 	mov	0x50c1+0, #0x00
                                    145 ;	src/main.c: 91: while((CLK->ICKR & (1 << 1)) == 0)
      0080C2                        146 00101$:
      0080C2 AE 50 C0         [ 2]  147 	ldw	x, #0x50c0
      0080C5 F6               [ 1]  148 	ld	a, (x)
      0080C6 A5 02            [ 1]  149 	bcp	a, #0x02
      0080C8 26 03            [ 1]  150 	jrne	00103$
                                    151 ;	src/main.c: 93: __asm__("nop");   // Waiting for HSIRDY (High speed internal oscillator ready) 
      0080CA 9D               [ 1]  152 	nop
      0080CB 20 F5            [ 2]  153 	jra	00101$
      0080CD                        154 00103$:
                                    155 ;	src/main.c: 97: CLK->PCKENR1 |= (1 << 7); // Enable TIM1
      0080CD 72 1E 50 C7      [ 1]  156 	bset	0x50c7, #7
      0080D1 81               [ 4]  157 	ret
                                    158 ;	src/main.c: 100: void init_tim1(void)
                                    159 ;	-----------------------------------------
                                    160 ;	 function init_tim1
                                    161 ;	-----------------------------------------
      0080D2                        162 _init_tim1:
                                    163 ;	src/main.c: 102: TIM1->CR1  &= ~(1 << 4); // Counter used as up-counter
      0080D2 AE 52 50         [ 2]  164 	ldw	x, #0x5250
      0080D5 F6               [ 1]  165 	ld	a, (x)
      0080D6 A4 EF            [ 1]  166 	and	a, #0xef
      0080D8 F7               [ 1]  167 	ld	(x), a
                                    168 ;	src/main.c: 104: TIM1->PSCRH = 0x07; // High bits of 2000d in prescaler
      0080D9 35 07 52 60      [ 1]  169 	mov	0x5260+0, #0x07
                                    170 ;	src/main.c: 105: TIM1->PSCRL = 0xD0; // Low  bits of 2000d in prescaler
      0080DD 35 D0 52 61      [ 1]  171 	mov	0x5261+0, #0xd0
                                    172 ;	src/main.c: 107: TIM1->ARRH  = 0x03; // high bits of 1000d in auto-reload register
      0080E1 35 03 52 62      [ 1]  173 	mov	0x5262+0, #0x03
                                    174 ;	src/main.c: 108: TIM1->ARRL  = 0xE8; // low  bits of 1000d in auto-reload register
      0080E5 35 E8 52 63      [ 1]  175 	mov	0x5263+0, #0xe8
                                    176 ;	src/main.c: 110: TIM1->IER  |= 0x01; // Enable interrupt
      0080E9 72 10 52 54      [ 1]  177 	bset	0x5254, #0
                                    178 ;	src/main.c: 111: TIM1->CR1  |= 0x01; // Counter enabled
      0080ED 72 10 52 50      [ 1]  179 	bset	0x5250, #0
      0080F1 81               [ 4]  180 	ret
                                    181 ;	src/main.c: 114: void TIM1_Update(void) __interrupt(11)
                                    182 ;	-----------------------------------------
                                    183 ;	 function TIM1_Update
                                    184 ;	-----------------------------------------
      0080F2                        185 _TIM1_Update:
                                    186 ;	src/main.c: 116: TIM1->SR1 &= 0x00;
      0080F2 AE 52 55         [ 2]  187 	ldw	x, #0x5255
      0080F5 F6               [ 1]  188 	ld	a, (x)
      0080F6 35 00 52 55      [ 1]  189 	mov	0x5255+0, #0x00
                                    190 ;	src/main.c: 118: if (GPIOD->ODR & (1 << 2))
      0080FA AE 50 0F         [ 2]  191 	ldw	x, #0x500f
      0080FD F6               [ 1]  192 	ld	a, (x)
      0080FE A5 04            [ 1]  193 	bcp	a, #0x04
      008100 27 09            [ 1]  194 	jreq	00102$
                                    195 ;	src/main.c: 119: GPIOD->ODR &= ~(1 << 2);
      008102 AE 50 0F         [ 2]  196 	ldw	x, #0x500f
      008105 F6               [ 1]  197 	ld	a, (x)
      008106 A4 FB            [ 1]  198 	and	a, #0xfb
      008108 F7               [ 1]  199 	ld	(x), a
      008109 20 07            [ 2]  200 	jra	00104$
      00810B                        201 00102$:
                                    202 ;	src/main.c: 121: GPIOD->ODR |= (1 << 2);
      00810B AE 50 0F         [ 2]  203 	ldw	x, #0x500f
      00810E F6               [ 1]  204 	ld	a, (x)
      00810F AA 04            [ 1]  205 	or	a, #0x04
      008111 F7               [ 1]  206 	ld	(x), a
      008112                        207 00104$:
      008112 80               [11]  208 	iret
                                    209 ;	src/main.c: 124: int main(void)
                                    210 ;	-----------------------------------------
                                    211 ;	 function main
                                    212 ;	-----------------------------------------
      008113                        213 _main:
                                    214 ;	src/main.c: 126: init_clk();
      008113 CD 80 B6         [ 4]  215 	call	_init_clk
                                    216 ;	src/main.c: 128: init_tim1();
      008116 CD 80 D2         [ 4]  217 	call	_init_tim1
                                    218 ;	src/main.c: 130: init_gpio();
      008119 CD 80 A0         [ 4]  219 	call	_init_gpio
                                    220 ;	src/main.c: 132: __asm__("rim"); // enable interrupts
      00811C 9A               [ 1]  221 	rim
                                    222 ;	src/main.c: 134: GPIOD->ODR |= (1 << 2);
      00811D AE 50 0F         [ 2]  223 	ldw	x, #0x500f
      008120 F6               [ 1]  224 	ld	a, (x)
      008121 AA 04            [ 1]  225 	or	a, #0x04
      008123 F7               [ 1]  226 	ld	(x), a
                                    227 ;	src/main.c: 136: while(1)
      008124                        228 00102$:
      008124 20 FE            [ 2]  229 	jra	00102$
      008126 81               [ 4]  230 	ret
                                    231 	.area CODE
                                    232 	.area INITIALIZER
                                    233 	.area CABS (ABS)
