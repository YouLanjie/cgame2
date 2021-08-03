#include "../include/head.h"

void printboard() {
	int count;
	int count2;

	printf("\033[2;1H\033[1;33m-----------------------------------------------\n");
	for (count = 0; count < Max; count++) {    //打印棋盘
		printf("|\033[0m");
		for (count2= 0; count2 < Max; count2++) {
			if (p -> board[count][count2] == 0) {
				printf("\033[37;40;2m + \033[0m");
			}
			else if (p -> board[count][count2] == 1) {
				printf("\033[30;47m @ \033[0m");
			}
			else if (p -> board[count][count2] == 2) {
				printf("\033[37;40m O \033[0m");
			}
		}
		printf("\033[1;33m|\n");
	}
	printf("-----------------------------------------------\033[0m\n");
	return;
}


