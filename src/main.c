#include "../include/head.h"                           //导入头文件
#include <signal.h>
#include <stdlib.h>

/* 定义结构体变量 */
struct Chess *p;

/* 文件位置 */
char Save[] = "/usr/local/cgame2/data/save.txt";
char Data[] = "/usr/local/cgame2/data/data.txt";
char Help[] = "/usr/local/cgame2/data/help.txt";
char Config[] = "/usr/local/cgame2/data/config.txt";
FILE * fp;

char LANG[LANGFILELINE][200];

int main() {
	int Input = 0;
	int m = 1;

	signal(SIGINT, stop);
	printf("\033[?25l");
	p = (struct Chess *)malloc(sizeof(struct Chess));
	Clear2
	while (Input != 0x1B && Input != 0x30 && Input != 0x51 && Input != 0x71) {
		init(p);
		welcome(m,2);
		Input = input();
		printf("\n\n\n\n");
		Clear2
		switch (Input) {
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
					Input = getchar();
					if (Input == 0x41 || Input == 0x44) {
						if (m > 1) {
							m--;
						}
						else {
							printf("\a");
						}
					}
					else if (Input == 0x42 || Input == 0x43) {
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
				printf("%s",LANG[28]);
				Input = input();
				if (strcmp(Save,"/usr/local/cgame2/data/save.txt") != 0) {
					printf("%s",LANG[29]);
				}
				if (Input == 0x59 || Input == 0x79) {
					fp = fopen(Data,"w");
					if(!fp) {
						perror(LANG[30]);
						input();
					}
					else {
						fprintf(fp, "0");
						fclose(fp);
					}
					fp = fopen(Save, "w");
					if(!fp) {
						perror(LANG[31]);
						input();
					}
					else {
						fclose(fp);
					}
					fp = fopen(Config,"w");
					if(!fp) {
						perror(LANG[32]);
						input();
					}
					else {
						fprintf(fp, "1 0");
						fclose(fp);
					}
				}
				if (strcmp(Save,"/usr/local/cgame2/data/save.txt") != 0) {
					remove(Save);
					remove(Data);
					remove(Config);
					remove("cgame2-data");
					printf("%s",LANG[33]);
					Input = input();
					if (Input != 0x4E && Input != 0x6E) {
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
	printf("程序退出\n");
	if (fp) {
		fclose(fp);
	}
	Clear2
	free(p);
	exit(0);
}
