PRJ_NAME   = gpio_led_blink
CC         = sdcc
SRCDIR     = src
SRC        = $(wildcard $(SRCDIR)/*.c)
PROGRAMMER = stm8flash
LIB        = ../Include/
BUILD_DIR  = build/
CFLAGS     = -mstm8 --std-c99 -I$(LIB) -o $(BUILD_DIR)
PGFLAGS    = -c stlinkv2 -p stm8s103f2 -w $(BUILD_DIR)main.ihx

.PHONY: all clean flash

all: 
	mkdir $(BUILD_DIR)
	$(CC) $(SRC) $(CFLAGS)

clean:
	rm -r $(BUILD_DIR) 

flash: 
	$(PROGRAMMER) $(PGFLAGS)

