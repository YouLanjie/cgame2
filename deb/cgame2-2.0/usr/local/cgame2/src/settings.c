#include "../include/head.h"

void settings() {
	unsigned short x = 1,y = 1,iy = 1,ix = 1;  //x轴坐标 y轴坐标 计算y轴位置的坐标
	int config[3] = {0, 0, 0};    //存储选项
	int Input = 0;    //输入

	fp = fopen(Config, "r");
	fscanf(fp, "%d%d%d", &config[0], &config[1], &config[2]);
	fclose(fp);
	printf("%s",LANG[34]);
	printf("%s",LANG[35]);
	kbhit2();
	for (int i = 1; i <= 3; i++) {  //i为循环中的临时变量
		iy = i / 2 + 3;
		if (i % 2 != 0) {
			iy = (i + 1) / 2 + 3;
			ix = 25;
		}
		else {
			ix = 49;
		}
		if (config[i - 1] == 1) {
			printf("\033[1;31m\033[%d;%dH*\033[0m",iy,ix);
		}
	}
	printf("\033[%d;%dH",y + 3,x * 24 + 1);
	kbhit2();
	while (Input != 'q' && Input != 'Q' && Input != 'w' && Input != 'W' && Input != 0x1B) {
		Input = input();
		if (Input == 0x1B) {
			if (kbhit_if() == 1) {
				kbhit2();
				Input = getchar();
			}
		}
		if (Input == 'D' && x > 1) {
			x--;
		}
		else if (Input == 'C' && x < 2) {
			x++;
		}
		else if (Input == 'A' && y > 1) {
			y--;
		}
		else if (Input == 'B' && y < 2) {
			y++;
		}
		else if (Input == 0x0A || Input == 0x20) {
			config[2 * (y - 1) + x - 1] = 1 - config[2 * (y - 1) + x - 1];
		}
		if (x == 2 && y ==2) {
			x = 1;
		}
		Clear
		printf("%s",LANG[34]);
		printf("%s",LANG[35]);
		kbhit2();
		if (config[0] == 1) {
			printf("\033[1;31m\033[4;25H*\033[0m");
		}
		if (config[1] == 1) {
			printf("\033[1;31m\033[4;25H*\033[0m");
		}
		for (int i = 1; i <= 3; i++) {
			iy = i / 2 + 3;
			if (i % 2 != 0) {
				iy = (i + 1) / 2 + 3;
				ix = 25;
			}
			else {
				ix = 49;
			}
			if (config[i - 1] == 1) {
				printf("\033[1;31m\033[%d;%dH*\033[0m",iy,ix);
			}
			else {
				printf("\033[0m\033[%d;%dH ",iy,ix);
			}
			kbhit2();
		}
		printf("\033[%d;%dH",y + 3,x * 24 + 1);
		kbhit2();
	}
	fp = fopen(Config, "w");
	fprintf(fp,"%d %d %d",config[0],config[1],config[2]);
	fclose(fp);
	printf("\033[?25l");
	return;
}

