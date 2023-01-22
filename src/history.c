#include "../include/head.h"

static void readSave();
static int fnKey(int ch);

static int line = 0;    //数数
static int board[52][52];
static int maxCount = 0;
static FILE * fp;

void History() {
	int chose = 0;    /* 选择 */
	int max = 0;      /* 备份GameInfo->config.max值 */
	int maxLine = 0;  /* 文件的行数 */
	char *cp;

	clear();
	attron(COLOR_PAIR(1));
	for (int i = 0; i < LINES; i++) {
		for (int i2 = 0; i2 < COLS; i2++) {
			mvaddch(i, i2, ' ');
		}
	}
	attroff(COLOR_PAIR(1));
	fp = fopen(GameInfo->config.Save,"rb");
	if (!fp) {
		move(0, 0);
		printw("无法打开存档，请自行确认存档文件是否存在！\n按任意按键返回\n");
		getch();
		return;
	}
	fseek(fp, 0L, 2);
	maxLine = ftell(fp);
	fseek(fp, 0L, 0);
	cp = (char *)malloc(300);
	for (int i = 0; 1; ) {
		if(fgetc(fp) == '\n') {
			i++;
		}
		if (ftell(fp) == maxLine) {
			maxLine = i;
			break;
		}
	}
	free(cp);
	if(maxLine == 0) {
		attron(COLOR_PAIR(1));
		move(0, 0);
		printw("你还没有游戏记录，赶紧去玩一下吧！");
		move(1, 0);
		printw("输入任意按键返回");
		attroff(COLOR_PAIR(1));
		getch();
		return;
	}
	fseek(fp, 0L, 0);
	InitChess();
	max = GameInfo->config.max;
	if (GameInfo->config.newest_history) {
		line = maxLine - 1;    /* 设置自动跳转到最后一行 */
	}
	for (; line + 1 <= maxLine; line++) {
		fseek(fp, 0L, 0);
		readSave();
		GameInfo->chess->way = 0;
		GameInfo->chess->count = 0;
		GameInfo->chess->x = 0;
		GameInfo->chess->y = 0;
		maxCount = 0;
		for (int i = 0; i < GameInfo->config.max; i++) {
			for (int i2 = 0; i2 < GameInfo->config.max; i2++) {
				if (GameInfo->chess->board[i][i2] > maxCount) {
					maxCount = GameInfo->chess->board[i][i2];
				}
			}
		}
		maxCount++;
		GameInfo->chess->count = maxCount;
		IfWin();
		PrintBoard();
		GameInfo->chess->count--;
		hiChess();
		GameInfo->chess->count++;

		attron(COLOR_PAIR(1));
		move(1, 2);
		printw(Time);
		attroff(COLOR_PAIR(1));

		move(GameInfo->config.max + 4, 2);
		attron(COLOR_PAIR(1));
		printw("(%03d/%03d)", line + 1, maxLine);
		mvaddstr(GameInfo->config.max + 4, 23, "wahk上一局，sdjl下一局");
		mvaddstr(GameInfo->config.max + 5, 4, "0q退出，g第一局，G查看最后一局，r查看回放");
		attroff(COLOR_PAIR(1));

		chose = getch();
		chose = fnKey(chose);
		switch (chose) {
			case 0x1B:
			case 0x30:
			case 0x51:
			case 0x71:
				fclose(fp);
				GameInfo->config.max = max;
				free(GameInfo->chess);
				GameInfo->chess = NULL;
				return;
				break;
			case 'w':    /* 上一个 */
			case 'a':
			case 'h':
			case 'k':
				if (line == 0) {
					line = -1;
				}
				else {
					line -= 2;
				}
				break;
			case 's':    /* 下一个 */
			case 'd':
			case 'l':
			case 'j':
				if (line + 1 >= maxLine) {
					line--;
				}
				break;
			case 'g':    /* 第一个 */
				line = -1;
				break;
			case 'G':    /* 最后一个 */
				while (line + 1 < maxLine - 1) {
					line++;
				}
				break;
			case 'r':
				for (int i = 0; i < GameInfo->config.max; i++) {
					for (int i2 = 0; i2 < GameInfo->config.max; i2++) {
						board[i][i2] = GameInfo->chess->board[i][i2];
					}
				}
				GameInfo->chess->count = 2;
				while (chose != 'q' && chose != 'Q' && chose != 0x1B && chose != '0') {
					for (int i = 0; i < GameInfo->config.max; i++) {
						for (int i2 = 0; i2 < GameInfo->config.max; i2++) {
							GameInfo->chess->board[i][i2] = 0;
							if (board[i][i2] <= GameInfo->chess->count - 1) {
								GameInfo->chess->board[i][i2] = board[i][i2];
							}
						}
					}
					PrintBoard();

					attron(COLOR_PAIR(1));
					move(1, 2);
					printw(Time);
					attroff(COLOR_PAIR(1));

					move(GameInfo->config.max + 4, 2);
					attron(COLOR_PAIR(1));
					printw("(%03d/%03d)", GameInfo->chess->count - 1, maxCount - 1);
					mvaddstr(GameInfo->config.max + 4, 24, "您现在正处于回放模式");
					mvaddstr(GameInfo->config.max + 5, 8, "wahk上一步，sdjl下一步。0q退出");
					attroff(COLOR_PAIR(1));

					if (GameInfo->chess->count == maxCount) {
						GameInfo->chess->count--;
						hiChess();
						GameInfo->chess->count++;
					}
					chose = getch();
					chose = fnKey(chose);
					switch (chose) {
					case 'w':    /* 上一个 */
					case 'a':
					case 'h':
					case 'k':
						if (2 < GameInfo->chess->count) {
							GameInfo->chess->count--;
						}
						break;
					case 's':    /* 下一个 */
					case 'd':
					case 'l':
					case 'j':
					case ' ':
					case '\r':
					case '\n':
						if (maxCount > GameInfo->chess->count) {
							GameInfo->chess->count++;
						}
						break;
					case 'g':
						GameInfo->chess->count = 2;
						break;
					case 'G':
						GameInfo->chess->count = maxCount;
						break;
					default:
						break;
					}
				}
				line--;
				break;
			default:
				line--;
				break;
		}
		move(1, 0);
	}
	fclose(fp);
	GameInfo->config.max = max;
	free(GameInfo->chess);
	GameInfo->chess = NULL;
	return;
}

