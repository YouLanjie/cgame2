#include "../include/head.h"                           //导入头文件
#include <stdio.h>

/* 定义结构体变量 */
struct Chess *p;

/* 文件位置 */
char Save[] = "/usr/local/cgame2/data/save.txt";
char Data[] = "/usr/local/cgame2/data/data.txt";
char Help[] = "/usr/local/cgame2/data/help.txt";
char Config[] = "/usr/local/cgame2/data/config.txt";
FILE * fp;

int main(int argc,char * argv[]) {
	int a;
	int m = 1;

	printf("\033[?25l");
	p = (struct Chess *)malloc(sizeof(struct Chess));
	Clear2
	while (a != 0x1B && a != 0x30 && a != 0x51 && a != 0x71) {
		init(p);
		welcome(m,2);
		a = input();
		printf("\n\n\n\n");
		Clear2
		switch (a) {
			case 0x30:
			case 0x51:
			case 0x71:
				free(p);
				printf("\033[?25h");
				return 0;
				break;
			case 0x1B:
				if (kbhit_if() == 1) {
					getchar();
					a = getchar();
					if (a == 0x41 || a == 0x44) {
						if (m > 1) {
							m--;
						}
						else {
							printf("\a");
						}
					}
					else if (a == 0x42 || a == 0x43) {
						if (m < 2) {
							m++;
						}
						else {
							printf("\a");
						}
					}
				}
				else {
					free(p);
					printf("\033[?25h");
					return 0;
					break;
				}
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
			case 0x34:
				Clear
				printf("\033[1;33m请确清除存档，您将失去您的所有记录！（Y/n）\n");
				a = input();
				if (strcmp(Save,"/usr/local/cgame2/data/save.txt") != 0) {
					printf("\n由于使用的是当前目录，所以会删除数据文件夹\n");
				}
				if (a == 0x59 || a == 0x79) {
					fp = fopen(Data,"w");
					if(!fp) {
						perror("\033[1;31m[main](remove Data): \033[0m");
						input();
					}
					else {
						fprintf(fp, "0");
						fclose(fp);
					}
					fp = fopen(Save, "w");
					if(!fp) {
						perror("\033[1;31m[main](remove Save): \033[0m");
						input();
					}
					else {
						fclose(fp);
					}
					fp = fopen(Config,"w");
					if(!fp) {
						perror("\033[1;31m[main](remove Config): \033[0m");
						input();
					}
					else {
						fprintf(fp, "0");
						fclose(fp);
					}
				}
				if (strcmp(Save,"/usr/local/cgame2/data/save.txt") != 0) {
					remove(Save);
					remove(Data);
					remove(Config);
					remove("cgame2-data");
					printf("是否直接退出游戏?否则将重新创建目录!(默认退出)Y/n\n");
					a = input();
					if (a != 0x4E && a != 0x6E) {
						free(p);
						printf("\033[?25h\n");
						Clear
						return 0;
					}
				}
				Clear
				break;
			case 0x35:
				settings();
				break;
			default:
				break;
		}
		Clear2
	}
	free(p);
	Clear2
	printf("\033[?25h");
	return 0;
}

void stop() {
	Clear2
	printf("退出程序中...\n");
	free(p);
}

