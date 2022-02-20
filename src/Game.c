#include "../include/head.h"

void Game() {
	int count,count2;      //用于计数
	int error = 0;         //记录错误
	int x = 1,y = 1;       //当前坐标
	int way;               //光标移动方向
	int win  = 0;          //赢家，1黑，2白
	int who = 1;           //现在下子的玩家
	int a = 0;             //是否要使用AI下棋

	fp = fopen(Config, "r");
	fscanf(fp, "%d", &a);
	fclose(fp);
	Clear
	GetTime();
	GetNowTime();
	printf(Time);

	while(win != 1 && win != 2) {
		PrintBoard();
		if (who == 1) {
			printf("黑方下\n");
		}
		else if (who == 2) {
			printf("白方下\n");
		}
		if (error == 1) {
			fontColorSet(1,33);
			gotoxy(20,1);
			printf("你不能下在非空的格子!\n");
			fontColorSet(0,0);
			error = 0;
		}
		if (p -> board[y - 1][x - 1] == 1) {
			gotoxy(y + 2, x * 3 - 1); fontColorSet(30, 47);
			printf(">");
			fontColorSet(0,0);
		}
		else if (p -> board[y - 1][x - 1] == 2) {
			gotoxy(y + 2, x * 3 - 1); fontColorSet(0,1); fontColorSet(37, 40);
			printf(">");
			fontColorSet(0,0);
		}
		else {
			gotoxy(y + 2, x * 3 - 1); fontColorSet(0,1); fontColorSet(37, 40);
			printf(">");
			fontColorSet(0,0);
		}
		way = getch();
		gotoxy(y + 2, x * 3 - 1);
		printf(" ");
		switch (way) {
			case 0x30:
			case 0x51:
			case 0x71:
				Clear
				fontColorSet(1,33);
				printf("请确认退出！本次游戏将不会记录！（Y/n）\n");
				way = getch();
				if (way == 0x59 || way == 0x79) {
					for (count = 0; count < Max ; count++) {
						for (count2= 0; count2 < Max; count2++) {
							p -> board[count][count2] = 0;
						}
					}
					Clear
					return;
				}
				else {
					way = 0x00;
					Clear
				}
				break;
			case 0x1B:
				way = kbhit();
				if (way == 0) {
					way = 0x1B;
				}
				else {
					getchar();
					way = getchar();
				}
				if (way == 0x41) {
					if (y < 2) {
						y = Max;
					}
					else {
						y--;
					}
				}
				else if (way == 0x44) {
					if (x < 2) {
						x = Max;
					}
					else {
						x--;
					}
				}
				else if (way == 0x42) {
					if (y > Max - 1) {
						y = 1;
					}
					else {
						y++;
					}
				}
				else if (way == 0x43) {
					if (x > Max - 1) {
						x = 1;
					}
					else {
						x++;
					}
				}
				else {
					Clear
					fontColorSet(1,33);
					printf("请确认退出！本次游戏将不会记录！（Y/n）\n");
					way = getch();
					if (way == 0x59 || way == 0x79) {
						for (count = 0; count < Max ; count++) {
							for (count2= 0; count2 < Max; count2++) {
								p -> board[count][count2] = 0;
							}
						}
						Clear
						return;
					}
					else {
						way = 0x00;
						Clear
					}
					break;
				}
				break;
			case 0x77:
				if (y < 2) {
					y = Max;
				}
				else {
					y--;
				}
				break;
			case 0x41:
			case 0x61:
				if (x < 2) {
					x = Max;
				}
				else {
					x--;
				}
				break;
			case 0x53:
			case 0x73:
				if (y > Max - 1) {
					y = 1;
				}
				else {
					y++;
				}
				break;
			case 0x44:
			case 0x64:
				if (x > Max - 1) {
					x = 1;
				}
				else {
					x++;
				}
				break;
			case 0x0D:
			case 0x20:
				if (p -> board[y - 1][x - 1] == 1 || p -> board[y - 1][x - 1] == 2) {
					error = 1;
					break;
				}
				else if (p -> board[y - 1][x - 1] == 0) {
					p -> board[y - 1][x - 1] = who;
					p -> who = who;
					p -> x = x;
					p -> y = y;
					win = IfWin(5);
					if (win == who) {
						Clear
						fontColorSet(0,33);
						printf("游戏结束，");
						if (who == 1) {
							printf("黑方");
						}
						else if (who == 2) {
							printf("白方");
						}
						printf("胜利！\n");
						fontColorSet(0,31);
						printf("按Enter返回\n");
						fontColorSet(0,0);
						getch();
					}
					if (a == 1) {
						AI();
					}
					else {
						who = 3 - who;
					}
					break;
				}
				break;
			default:
				Clear
				break;
		}
		printf("\n");
	}
	fp = fopen(Save,"a");
	if (!fp) {
		fontColorSet(1,31);
		perror("[save]");
		fontColorSet(0,0);
		getch();
		return;
	}
	fprintf(fp,Time);
	for (count = 0; count < Max ; count++) {    //打印棋盘到文件
		for (count2= 0; count2 < Max; count2++) {
			fprintf(fp,"%d", p -> board[count][count2]);
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"\n");
	fclose(fp);
	/* 清存 */
	for (count = 0; count < Max ; count++) {
		for (count2= 0; count2 < Max; count2++) {
			p -> board[count][count2] = 0;
		}
	}
	Clear
	return;
}

