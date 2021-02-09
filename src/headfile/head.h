#include <stdio.h>                           //标准库
#include <stdlib.h>                          //system();srand();rand();malloc();free();
#include <string.h>                          //strcmp();
#include <unistd.h>

#include "kbhit_input.h"
#include "gettime.h"

#define Clear system("clear");
#define Max 15

struct Chess
{
	int board[Max][Max];
	int count;
};

void init(struct Chess *p);
void welcome();
void game(struct Chess *p);
void save(struct Chess *p);
void history(struct Chess *p);
void help();
void printboard(struct Chess *p);
