#include "src/head.h"                           //导入头文件

int main() {
	int a=0,b;

	Clear
	while (a <= 100) {
		welcome();
		b = kbhit();
		getchar();
		switch (b) {
			case 0x1B:
			case 0x30:
			case 0x51:
			case 0x71:
				Clear
				return 0;
				break;
			case 0x31:
				Clear
				printf("暂未开发\n");
				getchar();
				break;
			case 0x32:
				Clear
				printf("暂未开发\n");
				getchar();
				break;
			case 0x33:
				Clear
				help();
				Clear
				break;
			default:
				Clear
				puts("输入错误！按下Enter重试");
				a++;
				getchar();
				Clear
				break;
		}
		Clear
	}
	Clear
	return 0;
}

void welcome() {
	printf("\n                                     \033[;31m欢迎\033[0m\n\n\n");
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

void help() {
	puts("\t\t\t\t   游戏帮助");
	printf("按Enter返回：");
	getchar();
	return;
}
