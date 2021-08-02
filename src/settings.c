#include "../include/head.h"
#include <stdio.h>

void settings() {
	FILE * fp;
	unsigned short x = 1,y = 1,iy = 1;
	int config[2];
	int a = 0;

	fp = fopen(Config, "r");
	fscanf(fp, "%d%d", &config[0], &config[1]);
	fclose(fp);
	printf("\033[?25h\033[2;25H\033[1;32m游戏设置\n\033[33mq键退出，退出保存\033[0m\n");
	printf("游戏时是否启用AI\033[4;24H( )\033[1;31m\033[4;27H|\033[0m使用英语\033[4;48H( )\n");
	printf("\033[%d;%dH",y + 3,x * 24 + 1);
	for (int i = 1; i <= 2; i++) {
		if (config[i - 1] == 1) {
			printf("\033[1;31m\033[%d;%dH*\033[0m",(i / 2) + 3,i * 24 + 1);
		}
	}
	while (a != 'q' && a != 'Q') {
		a = input();
		if (a == 'D' && x > 1) {
			x--;
		}
		else if (a == 'C' && x < 2) {
			x++;
		}
		else if (a == 0x0A || a == 0x20) {
			config[2 * (y - 1) + x - 1] = 1 - config[2 * (y - 1) + x - 1];
		}
		Clear
		printf("\033[?25h\033[2;25H\033[1;32m游戏设置\n\033[33mq键退出，退出保存\033[0m\n");
		printf("游戏时是否启用AI\033[4;24H( )\033[1;31m\033[4;27H|\033[0m使用英语\033[4;48H( )\n");
		if (config[0] == 1) {
			printf("\033[1;31m\033[4;25H*\033[0m");
		}
		if (config[1] == 1) {
			printf("\033[1;31m\033[4;25H*\033[0m");
		}
		for (int i = 1; i <= 2; i++) {
			iy = i / 2 + 3;
			if (i % 2 != 0) {
				iy = (i + 1) / 2 + 3;
			}
			
			if (config[i - 1] == 1) {
				printf("\033[1;31m\033[%d;%dH*\033[0m",iy,i * 24 + 1);
			}
			else {
				printf("\033[0m\033[%d;%dH ",iy,i * 24 + 1);
			}
			kbhit2();
		}
		printf("\033[%d;%dH",y + 3,x * 24 + 1);
		kbhit2();
	}
	fp = fopen(Config, "w");
	fprintf(fp,"%d %d",config[0],config[1]);
	fclose(fp);
	printf("\033[?25l");
	return;
}

