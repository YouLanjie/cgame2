#include "../include/head.h"                           //导入头文件

/* 定义结构体变量指针 */
struct Chess *p;

/* 文件位置 */
char Save[] = "/usr/local/cgame2/data/save.txt";
char Config[] = "/usr/local/cgame2/data/config.txt";
int Max = 15;
FILE * fp;

char LANG[LANGFILELINE][200];

int main() {
	int inputContent = 0; /* 输入的内容 */
	int currentPage = 1; /* 但前所处主菜单页面 */
	int config[3] = {1, 0, 0};    //配置选项

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
				printf("%s",LANG[29]);
				Menu2(LANG[7]);
				Input();
				break;
			case 0x34:
				Clear
				printf("%s",LANG[5]);
				inputContent = Input();
				if (strcmp(Save,"/usr/local/cgame2/data/save.txt") != 0) {
					printf("%s",LANG[4]);
				}
				if (inputContent == 0x59 || inputContent == 0x79) {
					fp = fopen(Save, "w");
					if(!fp) {
						perror(LANG[1]);
						Input();
					}
					else {
						fclose(fp);
					}
					fp = fopen(Config,"w");
					if(!fp) {
						perror(LANG[0]);
						Input();
					}
					else {
						fprintf(fp, "1 0 0 15");
						fclose(fp);
					}
				}
				if ((inputContent == 0x59 || inputContent == 0x79) && strcmp(Save,"/usr/local/cgame2/data/save.txt") != 0) {
					remove(Save);
					remove(Config);
					remove("cgame2-data");
					printf("%s",LANG[2]);
					inputContent = Input();
					if (inputContent != 0x4E && inputContent != 0x6E) {
						free(p);
						printf("\033[?25h\n");
						Clear
						return 0;
					}
					strcpy(Save, "/usr/local/cgame2/data/save.txt");
					strcpy(Config, "/usr/local/cgame2/data/config.txt");
					if (access(Config,0) == EOF) {
						fp = fopen(Config,"w");
						config[0] = 1;
						config[1] = 0;
						config[2] = 0;
						Max = 15;
						if (!fp) {
							perror("\033[1;31m[init](Config): fopen\033[0m");
							Input();
							exit(1);
						}
						fprintf(fp, "%d %d %d %d", config[0], config[1], config[2], Max);
						fclose(fp);
					}
					else {
						fp = fopen(Config,"w");
						config[2] = 0;
						fprintf(fp, "%d %d %d %d", config[0], config[1], config[2], Max);
						fclose(fp);
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
