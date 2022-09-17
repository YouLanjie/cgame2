#include "../include/head.h"

void InitChess()
{
	GameInfo->chess = (Chess *)malloc(sizeof(Chess));
	for (int count = 0; count < GameInfo->config.max ; count++) {  /* 用于初始化内存 */
		for (int count2 = 0; count2 < GameInfo->config.max; count2++) {
			GameInfo->chess-> board[count][count2] = 0;
		}
	}
	GameInfo->chess->x     = 1;
	GameInfo->chess->y     = 1;
	GameInfo->chess->way   = 0;
	GameInfo->chess->who   = 1;
	GameInfo->chess->count = 0;
	return;
}


int GetChessPlayer(int y, int x)
{
	y--;
	x--;
	if (GameInfo->chess->board[y][x] != 0 && GameInfo->chess->board[y][x] % 2 == 0) {
		return whiteChess;
	} else if (GameInfo->chess->board[y][x] % 2 == 1) {
		return blackChess;
	} else {
		return spaceChess;
	}
	return errorChess;
}

void PrintBoard() {
	int count;
	int count2;

	attron(COLOR_PAIR(1));
	move(0, 0);
	for (int i = 0; i < LINES; i++) {
		for (int i2 = 0; i2 < COLS; i2++) {
			mvaddch(i, i2, ' ');
		}
	}
	attroff(COLOR_PAIR(1));

	attron(COLOR_PAIR(8));
	attron(A_BOLD);

	move(0, 0);
	printw(LineLU);
	for (count = 0; count < GameInfo->config.max; count++) {
		printw("%s%s%s", LineH, LineH, LineH);
	}
	printw(LineRU);
	mvaddstr(1, GameInfo->config.max * 3 + 1, LineV);
	mvaddstr(1, 0, LineV);

	move(2, 0);
	printw(LineLC);
	for (count = 0; count < GameInfo->config.max; count++) {
		printw("%s%s%s", LineH, LineH, LineH);
	}
	printw(LineRC);
	attroff(COLOR_PAIR(8));

	for (count = 0; count < GameInfo->config.max; count++) {    //打印棋盘
		move(count + 3, 0);
		attron(COLOR_PAIR(8));
		attron(A_BOLD);
		printw(LineV);
		attroff(A_BOLD);
		attroff(COLOR_PAIR(8));
		for (count2 = 0; count2 < GameInfo->config.max; count2++) {
			if (GameInfo->chess->board[count][count2] && GameInfo->chess->board[count][count2] == GameInfo->chess->count - 1) {
				attron(A_REVERSE);
				attron(A_BOLD);
			}
			if (GetChessPlayer(count + 1, count2 + 1) == blackChess) {
				attron(COLOR_PAIR(7));
				if (GameInfo->config.show_count) {
					printw("%02d", GameInfo->chess->board[count][count2]);
				} else {
					printw("@@");
				}
				attron(COLOR_PAIR(7));
			} else if (GetChessPlayer(count + 1, count2 + 1) == whiteChess) {
				attron(COLOR_PAIR(8));
				if (GameInfo->config.show_count) {
					printw("%02d", GameInfo->chess->board[count][count2]);
				} else {
					printw("OO");
				}
				attron(COLOR_PAIR(8));
			} else {
				attron(COLOR_PAIR(1));
				if (GameInfo->config.show_count) {
					printw("%02d", GameInfo->chess->board[count][count2]);
				} else {
					printw("::");
				}
				attron(COLOR_PAIR(1));
			} 
			if (GameInfo->chess->board[count][count2] && GameInfo->chess->board[count][count2] == GameInfo->chess->count - 1) {
				attroff(A_REVERSE);
				attroff(A_BOLD);
			}
			attron(COLOR_PAIR(1));
			printw(" ");
			attroff(COLOR_PAIR(1));
		}
		attron(COLOR_PAIR(8));
		attron(A_BOLD);
		printw(LineV);
		attroff(A_BOLD);
		attroff(COLOR_PAIR(8));
	}

	attron(COLOR_PAIR(8));
	attron(A_BOLD);

	mvaddstr(count + 3, 0, LineLC);
	for (count = 0; count < GameInfo->config.max; count++) {
		printw("%s%s%s", LineH, LineH, LineH);
	}
	printw(LineRC);

	mvaddstr(count + 4, 0, LineV);
	for (count = 0; count < GameInfo->config.max; count++) {
		printw("   ");
	}
	printw(LineV);

	mvaddstr(count + 5, 0, LineV);
	for (count = 0; count < GameInfo->config.max; count++) {
		printw("   ");
	}
	printw(LineV);

	mvaddstr(count + 6, 0, LineLD);
	for (count = 0; count < GameInfo->config.max; count++) {
		printw("%s%s%s", LineH, LineH, LineH);
	}
	printw(LineRD);

	attroff(A_BOLD);
	attroff(COLOR_PAIR(8));
	refresh();
	return;
}

void hiChess()
{
	char chess[4] = "@@";

	attron(A_REVERSE);
	move(GameInfo->chess->y + 2, GameInfo->chess->x * 3 - 2);
	if (GameInfo->chess->who == 1) {
		attron(COLOR_PAIR(7));
		strcpy(chess, "@@");
	} else {
		attron(COLOR_PAIR(8));
		strcpy(chess, "00");
	}
	for (int i = 0; i < 5;i++) {
		if (GameInfo->config.show_count) {
			switch (GameInfo->chess->way) {
			case 1:
				move(GameInfo->chess->y + i + 2, GameInfo->chess->x * 3 - 2);
				printw("%02d", GameInfo->chess->board[GameInfo->chess->y - 1 + i][GameInfo->chess->x - 1]);
				break;
			case 2:
				move(GameInfo->chess->y + 2, GameInfo->chess->x * 3 - 2 + i * 3);
				printw("%02d", GameInfo->chess->board[GameInfo->chess->y + 1][GameInfo->chess->x - 1 + i]);
				break;
			case 3:
				move(GameInfo->chess->y + i + 2, GameInfo->chess->x * 3 - 2 + i * 3);
				printw("%02d", GameInfo->chess->board[GameInfo->chess->y - 1 + i][GameInfo->chess->x - 1 + i]);
				break;
			case 4:
				move(GameInfo->chess->y + i + 2, GameInfo->chess->x * 3 - 2 - i * 3);
				printw("%02d", GameInfo->chess->board[GameInfo->chess->y - 1 + i][GameInfo->chess->x - 1 - i]);
				break;
			default:
				break;
			}
		} else {
			switch (GameInfo->chess->way) {
			case 1:
				mvaddstr(GameInfo->chess->y + i + 2, GameInfo->chess->x * 3 - 2, chess);
				break;
			case 2:
				mvaddstr(GameInfo->chess->y + 2, GameInfo->chess->x * 3 - 2 + i * 3, chess);
				break;
			case 3:
				mvaddstr(GameInfo->chess->y + i + 2, GameInfo->chess->x * 3 - 2 + i * 3, chess);
				break;
			case 4:
				mvaddstr(GameInfo->chess->y + i + 2, GameInfo->chess->x * 3 - 2 - i * 3, chess);
				break;
			default:
				break;
			}
		}
	}
	if (GameInfo->chess->who == 1) {
		attroff(COLOR_PAIR(7));
	} else {
		attroff(COLOR_PAIR(8));
	}
	attroff(A_REVERSE);
	refresh();
	return;
}

