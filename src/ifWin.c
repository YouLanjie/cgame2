#include "../include/head.h"

/* 判断输赢
 * 返回值码：
 * 1 黑方胜
 * 2 白方胜利
 * 3 平局
 */
int IfWin() {
	int stat = 1;    /* 是否平局 */

	for (int i = 1; i <= GameInfo->config.max; i++) {
		for (int i2 = 1; i2 <= GameInfo->config.max; i2++) {
			if (GetChessPlayer(i, i2) == blackChess) {
				if ((i + 4) < GameInfo->config.max) {
					if (GetChessPlayer(i + 1, i2) == blackChess && GetChessPlayer(i + 2, i2) == blackChess && GetChessPlayer(i + 3, i2) == blackChess && GetChessPlayer(i + 4, i2) == blackChess) {
						GameInfo->chess->y = i;
						GameInfo->chess->x = i2;
						GameInfo->chess->way = 1;    /* 下 */
						return blackChess;
					}
				}
				if ((i2 + 4) < GameInfo->config.max) {
					if (GetChessPlayer(i, i2 + 1) == blackChess && GetChessPlayer(i, i2 + 2) == blackChess && GetChessPlayer(i, i2 + 3) == blackChess && GetChessPlayer(i, i2 + 4) == blackChess) {
						GameInfo->chess->y = i;
						GameInfo->chess->x = i2;
						GameInfo->chess->way = 2;    /* 右 */
						return blackChess;
					}
				}
				if ((i + 4) < GameInfo->config.max && (i2 + 4) < GameInfo->config.max) {
					if (GetChessPlayer(i + 1, i2 + 1) == blackChess && GetChessPlayer(i + 2, i2 + 2) == blackChess && GetChessPlayer(i + 3, i2 + 3) == blackChess && GetChessPlayer(i + 4, i2 + 4) == blackChess) {
						GameInfo->chess->y = i;
						GameInfo->chess->x = i2;
						GameInfo->chess->way = 3;    /* 右下 */
						return blackChess;
					}
				}
				if ((i + 4) < GameInfo->config.max && (i2 - 4) >= 0) {
					if (GetChessPlayer(i + 1, i2 - 1) == blackChess && GetChessPlayer(i + 2, i2 - 2) == blackChess && GetChessPlayer(i + 3, i2 - 3) == blackChess && GetChessPlayer(i + 4, i2 - 4) == blackChess) {
						GameInfo->chess->y = i;
						GameInfo->chess->x = i2;
						GameInfo->chess->way = 4;    /* 左下 */
						return blackChess;
					}
				}
			} else if (GetChessPlayer(i, i2) == whiteChess) {
				if ((i + 4) < GameInfo->config.max) {
					if (GetChessPlayer(i + 1, i2) == whiteChess && GetChessPlayer(i + 2, i2) == whiteChess && GetChessPlayer(i + 3, i2) == whiteChess && GetChessPlayer(i + 4, i2) == whiteChess) {
						GameInfo->chess->y = i;
						GameInfo->chess->x = i2;
						GameInfo->chess->way = 1;    /* 下 */
						return whiteChess;
					}
				}
				if ((i2 + 4) < GameInfo->config.max) {
					if (GetChessPlayer(i, i2 + 1) == whiteChess && GetChessPlayer(i, i2 + 2) == whiteChess && GetChessPlayer(i, i2 + 3) == whiteChess && GetChessPlayer(i, i2 + 4) == whiteChess) {
						GameInfo->chess->y = i;
						GameInfo->chess->x = i2;
						GameInfo->chess->way = 2;    /* 右 */
						return whiteChess;
					}
				}
				if ((i + 4) < GameInfo->config.max && (i2 + 4) < GameInfo->config.max) {
					if (GetChessPlayer(i + 1, i2 + 1) == whiteChess && GetChessPlayer(i + 2, i2 + 2) == whiteChess && GetChessPlayer(i + 3, i2 + 3) == whiteChess && GetChessPlayer(i + 4, i2 + 4) == whiteChess) {
						GameInfo->chess->y = i;
						GameInfo->chess->x = i2;
						GameInfo->chess->way = 3;    /* 右下 */
						return whiteChess;
					}
				}
				if ((i + 4) < GameInfo->config.max && (i2 - 4) >= 0) {
					if (GetChessPlayer(i + 1, i2 - 1) == whiteChess && GetChessPlayer(i + 2, i2 - 2) == whiteChess && GetChessPlayer(i + 3, i2 - 3) == whiteChess && GetChessPlayer(i + 4, i2 - 4) == whiteChess) {
						GameInfo->chess->y = i;
						GameInfo->chess->x = i2;
						GameInfo->chess->way = 4;    /* 左下 */
						return whiteChess;
					}
				}
			}
		}
	}

	for (int i = 0; i < GameInfo->config.max && stat; i++) {
		for (int i2 = 0; i2 < GameInfo->config.max && stat; i2++) {
			if (stat && GetChessPlayer(i + 1, i2 + 1) == spaceChess) {
				stat = 0;
			}
		}
	}
	if (stat) {
		return 3;
	}

	return 0;
}


