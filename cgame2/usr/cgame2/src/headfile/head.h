#include <stdio.h>                           //标准库
#include <stdlib.h>                          //system();srand();rand();malloc();free();
#include <string.h>                          //strcmp();
#include <unistd.h>
#include <time.h>

#include "kbhit_input.h"

#define Clear system("clear");
#define Max 15

#define Save "/usr/cgame2/build/save.txt"
#define Data "/usr/cgame2/build/data.txt"

#define Time "\033[1;31m日期：%d-%d-%d 时间：%d:%d:%d\n",p -> t.year,p -> t.mon,p -> t.day,p -> t.hour,p -> t.min,p -> t.sec
#define NowTime "\033[1;31m日期：%d-%d-%d 时间：%d:%d:%d\n",p -> nt.year,p -> nt.mon,p -> nt.day,p -> nt.hour,p -> nt.min,p -> nt.sec

struct time {
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
};

struct Chess {
	struct time t;         //开局时间
	struct time nt;        //现在时间
	int board[Max][Max];   //棋盘
	int count;             //一共有多少局
	int who;               //下棋的一方，1黑，2白
	int x;                 //新棋子的x轴
	int y;                 //新棋子的y轴
};

int ifWin(struct Chess *p);

void init(struct Chess *p);
void welcome();
void game(struct Chess *p);
void save(struct Chess *p);
void history(struct Chess *p);
void help();
void other();
void printboard(struct Chess *p);
void gettime(struct Chess *p);
void getnowtime(struct Chess *p);
