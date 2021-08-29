#!/usr/bin/make

CC = gcc
BIN = ./bin
SRC = $(shell find ./src/ -name "*.c")
incl = $(shell find ./include/ -name "*.h")
OBJ = $(SRC:%.c=%.o)
prom = cgame2

all: cgame2

$(prom): $(OBJ)
	@rm -rf $(BIN) $(prom).deb
	$(CC) $(OBJ) -o $(prom)
	@mkdir bin
	@mv $(prom) $(BIN)/main
	@rm -rf $(OBJ)

%.o: %.c $(incl)
	$(CC) -c $< -o $@

clean:
	@rm -rf $(OBJ) $(BIN) $(prom).deb

building:
	@rm -r ./deb/$(prom)/usr/local/$(prom)/*
	@cp -r ./src ./deb/$(prom)/usr/local/$(prom)/
	@cp -r ./include ./deb/$(prom)/usr/local/$(prom)/
	dpkg -b ./deb/$(prom) ./$(prom).deb

install:
	@sudo dpkg -i ./$(prom).deb
	@rm ./$(prom).deb


