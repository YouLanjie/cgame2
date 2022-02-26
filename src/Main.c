#include "../include/head.h"                           //导入头文件

struct Chess *p;

/* 文件位置 */
char Save[] = "/usr/local/cgame2/save.txt";
char Config[] = "/usr/local/cgame2/config.txt";
char * GameDir = "/usr/local/cgame2/";
int config[] = {0, 0};
int Max = 15;
FILE * fp;

int main() {
	int inputContent = 0; /* 输入的内容 */
	int currentPage = 1; /* 但前所处主菜单页面 */
	int config[2] = {1, 0};    //配置选项
#ifdef __linux
	struct winsize size;
#endif
	int startSize = 0;

	signal(SIGINT, stop);
#ifdef __linux
	printf("\033[?25l");
#endif
	p = (struct Chess *)malloc(sizeof(struct Chess));
	Clear2
	while (inputContent != 0x1B && inputContent != 0x30 && inputContent != 0x51 && inputContent != 0x71) {
		Init(p);
#ifdef __linux
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		startSize = size.ws_col / 2 - 20;
#else
		startSize = 56 / 2 -20;
#endif
		fontColorSet(1,33);
		if (currentPage == 1){
			gotoxy(8, startSize); printf("1.开始游戏"); gotoxy(8, startSize + 32); printf("2.游戏记录"); gotoxy(9, startSize); printf("3.游戏帮助"); gotoxy(9, startSize + 32); printf("4.清除存档");
		}
		else if (currentPage == 2) {
			gotoxy(8, startSize); printf("5.设置"); gotoxy(8, startSize + 32); printf("0.退出游戏");
		}
		fontColorSet(0,0);
		kbhitGetchar();
		Menu("游戏菜单",currentPage,2);
		kbhitGetchar();

		inputContent = getch();
		printf("\n");
		Clear2
		switch (inputContent) {
			case 0x30:
			case 0x51:
			case 0x71:
				free(p);
#ifdef __linux
				printf("\033[?25h");
#endif
				return 0;
				break;
			case 0x1B:
				if (kbhit() == 1) {
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
#ifdef __linux
				printf("\033[?25h");
#endif
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
#ifdef __linux
				ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
				startSize = size.ws_col / 2 - 20;
#else
				startSize = 56 / 2 -20;
#endif
				gotoxy(7, startSize); printf("按下0,q,Q退出"); gotoxy(8, startSize); printf("W S A D或者方向键控制上下左右，空格下子"); gotoxy(9, startSize); printf("@为黑棋,O为白棋,+为空白");
				Menu2("游戏帮助");
				getch();
				break;
			case 0x34:
				Clear
				fontColorSet(1,33);
				printf("请确清除存档，您将失去您的所有记录！（Y/n）\n");
				inputContent = getch();
				remove(Save);
				remove(Config);
				if (access("./cgame2-data/", 0) != EOF && config[1] == 1) {
					remove("./cgame2-data");
					printf("是否直接退出游戏?否则将重新创建目录!(默认退出)Y/n\n");
					inputContent = getch();
					if (inputContent != 0x4E && inputContent != 0x6E) {
						free(p);
#ifdef __linux
						printf("\033[?25h\n");
#endif
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
#ifdef __linux
	printf("\033[?25h");
#endif
	return 0;
}

void stop() {
#ifdef __linux
	printf("\033[?25h");
#endif
	Clear2
	printf("程序退出\n");
	if (fp) {
		fclose(fp);
	}
	Clear2
	exit(0);
}
