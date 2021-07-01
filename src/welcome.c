#include "../include/head.h"

void welcome(short p,short a) {
	Clear
	menu("游戏菜单",p,a);
	if (a == 1){
		printf("\033[8;11H\033[1;33m1.开始游戏\033[8;37H2.游戏记录");
		printf("\033[9;11H3.游戏帮助\033[9;37H4.清除存档");		
	}
	else if (a == 2) {
		printf("\033[8;11H\033[1;33m5.设置\033[8;33H0.退出游戏\033[0m");
	}
	Menu
	return;
}


