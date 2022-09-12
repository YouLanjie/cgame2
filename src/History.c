#include "../include/head.h"
#include <curses.h>

void History() {
	int count = 0;    //数数
	int chose = 0;    //选择
	int max = 0;      /* 备份Max值 */
	int line = 0;     //文件的行数
	int board[52][52];
	char *cp;
	FILE * fp;

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
	for (int i = 0; i < Max; i++) {
		for (int i2 = 0; i2 < Max; i2++) {
			p->board[i][i2] = 0;
			p->board2[i][i2] = 0;
		}
	}
	p->count = 0;
	p->x = 1;
	p->y = 1;
	max = Max;
	if (config[7]) {
		count = line - 1;    /* 设置自动跳转到最后一行 */
	}
	for (; count + 1 <= line; count++) {
		fseek(fp, 0L, 0);
		for (int i = 0; i < Max; i++) {
			for (int i2 = 0; i2 < Max; i2++) {
				p->board[i][i2] = 0;
				p->board2[i][i2] = 0;
				board[i][i2] = 0;
			}
		}
		for (int i = 0; i <= count; i++) {
			fscanf(fp, "%d%d%d%d%d%d%d", &p -> t.year, &p -> t.mon, &p -> t.day, &p -> t.hour, &p -> t.min, &p -> t.sec, &Max);
			for (int i = 0; i < Max; i++) {
				fscanf(fp, "%s", p -> board[i]);
				for (int i2 = 0; i2 < Max; i2++) {
					if (p->board[i][i2] == '0') {
						p->board[i][i2] = board[i][i2] = 0;
					}else if (p->board[i][i2] == '1') {
						p->board[i][i2] = board[i][i2] = 1;
					}else if (p->board[i][i2] == '2') {
						p->board[i][i2] = board[i][i2] = 2;
					}
				}
			}
			if (fgetc(fp) == ' ' && fgetc(fp) != '\n') {
				fseek(fp, -1L, 1);
				for (int i = 0; i < Max; i++) {
					for (int i2 = 0; i2 < Max; i2++) {
						fscanf(fp, "%d", &(p -> board2[i][i2]));
					}
				}
			}
		}

		PrintBoard();

		attron(COLOR_PAIR(1));
		move(1, 2);
		printw(Time);
		attroff(COLOR_PAIR(1));

		move(Max + 4, 2);
		attron(COLOR_PAIR(1));
		printw("(%03d/%03d)", count + 1, line);
		mvaddstr(Max + 4, 23, "wahk上一局，sdjl下一局");
		mvaddstr(Max + 5, 5, "0q退出，g第一局，G查看最后一局");
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
			case 'w':    /* 上一个 */
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
			case 's':    /* 下一个 */
			case 'd':
			case 'l':
			case 'j':
				if (count + 1 >= line) {
					count--;
				}
				break;
			case 'g':    /* 第一个 */
				count = -1;
				break;
			case 'G':    /* 最后一个 */
				while (count + 1 < line - 1) {
					count++;
				}
				break;
			case 'r':
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
