#include "../include/head.h"

void help() {
	FILE *fp;
	int a = 0,count = 0;
	char b[1392];

	menu2("游戏帮助");
	printf("\033[7;4H按下0,q,Q退出");
	printf("\033[8;4HW S A D或者方向键控制上下左右，空格下子");
	printf("\033[9;4H@为黑棋,O为白棋,+为空白");
	a = input();
	if(a == 0x1B) {
		if (kbhit_if() == 1) {
			getchar();
			a = getchar();
		}
		if(a == 0x42) {
			Clear
			fp = fopen(Help,"r");
			if(!fp) {
				perror("\033[1;31m[help]: fopen\033[0m");
				input();
				return;
			}
			for (count = 0;count < 5; count++){
				fread(b,3417,1,fp);
				puts(b);
				printf("\033[17;1H\033[0;1;31mn下一步;N上一步,0退出\033[0m");
				a = input();
				switch (a) {
					case 0x1B:
					case 0x30:
					case 0x51:
					case 0x71:
						return;
						break;
					case 0x57:
					case 0x77:
						if (count == 0) {
							Clear
							fseek(fp,0L,0);
							count--;
						}
						else {
							fseek(fp,-6834L,1);
							count -= 2;
						}
						Clear
						break;
					case 0x53:
					case 0x73:
						if (count == 4) {
							Clear
							fseek(fp,-3417L,3);
							count--;
						}
						Clear
						break;
					default:
						fseek(fp,-3417L,1);
						count--;
						Clear
						break;
				}
			}
			fclose(fp);
		}
	}
	return;
}


