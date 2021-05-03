#!/bin/sh
clear
cp -r ./src ./build/deb/cgame2/usr/local/cgame2/
dpkg -b ./build/deb/cgame2 ./build/cgame2.deb
