PRJ_NAME   = uart_1
CC         = sdcc
SRCDIR     = src
SRC        = $(wildcard $(SRCDIR)/*.c)
PROGRAMMER = stm8flash
LIB        = ../Include/
BUILD_DIR  = build/
PGFLAGS    = -c stlinkv2 -p stm8s103f2 -w $(BUILD_DIR)main.ihx
CFLAGS     = -mstm8 --std-c99 -I$(LIB) -o $(BUILD_DIR)


.PHONY: all clean flash burn hex bin

all: 
	[ -d $(BUILD_DIR) ] || mkdir $(BUILD_DIR)
	$(CC) $(SRC) $(CFLAGS)

clean:
	[ -d $(BUILD_DIR) ] && rm -r $(BUILD_DIR)

flash: 
	$(PROGRAMMER) $(PGFLAGS)


