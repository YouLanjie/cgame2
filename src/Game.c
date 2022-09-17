#include "../include/head.h"

void Undo();
static void PrintInfo();

#ifdef __linux
static void showTime();
#endif
static void Move(int way, int * x, int * y, int Way[4]);

void Game() {
	int *x,
	    *y,      //当前坐标
	    *who,    //现在下子的玩家
	    way,     //记录光标移动方向（输入）
	    win = 0, //赢家，1黑，2白
	    Way[4] = {
		    87, 65, 83, 68
	    },       //对应的键位
	    error = 0;   //记录错误(下棋位置重复)
	FILE * fp;

	InitChess();
	x   = &GameInfo->chess->x;
	y   = &GameInfo->chess->y;
	who = &GameInfo->chess->who;

	Clear
	GetTime();

#ifdef __linux
	struct itimerval tick;

	/* 定时间隔 */
	tick.it_interval.tv_sec = 1;
	tick.it_interval.tv_usec = 0;
	/* 延迟启动 */
	tick.it_value.tv_sec = 0;
	tick.it_value.tv_usec = 100000;

	alarm(0);
	signal(SIGALRM, showTime);
	if (setitimer(ITIMER_REAL, &tick, NULL)) {
		perror("Error");
		getch();
		return;
	}
#endif
#ifdef _WIN32
	Clear
	gotoxy(1, 1);
	fontColorSet(1,31);
	printf(Time);
#endif
	GameInfo->chess->count = 1;
	while(win == 0) {
		PrintInfo();
		if (error == 1) {
			move(GameInfo->config.max + 5, 3);
			attron(COLOR_PAIR(8));
			printw("你不能下在非空的格子!");
			attroff(COLOR_PAIR(8));
			error = 0;
		}
		way = getch();
		switch (way) {
			case 0x30: /* 0 */
			case 0x51: /* Q */
			case 0x71: /* q */
#ifdef __linux
				alarm(0);
#endif
				attron(COLOR_PAIR(1));
				move(GameInfo->config.max + 5, 3);
				printw("请确认退出！本次游戏将不会记录！（y/N）");
				attroff(COLOR_PAIR(1));
				way = getch();
				if (way == 0x59 || way == 0x79) {
					free(GameInfo->chess);
					GameInfo->chess = NULL;
					Clear
					return;
				}
				else {
					way = 0x00;
#ifdef __linux
					if (setitimer(ITIMER_REAL, &tick, NULL)) {
						perror("Error");
						getch();
						return;
					}
					Clear2
#else
					Clear
#endif
				}
				break;
			case 0x1B:  /* 在Linux中的Esc键 */
				if (!kbhit()) { /* 判断在esc符号后还有没有字符 */
					way = 0x1B;
#ifdef __linux
					alarm(0);
#endif
					if (GameInfo->config.draw) {
						break;
					}
					attron(COLOR_PAIR(1));
					move(0, 0);
					printw("请确认退出！本次游戏将不会记录！（y/N）");
					attroff(COLOR_PAIR(1));
					way = getch();
					if (way == 0x59 || way == 0x79) {
						free(GameInfo->chess);
						Clear2
						return;
					}
					else {
						way = 0x00;
#ifdef __linux
						if (setitimer(ITIMER_REAL, &tick, NULL)) {
							perror("Error");
							getch();
							return;
						}
						Clear2
#else
						Clear
#endif
					}
					break;
				}
				else {
					getchar();
					way = getchar(); /* 若有，则获取 */
				}
				if (way == 0x41 || way == 0x44 || way == 0x42 || way == 0x43) {
					Way[0] = 'A';
					Way[1] = 'D';
					Way[2] = 'B';
					Way[3] = 'C';
					Move(way, x, y, Way);
					Way[0] = 'W';
					Way[1] = 'A';
					Way[2] = 'S';
					Way[3] = 'D';
				}
				break;
			case 0x0D: /* CR回车键 \r */
			case '\n':
			case 0x20: /* 空格键 -> 下棋 */
				if (GameInfo->config.draw) {
					GameInfo->chess->board[*y - 1][*x - 1] = GameInfo->chess->count;
					GameInfo->chess->count++;
					break;
				}
				if ((!GameInfo->config.all_AI || way == '\n') && (GameInfo->chess->board[*y - 1][*x - 1] != 0)) {    /* 棋盘非空 */
					error = 1;
					break;
				} else if (GameInfo->chess->board[*y - 1][*x - 1] == 0 || (GameInfo->config.all_AI && way == ' ')) {
					if (!GameInfo->config.all_AI || way == '\n') {    /* 用户输入 */
						GameInfo->chess->board[*y - 1][*x - 1] = GameInfo->chess->count;
						GameInfo->chess->count++;
					} else {    /* 自动下棋 */
						AI();
					}
					win = IfWin(5);

					if (win != *who && GameInfo->config.use_AI == 1) {  /* 使用AI下棋 */
						*who = 3 - *who;
						AI();
						win = IfWin(5);
						if (win == 0) {
							*who = 3 - *who;
						}
					}

					if (win == *who || win == -1) {    /* 判断输赢 */
#ifdef __linux
						alarm(0);
#endif
						PrintBoard();
						PrintInfo();
						hiChess();

						move(GameInfo->config.max + 5, 3);
						attron(COLOR_PAIR(6));
						attron(A_BOLD);
						printw("游戏结束，");
						if (win == 1) {
							printw("黑方胜利！");
						} else if (win == 2) {
							printw("白方胜利！");
						} else if (win == -1) {
							printw("高手，平局");
						}
						printw("（按Q返回，可按u撤回）");
						attroff(A_BOLD);
						attroff(COLOR_PAIR(6));
						way = 0;
						while (way != 'q' && way != 'Q' && way != 'u' && way != 'U') {
							way = getch();
						}
						if (way == 'u' || way == 'U') {
							win = 0;
							Undo();
							if (GameInfo->config.use_AI) {
								Undo();
							}
						}
					}
					if (!GameInfo->config.use_AI) {  /* 切换下棋的一方 */
						*who = 3 - *who;
					}
					break;
				}
				break;
			case 'o':
			case 'O':
				alarm(0);
				clear();
				Settings();
				if (setitimer(ITIMER_REAL, &tick, NULL)) {
					perror("Error");
					getch();
					return;
				}
				if (GameInfo->config.use_AI == 1) {
					Undo();
					*who = blackChess;
				}
				break;
			case 'u':    /* 撤回 */
			case 'U':
				Undo();
				if (GameInfo->config.use_AI) {
					Undo();
				}
				break;
			case 'h':
			case 'j':
			case 'k':
			case 'l':
				Way[0] = 'K';
				Way[1] = 'H';
				Way[2] = 'J';
				Way[3] = 'L';
				Move(way, x, y, Way);
				Way[0] = 'W';
				Way[1] = 'A';
				Way[2] = 'S';
				Way[3] = 'D';
				break;
			case '1':
				if (GameInfo->config.draw) {
					*who = 0;
				}
				break;
			case '2':
				if (GameInfo->config.draw) {
					*who = 1;
				}
				break;
			case '3':
				if (GameInfo->config.draw) {
					*who = 2;
				}
				break;
			case 'n':
				if (GameInfo->config.draw) {
					fp = fopen(GameInfo->config.Save,"a");
					if (!fp) {
						fontColorSet(1,31);
						perror("[save]");
						fontColorSet(0,0);
						return;
					}

					fprintf(fp,"%d %d %d %d %d %d %d ", GameInfo->chess->t.year, GameInfo->chess->t.mon, GameInfo->chess->t.day, GameInfo->chess->t.hour, GameInfo->chess->t.min, GameInfo->chess->t.sec, GameInfo->config.max);

					for (int count = 0; count < GameInfo->config.max ; count++) {    //打印棋盘到文件
						for (int count2= 0; count2 < GameInfo->config.max; count2++) {
							fprintf(fp,"%d", GameInfo->chess->board[count][count2]);
						}
						fprintf(fp," ");
					}

					fprintf(fp,"\n");
					fclose(fp);

					if (GameInfo->config.draw_reset) {
						free(GameInfo->chess);
						GameInfo->chess = NULL;
						InitChess();
						GetTime();
					}
				}
				break;
			default:
				Move(way, x, y, Way);
				break;
		}
		if (GameInfo->config.draw && way == 0x1B) {
			break;
		}
	}
	fp = fopen(GameInfo->config.Save,"a");
	if (!fp) {
		fontColorSet(1,31);
		perror("[save]");
		fontColorSet(0,0);
		return;
	}
	fprintf(fp,"%d %d %d %d %d %d %d", GameInfo->chess->t.year, GameInfo->chess->t.mon, GameInfo->chess->t.day, GameInfo->chess->t.hour, GameInfo->chess->t.min, GameInfo->chess->t.sec, GameInfo->config.max);
	for (int count = 0; count < GameInfo->config.max ; count++) {    //打印棋盘到文件
		for (int count2 = 0; count2 < GameInfo->config.max; count2++) {
			fprintf(fp," %d", GameInfo->chess->board[count][count2]);
		}
	}
	fprintf(fp,"\n");
	fclose(fp);
	free(GameInfo->chess);
	Clear
	return;
}

