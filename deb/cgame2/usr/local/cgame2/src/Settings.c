#include "../include/head.h"

void Settings() {
	unsigned short where = 1, a = 0;  //对应的位置
	int inputContent = 0;    //输入
#ifdef __linux
	struct winsize size;
#endif
	int startSize = 0;
	FILE * fp;

	fp = fopen(Config, "r"); /* 读取文件 */
	fscanf(fp, "%d%d%d", &config[0], &config[1], &Max);
	fclose(fp);
#ifdef __linux
		printf("\033[?25h");
#endif
#ifdef __linux
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		startSize = size.ws_col / 2 - 20;
#else
		startSize = 56 / 2 -20
#endif
	/* 打印菜单 */
	while (inputContent != 'q' && inputContent != 'Q' && inputContent != 'w' && inputContent != 'W' && inputContent != 0x1B) {
		Clear2
		/* 显示菜单 */
		Menu("游戏设置", 1, 1);
		fontColorSet(1,33); gotoxy(3,startSize); printf("q键退出，退出保存\n");
		fontColorSet(0,0); gotoxy(8, startSize); printf("自动下棋 ( )"); gotoxy(8,startSize + 32); printf("当前目录 ( )"); gotoxy(9, startSize); printf("棋盘大小：%d", Max);
		kbhitGetchar();
		/* 显示状态 */
		for (int i = 1; i <= 2; i++) {
			if (i % 2) {
				i++;
				a = 1;
			}
			else {
				a = 0;
			}
			if (config[i - 1 - a] == 1) {
				gotoxy(i / 2 + 7, startSize + 10 + (i + 1 - a) % 2 * 32); fontColorSet(1,31);
				printf("*");
				fontColorSet(1,31);
			}
			else {
				gotoxy(i / 2 + 7, startSize + 10 + (i + 1 - a) % 2 * 32); fontColorSet(0,0);
				printf(" ");
			}
			i -= a;
			kbhitGetchar();
		}
		if (where % 2) {
			gotoxy((where + 1) / 2 + 7, startSize + 10 + (where + 1) % 2 * 32);
		}
		else {
			gotoxy(where / 2 + 7, startSize + 10 + (where + 1) % 2 * 32);
		}
		kbhitGetchar();
		inputContent = getch();
		/* 更改状态 */
		if (inputContent == 0x1B) {
			if (kbhit() == 1) {
				kbhitGetchar();
				inputContent = getchar();
			}
		}
		if (inputContent == 'D' && where > 1) {
			where--;
		}
		else if (inputContent == 'C' && where < 3) {
			where++;
		}
		else if (inputContent == 'A' && where > 2) {
			where -= 2;
		}
		else if (inputContent == 'B' && where < 3) {
			where += 2;
			if (where == 4) {
				where = 3;
			}
		}
		else if (inputContent == 0x0D || inputContent == 0x20) {
			config[where - 1] = 1 - config[where - 1];
		}
		else if (inputContent == '+' && where == 3) {
			Max++;
		}
		else if (inputContent == '-' && where == 3) {
			Max--;
		}
	}
	fp = fopen(Config, "w");
	fprintf(fp,"%d %d %d", config[0], config[1], Max);
	Max = config[2];
	fclose(fp);
#ifdef __linux
	printf("\033[?25l");
#endif
	return;
}
