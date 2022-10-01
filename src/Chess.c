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
	GameInfo->chess->count = 0;
	return;
}

int GetChessPlayer(int y, int x)
{
	if (GetChessVal(y, x) != 0 && GetChessVal(y, x) % 2 == 0) {
		return whiteChess;
	} else if (GetChessVal(y, x) % 2 == 1) {
		return blackChess;
	} else {
		return spaceChess;
	}
	return errorChess;
}

void Move(int way, int * x, int * y, int Way[4])
{
	int up = Way[0], down = Way[2], left = Way[1], right = Way[3];
	/* 方向键对应字符、WASD式控制键位与坐标设计示意
	 *         A           W           W      yx->
	 *      D  +  C     A  +  D     A  +  D   | ++++
	 *         B           S           S      v ++++
	 */
	if (way == up || way == up + 32) {
		if (*y < 2) *y = GameInfo->config.max + 1;
		(*y)--;
	}
	else if (way == left || way == left + 32) {
		if (*x < 2) *x = GameInfo->config.max + 1;
		(*x)--;
	}
	else if (way == down || way == down + 32) {
		if (*y > GameInfo->config.max - 1) *y = 0;
		(*y)++;
	}
	else if (way == right || way == right + 32) {
		if (*x > GameInfo->config.max - 1) *x = 0;
		(*x)++;
	}
	return;
}

/* 该函数能够在指定的位置下棋并调用AI下棋
 * 用于Game()函数内部
 * 返回值：
 * 0   无胜负
 * 1~3 同Ifwin()返回值
 * -1  下子处非空
 * -2  处于绘图模式
 */
int PutChess(int input)
{
	int *x = &GameInfo->chess->x,
	    *y = &GameInfo->chess->y,
	    win = 0;

	if (GameInfo->config.draw) {    /* 处于绘图模式 */
		GetChessVal(*y, *x) = GameInfo->chess->count;
		GameInfo->chess->count++;
		return -2;
	} else if ((!GameInfo->config.all_AI || input == '\n') && (GetChessVal(*y, *x) != 0)) {    /* 格子非空 */
		return -1;
	} else if (GetChessVal(*y, *x) == 0 || (GameInfo->config.all_AI && input == ' ')) {
		if ((!GameInfo->config.all_AI && input == ' ') || input == '\n') {    /* 用户输入 */
			GetChessVal(*y, *x) = GameInfo->chess->count;
		} else {    /* 自动下棋 */
			AI();
		}
		win = IfWin();
		if (win == 0) {
			GameInfo->chess->count++;    /* 切换下棋方 */
			if (GameInfo->config.use_AI) {  /* 使用AI下棋 */
				AI();
				win = IfWin();
				if (win == 0) {
					GameInfo->chess->count++;    /* 切换下棋方 */
				}
			}
		}
	}
	return win;
}

/* 该函数用于实现撤销
 */
void Undo()
{
	for (int i = 0; i < GameInfo->config.max; i++) {
		for (int i2 = 0; i2 < GameInfo->config.max; i2++) {
			if (GameInfo->chess->count > 1 && (GetChessVal2(i, i2) >= 0 ? GetChessVal2(i, i2) == GameInfo->chess->count - 1 : - GetChessVal2(i, i2) == GameInfo->chess->count - 1)) {
				GetChessVal2(i, i2) = spaceChess;
				GameInfo->chess->count--;
				return;
			}
		}
	}
	return;
}

void PrintBoard()
{
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
			if (GetChessVal2(count, count2) && GetChessVal2(count, count2) == GameInfo->chess->count - 1) {
				attron(A_REVERSE);
				attron(A_BOLD);
			}
			if (GetChessPlayer(count + 1, count2 + 1) == blackChess) {
				attron(COLOR_PAIR(7));
				if (GameInfo->config.show_count) {
					printw("%02d", GetChessVal2(count, count2));
				} else {
					printw("@@");
				}
				attron(COLOR_PAIR(7));
			} else if (GetChessPlayer(count + 1, count2 + 1) == whiteChess) {
				attron(COLOR_PAIR(8));
				if (GameInfo->config.show_count) {
					printw("%02d", GetChessVal2(count, count2));
				} else {
					printw("OO");
				}
				attron(COLOR_PAIR(8));
			} else {
				attron(COLOR_PAIR(1));
				if (GameInfo->config.show_count) {
					printw("%02d", GetChessVal2(count, count2));
				} else {
					printw("::");
				}
				attron(COLOR_PAIR(1));
			} 
			if (GetChessVal2(count, count2) && GetChessVal2(count, count2) == GameInfo->chess->count - 1) {
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
	if (GameInfo->config.more_info) {
		move(count + 7, 0);
		printw("X:%02d Y:%02d count:%03d", GameInfo->chess->x, GameInfo->chess->y, GameInfo->chess->count);
	}
	attroff(COLOR_PAIR(8));
	refresh();
	return;
}

void hiChess()
{
	char chess[4] = "@@";

	attron(A_REVERSE);
	move(GameInfo->chess->y + 2, GameInfo->chess->x * 3 - 2);
	if (myChess == 1) {
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
				printw("%02d", GetChessVal2(GameInfo->chess->y - 1 + i, GameInfo->chess->x - 1));
				break;
			case 2:
				move(GameInfo->chess->y + 2, GameInfo->chess->x * 3 - 2 + i * 3);
				printw("%02d", GetChessVal2(GameInfo->chess->y + 1, GameInfo->chess->x - 1 + i));
				break;
			case 3:
				move(GameInfo->chess->y + i + 2, GameInfo->chess->x * 3 - 2 + i * 3);
				printw("%02d", GetChessVal2(GameInfo->chess->y - 1 + i, GameInfo->chess->x - 1 + i));
				break;
			case 4:
				move(GameInfo->chess->y + i + 2, GameInfo->chess->x * 3 - 2 - i * 3);
				printw("%02d", GetChessVal2(GameInfo->chess->y - 1 + i, GameInfo->chess->x - 1 - i));
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
	if (myChess == 1) {
		attroff(COLOR_PAIR(7));
	} else {
		attroff(COLOR_PAIR(8));
	}
	attroff(A_REVERSE);
	refresh();
	return;
}

