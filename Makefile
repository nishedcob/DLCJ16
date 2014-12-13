#Compilador:
CC_LIN64=gcc
CC_WIN32=i686-w64-mingw32-gcc
CC_WIN64=x86_64-w64-mingw32-gcc
#ARGS:
#With Warnings
CFLAGS=-Wall
#Without Warnings
#CFLAGS=
#Source code
SRC=src/
BIN=bin/
LOG=log/

#Commands:
all: lin64 win32 win64 clean

lin64: cargar_lin64.o isa_lin64.o vm_lin64.o memoria_lin64.o main_lin64.o
	$(CC_LIN64) $(CFLAGS) $(BIN)*lin64.o -o $(BIN)DLCJ16_x64.elf
	date > $(LOG)build_linux_x64.txt

win32: cargar_win32.o isa_win32.o vm_win32.o memoria_win32.o main_win32.o
	$(CC_WIN32) $(CFLAGS) $(BIN)*win32.o -o $(BIN)DLCJ16_x86.exe
	date > $(LOG)build_windows_x86.txt

win64: cargar_win64.o isa_win64.o vm_win64.o memoria_win64.o main_win64.o
	$(CC_WIN64) $(CFLAGS) $(BIN)*win64.o -o $(BIN)DLCJ16_x64.exe
	date > $(LOG)build_windows_x64.txt

#LINUX x86_64
cargar_lin64.o:
	$(CC_LIN64) -c $(SRC)cargar.c -o $(BIN)cargar_lin64.o

isa_lin64.o:
	$(CC_LIN64) -c $(SRC)isa.c -o $(BIN)isa_lin64.o

vm_lin64.o:
	$(CC_LIN64) -c $(SRC)vm.c -o $(BIN)vm_lin64.o

memoria_lin64.o:
	$(CC_LIN64) -c $(SRC)memoria.c -o $(BIN)memoria_lin64.o

main_lin64.o:
	$(CC_LIN64) -c $(SRC)main.c -o $(BIN)main_lin64.o

#WINDOWS x86_64
cargar_win64.o:
	$(CC_WIN64) -c $(SRC)cargar.c -o $(BIN)cargar_win64.o

isa_win64.o:
	$(CC_WIN64) -c $(SRC)isa.c -o $(BIN)isa_win64.o

vm_win64.o:
	$(CC_WIN64) -c $(SRC)vm.c -o $(BIN)vm_win64.o

memoria_win64.o:
	$(CC_WIN64) -c $(SRC)memoria.c -o $(BIN)memoria_win64.o

main_win64.o:
	$(CC_WIN64) -c $(SRC)main.c -o $(BIN)main_win64.o

#WINDOWS x86
cargar_win32.o:
	$(CC_WIN32) -c $(SRC)cargar.c -o $(BIN)cargar_win32.o

isa_win32.o:
	$(CC_WIN32) -c $(SRC)isa.c -o $(BIN)isa_win32.o

vm_win32.o:
	$(CC_WIN32) -c $(SRC)vm.c -o $(BIN)vm_win32.o

memoria_win32.o:
	$(CC_WIN32) -c $(SRC)memoria.c -o $(BIN)memoria_win32.o

main_win32.o:
	$(CC_WIN32) -c $(SRC)main.c -o $(BIN)main_win32.o

#CLEAN
clean:
	rm $(BIN)*.o