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

#define Time "日期：%d-%d-%d 时间：%d:%d:%d\n",p -> t.year,p -> t.mon,p -> t.day,p -> t.hour,p -> t.min,p -> t.sec

struct Chess {
	struct time t;
	int board[Max][Max];
	int count;
};

struct time {
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
};


void init(struct Chess *p);
void welcome();
void game(struct Chess *p);
void save(struct Chess *p);
void history(struct Chess *p);
void help();
void printboard(struct Chess *p);
void gettime(struct Chess *p);
