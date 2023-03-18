#include "../include/head.h"                           //导入头文件

Games *GameInfo;

/* 文件指针 */
static FILE * fp;

int main() {
	int inputContent = 0; /* 输入的内容 */
	ctools_menu_t * data,
		      * help;

	ctools_menu_Init();

	init_pair(1, COLOR_WHITE, COLOR_BLUE);      /* 蓝底白字 */
	init_pair(2, COLOR_BLUE, COLOR_WHITE);      /* 白底蓝字 */
	init_pair(3, COLOR_WHITE, COLOR_YELLOW);    /* 黄底白字 */
	init_pair(4, COLOR_BLACK, COLOR_WHITE);     /* 白底黑字 */
	init_pair(5, COLOR_WHITE, COLOR_BLACK);     /* 黑底白字 */

	ctools_menu_t_init(&data);
	ctools_menu_t_init(&help);

	data -> title = "游戏菜单";
	ctools_menu_AddText(data, "1.开始游戏", "2.游戏记录", "3.游戏帮助", "4.清除存档", "5.设置", "0.退出游戏", NULL);
	ctools_menu_AddTextData(data, 0, "%s%s%s%s%s", "开始玩五子棋!好耶!", "查看所有记录下来的棋盘结果记录", "查看和游戏有关的帮助内容", "这会移除所有的记录，请慎重", "设置游戏内部的一些变量");

	help -> title = "游戏帮助";
	help -> cfg   = 2;
	ctools_menu_AddText(help, "1.按下0,q,Q,esc退出", "2.WSAD或者方向键控制方向，回车、空格下子", "3.@为黑棋,O为白棋,+为未下棋子", "4.可以参照界面的提示操作", "5.同时可以用方向键控制方向", "6.历史界面需要您的终端足够大以保持正常显示。按下r键可以进入单局回放，操作逻辑基本相同", "7.按照提示，键入Y删除，否则键入N或者其他按键", "8.倘若您使用当前目录作为数据的存储目录，则会提示是否删除直接退出程序防止再次创建文件夹", "9.同其他界面，使用WASD或方向键移动光标", "10.使用空格或者回车开启或者关闭光标所在选项", "11.棋盘大小可以使用+(或=)/-增加或者减少", "12.在绘图模式下，按下esc键保存退出，按下n键切换到下以张图", NULL);

	init_pair(6, COLOR_YELLOW, COLOR_BLUE);
	init_pair(7, COLOR_BLACK, COLOR_BLUE);
	init_pair(8, COLOR_WHITE, COLOR_BLUE);

	GameInfo = NULL;
	Init();

	signal(SIGINT, stop);
	Clear;
	while (inputContent != 0x1B && inputContent != 0x30 && inputContent != 0x51 && inputContent != 0x71) {
		readConfig();
		if ((fp = fopen(GameInfo->config.Config, "r"))) {
			ConfigRead;
			fclose(fp);
		}
		inputContent = ctools_menu_Show(data);
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
				free(data);
				free(help);
				return 0;
				break;
			case '1':
				Game();
				break;
			case '2':
				History();
				break;
			case '3':
				ctools_menu_Show(help);
				break;
			case '4':
				attron(COLOR_PAIR(1));
				move(0, 0);
				printw("请确清除存档，您将失去您的所有记录！（y/N）");
				inputContent = getch();
				if (inputContent == 'y' || inputContent == 'Y') {
					remove(GameInfo->config.Save);
					remove(GameInfo->config.Config);
					if (access("./cgame2-data/", 0) != EOF && GameInfo->config.chdir == 1) {
						remove("./cgame2-data");
						GameInfo->config.chdir = 0;
						changeDir("/etc/cgame2/");
						if ((fp = fopen(GameInfo->config.Config, "w"))) {
							ConfigWrite;
							fclose(fp);
						}
						move(1, 0);
						printw("是否直接退出游戏?否则将重新创建数据目录!(默认退出)Y/n");
						inputContent = getch();
						if (inputContent != 0x4E && inputContent != 0x6E) {
							Clear;
							endwin();
							return 0;
						}
					}
				}
				Clear;
				attroff(COLOR_PAIR(1));
				break;
			case '5':
				Settings();
				break;
			default:
				break;
		}
		Clear;
	}
	Clear;
	endwin();
	free(data);
	free(help);
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

