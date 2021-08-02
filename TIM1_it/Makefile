PRJ_NAME   = TIM1_it
CC         = sdcc
SRCDIR     = src
SRC        = $(wildcard $(SRCDIR)/*.c)
PROGRAMMER = stm8flash
LIB        = ../Include/
PGFLAGS    = -c stlinkv2 -p stm8s103f2 -w main.ihx
CFLAGS     = -mstm8 --std-c99 -I$(LIB)


.PHONY: all clean flash

all: 
	$(CC) $(SRC) $(CFLAGS)

clean:
	rm -f *.sym *.rst *.rel *.map *.lst *.lk *.ihx *.cdb *.asm 

flash: 
	$(PROGRAMMER) $(PGFLAGS)


