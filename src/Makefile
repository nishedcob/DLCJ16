#Compilador:
CC_LIN64=gcc
CC_WIN32=i686-w64-mingw32-gcc
CC_WIN64=x86_64-w64-mingw32-gcc
#ARGS:
#With Warnings
#CFLAGS=-Wall
#Without Warnings
#CFLAGS=
#With Warnings and Debugger Symbols
CFLAGS=-Wall -ggdb
#Source code
SRC=
BIN=
LOG=

#Commands:
all: lin64 clean

lin64: cargar_lin64.o isa_lin64.o vm_lin64.o memoria_lin64.o main_lin64.o
	$(CC_LIN64) $(CFLAGS) $(BIN)*lin64.o -o $(BIN)DLCJ16_x64.elf
	date > $(LOG)build_linux_x64.txt

#LINUX x86_64
cargar_lin64.o:
	$(CC_LIN64) $(CFLAGS) -c $(SRC)cargar.c -o $(BIN)cargar_lin64.o

isa_lin64.o:
	$(CC_LIN64) $(CFLAGS) -c $(SRC)isa.c -o $(BIN)isa_lin64.o

vm_lin64.o:
	$(CC_LIN64) $(CFLAGS) -c $(SRC)vm.c -o $(BIN)vm_lin64.o

memoria_lin64.o:
	$(CC_LIN64) $(CFLAGS) -c $(SRC)memoria.c -o $(BIN)memoria_lin64.o

main_lin64.o:
	$(CC_LIN64) $(CFLAGS) -c $(SRC)main.c -o $(BIN)main_lin64.o

#CLEAN
clean:
	rm $(BIN)*.o
	rm $(LOG)*.txt
