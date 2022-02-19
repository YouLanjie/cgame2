#include "../include/head.h"

void Settings() {
	unsigned short x = 1,y = 1,iy = 1,ix = 1;  //x轴坐标 y轴坐标 计算y轴位置的坐标
	int config[4] = {0, 0, 0};    //存储选项
	int inputContent = 0;    //输入

	fp = fopen(Config, "r");
	fscanf(fp, "%d%d%d%d", &config[0], &config[1], &config[2], &config[3]);
	fclose(fp);
	printf("%s",LANG[3]);
	printf("%s",LANG[6]);
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
			printf("\033[1;31m\033[%d;%dH*\033[0m",iy,ix);
		}
	}
	printf("\033[%d;%dH",y + 3,x * 25 + 1);
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
		printf("%s",LANG[3]);
		printf("%s",LANG[6]);
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
				printf("\033[1;31m\033[%d;%dH*\033[0m",iy,ix);
			}
			else {
				printf("\033[0m\033[%d;%dH ",iy,ix);
			}
			kbhitGetchar();
		}
		printf("\033[%d;%dH",y + 3,x * 25 + 1);
		kbhitGetchar();
	}
	fp = fopen(Config, "w");
	fprintf(fp,"%d %d %d %d", config[0], config[1], config[2], config[3]);
	fclose(fp);
	printf("\033[?25l");
	return;
}

