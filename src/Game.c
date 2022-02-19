#include "../include/head.h"

void Game() {
	int count,count2;      //用于计数
	int error = 0;         //记录错误
	int x = 1,y = 1;       //当前坐标
	int way;               //光标移动方向
	int win  = 0;          //赢家，1黑，2白
	int who = 1;           //现在下子的玩家
	int a = 0;             //是否要使用AI下棋

	pid_t pid = 1;

	fp = fopen(Config, "r");
	fscanf(fp, "%d", &a);
	fclose(fp);
	Clear
	GetTime();
	GetNowTime();
	printf(NowTime);

	while(win != 1 && win != 2) {
		if (pid == 1) {
			pid = fork();
			if (pid != 0) {
				system("sleep 0.05");
			}
		}
		while (pid == 0) {
			printf("\033[s\033[1;1H");
			kbhitGetchar();
			GetNowTime();
			printf(NowTime);
			printf("\033[u");
			kbhitGetchar();
			sleep(1);
		}
		PrintBoard();
		if (who == 1) {
			printf("%s",LANG[13]);
		}
		else if (who == 2) {
			printf("%s",LANG[14]);
		}
		if (error == 1) {
			printf("%s",LANG[15]);
			error = 0;
		}
		if (p -> board[y - 1][x - 1] == 1) {
			printf("\033[%d;%dH\033[30;47m>\033[0m",y + 2,x * 3 - 1);
		}
		else if (p -> board[y - 1][x - 1] == 2) {
			printf("\033[%d;%dH\033[1;37;40m>\033[0m",y + 2,x * 3 - 1);
		}
		else {
			printf("\033[%d;%dH\033[1;37;40m>\033[0m",y + 2,x * 3 - 1);
		}
		way = getch();
		printf("\033[%d;%dH\033[2m \033[0m",y + 2,x * 3 - 1);
		switch (way) {
			case 0x30:
			case 0x51:
			case 0x71:
				kill(pid,1);
				pid = 1;
				Clear
				printf("%s",LANG[16]);
				way = getch();
				if (way == 0x59 || way == 0x79) {
					for (count = 0; count < Max ; count++) {
						for (count2= 0; count2 < Max; count2++) {
							p -> board[count][count2] = 0;
						}
					}
					Clear
					kill(pid,1);
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
					kill(pid,1);
					pid = 1;
					Clear
					printf("%s",LANG[16]);
					way = getch();
					if (way == 0x59 || way == 0x79) {
						for (count = 0; count < Max ; count++) {
							for (count2= 0; count2 < Max; count2++) {
								p -> board[count][count2] = 0;
							}
						}
						Clear
						kill(pid,1);
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
						kill(pid,1);
						Clear
						printf("%s",LANG[17]);
						if (who == 1) {
							printf("%s",LANG[18]);
						}
						else if (who == 2) {
							printf("%s",LANG[19]);
						}
						printf("%s",LANG[20]);
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
		perror("\033[1;31m[save]\033[0m");
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

