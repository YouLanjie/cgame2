#!/bin/bash
clear
if [ `dpkg --get-selections cgame2 |wc -l` -eq 1 ]
then
	clear
	sudo dpkg -r cgame2
fi
sudo dpkg -i ./build/cgame2.deb
rm ./build/cgame2.deb

