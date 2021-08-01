# stm8-examples

This repository contains some examples for stm8s103f2p6. 
It compiles well on Ubuntu. Other linux distroes are not tested. Should work fine on Windows with Cygwin.
To use any example build source code with Makefiles and make.
Files in "Include/" dir were created by ST. I add some changes to make SDCC compiler support.

Build project:
 $ make
Flash binary file that was created by previous command:
 $ make flash
Clean project directory:
 $ make clean

Install compiler (Ubuntu):
 $ sudo apt install sdcc

Install flash tool:
 $ git clone https://github.com/vdudouyt/stm8flash
 $ cd stm8flash/
 $ make
 $ make install
Note: this tool may require libusb-1.0-0-dev package.
To install this package use:
 $ sudo apt install libusb-1.0-0-dev

Compile:
 $ sdcc -mstm8 --std-c99 main.c

Flash:
 $ stm8flash -c stlinkv2 -p stm8s103f2 -w main.ihx

