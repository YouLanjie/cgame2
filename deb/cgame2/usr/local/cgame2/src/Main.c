#include "../include/head.h"                           //导入头文件
#include <stdio.h>
#include <unistd.h>

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
	struct winsize size;
	int startSize = 0;

	signal(SIGINT, stop);
	printf("\033[?25l");
	p = (struct Chess *)malloc(sizeof(struct Chess));
	Clear2
	while (inputContent != 0x1B && inputContent != 0x30 && inputContent != 0x51 && inputContent != 0x71) {
		Init(p);
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		startSize = size.ws_col / 2 - 20;
		fp = fopen(Config,"r");
		fscanf(fp,"%d%d",&config[0],&config[1]);
		fclose(fp);
		if (currentPage == 1){
			if (config[1] == 0) {
				printf("\033[8;%dH\033[1;33m1.开始游戏\033[8;%dH2.游戏记录\033[9;%dH3.游戏帮助\033[9;%dH4.清除存档", startSize, startSize + 32, startSize, startSize + 32);
			}
			else {
				printf("\033[8;%dH\033[1;33m1.Start the game\033[8;%dH2.Game history\033[9;%dH3.Game help\033[9;%dH4.Clear the archive", startSize, startSize + 32, startSize, startSize + 32);
			}
		}
		else if (currentPage == 2) {
			if (config[1] == 0) {
				printf("\033[8;%dH\033[1;33m5.设置\033[8;%dH0.退出游戏\033[0m", startSize, startSize + 32);
			}
			else {
				printf("\033[8;%dH\033[1;33m5.Setting(设置)\033[8;%dH0.Quit the game\033[0m", startSize, startSize + 32);
			}
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
				ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
				startSize = size.ws_col / 2 - 20;
				if (config[1] == 0) {
					printf("\033[7;%dH按下0,q,Q退出\033[8;%dHW S A D或者方向键控制上下左右，空格下子\033[9;%dH@为黑棋,O为白棋,+为空白", startSize, startSize, startSize);
					Menu2("游戏帮助");
				}
				else {
					printf("\033[7;%dH Press 0,q,Q to exit \033[8;%dHW S A D or arrow keys to control up and down, space to play \033[9;%dH@ for black, O for white, + for blank", startSize, startSize, startSize);
					Menu2("Game Help");
				}
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
