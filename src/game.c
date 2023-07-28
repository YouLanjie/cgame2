#include "../include/head.h"
#include <stdio.h>

static void PrintInfo();

#ifdef __linux
static void showTime();
#endif

void Game() {
	int *x,
	    *y,      //当前坐标
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

	clear();
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
	clear();
	gotoxy(1, 1);
	fontColorSet(1,31);
	printf(Time);
#endif
	GameInfo->chess->count = 1;
	while(win <= 0) {
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
				clear();
				return;
			} else {
				way = 0x00;
#ifdef __linux
				if (setitimer(ITIMER_REAL, &tick, NULL)) {
					perror("Error");
					getch();
					return;
				}
				clear();
#else
				clear();
#endif
			}
			break;
		case 0x1B:  /* 在Linux中的Esc键 */
			if (!ctools_kbhit()) { /* 判断在esc符号后还有没有字符 */
				way = 0x1B;
#ifdef __linux
				alarm(0);
#endif
				if (GameInfo->config.draw) {
					break;
				}
				attron(COLOR_PAIR(1));
				move(GameInfo->config.max + 5, 3);
				printw("请确认退出！本次游戏将不会记录！（y/N）");
				attroff(COLOR_PAIR(1));
				way = getch();
				if (way == 0x59 || way == 0x79) {
					free(GameInfo->chess);
					clear();
					return;
				} else {
					way = 0x00;
#ifdef __linux
					if (setitimer(ITIMER_REAL, &tick, NULL)) {
						perror("Error");
						getch();
						return;
					}
					clear();
#else
					clear();
#endif
				}
				break;
			} else {
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
			win = PutChess(way);
			if (win > 0 && win <= 3) {    /* 判断输赢 */
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
					Undo();
					if (GameInfo->config.use_AI && win == blackChess) {
						Undo();
					}
					win = 0;
				}
			} else if (win == -1) {
				error = 1;
			}
			break;
		case 'o':
		case 'O':
			alarm(0);
			clear();
			if (!GameInfo->config.use_AI) {
				Settings();
				if (setitimer(ITIMER_REAL, &tick, NULL)) {
					perror("Error");
					getch();
					return;
				}
				if (GameInfo->config.use_AI && myChess == 2) {
					AI();
					GameInfo->chess->count++;
				}
			} else {
				Settings();
				if (setitimer(ITIMER_REAL, &tick, NULL)) {
					perror("Error");
					getch();
					return;
				}
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
				GameInfo->chess->count++;
				GameInfo->chess->count = - GameInfo->chess->count;
			}
			break;
		case '2':
			if (GameInfo->config.draw) {
				if (GameInfo->chess->count < 0) {
					GameInfo->chess->count = - GameInfo->chess->count;
				}
				while (myChess != 1) {
					GameInfo->chess->count++;
				}
			}
			break;
		case '3':
			if (GameInfo->config.draw) {
				if (GameInfo->chess->count < 0) {
					GameInfo->chess->count = - GameInfo->chess->count;
				}
				while (myChess != 2) {
					GameInfo->chess->count++;
				}
			}
			break;
		case 'n':
			if (GameInfo->config.draw) {
				fp = fopen(GameInfo->config.Save,"a");
				if (!fp) {
					fputs("\033[0;1;31m[save]\033[0m", stderr);
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
		fputs("\033[0;1;31m[save]\033[0m", stderr);
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
	clear();
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
	if (myChess == 1) {
		printw("黑方下 @");
	} else if (myChess == 2) {
		printw("白方下 0");
	} else if (myChess == 0) {
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