static int fnKey(int ch)
{
	if (ch == 0x1B && ctools_kbhit()) {
		getchar();
		ch = getchar();
		switch (ch) {
		case 'A':
			return 'w';
			break;
		case 'B':
			return 's';
			break;
		case 'C':
			return 'd';
			break;
		case 'D':
			return 'a';
			break;
		default:
			break;
		}
	} else if (ch == 0x1B) {
		return 0x1B;
	}
	return ch;
}


static void readSave()
{
	for (int i = 0; i < GameInfo->config.max; i++) {
		for (int i2 = 0; i2 < GameInfo->config.max; i2++) {
			GameInfo->chess->board[i][i2] = 0;
			board[i][i2] = 0;
		}
	}
	for (int i = 0; i <= line; i++) {
		fscanf(fp, "%d%d%d%d%d%d%d", &GameInfo->chess->t.year, &GameInfo->chess->t.mon, &GameInfo->chess->t.day, &GameInfo->chess->t.hour, &GameInfo->chess->t.min, &GameInfo->chess->t.sec, &GameInfo->config.max);
		for (int i = 0; i < GameInfo->config.max; i++) {
			for (int i2 = 0; i2 < GameInfo->config.max; i2++) {
				fscanf(fp, "%d", &(GameInfo->chess->board[i][i2]));
			}
		}
		if (fgetc(fp) == ' ' && fgetc(fp) != '\n') {
			fseek(fp, -1L, 1);
		}
	}
return;
}

