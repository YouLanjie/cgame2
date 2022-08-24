#include "../include/head.h"

#ifdef __linux
static void showTime();
#endif
static void Move(int way, int * x, int * y, int Way[4]);

void Game() {
	int count,count2;                      //用于计数
	int error = 0;                         //记录错误(下棋位置重复)
	int x = 1,y = 1;                       //当前坐标
	int way;                               //记录光标移动方向
	int Way[4] = {87, 65, 83, 68};         //对应的键位
	int win  = 0;	                       //赢家，1黑，2白
	int who = 1;                           //现在下子的玩家
	FILE * fp;

	Clear
	p = (struct Chess *)malloc(sizeof(struct Chess));
	for (count = 0; count < Max ; count++) {  /* 用于初始化内存 */
		for (count2 = 0; count2 < Max; count2++) {
			p -> board[count][count2] = 0;
		}
	}
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
	while(win != 1 && win != 2) {
		GetNowTime();
		move(0, 0);
		attron(COLOR_PAIR(1));
		printw(NowTime);
		attroff(COLOR_PAIR(1));
		PrintBoard();
		attron(COLOR_PAIR(1));
		move(Max + 4, Max * 3 / 4 * 1 - 4);
		if (who == 1) {
			printw("黑方下 @");
		}
		else if (who == 2) {
			printw("白方下 0");
		}
		else if (who == 0) {
			printw("空白下 ::");
		}
		if (config[0] == 1) {
			mvaddstr(Max + 4, Max * 3 / 4 * 3 - 5, "自动下棋开启");
		}
		if (error == 1) {
			move(Max + 5, 3);
			printw("你不能下在非空的格子!");
			error = 0;
		}
		attroff(COLOR_PAIR(1));
		showTime();
		move(y + 2, x * 3 - 2);
		attron(A_REVERSE);
		if (p -> board[y - 1][x - 1] == 1) {
			attron(COLOR_PAIR(7));
			printw("@@");
			attroff(COLOR_PAIR(7));
		}
		else if (p -> board[y - 1][x - 1] == 2) {
			attron(COLOR_PAIR(8));
			printw("OO");
			attroff(COLOR_PAIR(8));
		}
		else {
			attron(COLOR_PAIR(1));
			printw("><");
			attroff(COLOR_PAIR(1));
		}
		attroff(A_REVERSE);
		way = getch();
		switch (way) {
			case 0x30: /* 0 */
			case 0x51: /* Q */
			case 0x71: /* q */
#ifdef __linux
				alarm(0);
#endif
				attron(COLOR_PAIR(1));
				move(Max + 5, 3);
				printw("请确认退出！本次游戏将不会记录！（y/N）");
				attroff(COLOR_PAIR(1));
				way = getch();
				if (way == 0x59 || way == 0x79) {
					free(p);
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
					if (config[4]) {
						break;
					}
					attron(COLOR_PAIR(1));
					move(0, 0);
					printw("请确认退出！本次游戏将不会记录！（y/N）");
					attroff(COLOR_PAIR(1));
					way = getch();
					if (way == 0x59 || way == 0x79) {
						free(p);
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
					Move(way, &x, &y, Way);
					Way[0] = 'W';
					Way[1] = 'A';
					Way[2] = 'S';
					Way[3] = 'D';
				}
				break;
			case 0x0D: /* CR回车键 \r */
			case '\n':
			case 0x20: /* 空格键 -> 下棋 */
				if (config[4]) {
					p -> board[y - 1][x - 1] = who;
					break;
				}
				if (!config[3] && (p -> board[y - 1][x - 1] == 1 || p -> board[y - 1][x - 1] == 2)) {
					error = 1;
					break;
				}
				else if (p -> board[y - 1][x - 1] == 0 || config[3]) {
					if (!config[3] || way == '\n') {    /* 用户输入 */
						p -> board[y - 1][x - 1] = who;
					}
					else {    /* 自动下棋 */
						AI();
					}
					p -> who = who;
					win = IfWin(5);

					if (win != who && config[0] == 1) {  /* 使用AI下棋 */
						who = 3 - who;
						p -> who = who;
						AI();
						win = IfWin(5);
						if (win == 0) {
							who = 3 - who;
							p -> who = who;
						}
					}

					if (win == who) {    /* 判断输赢 */
#ifdef __linux
						alarm(0);
#endif
						PrintBoard();
						showTime();
						attron(COLOR_PAIR(1));
						move(Max + 4, Max * 3 / 4 * 1 - 4);
						if (who == 1) {
							printw("黑方下 @");
						}
						else if (who == 2) {
							printw("白方下 0");
						}
						else if (who == 0) {
							printw("空白下 ::");
						}
						if (config[0] == 1) {
							mvaddstr(Max + 4, Max * 3 / 4 * 3 - 5, "自动下棋开启");
						}
						attroff(COLOR_PAIR(1));

						move(y + 2, x * 3 - 2);
						attron(A_REVERSE);
						if (p -> board[y - 1][x - 1] == 1) {
							attron(COLOR_PAIR(7));
							printw("@@");
							attroff(COLOR_PAIR(7));
						}
						else if (p -> board[y - 1][x - 1] == 2) {
							attron(COLOR_PAIR(8));
							printw("OO");
							attroff(COLOR_PAIR(8));
						}
						else {
							attron(COLOR_PAIR(1));
							printw("><");
							attroff(COLOR_PAIR(1));
						}
						attroff(A_REVERSE);

						move(Max + 5, 3);
						attron(COLOR_PAIR(6));
						attron(A_BOLD);
						printw("游戏结束，");
						if (who == 1) {
							printw("黑方");
						}
						else if (who == 2) {
							printw("白方");
						}
						printw("胜利！");
						printw("（按Q键返回）");
						attroff(A_BOLD);
						attroff(COLOR_PAIR(6));
						way = 0;
						while (way != 'q' && way != 'Q') {
							way = getch();
						}
					}
					if (config[0] == 0) {  /* 切换下棋的一方 */
						who = 3 - who;
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
				if (config[0] == 1) {
					who = 1;
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
				Move(way, &x, &y, Way);
				Way[0] = 'W';
				Way[1] = 'A';
				Way[2] = 'S';
				Way[3] = 'D';
				break;
			case '1':
				if (config[4]) {
					who = 0;
				}
				break;
			case '2':
				if (config[4]) {
					who = 1;
				}
				break;
			case '3':
				if (config[4]) {
					who = 2;
				}
				break;
			case 'n':
				if (config[4]) {
					fp = fopen(Save,"a");
					if (!fp) {
						fontColorSet(1,31);
						perror("[save]");
						fontColorSet(0,0);
						return;
					}

					fprintf(fp,"%d %d %d %d %d %d %d ", p -> t.year, p -> t.mon, p -> t.day, p -> t.hour, p -> t.min, p -> t.sec, Max);

					for (count = 0; count < Max ; count++) {    //打印棋盘到文件
						for (count2= 0; count2 < Max; count2++) {
							fprintf(fp,"%d", p -> board[count][count2]);
						}
						fprintf(fp," ");
					}

					fprintf(fp,"\n");
					fclose(fp);

					if (config[5]) {
						free(p);

						p = (struct Chess *)malloc(sizeof(struct Chess));
						for (count = 0; count < Max ; count++) {  /* 用于初始化内存 */
							for (count2 = 0; count2 < Max; count2++) {
								p -> board[count][count2] = 0;
							}
						}
						GetTime();
					}
					p -> x = x;
					p -> y = y;
				}
				break;
			default:
				Move(way, &x, &y, Way);
				break;
		}
		if (config[4] && way == 0x1B) {
			break;
		}
	}
	fp = fopen(Save,"a");
	if (!fp) {
		fontColorSet(1,31);
		perror("[save]");
		fontColorSet(0,0);
		return;
	}
	fprintf(fp,"%d %d %d %d %d %d %d ", p -> t.year, p -> t.mon, p -> t.day, p -> t.hour, p -> t.min, p -> t.sec, Max);
	for (count = 0; count < Max ; count++) {    //打印棋盘到文件
		for (count2= 0; count2 < Max; count2++) {
			fprintf(fp,"%d", p -> board[count][count2]);
		}
		fprintf(fp," ");
	}
	fprintf(fp,"\n");
	fclose(fp);
	free(p);
	Clear
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
		if (*y < 2) *y = Max + 1;
		(*y)--;
	}
	else if (way == left || way == left + 32) {
		if (*x < 2) *x = Max + 1;
		(*x)--;
	}
	else if (way == down || way == down + 32) {
		if (*y > Max - 1) *y = 0;
		(*y)++;
	}
	else if (way == right || way == right + 32) {
		if (*x > Max - 1) *x = 0;
		(*x)++;
	}
	return;
}

