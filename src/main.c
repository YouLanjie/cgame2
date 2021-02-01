#include "headfile/head.h"                           //导入头文件

int main() {
	int a;
	int count = 0, *p = &count;
	Clear
	while (a != 0x1B && 0x30 && 0x51 && 0x71) {
		init();
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
				game(p);
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

void init() {
	FILE *fp;
	int a = 0;
	if (access("./.save",0)) {
		fopen("./.save","w");
	}
	else {
		return;
	}
	fclose(fp);
	return;
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

void game(int *count) {
	struct Chess *p;

	p = (struct Chess*) malloc(sizeof(struct Chess));
	*count += 1;

	printf("第%d局：\n",*count);
	printboard(p);
	input();
	save(p,*count);
	free(p);
	Clear
	return;
}

void save(struct Chess *p,int Count) {
	int count;
	int count2;
	FILE *fp;

	fp = fopen(".save","a");
	if (!fp) {
		printf("无法保存\n按任意按键返回\n");
		input();
		return;
	}
	fprintf(fp,"第%d局：\n",Count);
	for (count = 0; count < Max; count++) {    //打印棋盘到文件
		for (count2= 0; count2 < Max; count2++) {
			if (p -> board[count][count2] == 0) {
				fprintf(fp," + ");
			}
			else if (p -> board[count][count2] == 1) {
				fprintf(fp,"⚫ ");
			}
			else if (p -> board[count][count2] == 2) {
				fprintf(fp,"⚪ ");
			}
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	return;
}

void history() {
	int count;
	char a[100];
	FILE *fp;

	fp = fopen("./.save","r");
	if (!fp) {
		printf("无法打开存档，请自行确认存档文件是否存在！\n按任意按键返回\n");
		input();
		return;
	}
	for (count = 0; count < Max; count++) {
		fgets(a,sizeof(a),fp);
		puts(a);
	}
	
	fclose(fp);
	return;
}

void help() {
	puts("\t\t\t       游戏帮助");
	puts("\t如果想要退出，0、q、Q、Esc都可以哦");
	puts("\tW S A D控制上下左右，空格下子");
	printf("按任意按键返回：");
	input();
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
	return;
}
