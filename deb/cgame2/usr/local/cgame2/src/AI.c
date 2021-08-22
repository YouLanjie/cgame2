#include "../include/head.h"

void AI() {
	int x,y; /* 坐标 */
	int have = 1; /* 连成一线的棋子数量 */

	x = p -> x - 1;
	y = p -> y - 1;

	for (int count = 1; count < 3; count++) {         //x轴
		if (x - count > -1 && p -> board[y][x - count] == p -> who) {
			have++;
		}
		if (x + count < Max && p -> board[y][x + count] == p -> who) {
			have++;
		}
		for (int count = 1; have > 2 && x + count < Max ; count++) {
			if (p -> board[y][x + count] == 0) {
				p -> board[y][x + count] = 3 - p -> who;
				return;
			}
		}
		for (int count = 1; have > 2 && x - count > -1 ; count++) {
			if (p -> board[y][x - count] == 0) {
				p -> board[y][x - count] = 3 - p -> who;
				return;
			}
		}
	}
	have = 1;
	for (int count = 1; count < 3; count++) {         //y轴
		if ((y - count) > -1 && p -> board[y - count][x] == p -> who) {
			have++;
		}
		if (y + count < Max && p -> board[y + count][x] == p -> who) {
			have++;
		}
		for (int count = 1; have > 2 && y + count < Max ; count++) {
			if (p -> board[y + count][x] == 0) {
				p -> board[y + count][x] = 3 - p -> who;
				return;
			}
		}
		for (int count = 1; have > 2 && y - count > -1 ; count++) {
			if (p -> board[y - count][x] == 0) {
				p -> board[y - count][x] = 3 - p -> who;
				return;
			}
		}
	}
	have = 1;
	for (int count = 1; count < 3; count++) {         //左上右下
		if (y - count > -1 && x - count > -1 && p -> board[y - count][x - count] == p -> who) {
			have++;
		}
		if (y + count < Max && x + count < 15 && p -> board[y + count][x + count] == p -> who) {
			have++;
		}
		for (int count = 1; have > 2 && y + count < Max && x + count < 15 ; count++) {
			if (p -> board[y + count][x + count] == 0) {
				p -> board[y + count][x + count] = 3 - p -> who;
				return;
			}
		}
		for (int count = 1; have > 2 && y - count > -1 && x - count > -1 ; count++) {
			if (p -> board[y - 1][x - 1] == 0) {
				p -> board[y - count][x - count] = 3 - p -> who;
				return;
			}
		}
	}
	have = 1;
	for (int count = 1; count < 3; count++) {         //左下右上
		if (y + count < Max && x - count > -1 && p -> board[y + count][x - count] == p -> who) {
			have++;
		}
		if (y - count > -1 && x + 1 < Max && p -> board[y - count][x + count] == p -> who) {
			have++;
		}
		for(int count = 1; have > 2 && y - count > -1 && x + count < Max ; count++) {
			if (p -> board[y - count][x + count] == 0) {
				p -> board[y - count][x + count] = 3 - p -> who;
				return;
			}
		}
		for(int count = 1; have > 2 && y + count < Max && x - count > -1 ; count++) {
			if (p -> board[y + count][x - count] == 0) {
				p -> board[y + count][x - count] = 3 - p -> who;
				return;
			}
		}
	}
	for(int count = 1;count < 3; count++) {
		int i;

		i = rand() % 4 + 1;
		if (i == 1 && x > 0 && p -> board[y][x - 1] == 0) {
			p -> board[y][x - 1] = 3 - p -> who;
			return;
		}
		else if (i == 2 && x < 14 && p -> board[y][x + 1] == 0) {
			p -> board[y][x + 1] = 3 - p -> who;
			return;
		}
		else if (i == 3 && y < 14 && p -> board[y + 1][x] == 0) {
			p -> board[y + 1][x] = 3 - p -> who;
			return;
		}
		else if (i == 4 && y > 0 && p -> board[y - 1][x] == 0) {
			p -> board[y - 1][x] = 3 - p -> who;
			return;
		}
		y = rand() % 14;
		y = rand() % 14;
	}
	
	return;
}

