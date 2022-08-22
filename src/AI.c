#include "../include/head.h"

static int sourceSum(int stat1, int stat2, int count, int spaceNum, int who);
static int getSource(int y, int x, int who);

void AI() {
	int x,           /* 坐标 */
	    y,           /* 是以0为基准的数组坐标 */
	    have = 0,    /* 连成一线的棋子数量 */
	    sourceMapPlayer[Max][Max],
	    sourceMapComputer[Max][Max];
	
	for (y = 0; y < Max; y++) {
		for (x = 0; x < Max; x++) {    /* 配置分数表 */
			/* 为电脑记分 */
			sourceMapComputer[y][x] = 0;
			sourceMapComputer[y][x] = getSource(y, x, computerChess);
			/* 为玩家记分 */
			sourceMapPlayer[y][x] = 0;
			sourceMapPlayer[y][x] = getSource(y, x, playerChess);
		}
	}

	for (int i = 0; i < Max; i++) {    /* 获得最高分 */
		for (int i2 = 0; i2 < Max; i2++) {
			if (sourceMapComputer[i][i2] > have) {
				have = sourceMapComputer[i][i2];    /* 获取分数最高的 */
				y = i;
				x = i2;
			}

			if (sourceMapPlayer[i][i2] > have) {
				have = sourceMapPlayer[i][i2];    /* 获取分数最高的 */
				y = i;
				x = i2;
			}
		}
	}

	if (p -> board[y][x] == spaceChess) {
		p -> board[y][x] = computerChess;
	}
	p -> x = x + 1;
	p -> y = y + 1;
	return;
}

