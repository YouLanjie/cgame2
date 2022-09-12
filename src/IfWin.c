#include "../include/head.h"

int IfWin(int c) {
	int stat = 1;    /* 是否平局 */

	for (int i = 0; i < Max; i++) {
		for (int i2 = 0; i2 < Max; i2++) {
			if (p -> board[i][i2] == computerChess) {
				p->y = i + 3;
				p->x = i2 * 3 + 1;
				if ((i + 4) < Max) {
					if (p -> board[i + 1][i2] == computerChess && p -> board[i + 2][i2] == computerChess && p -> board[i + 3][i2] == computerChess && p -> board[i + 4][i2] == computerChess) {
						p->way = 1;    /* 下 */
						return computerChess;
					}
				}
				if ((i2 + 4) < Max) {
					if (p -> board[i][i2 + 1] == computerChess && p -> board[i][i2 + 2] == computerChess && p -> board[i][i2 + 3] == computerChess && p -> board[i][i2 + 4] == computerChess) {
						p->way = 2;    /* 右 */
						return computerChess;
					}
				}
				if ((i + 4) < Max && (i2 + 4) < Max) {
					if (p -> board[i + 1][i2 + 1] == computerChess && p -> board[i + 2][i2 + 2] == computerChess && p -> board[i + 3][i2 + 3] == computerChess && p -> board[i + 4][i2 + 4] == computerChess) {
						p->way = 3;    /* 右下 */
						return computerChess;
					}
				}
				if ((i + 4) < Max && (i2 - 4) >= 0) {
					if (p -> board[i + 1][i2 - 1] == computerChess && p -> board[i + 2][i2 - 2] == computerChess && p -> board[i + 3][i2 - 3] == computerChess && p -> board[i + 4][i2 - 4] == computerChess) {
						p->way = 4;    /* 左下 */
						return computerChess;
					}
				}
			}
		}
	}

	for (int i = 0; i < Max && stat; i++) {
		for (int i2 = 0; i2 < Max && stat; i2++) {
			if (stat && p->board[i][i2] == 0) {
				stat = 0;
			}
		}
	}
	if (stat) {
		return -1;
	}

	return 0;
}


