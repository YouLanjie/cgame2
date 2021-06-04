#!/bin/sh
clear
if [ `dpkg --get-selections | grep cgame2 |wc -l` -eq 1 ]
then
	clear
	sudo dpkg -r cgame2-en
fi
sudo dpkg -i ./build/cgame2-en.deb
rm ./build/cgame2-en.deb

