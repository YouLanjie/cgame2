#include "../include/head.h"

void help() {
	printf("\033[7;4H按下0,q,Q退出");
	printf("\033[8;4HW S A D或者方向键控制上下左右，空格下子");
	printf("\033[9;4H@为黑棋,O为白棋,+为空白");
	menu2("游戏帮助");
	input();
	return;
}


