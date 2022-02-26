#!/usr/bin/make

CC = gcc
BIN = ./bin
SRC = $(shell find ./ -name "*.c")
incl = $(shell find ./ -name "*.h")
OBJ = $(SRC:%.c=%.o)
prom = cgame2
INDIR = /usr/local/$(prom)
RESDIR = ./res

all: cgame2

$(prom): $(OBJ)
	@rm -rf $(BIN)
	$(CC) $(OBJ) -o $(prom)
	@mkdir bin
	@mv $(prom) $(BIN)/main

%.o: %.c $(incl)
	$(CC) -c $< -o $@

clean:
	@rm -rf $(OBJ) $(prom).deb

install:
	@sudo rm -rf $(INDIR)
	@sudo mkdir $(INDIR)
	@sudo chmod 777 $(INDIR)
	cp $(BIN)/main $(INDIR)/$(prom)
	@cp $(RESDIR)/$(prom).svg $(INDIR)/$(prom).svg
	@sudo cp $(RESDIR)/$(prom).desktop /usr/share/applications/$(prom).desktop
	@sudo rm -f /usr/bin/$(prom)
	sudo ln -s $(INDIR)/$(prom) /usr/bin/$(prom)

unstall:
	sudo rm -rf $(INDIR)
	@sudo rm -f /usr/share/applications/$(prom).desktop /usr/bin/$(prom)

