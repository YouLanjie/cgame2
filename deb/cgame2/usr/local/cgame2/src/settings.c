#include "../include/head.h"

void settings() {
	unsigned short x = 0,y = 0;
	int a;
	printf("\033[2;25H\033[1;32m游戏设置\033[0m");
	while (a != 'q' && a != 'Q') {
		a = input();
	}
	return;
}

