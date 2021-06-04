#!/bin/sh
clear
cp -r ./src ./build/deb/cgame2-en/usr/local/cgame2-en/
dpkg -b ./build/deb/cgame2-en ./build/cgame2-en.deb
