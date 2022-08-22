#include "../include/head.h"                           //导入头文件
#include <curses.h>

struct Chess *p;

/* 文件位置 */
char Save[20] = "/etc/cgame2/save.txt";
char Config[25] = "/etc/cgame2/config.txt";
char * GameDir = "/etc/cgame2/";
int config[] = {0, 0, 0};
int Max = 15;
FILE * fp;

int main() {
	int inputContent = 0; /* 输入的内容 */
	int config[] = {1, 0, 0};    //配置选项
	menuData data = menuDataInit(), help = menuDataInit();

	data.title = "游戏菜单";
	data.addText(&data, "1.开始游戏", "2.游戏记录", "3.游戏帮助", "4.清除存档", "5.设置", "0.退出游戏", NULL);
	data.addTextData(&data, 0, "%s%s%s%s%s", "%z开始玩五子棋%z!%z好耶%z!", "%z查看所有记录下来的棋盘结果记录%z", "%z查看和游戏有关的帮助内容%z", "%z这会移除所有的记录%z，%z请慎重%z", "%z设置游戏内部的一些变量%z");

	help.title = "游戏帮助";
	help.cfg   = 2;
	help.addText(&help, "1.%z按下%z0,q,Q,esc%z退出%z", "2.WSAD%z或者方向键控制方向，回车、空格下子%z", "3.@%z为黑棋%z,O%z为白棋%z,+%z为未下棋子%z", "4.%z可以参照界面的提示操作%z", "5.%z同时可以用方向键控制方向%z", "6.%z历史界面需要您的终端足够大以保持正常显示%z", "7.%z按照提示，键入%zY%z删除，否则键入%zN%z或者其他按键%z", "8.%z倘若您使用当前目录作为数据的存储目录，则会提示是否删除直接退出程序防止再次创建文件夹%z", "9.%z同其他界面，使用%zWASD%z或方向键移动光标%z", "10.%z使用空格或者回车开启或者关闭光标所在选项%z", "11.%z棋盘大小可以使用%z+(%z或%z=)/-%z增加或者减少%z", NULL);

	init_pair(6, COLOR_YELLOW, COLOR_BLUE);
	init_pair(7, COLOR_BLACK, COLOR_BLUE);
	init_pair(8, COLOR_WHITE, COLOR_BLUE);

	signal(SIGINT, stop);
	Clear2
	Max = 15;
	while (inputContent != 0x1B && inputContent != 0x30 && inputContent != 0x51 && inputContent != 0x71) {
		Init();
		if ((fp = fopen(Config, "r"))) {
			fscanf(fp,"%d%d%d%d", &config[0], &config[1], &config[2], &Max);
			fclose(fp);
		}
		inputContent = data.menuShow(&data);
		attron(COLOR_PAIR(1));
		for (int i = 0; i < LINES; i++) {
			for (int i2 = 0; i2 < COLS; i2++) {
				mvaddch(i, i2, ' ');
			}
		}
		attroff(COLOR_PAIR(1));
		switch (inputContent) {
			case '0':
			case '6':
				endwin();
				return 0;
				break;
			case '1':
				Game(p);
				break;
			case '2':
				History(p);
				break;
			case '3':
				help.menuShow(&help);
				break;
			case '4':
				attron(COLOR_PAIR(1));
				move(0, 0);
				printw("请确清除存档，您将失去您的所有记录！（y/N）");
				inputContent = getch();
				if (inputContent == 'y' || inputContent == 'Y') {
					remove(Save);
					remove(Config);
					if (access("./cgame2-data/", 0) != EOF && config[1] == 1) {
						remove("./cgame2-data");
						config[1] = 0;
						changeDir("/etc/cgame2/");
						if ((fp = fopen(Config, "w"))) {
							fprintf(fp,"%d %d %d", config[0], 0, Max);
							fclose(fp);
						}
						move(1, 0);
						printw("是否直接退出游戏?否则将重新创建数据目录!(默认退出)Y/n");
						inputContent = getch();
						if (inputContent != 0x4E && inputContent != 0x6E) {
							Clear
							endwin();
							return 0;
						}
					}
				}
				Clear
				attroff(COLOR_PAIR(1));
				break;
			case '5':
				Settings();
				break;
			default:
				break;
		}
		Clear2
	}
	Clear2
	endwin();
	return 0;
}

void stop() {
	endwin();
	printf("程序退出\n");
	if (fp) {
		fclose(fp);
	}
	exit(0);
}

