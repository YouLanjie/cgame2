#include "headfile/head.h"                           //导入头文件

int main() {
	int a;
	struct Chess *p;
	
	p = (struct Chess *)malloc(sizeof(struct Chess));
	Clear
	while (a != 0x1B && 0x30 && 0x51 && 0x71) {
		init(p);
		welcome();
		a = input();
		printf("\n\n\n");
		Clear
		switch (a) {
			case 0x1B:
			case 0x30:
			case 0x51:
			case 0x71:
				return 0;
				break;
			case 0x31:
				game(p);
				break;
			case 0x32:
				history(p);
				break;
			case 0x33:
				help();
				break;
			case 0x34:
				other();
				break;
			default:
				puts("\n\t\t\t\t    错误！");
				puts("\t\t\t       按任意按键返回");
				kbhit();
				getchar();
				break;
		}
		Clear
	}
	Clear
	return 0;
}

void init(struct Chess *p) {
	FILE *fp;
	int a = 0;
	char b[5];

	if (access(Save,0) == EOF) {
		fp = fopen(Save,"w");
		fclose(fp);
		p -> count = 0;
		return;
	}
	if (access(Data,0) == EOF) {
		fp = fopen(Data,"w");
		fprintf(fp,"%d\n",p -> count);
		fclose(fp);
	}
	else {
		fp = fopen(Data,"r");
		fscanf(fp,"%s",b);
		a = atoi(b);
		p -> count = a;
		fclose(fp);
	}
	return;
}

void welcome() {
	Clear
	printf("\n                        \033[1;32m游戏菜单\033[0m\n\n\n");
	printf("\033[34m--------------------------------------------------------\n");
	printf("\033[34m|                                                      |\n");
	printf("\033[34m|                                                      |\033[0m\n");
	printf("\033[34m|\033[1;33m         1.开始游戏                2.游戏记录         \033[0;34m|\033[0m\n");
	printf("\033[34m|\033[1;33m         3.游戏帮助                4.更多选项         \033[0;34m|\033[0m\n");
	printf("\033[34m|\033[1;33m         0.退出游戏                                   \033[0;34m|\033[0m\n");
	printf("\033[34m|\033[1;31m  请选择:\033[0m\033[45C\033[34m|\n");
	printf("\033[34m|                                                      |\n");
	printf("--------------------------------------------------------\033[0m\033[2A\033[45D");
	return;
}

void game(struct Chess *p) {
	int count,count2;      //用于计数

	int x = 1,y = 1;       //当前坐标
	int way;               //光标移动方向
	int win  = 0;          //赢家，1黑，2白
	int who = 1;           //现在下子的玩家

	gettime(p);

	while(win != 1 && win != 2) {
		getnowtime(p);
		printf(NowTime);
		printboard(p);
		if(who == 1) {
			printf("黑方下\n");
			printf("\033[%dA\033[%dC\033[31m",18 - y,x * 3 - 1);
			way = input();
			switch (way) {
				case 0x1B:
				case 0x30:
				case 0x51:
				case 0x71:
					Clear
					printf("\033[1;33m请确认退出！（Y/n）\n");
					way = input();
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
					}
					
					break;
				case 0x57:
				case 0x77:
					if (y < 2) {
						y = 15;
						printf("\033[15B");
					}
					else {
						y--;
						printf("\033[1A");
					}
					break;
				case 0x41:
				case 0x61:
					if (x < 2) {
						x = 15;
						printf("\033[15C");
					}
					else {
						x--;
						printf("\033[1D");
					}
					break;
				case 0x53:
				case 0x73:
					if (y > 14) {
						y = 1;
						printf("\033[15A");
					}
					else {
						y++;
						printf("\033[1B");
					}
					break;
				case 0x44:
				case 0x64:
					if (x > 14) {
						x = 1;
						printf("\033[15D");
					}
					else {
						x++;
						printf("\033[1C");
					}
					break;
				case 0x0D:
				case 0x20:
					p -> board[y - 1][x - 1] = 1;
					p -> who = 1;
					p -> x = x;
					p -> y = y;
					win = ifWin(p);
					if (win == who) {
						Clear
						printf("\033[33m游戏结束，黑方胜利！\n\033[31m按Enter返回\n\033[0m");
						input();
					}
					who = 3 - who;
					break;
				default:
					Clear
					break;
			}
		}
		else if (who == 2) {
			printf("白方下\n");
			printf("\033[%dA\033[%dC\033[31m",18 - y,x * 3 - 1);
			way = input();
			switch (way) {
				case 0x1B:
				case 0x30:
				case 0x51:
				case 0x71:
					for (count = 0; count < Max ; count++) {
						for (count2= 0; count2 < Max; count2++) {
							p -> board[count][count2] = 0;
						}
					}
					Clear
					return;
					break;
				case 0x57:
				case 0x77:
					if (y < 2) {
						y = 15;
						printf("\033[15B");
					}
					else {
						y--;
						printf("\033[1A");
					}
					break;
				case 0x41:
				case 0x61:
					if (x < 2) {
						x = 15;
						printf("\033[15C");
					}
					else {
						x--;
						printf("\033[1D");
					}
					break;
				case 0x53:
				case 0x73:
					if (y > 14) {
						y = 1;
						printf("\033[15A");
					}
					else {
						y++;
						printf("\033[1B");
					}
					break;
				case 0x44:
				case 0x64:
					if (x > 14) {
						x = 1;
						printf("\033[15D");
					}
					else {
						x++;
						printf("\033[1C");
					}
					break;
				case 0x0D:
				case 0x20:
					p -> board[y - 1][x - 1] = 2;
					p -> who = 2;
					p -> x = x;
					p -> y = y;
					win = ifWin(p);
					if (win == who) {
						Clear
						printf("\033[33m游戏结束，白方胜利！\n\033[31m按Enter返回\n\033[0m");
						input();
					}
					who = 3 - who;
					break;
				default:
					Clear
					break;
			}
		}
		else {
			return;
		}
		printf("\n");
		Clear
	}
	p -> count += 1;      //局数加一
	save(p);
	Clear
	return;
}

