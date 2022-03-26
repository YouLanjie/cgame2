#include "../include/head.h"

#ifdef __linux
static void * showTime();
#endif
static void move(int way, int * x, int * y, int Way[4]);

void Game() {
	int count,count2;                      //用于计数
	int error = 0;                         //记录错误(下棋位置重复)
	int x = 1,y = 1;                       //当前坐标
	int way;                               //记录光标移动方向
	int Way[4] = {87, 65, 83, 68};         //对应的键位
	int win  = 0;	                       //赢家，1黑，2白
	int who = 1;                           //现在下子的玩家
	FILE * fp;
#ifdef __linux
	pthread_t pid;
#endif

	Clear
	p = (struct Chess *)malloc(sizeof(struct Chess));
	GetTime();

#ifdef __linux
	pthread_create(&pid, NULL, showTime, NULL);
	Clear2
	GetNowTime();
	gotoxy(1, 1);
	fontColorSet(1,31);
	printf(NowTime);
#endif
#ifdef _WIN32
	gotoxy(1, 1);
	fontColorSet(1,31);
	printf(Time);
	for (count = 0; count < Max ; count++) {
		for (count2= 0; count2 < Max; count2++) {
			p -> board[count][count2] = 0;
		}
	}
#endif
	while(win != 1 && win != 2) {
		gotoxy(2,1);
		PrintBoard();
		if (who == 1) {
			printf("黑方下\n");
		}
		else if (who == 2) {
			printf("白方下\n");
		}
		if (error == 1) {
			fontColorSet(1,33);
			gotoxy(20,1);
			printf("你不能下在非空的格子!\n");
			fontColorSet(0,0);
			error = 0;
		}
#ifdef __linux
		if (p -> board[y - 1][x - 1] == 1) {
			gotoxy(y + 2, x * 3 - 1); fontColorSet(30, 47);
			printf(">");
			fontColorSet(0,0);
		}
		else if (p -> board[y - 1][x - 1] == 2) {
			gotoxy(y + 2, x * 3 - 1); fontColorSet(0,1); fontColorSet(37, 40);
			printf(">");
			fontColorSet(0,0);
		}
		else {
			gotoxy(y + 2, x * 3 - 1); fontColorSet(0,1); fontColorSet(37, 40);
			printf(">");
			fontColorSet(0,0);
		}
#endif
#ifdef _WIN32
		gotoxy(y + 2, x * 3 - 2);
		printf(">");
#endif
		way = getch();
		gotoxy(y + 2, x * 3 - 1);
		printf(" ");
		switch (way) {
			case 0x30: /* 0 */
			case 0x51: /* Q */
			case 0x71: /* q */
#ifdef __linux
				pthread_cancel(pid);
#endif
				Clear
				fontColorSet(1,33);
				printf("请确认退出！本次游戏将不会记录！（Y/n）\n");
				way = getch();
				if (way == 0x59 || way == 0x79) {
					free(p);
					Clear
					return;
				}
				else {
					way = 0x00;
#ifdef __linux
					pthread_create(&pid, NULL, showTime, NULL);
#endif
					Clear
				}
				break;
			case 0x1B:  /* 在Linux中的Esc键 */
				if (way == kbhit()) { /* 判断在esc符号后还有没有字符 */
					way = 0x1B;
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
					move(way, &x, &y, Way);
					Way[0] = 'W';
					Way[1] = 'A';
					Way[2] = 'S';
					Way[3] = 'D';
				}
				else { /* 不是以上的则认作退出处理 */
#ifdef __linux
					pthread_cancel(pid);
#endif
					Clear
					fontColorSet(1,33);
					printf("请确认退出！本次游戏将不会记录！（Y/n）\n");
					way = getch();
					if (way == 0x59 || way == 0x79) {
						free(p);
						Clear
						return;
					}
					else {
						way = 0x00;
#ifdef __linux
						pthread_create(&pid, NULL, showTime, NULL);
#endif
						Clear
					}
					break;
				}
				break;
			case 0x0D: /* CR回车键 \r */
			case 0x20: /* 空格键 */
				if (p -> board[y - 1][x - 1] == 1 || p -> board[y - 1][x - 1] == 2) {
					error = 1;
					break;
				}
				else if (p -> board[y - 1][x - 1] == 0) {
					p -> board[y - 1][x - 1] = who;
					p -> who = who;
					p -> x = x;
					p -> y = y;
					win = IfWin(5);
					if (win == who) {
#ifdef __linux
	pthread_cancel(pid);
#endif
						Clear
						fontColorSet(0,33);
						printf("游戏结束，");
						if (who == 1) {
							printf("黑方");
						}
						else if (who == 2) {
							printf("白方");
						}
						printf("胜利！\n");
						fontColorSet(0,31);
						printf("按Enter返回\n");
						fontColorSet(0,0);
						getch();
					}
					if (config[0] == 1) {  /* 调用自动下棋 */
						AI();
					}
					else {  /* 切换下棋的一方 */
						who = 3 - who;
					}
					break;
				}
				break;
			default:
				move(way, &x, &y, Way);
				break;
		}
		printf("\n");
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
static void * showTime() {
	while(1) {
		GetNowTime();
		gotoxy(1, 1);
		fontColorSet(1,31);
		printf(NowTime);
		sleep(1);
	}
	pthread_exit(0);
}
#endif

static void move(int way, int * x, int * y, int Way[4]) {
	int up = Way[0], down = Way[2], left = Way[1], right = Way[3];
	/* 方向键对应字符、WASD式控制键位与坐标设计示意
	 *         A           W        yx->
	 *      D  +  C     A  +  D     | ++++ 
	 *         B           S        v ++++ */
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

