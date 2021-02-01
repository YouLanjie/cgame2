#include "headfile/head.h"                           //导入头文件

int main() {
	int a;
	Clear
	while (a != 0x1B && 0x30 && 0x51 && 0x71) {
		welcome();
		a = input();
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
	printf("\n                          \033[1;32m欢迎\033[0m\n\n\n");
	printf("\033[34m--------------------------------------------------------\n");
	printf("\033[34m|                                                      |\n");
	printf("\033[34m|                                                      |\033[0m\n");
	printf("\033[34m|\033[1;33m         1.开始游戏                2.游戏记录         \033[0;34m|\033[0m\n");
	printf("\033[34m|\033[1;33m         3.游戏帮助                0.退出游戏         \033[0;34m|\033[0m\n");
	printf("\033[34m|\033[1;31m  请选择:\033[0m\033[45C\033[34m|\n");
	printf("\033[34m|                                                      |\n");
	printf("--------------------------------------------------------\033[0m\033[2A\033[45D");
	return;
}

void game() {
	struct Chess *p;

	p = (struct Chess*) malloc(sizeof(struct Chess));
	p -> board[10][10] = 1;

	printboard(p);
	kbhit();
	getchar();
	free(p);
	Clear
	return;
}

void help() {
	puts("\t\t\t       游戏帮助");
	puts("\t如果想要退出，0、q、Q、Esc都可以哦");
	puts("\tW S A D控制上下左右，空格下子");
	printf("按任意按键返回：");
	kbhit();
	getchar();
	return;
}

void printboard(struct Chess *p) {
	int count;
	int count2;

	printf("\033[1;33m-----------------------------------------------\n");
	for (count = 0; count < Max; count++) {    //打印棋盘
		printf("|\033[0m");
		for (count2= 0; count2 < Max; count2++) {
			if (p -> board[count][count2] == 0) {
				printf(" + ");
			}
			else if (p -> board[count][count2] == 1) {
				printf("⚫ ");
			}
			else if (p -> board[count][count2] == 2) {
				printf("⚪ ");
			}
		}
		printf("\033[1;33m|\n");
	}
	printf("-----------------------------------------------\033[0m\n");
}
