#include <stdio.h>                           //标准库
#include <stdlib.h>                          //system();srand();rand();malloc();free();
#include <string.h>                          //strcmp();
#include <unistd.h>

#include "kbhit_input.h"

#define Clear system("clear");
#define Max 15

struct Chess
{
	int board[Max][Max];
	int count;
};

void init();
void welcome();
void game(int *count);
void save(struct Chess *p,int Count);
void history();
void help();
void printboard(struct Chess *p);
