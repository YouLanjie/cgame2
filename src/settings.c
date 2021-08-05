#include "../include/head.h"

void settings() {
	FILE * fp;
	unsigned short x = 1,y = 1,iy = 1;
	int config[2];
	int a = 0;

	fp = fopen(Config, "r");
	fscanf(fp, "%d%d", &config[0], &config[1]);
	fclose(fp);
	printf("%s",LANG[34]);
	printf("%s",LANG[35]);
	kbhit2();
	for (int i = 1; i <= 2; i++) {
		iy = i / 2 + 3;
		if (i % 2 != 0) {
			iy = (i + 1) / 2 + 3;
		}
		if (config[i - 1] == 1) {
			printf("\033[1;31m\033[%d;%dH*\033[0m",iy,i * 24 + 1);
		}
	}
	printf("\033[%d;%dH",y + 3,x * 24 + 1);
	kbhit2();
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
		printf("%s",LANG[34]);
		printf("%s",LANG[35]);
		kbhit2();
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

