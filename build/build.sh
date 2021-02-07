#!/bin/bash

# 判断是否安装了gcc
if [ `dpkg --get-selections | grep gcc |wc -l` -eq 0 ]
then
echo "未安装gcc，需要安装"
sudo apt install gcc
fi

# 清屏
clear

# 编译
gcc ../src/main.c -o ./test.out