static int getSource(int y, int x, int who) {
	int spaceNum  = 0,               /* 空白数 */
	    count     = 1,               /* 连接数 */
	    had       = 0,               /* 上半侧拥有的同子数量 */
	    y2        = y,               /* 用作备份x与y */
	    x2        = x,               /* 同y2 */
	    stat1     = 0,               /* 棋链一侧的状态 */
	    stat2     = 0,               /* 棋链另一侧的状态 */
	    source[4] = {0, 0, 0, 0};    /* 存储各个方向的分数 */

	if (p -> board[y][x] != spaceChess) {
		return 0;
	}

	/* 横向判断 */
	while (x > 0 && (p -> board[y][x - 1] == spaceChess || p -> board[y][x - 1] == who)) {
		if (p -> board[y][x - 1] == spaceChess && spaceNum < 1) {    /* 第一个空白 */
			if (p -> board[y][x - 2] != who) {    /* 非同色子 */
				stat1 = 1;    /* 设置离开状态为1 */
				break;
			}
			/* 同色   ->  # # */
			/* 空白数加一 */
			spaceNum++;
			/* x轴左移 */
			x--;
		}
		else if (p -> board[y][x - 1] == who) {    /* 同子 -> ## */
			had = 1;    /* 设置同子值为Ture */
			/* x轴左移 */
			x--;
			/* 连接数加一 */
			count++;
		}
		else {    /* 遇挡/空白及以上 -> # / #@ */
			stat1 = 1;
			break;
		}
	}

	//如果左边没有同色子，设置空白数为0
	if (!had) {    /* had == 0 */
		spaceNum = 0;    /* 空白数设置为0 */
	}

	x = x2;    /* 重置x轴值 */

	while (x < Max - 1 && (p -> board[y][x + 1] == spaceChess || p -> board[y][x + 1] == who)) {
		if (p -> board[y][x + 1] == spaceChess && spaceNum < 1) {    /* 第一个空白 */
			if (p -> board[y][x + 2] != who) {    /* 右侧空白后遇挡/空白==结束 */
				stat2 = 1;
				break;
			}
			spaceNum++;
			x++;
		}
		else if (p -> board[y][x + 1] == spaceChess && spaceNum > 0) {    /* 第2个空白 */
			stat2 = 1;
			break;
		}
		else {
			x++;
			count++;
		}
	}
	source[0] = sourceSum(stat1, stat2, count, spaceNum, who);

	/* 竖向判断 */
	stat2 = stat1 = spaceNum = had = 0;
	count = 1;
	x = x2;
	y = y2;
	while (y > 0 && (p -> board[y - 1][x] == spaceChess || p -> board[y - 1][x] == who)) {
		if (p -> board[y - 1][x] == spaceChess && spaceNum < 1) {    /* 第一个空白 */
			if (p -> board[y - 2][x] != who) {    /* 非同色子 */
				stat1 = 1;    /* 设置离开状态为1 */
				break;
			}
			/* 同色   ->  # # */
			/* 空白数加一 */
			spaceNum++;
			/* y轴上移 */
			y--;
		}
		else if (p -> board[y - 1][x] == who) {    /* 同子 -> ## */
			had = 1;    /* 设置同子值为Ture */
			/* y轴上移 */
			y--;
			/* 连接数加一 */
			count++;
		}
		else {    /* 遇挡/空白及以上 -> # / #@ */
			stat1 = 1;
			break;
		}
	}

	//如果左边没有同色子，设置空白数为0
	if (!had) {    /* had == 0 */
		spaceNum = 0;    /* 空白数设置为0 */
	}

	x = x2;    /* 重置x轴值 */
	y = y2;    /* 重置y轴值 */

	while (y < Max - 1 && (p -> board[y + 1][x] == spaceChess || p -> board[y + 1][x] == who)) {
		if (p -> board[y + 1][x] == spaceChess && spaceNum < 1) {    /* 第一个空白 */
			if (p -> board[y + 2][x] != who) {    /* 下侧空白后遇挡/空白==结束 */
				stat2 = 1;
				break;
			}
			spaceNum++;
			y++;
		}
		else if (p -> board[y + 1][x] == spaceChess && spaceNum > 0) {    /* 第2个空白 */
			stat2 = 1;
			break;
		}
		else {
			y++;
			count++;
		}
	}
	source[1] = sourceSum(stat1, stat2, count, spaceNum, who);

	/* 左斜下方向判断 */
	stat2 = stat1 = spaceNum = had = 0;
	count = 1;
	x = x2;
	y = y2;
	while (y < Max - 1 && x > 0 && (p -> board[y + 1][x - 1] == spaceChess || p -> board[y + 1][x - 1] == who)) {
		if (p -> board[y + 1][x - 1] == spaceChess && spaceNum < 1) {    /* 第一个空白 */
			if (p -> board[y + 2][x - 2] != who) {    /* 非同色子 */
				stat1 = 1;    /* 设置离开状态为1 */
				break;
			}
			/* 同色   ->  # # */
			/* 空白数加一 */
			spaceNum++;
			/* x轴左移 */
			x--;
			y++;
		}
		else if (p -> board[y + 1][x - 1] == who) {    /* 同子 -> ## */
			had = 1;    /* 设置同子值为Ture */
			/* x轴左移 */
			x--;
			y++;
			/* 连接数加一 */
			count++;
		}
		else {    /* 遇挡/空白及以上 -> # / #@ */
			stat1 = 1;
			break;
		}
	}

	//如果左边没有同色子，设置空白数为0
	if (!had) {    /* had == 0 */
		spaceNum = 0;    /* 空白数设置为0 */
	}

	x = x2;    /* 重置x轴值 */
	y = y2;    /* 重置y轴值 */

	while (y > 0 && x < Max - 1 && (p -> board[y - 1][x + 1] == spaceChess || p -> board[y - 1][x + 1] == who)) {
		if (p -> board[y - 1][x + 1] == spaceChess && spaceNum < 1) {    /* 第一个空白 */
			if (p -> board[y - 2][x + 2] != who) {
				stat2 = 1;
				break;
			}
			spaceNum++;
			x++;
			y--;
		}
		else if (p -> board[y - 1][x + 1] == spaceChess && spaceNum > 0) {    /* 第2个空白 */
			stat2 = 1;
			break;
		}
		else {
			x++;
			y--;
			count++;
		}
	}
	source[2] = sourceSum(stat1, stat2, count, spaceNum, who);

	/* 右斜下方向判断 */
	stat2 = stat1 = spaceNum = had = 0;
	count = 1;
	x = x2;
	y = y2;
	while (y > 0 && x > 0 && (p -> board[y - 1][x - 1] == spaceChess || p -> board[y - 1][x - 1] == who)) {
		if (p -> board[y - 1][x - 1] == spaceChess && spaceNum < 1) {    /* 第一个空白 */
			if (p -> board[y - 2][x - 2] != who) {    /* 非同色子 */
				stat1 = 1;    /* 设置离开状态为1 */
				break;
			}
			/* 同色   ->  # # */
			/* 空白数加一 */
			spaceNum++;
			/* x轴左移 */
			x--;
			y--;
		}
		else if (p -> board[y - 1][x - 1] == who) {    /* 同子 -> ## */
			had = 1;    /* 设置同子值为Ture */
			/* x轴左移 */
			x--;
			y--;
			/* 连接数加一 */
			count++;
		}
		else {    /* 遇挡/空白及以上 -> # / #@ */
			stat1 = 1;
			break;
		}
	}

	//如果左边没有同色子，设置空白数为0
	if (!had) {    /* had == 0 */
		spaceNum = 0;    /* 空白数设置为0 */
	}

	x = x2;    /* 重置x轴值 */
	y = y2;    /* 重置y轴值 */

	/*  Max:y == 13 与   右侧为空          或  右侧为同色 */
	while (y < Max - 1 && x < Max - 1 && (p -> board[y + 1][x + 1] == spaceChess || p -> board[y + 1][x + 1] == who)) {
		if (p -> board[y + 1][x + 1] == spaceChess && spaceNum < 1) {    /* 第一个空白 */
			if (p -> board[y + 2][x + 2] != who) {    /* 右侧空白后遇挡/空白==结束 */
				stat2 = 1;
				break;
			}
			spaceNum++;
			x++;
			y++;
		}
		else if (p -> board[y + 1][x + 1] == spaceChess && spaceNum > 0) {    /* 第2个空白 */
			stat2 = 1;
			break;
		}
		else {
			x++;
			y++;
			count++;
		}
	}
	source[3] = sourceSum(stat1, stat2, count, spaceNum, who);
	return source[0] + source[1] + source[2] + source[3];
}

