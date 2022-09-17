#include "../include/head.h"

int IfWin() {
	int stat = 1;    /* 是否平局 */

	for (int i = 1; i <= GameInfo->config.max; i++) {
		for (int i2 = 1; i2 <= GameInfo->config.max; i2++) {
			if (GetChessPlayer(i, i2) == myChess) {
				if ((i + 4) < GameInfo->config.max) {
					if (GetChessPlayer(i + 1, i2) == myChess && GetChessPlayer(i + 2, i2) == myChess && GetChessPlayer(i + 3, i2) == myChess && GetChessPlayer(i + 4, i2) == myChess) {
						GameInfo->chess->y = i;
						GameInfo->chess->x = i2;
						GameInfo->chess->way = 1;    /* 下 */
						return myChess;
					}
				}
				if ((i2 + 4) < GameInfo->config.max) {
					if (GetChessPlayer(i, i2 + 1) == myChess && GetChessPlayer(i, i2 + 2) == myChess && GetChessPlayer(i, i2 + 3) == myChess && GetChessPlayer(i, i2 + 4) == myChess) {
						GameInfo->chess->y = i;
						GameInfo->chess->x = i2;
						GameInfo->chess->way = 2;    /* 右 */
						return myChess;
					}
				}
				if ((i + 4) < GameInfo->config.max && (i2 + 4) < GameInfo->config.max) {
					if (GetChessPlayer(i + 1, i2 + 1) == myChess && GetChessPlayer(i + 2, i2 + 2) == myChess && GetChessPlayer(i + 3, i2 + 3) == myChess && GetChessPlayer(i + 4, i2 + 4) == myChess) {
						GameInfo->chess->y = i;
						GameInfo->chess->x = i2;
						GameInfo->chess->way = 3;    /* 右下 */
						return myChess;
					}
				}
				if ((i + 4) < GameInfo->config.max && (i2 - 4) >= 0) {
					if (GetChessPlayer(i + 1, i2 - 1) == myChess && GetChessPlayer(i + 2, i2 - 2) == myChess && GetChessPlayer(i + 3, i2 - 3) == myChess && GetChessPlayer(i + 4, i2 - 4) == myChess) {
						GameInfo->chess->y = i;
						GameInfo->chess->x = i2;
						GameInfo->chess->way = 4;    /* 左下 */
						return myChess;
					}
				}
			}
		}
	}

	for (int i = 0; i < GameInfo->config.max && stat; i++) {
		for (int i2 = 0; i2 < GameInfo->config.max && stat; i2++) {
			if (stat && GetChessPlayer(i, i2) == 0) {
				stat = 0;
			}
		}
	}
	if (stat) {
		return -1;
	}

	return 0;
}


