#include "../include/head.h"

int IfWin(int c) {
	int x = 1,y = 1;
	int have = 1;
	int count;

	x = p -> x - 1;
	y = p -> y - 1;

	for (count = 1; count < c; count++) {         //x轴
		if (x - count > -1 && p -> board[y][x - count] == p -> who) {
			have++;
		}
		if (x + count < 15 && p -> board[y][x + count] == p -> who) {
			have++;
		}
		if (have == c) {
			return p -> who;
		}
	}
	have = 1;
	for (count = 1; count < c; count++) {         //y轴
		if (y - count > -1 && p -> board[y - count][x] == p -> who) {
			have++;
		}
		if (y + count < 15 && p -> board[y + count][x] == p -> who) {
			have++;
		}
		if (have == c) {
			return p -> who;
		}
	}
	have = 1;
	for (count = 1; count < c; count++) {         //左上右下
		if (y - count > -1 && x - count > -1 && p -> board[y - count][x - count] == p -> who) {
			have++;
		}
		if (y + count < 15 && x + count < 15 && p -> board[y + count][x + count] == p -> who) {
			have++;
		}
		if (have == c) {
			return p -> who;
		}
	}
	have = 1;
	for (count = 1; count < c; count++) {         //左下右上
		if (y + count < 15 && x - count > -1 && p -> board[y + count][x - count] == p -> who) {
			have++;
		}
		if (y - count > -1 && x + 1 < 15 && p -> board[y - count][x + count] == p -> who) {
			have++;
		}
		if (have == c) {
			return p -> who;
		}
	}
	return 0;
}


