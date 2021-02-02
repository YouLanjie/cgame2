#include "headfile/head.h"                           //导入头文件

int main() {
	int a;
	struct Chess *p;
	
	p = (struct Chess *)malloc(sizeof(struct Chess));
	Clear
	while (a != 0x1B && 0x30 && 0x51 && 0x71) {
		init(p);
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
				history(p);
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

void init(struct Chess *p) {
	FILE *fp;
	int a = 0;

	if (access("./.save",0) == EOF) {
		fp = fopen("./.save","w");
		p -> count = 0;
		return;
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

void game(struct Chess *p) {
	p -> count += 1;

	printf("第%d局：\n",p -> count);
	printboard(p);
	input();
	save(p);
	Clear
	return;
}

void save(struct Chess *p) {
	int count;
	int count2;
	FILE *fp;

	fp = fopen(".save","a");
	if (!fp) {
		printf("无法保存\n按任意按键返回\n");
		input();
		return;
	}
	fprintf(fp,"第%d局：\n",p -> count);
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

void history(struct Chess *p) {
	int count;
	int b;
	char a[p -> count * (Max + 1)][100];
	FILE *fp;

	if(p -> count == 0) {
		printf("\033[1;33m你还没有游戏记录，赶紧去玩一下吧！\033[0m\n输入任意按键返回\n");
		input();
		return;
	}
	fp = fopen("./.save","r");
	if (!fp) {
		printf("无法打开存档，请自行确认存档文件是否存在！\n按任意按键返回\n");
		input();
		return;
	}
	for (count = 0; count < p -> count * (Max + 1); count++) {
		fgets(a[count],sizeof(a),fp);
		if ((count + 1) % (Max + 1) == 0) {
			printf("按下W查看上一局，按下S查看下一局，输入数字查看对应局数\n");
			b = input();
			switch (b) {
				case 0x57:
				case 0x77:
					if (count + 1 - Max + 1 == 0) {
						Clear
						printf("这已经是第一局了\n");
						count -= Max + 2;
					}
					else {
						count -= 2 * (Max + 1);
					}
					break;
				case 0x53:
				case 0x73:
					if (count + 1 == p -> count) {
						Clear
						printf("这已经是最后一局了\n");
						count -= Max + 1;
					}
					break;
				default:
					count -= Max + 1;
					break;
			}
		}
		
		puts(a[count]);
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
