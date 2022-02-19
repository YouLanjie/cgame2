#include "../include/head.h"

void PrintBoard() {
	int count;
	int count2;

	gotoxy(2,1);
	fontColorSet(1,33);
	printf("-");
	for (count = 0; count < Max; count++) {
		printf("---");
	}
	printf("-\n");
	fontColorSet(1,33);
	kbhitGetchar();
	for (count = 0; count < Max; count++) {    //打印棋盘
		fontColorSet(1,33); printf("|"); fontColorSet(0,0);
		for (count2= 0; count2 < Max; count2++) {
			if (p -> board[count][count2] == 0) {
				fontColorSet(0,2); fontColorSet(37,40);
				printf(" + ");
				fontColorSet(0,0);
			}
			else if (p -> board[count][count2] == 1) {
				fontColorSet(0,2); fontColorSet(30,47);
				printf(" @ ");
				fontColorSet(0,0);
			}
			else if (p -> board[count][count2] == 2) {
				fontColorSet(0,2); fontColorSet(37,40);
				printf(" O ");
				fontColorSet(0,0);
			}
		}
		fontColorSet(1,33); printf("|"); fontColorSet(0,0);
	}
	fontColorSet(1,33);
	for (count = 0; count < Max; count++) {
		printf("---");
	}
	printf("--\n");
	fontColorSet(0,0);
	kbhitGetchar();
	return;
}

