#include "../include/head.h"
#include <stdio.h>

void Settings() {
	unsigned short x = 1,y = 1,iy = 1,ix = 1;  //x轴坐标 y轴坐标 计算y轴位置的坐标
	int config[3] = {0, 0, 0};    //存储选项
	int inputContent = 0;    //输入

	fp = fopen(Config, "r");
	fscanf(fp, "%d%d%d", &config[0], &config[1], &config[2]);
	fclose(fp);
	gotoxy(2,25); fontColorSet(1,32); printf("游戏设置\n"); fontColorSet(1,33); printf("q键退出，退出保存\n");
	printf("游戏时是否启用AI"); gotoxy(4,25); printf("( )"); fontColorSet(1,31); gotoxy(4,29); printf("|"); fontColorSet(0,0); printf("使用当前目录作为游戏目录"); gotoxy(4,50); printf("( )\n"); gotoxy(5,25) ;printf("( )");
	kbhitGetchar();
	for (int i = 1; i <= 3; i++) {  //i为循环中的临时变量
		iy = i / 2 + 3;
		if (i % 2 != 0) {
			iy = (i + 1) / 2 + 3;
			ix = 26;
		}
		else {
			ix = 51;
		}
		if (config[i - 1] == 1) {
			gotoxy(iy, ix); fontColorSet(1,31);
			printf("*");
			fontColorSet(1,31);
		}
	}
	gotoxy(y + 3,x * 25 + 1);
	kbhitGetchar();
	while (inputContent != 'q' && inputContent != 'Q' && inputContent != 'w' && inputContent != 'W' && inputContent != 0x1B) {
		inputContent = getch();
		if (inputContent == 0x1B) {
			if (kbhit() == 1) {
				kbhitGetchar();
				inputContent = getchar();
			}
		}
		if (inputContent == 'D' && x > 1) {
			x--;
		}
		else if (inputContent == 'C' && x < 2) {
			x++;
		}
		else if (inputContent == 'A' && y > 1) {
			y--;
		}
		else if (inputContent == 'B' && y < 2) {
			y++;
		}
		else if (inputContent == 0x0A || inputContent == 0x20) {
			config[2 * (y - 1) + x - 1] = 1 - config[2 * (y - 1) + x - 1];
		}
		if (x == 2 && y ==2) {
			x = 1;
		}
		Clear
#ifdef __linux
		printf("\033[?25h");
#endif
		gotoxy(2,25); fontColorSet(1,32); printf("游戏设置\n"); fontColorSet(1,33); printf("q键退出，退出保存\n");
		printf("游戏时是否启用AI"); gotoxy(4,25); printf("( )"); fontColorSet(1,31); gotoxy(4,29); printf("|"); fontColorSet(0,0); printf("使用当前目录作为游戏目录"); gotoxy(4,50); printf("( )\n"); gotoxy(5,25) ;printf("( )");
		kbhitGetchar();
		for (int i = 1; i <= 3; i++) {
			iy = i / 2 + 3;
			if (i % 2 != 0) {
				iy = (i + 1) / 2 + 3;
				ix = 26;
			}
			else {
				ix = 51;
			}
			if (config[i - 1] == 1) {
				gotoxy(iy, ix); fontColorSet(1,31);
				printf("*");
				fontColorSet(1,31);
			}
			else {
				gotoxy(iy, ix); fontColorSet(0,0);
				printf(" ");
			}
			kbhitGetchar();
		}
		gotoxy(y + 3,x * 25 + 1);
		kbhitGetchar();
	}
	fp = fopen(Config, "w");
	fprintf(fp,"%d %d %d", config[0], config[1], config[2]);
	fclose(fp);
#ifdef __linux
	printf("\033[?25l");
#endif
	return;
}
