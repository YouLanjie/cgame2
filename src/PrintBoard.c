#include "../include/head.h"
#include <curses.h>

void PrintBoard() {
	int count;
	int count2;

	attron(COLOR_PAIR(1));
	move(0, 0);
	for (int i = 0; i < LINES; i++) {
		for (int i2 = 0; i2 < COLS; i2++) {
			mvaddch(i, i2, ' ');
		}
	}
	attroff(COLOR_PAIR(1));

	attron(COLOR_PAIR(8));
	attron(A_BOLD);

	move(0, 0);
	printw(LineLU);
	for (count = 0; count < Max; count++) {
		printw("%s%s%s", LineH, LineH, LineH);
	}
	printw(LineRU);
	mvaddstr(1, Max * 3 + 1, LineV);
	mvaddstr(1, 0, LineV);

	move(2, 0);
	printw(LineLC);
	for (count = 0; count < Max; count++) {
		printw("%s%s%s", LineH, LineH, LineH);
	}
	printw(LineRC);
	attroff(COLOR_PAIR(8));

	for (count = 0; count < Max; count++) {    //打印棋盘
		move(count + 3, 0);
		attron(COLOR_PAIR(8));
		attron(A_BOLD);
		printw(LineV);
		attroff(A_BOLD);
		attroff(COLOR_PAIR(8));
		for (count2= 0; count2 < Max; count2++) {
			if (p -> board2[count][count2] && p->board2[count][count2] == p->count - 1) {
				attron(A_REVERSE);
				attron(A_BOLD);
			}
			if (p -> board[count][count2] == 1) {
				attron(COLOR_PAIR(7));
				if (config[8]) {
					printw("%02d", p -> board2[count][count2]);
				} else if (config[9]) {
					printw("%02d", p -> board[count][count2]);
				} else {
					printw("@@");
				}
				attron(COLOR_PAIR(7));
			} else if (p -> board[count][count2] == 2) {
				attron(COLOR_PAIR(8));
				if (config[8]) {
					printw("%02d", p -> board2[count][count2]);
				} else if (config[9]) {
					printw("%02d", p -> board[count][count2]);
				} else {
					printw("OO");
				}
				attron(COLOR_PAIR(8));
			} else {
				attron(COLOR_PAIR(1));
				if (config[9]) {
					printw("%02d", p -> board2[count][count2]);
				} else {
					printw("::");
				}
				attron(COLOR_PAIR(1));
			} 
			if (p -> board2[count][count2] && p -> board2[count][count2] == p->count - 1) {
				attroff(A_REVERSE);
				attroff(A_BOLD);
			}
			attron(COLOR_PAIR(1));
			printw(" ");
			attroff(COLOR_PAIR(1));
		}
		attron(COLOR_PAIR(8));
		attron(A_BOLD);
		printw(LineV);
		attroff(A_BOLD);
		attroff(COLOR_PAIR(8));
	}

	attron(COLOR_PAIR(8));
	attron(A_BOLD);

	mvaddstr(count + 3, 0, LineLC);
	for (count = 0; count < Max; count++) {
		printw("%s%s%s", LineH, LineH, LineH);
	}
	printw(LineRC);

	mvaddstr(count + 4, 0, LineV);
	for (count = 0; count < Max; count++) {
		printw("   ");
	}
	printw(LineV);

	mvaddstr(count + 5, 0, LineV);
	for (count = 0; count < Max; count++) {
		printw("   ");
	}
	printw(LineV);

	mvaddstr(count + 6, 0, LineLD);
	for (count = 0; count < Max; count++) {
		printw("%s%s%s", LineH, LineH, LineH);
	}
	printw(LineRD);

	attroff(A_BOLD);
	attroff(COLOR_PAIR(8));
	refresh();
	return;
}

