#!/usr/bin/make

CC = gcc
BIN = ./bin
SRC = $(shell find ./ -name "*.c")
incl = $(shell find ./ -name "*.h")
OBJ = $(SRC:%.c=%.o)
prom = cgame2

all: cgame2

$(prom): $(OBJ)
	@if [ ! -d "$(BIN)" ]; then mkdir $(BIN); fi
	$(CC) -z now $(OBJ) -lncurses -o $(BIN)/main

%.o: %.c $(incl)
	$(CC) -g -Wall -c $< -o $@

clean:
	rm -rf $(OBJ)

