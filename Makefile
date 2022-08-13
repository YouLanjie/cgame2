#!/usr/bin/make

CC = gcc
BIN = ./bin
SRC = $(shell find ./ -name "*.c")
incl = $(shell find ./ -name "*.h")
OBJ = $(SRC:%.c=%.o)
prom = cgame2

all: cgame2

$(prom): $(OBJ)
	@rm -rf $(BIN)
	@mkdir bin
	$(CC) -z now $(OBJ) -L lib -ltools -o $(BIN)/main

%.o: %.c $(incl)
	$(CC) -g -c $< -o $@

clean:
	@rm -rf $(OBJ) $(prom).deb

