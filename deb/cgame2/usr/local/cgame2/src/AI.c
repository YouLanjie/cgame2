#include "../include/head.h"

void AI() {
	int x,y;
	int have = 1;

	x = p -> x - 1;
	y = p -> y - 1;

	for (int count = 1; count < 4; count++) {         //x轴
		if (x - count > -1 && p -> board[y][x - count] == p -> who) {
			have++;
		}
		if (x + count < 15 && p -> board[y][x + count] == p -> who) {
			have++;
		}
		for (int count = 1; have > 2 && x + count < 15 && p -> board[y][x + count] == 0 && p -> board[y][x + count] != p -> who; count++) {
			p -> board[y][x + count] = 3 - p -> who;
			return;
		}
		for (int count = 1; have > 2 && x - count > -1 && p -> board[y][x - count] == 0 && p -> board[y][x - count] != p -> who; count++) {
			p -> board[y][x - count] = 3 - p -> who;
			return;
		}
	}
	have = 1;
	for (int count = 1; count < 4; count++) {         //y轴
		if ((y - count) > -1 && p -> board[y - count][x] == p -> who) {
			have++;
		}
		if (y + count < 15 && p -> board[y + count][x] == p -> who) {
			have++;
		}
		for (int count = 1; have > 2 && y + count < 15 && p -> board[y + count][x] == 0 && p -> board[y + count][x] != p -> who; count++) {
			p -> board[y + count][x] = 3 - p -> who;
			return;
		}
		for (int count = 1; have > 2 && y - count > -1 && p -> board[y - count][x] == 0 && p -> board[y - count][x] != p -> who; count++) {
			p -> board[y - count][x] = 3 - p -> who;
			return;
		}
	}
	have = 1;
	for (int count = 1; count < 4; count++) {         //左上右下
		if (y - count > -1 && x - count > -1 && p -> board[y - count][x - count] == p -> who) {
			have++;
		}
		if (y + count < 15 && x + count < 15 && p -> board[y + count][x + count] == p -> who) {
			have++;
		}
		for (int count = 1; have > 2 && y + count < 15 && x + count < 15 && p -> board[y + count][x + count] == 0; count++) {
			p -> board[y + count][x + count] = 3 - p -> who;
			return;
		}
		for (int count = 1; have > 2 && y - count > -1 && x - count > -1 && p -> board[y - 1][x - 1] == 0; count++) {
			p -> board[y - count][x - count] = 3 - p -> who;
			return;
		}
	}
	have = 1;
	for (int count = 1; count < 4; count++) {         //左下右上
		if (y + count < 15 && x - count > -1 && p -> board[y + count][x - count] == p -> who) {
			have++;
		}
		if (y - count > -1 && x + 1 < 15 && p -> board[y - count][x + count] == p -> who) {
			have++;
		}
		for(int count = 1; have > 2 && y - count > -1 && x + count < 15 && p -> board[y - count][x + count] == 0; count++) {
			p -> board[y - count][x + count] = 3 - p -> who;
			return;
		}
		for(int count = 1; have > 2 && y + count < 15 && x - count > -1 && p -> board[y + count][x - count] == 0; count++) {
			p -> board[y + count][x - count] = 3 - p -> who;
			return;
		}
	}
	for(int count = 1;count < 3; count++) {
		int i;
		i = rand() % 5 + 1;
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
	}
	
	return;
}

