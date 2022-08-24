#include "../include/head.h"

int IfWin(int c) {
	for (int i = 0; i < Max; i++) {
		for (int i2 = 0; i2 < Max; i2++) {
			if (p -> board[i][i2] == computerChess) {
				if ((i + 4) < Max) {
					if (p -> board[i + 1][i2] == computerChess && p -> board[i + 2][i2] == computerChess && p -> board[i + 3][i2] == computerChess && p -> board[i + 4][i2] == computerChess) {
						return computerChess;
					}
				}
				if ((i2 + 4) < Max) {
					if (p -> board[i][i2 + 1] == computerChess && p -> board[i][i2 + 2] == computerChess && p -> board[i][i2 + 3] == computerChess && p -> board[i][i2 + 4] == computerChess) {
						return computerChess;
					}
				}
				if ((i + 4) < Max && (i2 + 4) < Max) {
					if (p -> board[i + 1][i2 + 1] == computerChess && p -> board[i + 2][i2 + 2] == computerChess && p -> board[i + 3][i2 + 3] == computerChess && p -> board[i + 4][i2 + 4] == computerChess) {
						return computerChess;
					}
				}
				if ((i + 4) < Max && (i2 - 4) >= 0) {
					if (p -> board[i + 1][i2 - 1] == computerChess && p -> board[i + 2][i2 - 2] == computerChess && p -> board[i + 3][i2 - 3] == computerChess && p -> board[i + 4][i2 - 4] == computerChess) {
						return computerChess;
					}
				}
			}
		}
	}
	return 0;
}

