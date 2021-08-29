#!/usr/bin/make

CC = gcc
SRC = $(shell find ./src/ -name "*.c")
incl = $(shell find ./include/ -name "*.h")
OBJ = $(SRC:%.c=%.o)
prom = cgame2

ICONS = $(CURDIR)/debian/cgame2/usr/share/icons/
DESKTOP = $(CURDIR)/debian/cgame2/usr/share/applications/
BINDIR = $(CURDIR)/debian/cgame2/usr/bin/

all: cgame2

$(prom): $(OBJ)
	$(CC) $(OBJ) -o $(prom)
	@rm -rf $(OBJ)

%.o: %.c $(incl)
	$(CC) -c $< -o $@

install:
	install -d "$(BINDIR)" "$(ICONS)" "$(DESKTOP)"
	install "$(CURDIR)/cgame2" "$(BINDIR)"
	install "$(CURDIR)/debian/cgame2.svg" "$(ICONS)"
	install "$(CURDIR)/debian/cgame2.desktop" "$(DESKTOP)"
	@rm -rf $(OBJ) $(prom)

clean:
	@rm -rf $(OBJ) $(prom)

