PRJ_NAME   = gpio_led_blink
CC         = sdcc
SRCDIR     = src
SRC        = $(wildcard $(SRCDIR)/*.c)
PROGRAMMER = stm8flash
PGFLAGS    = -c stlinkv2 -p stm8s103f2 -w main.ihx
CFLAGS     = -mstm8 --std-c99


.PHONY: all clean flash

all: 
	$(CC) $(SRC) $(CFLAGS)

clean:
	rm -f *.sym *.rst *.rel *.map *.lst *.lk *.ihx *.cdb *.asm 

flash: 
	$(PROGRAMMER) $(PGFLAGS)


