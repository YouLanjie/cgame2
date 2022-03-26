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
	Clear2
	while (inputContent != 0x1B && inputContent != 0x30 && inputContent != 0x51 && inputContent != 0x71) {
		Init(p);
		if ((fp = fopen(Config, "r"))) {
			fscanf(fp,"%d%d%d", &config[0], &config[1], &Max);
			fclose(fp);
		}
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
#ifdef __linux
					printf("\033[?25h");
#endif
					return 0;
					break;
				}
				break;
			case 0x57:
			case 0x77:
				if (currentPage > 1) {
					currentPage--;
				}
				else {
					printf("\a");
				}
				break;
			case 0x53:
			case 0x73:
				if (currentPage < 2) {
					currentPage++;
				}
				else {
					printf("\a");
				}
				break;
			case 0x31:
				Game(p);
				break;
			case 0x32:
				History(p);
				break;
			case 0x33:
				for (int currentPage = 1; inputContent != 'q' && inputContent != 'Q' && inputContent != '0' && inputContent != 0x1B; ) {
#ifdef __linux
					ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
					startSize = size.ws_col / 2 - 20;
#else
					startSize = 56 / 2 -20;
#endif
					Clear
					if (currentPage == 1) {
						gotoxy(7, startSize); printf("1.按下0,q,Q,esc退出"); gotoxy(8, startSize); printf("2.WSAD或者方向键控制方向，回车、空格下子"); gotoxy(9, startSize); printf("3.@为黑棋,O为白棋,+为未下棋子");
						Menu("游戏帮助 - 游戏界面", currentPage, 4);
					}
					if (currentPage == 2) {
						gotoxy(7, startSize); printf("1.可以参照界面的提示操作"); gotoxy(8, startSize); printf("2.同时可以用方向键控制方向"); gotoxy(9, startSize); printf("3.历史界面需要您的终端足够大以保持正常显示");
						Menu("游戏帮助 - 历史记录", currentPage, 4);
					}
					if (currentPage == 3) {
						gotoxy(7, startSize); printf("1.按照提示，键入Y删除，否则键入N或者其他按键"); gotoxy(8, startSize); printf("2.倘若您使用当前目录作为数据的存储目录，则会提"); gotoxy(9, startSize); printf("  示是否删除直接退出程序防止再次创建文件夹");
						Menu("游戏帮助 - 清除存档", currentPage, 4);
					}
					if (currentPage == 4) {
						gotoxy(7, startSize); printf("1.同其他界面，使用WASD或方向键移动光标"); gotoxy(8, startSize); printf("2.使用空格或者回车开启或者关闭光标所在选项"); gotoxy(9, startSize); printf("3.棋盘大小可以使用+(或=)/-增加或者减少");
						Menu("游戏帮助 - 设置", currentPage, 4);
					}
					inputContent = getch();
					if (inputContent == 0x1B) {
						if (kbhit() == 1) {
							getchar();
							inputContent = getchar();
							if (inputContent == 0x41 || inputContent == 0x44) {
								if (currentPage > 1) currentPage--;
								else printf("\a");
							}
							else if (inputContent == 0x42 || inputContent == 0x43) {
								if (currentPage < 4) currentPage++;
								else printf("\a");
							}
						}
					}
					else if (inputContent == 0x57 || inputContent == 0x77) {
						if (currentPage > 1) currentPage--;
						else printf("\a");
					}
					else if (inputContent == 0x53 || inputContent == 0x73) {
						if (currentPage < 4) currentPage++;
						else printf("\a");
					}
				}
				inputContent = 3;
				break;
			case 0x34:
				Clear
				fontColorSet(1,33);
				printf("请确清除存档，您将失去您的所有记录！（Y/n）\n");
				inputContent = getch();
				if (inputContent == 'y' || inputContent == 'Y') {
					remove(Save);
					remove(Config);
					if (access("./cgame2-data/", 0) != EOF && config[1] == 1) {
						remove("./cgame2-data");
						config[1] = 0;
						changeDir("/usr/local/cgame2/");
						if ((fp = fopen(Config, "w"))) {
							fprintf(fp,"%d %d %d", config[0], 0, Max);
							fclose(fp);
						}
						printf("是否直接退出游戏?否则将重新创建数据目录!(默认退出)Y/n\n");
						inputContent = getch();
						if (inputContent != 0x4E && inputContent != 0x6E) {
#ifdef __linux
							printf("\033[?25h\n");
#endif
							Clear
							return 0;
						}
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

