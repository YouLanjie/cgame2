#include "src/head.h"                           //导入头文件

int main() {
	int a;
	Clear
	while (a != 0x1B && 0x30 && 0x51 && 0x71) {
		welcome();
		a = kbhit();
		getchar();
		printf("\n\n\n");
		Clear
		switch (a) {
			case 0x1B:
			case 0x30:
			case 0x51:
			case 0x71:
				return 0;
				break;
			case 0x31:
				game();
				break;
			case 0x32:
				printf("暂未开发\n");
				kbhit();
				getchar();
				break;
			case 0x33:
				help();
				break;
			default:
				puts("\n\t\t\t\t    错误！");
				puts("\t\t\t       按任意按键返回");
				kbhit();
				getchar();
				break;
		}
		Clear
	}
	Clear
	return 0;
}

void welcome() {
	Clear
	printf("\n                                     \033[;37m欢迎\033[0m\n\n\n");
	printf("\033[;33m--------------------------------------------------------------------------------\n");
	printf("\033[;33m|                                                                              |\n");
	printf("\033[;33m|                                                                              |\033[0m\n");
	printf("\033[;33m|\033[0m                   1.开始游戏                    2.游戏记录                   \033[;33m|\033[0m\n");
	printf("\033[;33m|\033[0m                   3.游戏帮助                    0.退出游戏                   \033[;33m|\033[0m\n");
	printf("\033[;33m|\033[0m  请选择:\033[69C\033[;33m|\n");
	printf("\033[;33m|                                                                              |\n");
	printf("--------------------------------------------------------------------------------\033[0m\033[2A\033[69D");
	return;
}

void game() {

	return;
}

void help() {
	puts("\t\t\t\t   游戏帮助");
	printf("按任意按键返回：");
	kbhit();
	getchar();
	return;
}
