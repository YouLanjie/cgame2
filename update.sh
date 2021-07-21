#!/bin/bash

rm -r ./deb/cgame2-en/usr/local/cgame2-en/*
cp -r ./src ./deb/cgame2-en/usr/local/cgame2-en/
cp -r ./include ./deb/cgame2-en/usr/local/cgame2-en/
dpkg -b ./deb/cgame2-en ./deb/cgame2-en.deb

if [ `dpkg --get-selections | grep cgame2-en |wc -l` -eq 1 ]
then
	sudo dpkg -r cgame2-en
fi
sudo dpkg -i ./deb/cgame2-en.deb
rm ./deb/cgame2-en.deb

