#!/usr/bin/make

prom = cgame2

all: cgame2

$(prom):
	dpkg -b ./deb/$(prom) ./$(prom).deb

install:
	@sudo dpkg -i ./$(prom).deb
	@rm ./$(prom).deb