int ifWin(struct Chess *p) {
	int x = 1,y = 1;
	int have = 1;
	int count;

	x = p -> x - 1;
	y = p -> y - 1;

	for (count = 1; count < 6; count++) {         //x轴
		if ((x - (count - 1)) > 0 && p -> board[y][x - count] == p -> who) {
			have++;
		}
		else if (x + 1 < 15 && p -> board[y][x + 1] == p -> who) {
			for (count = 1; count < 6; count++) {
				if (x + count < 15 && p -> board[y][x + count] == p -> who) {
					have++;
				}
				if (have == 5) {
					return p -> who;
				}
			}
		}
		else {
			break;
		}
		if (have == 5) {
			return p -> who;
		}
	}
	for (count = 1; count < 6; count++) {         //y轴
		if ((y - (count - 1)) > 0 && p -> board[y - count][x] == p -> who) {
			have++;
		}
		else if (y + 1 < 15 && p -> board[y + 1][x] == p -> who) {
			for (count = 1; count < 6; count++) {
				if (y + count < 15 && p -> board[y + count][x] == p -> who) {
					have++;
				}
				if (have == 5) {
					return p -> who;
				}
			}
		}
		else {
			break;
		}
		if (have == 5) {
			return p -> who;
		}
	}
	for (count = 1; count < 6; count++) {         //左上右下
		if ((y - (count - 1)) > 0 && (x - (count - 1)) > 0 && p -> board[y - count][x - count] == p -> who) {
			have++;
		}
		else if (y + 1 < 15 && x + 1 < 15 && p -> board[y + 1][x + 1] == p -> who) {
			for (count = 1; count < 6; count++) {
				if (y + count < 15 && x + count < 15 && p -> board[y + count][x + count] == p -> who) {
					have++;
				}
				if (have == 5) {
					return p -> who;
				}
			}
		}
		else {
			break;
		}
		if (have == 5) {
			return p -> who;
		}
	}
	for (count = 1; count < 6; count++) {         //左下右上
		if (y + count < 15 && (x - (count - 1)) > 0 && p -> board[y + count][x - count] == p -> who) {
			have++;
		}
		else if ((y - (count - 1)) > 0 && x + 1 < 15 && p -> board[y + 1][x] == p -> who) {
			for (count = 1; count < 6; count++) {
				if ((y - (count - 1)) > 0 && x + 1 < 15 && p -> board[y - count][x + count] == p -> who) {
					have++;
				}
				if (have == 5) {
					return p -> who;
				}
			}
		}
		else {
			break;
		}
		if (have == 5) {
			return p -> who;
		}
	}
	return 0;
}

void save(struct Chess *p) {
	int count;
	int count2;
	FILE *fp;
	FILE *fp2;

	fp = fopen(Save,"a");
	fp2 = fopen(Data,"w");
	if (!fp && !fp2) {
		printf("无法保存\n按任意按键返回\n");
		input();
		return;
	}
	fprintf(fp2,"%d",p -> count);
	fprintf(fp,Time);
	for (count = 0; count < Max ; count++) {    //打印棋盘到文件
		for (count2= 0; count2 < Max; count2++) {
			if (p -> board[count][count2] == 0) {
				fprintf(fp,"\033[37;40m + \033[0");
			}
			else if (p -> board[count][count2] == 1) {
				fprintf(fp,"\033[30;47m @ \033[0");
			}
			else if (p -> board[count][count2] == 2) {
				fprintf(fp,"\033[37;40m O \033[0");
			}
		}
		fprintf(fp,"\n");
	}
	fclose(fp2);
	fclose(fp);
	for (count = 0; count < Max ; count++) {
		for (count2= 0; count2 < Max; count2++) {
			p -> board[count][count2] = 0;
		}
	}
	return;
}