void Undo() {
	for (int i = 0; i < GameInfo->config.max; i++) {
		for (int i2 = 0; i2 < GameInfo->config.max; i2++) {
			if (GameInfo->chess->count && GameInfo->chess->count > 1 && GameInfo->chess->board[i][i2] == GameInfo->chess->count - 1) {
				GameInfo->chess->board[i][i2] = spaceChess;
				GameInfo->chess->count--;
				GameInfo->chess->who = (GameInfo->chess->count % 2 ? (1) : (GameInfo->chess->count ? 2 : 0));
				return;
			}
		}
	}
	return;
}

static void PrintInfo()
{
	GetNowTime();
	move(0, 0);
	attron(COLOR_PAIR(1));
	printw(NowTime);
	attroff(COLOR_PAIR(1));
	PrintBoard();
	attron(COLOR_PAIR(1));
	move(GameInfo->config.max + 4, GameInfo->config.max * 3 / 4 * 1 - 4);
	if (GameInfo->chess->who == 1) {
		printw("黑方下 @");
	} else if (GameInfo->chess->who == 2) {
		printw("白方下 0");
	} else if (GameInfo->chess->who == 0) {
		printw("空白下 ::");
	}
	if (GameInfo->config.use_AI == 1) {
		mvaddstr(GameInfo->config.max + 4, GameInfo->config.max * 3 / 4 * 3 - 5, "自动下棋开启");
	}
	attroff(COLOR_PAIR(1));
	showTime();

	move(GameInfo->chess->y + 2, GameInfo->chess->x * 3 - 2);
	attron(A_REVERSE);
	if (GetChessPlayer(GameInfo->chess->y, GameInfo->chess->x) == blackChess) {
		attron(COLOR_PAIR(7));
		if (GameInfo->config.show_count) {
			printw("%02d<", GameInfo->chess->board[GameInfo->chess->y - 1][GameInfo->chess->x - 1]);
		} else {
			printw(">@");
		}
		attroff(COLOR_PAIR(7));
	} else if (GetChessPlayer(GameInfo->chess->y, GameInfo->chess->x) == whiteChess) {
		attron(COLOR_PAIR(8));
		if (GameInfo->config.show_count) {
			printw("%02d<", GameInfo->chess->board[GameInfo->chess->y - 1][GameInfo->chess->x - 1]);
		} else {
			printw(">O");
		}
		attroff(COLOR_PAIR(8));
	}
	else {
		attron(COLOR_PAIR(1));
		printw("><");
		attroff(COLOR_PAIR(1));
	}
	attroff(A_REVERSE);
return;
}

#ifdef __linux
static void showTime() {
	GetNowTime();
	move(1, 3);
	attron(COLOR_PAIR(1));
	printw(NowTime);
	attroff(COLOR_PAIR(1));
	refresh();
	return;
}
#endif

static void Move(int way, int * x, int * y, int Way[4]) {
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

