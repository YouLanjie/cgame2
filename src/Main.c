#include "../include/head.h"                           //导入头文件

/* 定义结构体变量指针 */
struct Chess *p;

/* 文件位置 */
char Save[] = "/usr/local/cgame2/data/save.txt";
char Data[] = "/usr/local/cgame2/data/data.txt";
char Help[] = "/usr/local/cgame2/data/help.txt";
char Config[] = "/usr/local/cgame2/data/config.txt";
int Max = 15;
FILE * fp;

char LANG[LANGFILELINE][200];

int main() {
	int inputContent = 0; /* 输入的内容 */
	int currentPage = 1; /* 但前所处主菜单页面 */
	int Max = 15;

	signal(SIGINT, stop);
	printf("\033[?25l");
	p = (struct Chess *)malloc(sizeof(struct Chess));
	Clear2
	while (inputContent != 0x1B && inputContent != 0x30 && inputContent != 0x51 && inputContent != 0x71) {
		Init(p);
		if (currentPage == 1){
			printf("%s",LANG[10]);
		}
		else if (currentPage == 2) {
			printf("%s",LANG[11]);
		}
		KbhitNoTime();
		Menu(LANG[12],currentPage,2);
		KbhitNoTime();

		inputContent = Input();
		printf("\n\n\n\n");
		Clear2
		switch (inputContent) {
			case 0x30:
			case 0x51:
			case 0x71:
				free(p);
				printf("\033[?25h");
				return 0;
				break;
			case 0x1B:
				if (KbhitHas() == 1) {
					getchar();
					inputContent = getchar();
					if (inputContent == 0x41 || inputContent == 0x44) {
						if (currentPage > 1) {
							currentPage--;
						}
						else {
							printf("\a");
						}
					}
					else if (inputContent == 0x42 || inputContent == 0x43) {
						if (currentPage < 2) {
							currentPage++;
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
				Game(p);
				break;
			case 0x32:
				History(p);
				break;
			case 0x33:
				printf("%s",LANG[26]);
				Menu2(LANG[27]);
				Input();
				break;
			case 0x34:
				Clear
				printf("%s",LANG[28]);
				inputContent = Input();
				if (strcmp(Save,"/usr/local/cgame2/data/save.txt") != 0) {
					printf("%s",LANG[29]);
				}
				if (inputContent == 0x59 || inputContent == 0x79) {
					fp = fopen(Data,"w");
					if(!fp) {
						perror(LANG[30]);
						Input();
					}
					else {
						fprintf(fp, "0");
						fclose(fp);
					}
					fp = fopen(Save, "w");
					if(!fp) {
						perror(LANG[31]);
						Input();
					}
					else {
						fclose(fp);
					}
					fp = fopen(Config,"w");
					if(!fp) {
						perror(LANG[32]);
						Input();
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
					inputContent = Input();
					if (inputContent != 0x4E && inputContent != 0x6E) {
						free(p);
						printf("\033[?25h\n");
						Clear
						return 0;
					}
				}
				Clear
				break;
			case 0x35:
				Settings();
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