void history(struct Chess *p) {
	int count;
	int b;
	char a[p -> count * (Max + 1)][212];
	FILE *fp;

	if(p -> count == 0) {
		printf("\033[1;33m你还没有游戏记录，赶紧去玩一下吧！\033[0m\n输入任意按键返回\n");
		input();
		return;
	}
	fp = fopen(Save,"r");
	if (!fp) {
		printf("无法打开存档，请自行确认存档文件是否存在！\n按任意按键返回\n");
		input();
		return;
	}
	for (count = 0; count < 2 + p -> count * (Max + 1); count++) {
		fgets(a[count],sizeof(a),fp);
		if (count != 0 && count % (Max + 1) == 0) {
			printf("\033[1;31m按下W查看上一局，按下S查看下一局，输入数字查看对应局数,0退出\033[0m\n");
			b = input();
			switch (b) {
				case 0x1B:
				case 0x30:
				case 0x51:
				case 0x71:
					return;
					break;
				case 0x57:
				case 0x77:
					if (count == Max +1) {
						Clear
						printf("\033[33m这已经是第一个记录了\n\033[1;31m按下任意键继续\033[0m\n");
						count -= (Max + 1);
						input();
					}
					else {
						count -= 2 * (Max + 1);
					}
					Clear
					break;
				case 0x53:
				case 0x73:
					if ((count + 1) / (Max + 1)== p -> count) {
						Clear
						printf("\033[33m这已经是最后一个记录了\033[1;31m\n按下任意键继续\033[0m\n");
						count -= (Max + 1);
						input();
					}
					Clear
					break;
				default:
					count -= (Max + 1);
					Clear
					break;
			}
		}
		printf("\033[1;33m%s\033[0m",a[count]);
	}
	
	fclose(fp);
	return;
}

void help() {
	puts("\n\t\t\t\033[1;32m游戏帮助\033[33m");
	puts("\t如果想要退出，0、q、Q、Esc都可以哦");
	puts("\tW S A D控制上下左右，空格下子");
	printf("\033[1;31m按任意按键返回：\033[0m");
	input();
	return;
}

void other() {
	FILE *fp,*fp2;
	int a;

	printf("\n                        \033[1;32m其他选项\033[0m\n\n\n");
	printf("\033[34m--------------------------------------------------------\n");
	printf("\033[34m|                                                      |\033[0m\n");
	printf("\033[34m|                                                      |\033[0m\n");
	printf("\033[34m|\033[1;33m         1.清除存档                0.返回菜单         \033[0;34m|\033[0m\n");
	printf("\033[34m|                                                      |\033[0m\n");
	printf("\033[34m|                                                      |\033[0m\n");
	printf("\033[34m|\033[1;31m  请选择:\033[0m\033[45C\033[34m|\n");
	printf("\033[34m|                                                      |\n");
	printf("--------------------------------------------------------\033[0m\033[2A\033[45D");
	a = input();
	if(a == 0x1B || a == 0x30 || a == 0x51 || a == 0x71) {
		return;
	}
	else if(a == 0x31) {
		fp = fopen(Data,"w");
		fp2 = fopen(Save,"w");
		if(!fp && !fp2) {
			printf("\033[1;31m无法打开存档\n按任意按键返回：\033[0m");
			input();
			return;
		}
		else {
			fprintf(fp,"0");
			fclose(fp);
			fclose(fp2);
			Clear
			printf("\033[1;33m清除成功\n\033[1;31m按任意按键返回：\033[0m");
			input();
		}
	}
	else {
		return;
	}
	return;
}

void printboard(struct Chess *p) {
	int count;
	int count2;

	printf("\033[1;33m-----------------------------------------------\n");
	for (count = 0; count < Max; count++) {    //打印棋盘
		printf("|\033[0m");
		for (count2= 0; count2 < Max; count2++) {
			if (p -> board[count][count2] == 0) {
				printf("\033[37;40m + \033[0");
			}
			else if (p -> board[count][count2] == 1) {
				printf("\033[30;47m @ \033[0");
			}
			else if (p -> board[count][count2] == 2) {
				printf("\033[37;40m O \033[0");
			}
		}
		printf("\033[1;33m|\n");
	}
	printf("-----------------------------------------------\033[0m\n");
	return;
}

void gettime(struct Chess *p) {
	time_t timep;
	struct tm *tp;

	time(&timep);
	tp=gmtime(&timep);

	p -> t.year = 1900+tp->tm_year;
	p -> t.mon = 1+tp->tm_mon;
	p -> t.day = tp->tm_mday;
	p -> t.hour = 8 + tp->tm_hour;
	p -> t.min = tp->tm_min;
	p -> t.sec = tp->tm_sec;
	return;
}

void getnowtime(struct Chess *p) {
	time_t timep;
	struct tm *tp;

	time(&timep);
	tp=gmtime(&timep);

	p -> nt.year = 1900+tp->tm_year;
	p -> nt.mon = 1+tp->tm_mon;
	p -> nt.day = tp->tm_mday;
	p -> nt.hour = 8 + tp->tm_hour;
	p -> nt.min = tp->tm_min;
	p -> nt.sec = tp->tm_sec;
	return;
}
