#!/bin/bash

rm -r ./deb/cgame2/usr/local/cgame2/*
cp -r ./src ./deb/cgame2/usr/local/cgame2/
cp -r ./include ./deb/cgame2/usr/local/cgame2/
cp -r ./doc ./deb/cgame2/usr/local/cgame2/
dpkg -b ./deb/cgame2 ./deb/cgame2.deb

if [ `dpkg --get-selections cgame2 |wc -l` -eq 1 ]
then
	sudo dpkg -r cgame2
fi
sudo dpkg -i ./deb/cgame2.deb
rm ./deb/cgame2.deb

