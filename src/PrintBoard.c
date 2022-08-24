#include "../include/head.h"
#include <stdio.h>

void PrintBoard() {
	int count;
	int count2;

	fontColorSet(37, 44);
	Clear

	fontColorSet(0, 1);
	fontColorSet(37, 44);
	gotoxy(1, 1);
	printf(LineLU);
	for (count = 0; count < Max; count++) {
		printf("%s%s%s", LineH, LineH, LineH);
	}
	printf(LineRU);
	gotoxy(2, Max * 3 + 2);
	printf(LineV);
	gotoxy(2, 1);
	printf(LineV);

	gotoxy(3, 1);
	printf(LineLC);
	for (count = 0; count < Max; count++) {
		printf("%s%s%s", LineH, LineH, LineH);
	}
	printf(LineRC);

	for (count = 0; count < Max; count++) {    //打印棋盘
		gotoxy(count + 4, 1);
		fontColorSet(0, 1);
		fontColorSet(37, 44);
		printf(LineV);
		fontColorSet(0, 0);
		for (count2= 0; count2 < Max; count2++) {
			fontColorSet(37,44);
			printf(" ");
			if (p -> board[count][count2] == 0) {
				fontColorSet(37,44);
				printf("::");
			}
			else if (p -> board[count][count2] == 1) {
				fontColorSet(30,44);
				printf("@@");
			}
			else if (p -> board[count][count2] == 2) {
					fontColorSet(37,44);
					printf("OO");
			}
		}
		fontColorSet(0, 1);
		fontColorSet(37, 44);
		printf(LineV);
		fontColorSet(0, 0);
	}

	fontColorSet(0, 1);
	fontColorSet(37, 44);

	gotoxy(count + 4, 1);
	printf(LineLC);
	for (count = 0; count < Max; count++) {
		printf("%s%s%s", LineH, LineH, LineH);
	}
	printf(LineRC);

	gotoxy(count + 5, 1);
	printf(LineV);
	for (count = 0; count < Max; count++) {
		printf("   ");
	}
	printf(LineV);

	gotoxy(count + 6, 1);
	printf(LineV);
	for (count = 0; count < Max; count++) {
		printf("   ");
	}
	printf(LineV);

	gotoxy(count + 7, 1);
	printf(LineLD);
	for (count = 0; count < Max; count++) {
		printf("%s%s%s", LineH, LineH, LineH);
	}
	printf(LineRD);

	fontColorSet(0, 0);
	kbhitGetchar();
	return;
}

