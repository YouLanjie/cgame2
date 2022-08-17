#!/usr/bin/make

CC = gcc
BIN = ./bin
SRC = $(shell find ./ -name "*.c")
incl = $(shell find ./ -name "*.h")
OBJ = $(SRC:%.c=%.o)
prom = cgame2

all: cgame2

$(prom): $(OBJ)
	$(CC) -z now $(OBJ) -L lib -ltools -o $(BIN)/main
	#i686-w64-mingw32-gcc src/*.c lib/libtools_win_i686.lib -o bin/main_win_i686.exe
	#x86_64-w64-mingw32-gcc src/*.c lib/libtools_win_x86_64.lib -o bin/main_win_x86_64.exe

%.o: %.c $(incl)
	$(CC) -g -Wall -c $< -o $@

clean:
	@rm -rf $(OBJ) $(prom).deb