static int sourceSum(int stat1, int stat2, int count, int spaceNum, int who) {
	if (count == 1) {
		return 1;
	}
	else if (count == 2) {
		if (stat1 && stat2) { //左右两边都是空的 /* break出的 */
			if (spaceNum == 0) {    /* 空格为0 */
				//电脑60
				/* 电脑黑棋 */
				/*     玩家是否为电脑 返回：是/否 */
				return who == computerChess ? 60 : 50;
			}
			else {
				return who == computerChess ? 40 : 35;
			}
		}
		else if (!stat1 && !stat2) {    /* 没有满足任何条件 */
			return 1;
		}
		else {    /* 只满足了一边 */
			return 10;
		}
	}
	else if (count == 3) {
		if (stat1 && stat2) { //左右两边都是空的
			if (spaceNum == 0) {
				//电脑950
				return who == computerChess ? 950 : 700;
			}
			else {
				return who == computerChess ? 900 : 650;
			}
		}
		else if (!stat1 && !stat2) {
			return 1;
		}
		else {
			return 100;
		}
	}
	else if (count == 4) {
		if (stat1 && stat2) { //左右两边都是空的
			if (spaceNum == 0) {
				return who == computerChess ? 6000 : 3500;
			}
			else {
				return who == computerChess ? 5000 : 3000;
			}
		}
		else if (!stat1 && !stat2) {
			return 1;
		}
		else {
			if (spaceNum == 0) {
				return who == computerChess ? 4000 : 800;
			}
			else {
				return who == computerChess ? 3600 : 750;
			}
		}
	}
	else {
		if (spaceNum == 0) {
			return who == computerChess ? 20000 : 15000;
		}
		else {
			return who == computerChess ? 10000 : 3300;
		}
	}
	return 0;
}

