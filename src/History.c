#include "../include/head.h"
#include <curses.h>

void History() {
	int count;              //数数
	int chose = 0;              //选择
	int max = 0;
	char *cp;
	int line = 0;           //文件的大小
	FILE * fp;
	int i;    /* 循环变量 */

	clear();
	move(0, 0);
	for (int i = 0; i < LINES; i++) {
		for (int i2 = 0; i2 < COLS; i2++) {
			mvaddch(i, i2, ' ');
		}
	}
	fp = fopen(Save,"rb");
	if (!fp) {
		move(0, 0);
		printw("无法打开存档，请自行确认存档文件是否存在！\n按任意按键返回\n");
		getch();
		return;
	}
	fseek(fp, 0L, 2);
	line = ftell(fp);
	fseek(fp, 0L, 0);
	cp = (char *)malloc(300);
	for (int i = 0; 1; ) {
		if(fgetc(fp) == '\n') {
			i++;
		}
		if (ftell(fp) == line) {
			line = i;
			break;
		}
	}
	free(cp);
	fseek(fp, 0L, 0);
	if(line == 0) {
		attron(COLOR_PAIR(1));
		move(0, 0);
		printw("你还没有游戏记录，赶紧去玩一下吧！");
		move(1, 0);
		printw("输入任意按键返回");
		attroff(COLOR_PAIR(1));
		getch();
		return;
	}
	fseek(fp, 0L, 0);
	p = (struct Chess *)malloc(sizeof(struct Chess));
	max = Max;
	for (count = 0; count + 1 <= line; count++) {
		fseek(fp, 0L, 0);
		for (int i = 0; i <= count; i++) {
			fscanf(fp, "%d%d%d%d%d%d%d", &p -> t.year, &p -> t.mon, &p -> t.day, &p -> t.hour, &p -> t.min, &p -> t.sec, &Max);
			for (int i = 0; i < Max; i++) {
				fscanf(fp, "%s", p -> board[i]);
				p -> board[i + 1][0] = '\0';
			}
		}
		move(0, 0);
		attron(COLOR_PAIR(1));
		for (int i = 0; i < LINES; i++) {
			for (int i2 = 0; i2 < COLS; i2++) {
				mvaddch(i, i2, ' ');
			}
		}
		move(0, 0);
		printw(Time);
		attroff(COLOR_PAIR(1));
		for (i = 0; p -> board[i][0] != '\0' && p -> board[i][0] != EOF; i++) {
			move(i + 1, 0);
			for (int i2 = 0; p -> board[i][i2] != '\0' && p -> board[i][i2] != EOF; i2++) {
				if (p -> board[i][i2] == '0') {
					attron(COLOR_PAIR(1));
					printw("::");
					attron(COLOR_PAIR(1));
				}
				else if (p -> board[i][i2] == '1') {
					attron(COLOR_PAIR(7));
					printw("@@");
					attron(COLOR_PAIR(7));
				}
				else if (p -> board[i][i2] == '2') {
					attron(COLOR_PAIR(8));
					printw("OO");
					attron(COLOR_PAIR(8));
				}
				attron(COLOR_PAIR(1));
				printw(" ");
				attroff(COLOR_PAIR(1));
			}
		}
		move(i + 1, 0);
		attron(COLOR_PAIR(1));
		printw("(%02d/%02d)", count + 1, line);
		mvaddstr(i + 2, 0, "按下wahk查看上一局，按下sdjl查看下一局,0q退出");
		attroff(COLOR_PAIR(1));
		chose = getch();
		if (chose == 0x1B) {
			if (kbhit() == 1) {
				getchar();
				chose = getchar();
				if (chose == 0x41 || chose == 0x44) {
					chose = 'w';
				}
				else if (chose == 0x42 || chose == 0x43) {
					chose = 's';
				}
			}
			else {
				free(p);
				return;
			}
		}
		switch (chose) {
			case 0x30:
			case 0x51:
			case 0x71:
				free(p);
				return;
				break;
			case 'w':    /* 下一个 */
			case 'a':
			case 'h':
			case 'k':
				if (count == 0) {
					count = -1;
				}
				else {
					count -= 2;
				}
				break;
			case 's':    /* 上一个 */
			case 'd':
			case 'l':
			case 'j':
				if (count + 1 >= line) {
					count--;
				}
				break;
			case 'r':
			case 'R':
				Clear2
				count = -1;
				break;
			default:
				count--;
				break;
		}
		move(1, 0);
	}
	fclose(fp);
	Max = max;
	free(p);
	return;
}
