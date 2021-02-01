#include <stdio.h>                           //标准库
#include <stdlib.h>                          //system();srand();rand();malloc();free();
#include <string.h>                          //strcmp();

#include "kbhit_input.h"

#define Clear system("clear");
#define Max 15

struct Chess
{
	int board[Max][Max];
	int count;
};

void welcome();
void game();
void help();
void printboard();
