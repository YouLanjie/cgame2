#include "headfile/head.h"                           //导入头文件

int main(int argc,char * argv[]) {
	int a;
	int b;
	struct Chess *p;

	printf("\033[?25l");
	p = (struct Chess *)malloc(sizeof(struct Chess));
	Clear2
	init(p);
	if (b == 1) {
		free(p);
		Clear2
		printf("\033[?25h");
		return 0;
	}
	while (a != 0x1B && a != 0x30 && a != 0x51 && a != 0x71) {
		init(p);
		if (b == 1) {
			free(p);
			Clear2
			printf("\033[?25h");
			return 0;
		}
		welcome();
		a = input();
		printf("\n\n\n\n");
		Clear2
		switch (a) {
			case 0x1B:
			case 0x30:
			case 0x51:
			case 0x71:
				free(p);
				printf("\033[?25h");
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
				break;
		}
		Clear2
	}
	free(p);
	Clear2
	printf("\033[?25h");
	return 0;
}

void init(struct Chess *p) {
	FILE *fp;
	int a = 0;            //保存转换后的数字
	int c = 0;            //语言选择的结果
	int count = 0;
	int If = 0;
	char d[5];            //查看语言
	char b[5];            //转换前的字符

	if(access(Save,0) == EOF) {
		fp = fopen(Save,"w");
		fclose(fp);
		p -> count = 0;
		return;
	}
	if(access(Data,0) == EOF) {
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
	menu("Game Menu");
	printf("\033[8;11H\033[1;33m1.Start the game\033[8;37H2.Game record");
	printf("\033[9;11H3.Game help\033[9;37H4.Other options");
	printf("\033[10;11H0.Exit the game");
	Menu
	return;
}

void game(struct Chess *p) {
	int count,count2;      //用于计数

	int x = 1,y = 1;       //当前坐标
	int way;               //光标移动方向
	int win  = 0;          //赢家，1黑，2白
	int who = 1;           //现在下子的玩家

	int a = 0;

	Clear
	printf("Play with AI?(Y/n)\n");
	way = input();
	if (way == 0x59 || way == 0x79) {
		a = 1;
	}
	else {
		a = 0;
	}
	Clear

	gettime(p);

	while(win != 1 && win != 2) {
		getnowtime(p);
		printf(NowTime);
		printboard(p);
		if (who == 1) {
			printf("Now:black play chess\n");
		}
		else if (who == 2) {
			printf("Now:white play chess\n");
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
		way = input();
		printf("\033[%d;%dH\033[2m \033[0m",y + 2,x * 3 - 1);
		switch (way) {
			case 0x30:
			case 0x51:
			case 0x71:
				Clear
				printf("\033[1;33mPlease confirm your exit!This round will not be saved!(Y/n)\n");
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
			case 0x1B:
				way = kbhit_if();
				if (way == 0) {
					way = 0x1B;
				}
				else {
					getchar();
					way = getchar();
				}
				if (way == 0x41) {
					if (y < 2) {
						y = 15;
					}
					else {
						y--;
					}
				}
				else if (way == 0x44) {
					if (x < 2) {
						x = 15;
					}
					else {
						x--;
					}
				}
				else if (way == 0x42) {
					if (y > 14) {
						y = 1;
					}
					else {
						y++;
					}
				}
				else if (way == 0x43) {
					if (x > 14) {
						x = 1;
					}
					else {
						x++;
					}
				}
				else {
					Clear
					printf("\033[1;33mPlease confirm your exit!This round will not be saved!(Y/n)\n");
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
				}
				break;
			case 0x77:
				if (y < 2) {
					y = 15;
				}
				else {
					y--;
				}
				break;
			case 0x41:
			case 0x61:
				if (x < 2) {
					x = 15;
				}
				else {
					x--;
				}
				break;
			case 0x53:
			case 0x73:
				if (y > 14) {
					y = 1;
				}
				else {
					y++;
				}
				break;
			case 0x44:
			case 0x64:
				if (x > 14) {
					x = 1;
				}
				else {
					x++;
				}
				break;
			case 0x0D:
			case 0x20:
				if (p -> board[y - 1][x - 1] == 1 || p -> board[y - 1][x - 1] == 2) {
					break;
				}
				else if (p -> board[y - 1][x - 1] == 0) {
					p -> board[y - 1][x - 1] = who;
					p -> who = who;
					p -> x = x;
					p -> y = y;
					win = ifWin(p);
					if (win == who) {
						Clear
						printf("\033[33mThe game is over and the ");
						if (who == 1) {
							printf("Blacks");
						}
						else if (who == 2) {
							printf("White");
						}
						printf(" wins！\n\033[31mPress enter to return:\n\033[0m");
						input();
					}
					if (a == 1) {
						AI(p);
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
		Clear
	}
	p -> count += 1;      //局数加一
	save(p);
	Clear
	return;
}

void AI(struct Chess *p) {
	int x,y;
	int have = 1;

	x = p -> x - 1;
	y = p -> y - 1;

	for (int count = 1; count < 4; count++) {         //x轴
		if (x - count > -1 && p -> board[y][x - count] == p -> who) {
			have++;
		}
		if (x + count < 15 && p -> board[y][x + count] == p -> who) {
			have++;
		}
		for (int count = 1; have > 2 && x + count < 15 && p -> board[y][x + count] == 0 && p -> board[y][x + count] != p -> who; count++) {
			p -> board[y][x + count] = 3 - p -> who;
			return;
		}
		for (int count = 1; have > 2 && x - count > -1 && p -> board[y][x - count] == 0 && p -> board[y][x - count] != p -> who; count++) {
			p -> board[y][x - count] = 3 - p -> who;
			return;
		}
	}
	have = 1;
	for (int count = 1; count < 4; count++) {         //y轴
		if ((y - count) > -1 && p -> board[y - count][x] == p -> who) {
			have++;
		}
		if (y + count < 15 && p -> board[y + count][x] == p -> who) {
			have++;
		}
		for (int count = 1; have > 2 && y + count < 15 && p -> board[y + count][x] == 0 && p -> board[y + count][x] != p -> who; count++) {
			p -> board[y + count][x] = 3 - p -> who;
			return;
		}
		for (int count = 1; have > 2 && y - count > -1 && p -> board[y - count][x] == 0 && p -> board[y - count][x] != p -> who; count++) {
			p -> board[y - count][x] = 3 - p -> who;
			return;
		}
	}
	have = 1;
	for (int count = 1; count < 4; count++) {         //左上右下
		if (y - count > -1 && x - count > -1 && p -> board[y - count][x - count] == p -> who) {
			have++;
		}
		if (y + count < 15 && x + count < 15 && p -> board[y + count][x + count] == p -> who) {
			have++;
		}
		for (int count = 1; have > 2 && y + count < 15 && x + count < 15 && p -> board[y + count][x + count] == 0; count++) {
			p -> board[y + count][x + count] = 3 - p -> who;
			return;
		}
		for (int count = 1; have > 2 && y - count > -1 && x - count > -1 && p -> board[y - 1][x - 1] == 0; count++) {
			p -> board[y - count][x - count] = 3 - p -> who;
			return;
		}
	}
	have = 1;
	for (int count = 1; count < 4; count++) {         //左下右上
		if (y + count < 15 && x - count > -1 && p -> board[y + count][x - count] == p -> who) {
			have++;
		}
		if (y - count > -1 && x + 1 < 15 && p -> board[y - count][x + count] == p -> who) {
			have++;
		}
		for(int count = 1; have > 2 && y - count > -1 && x + count < 15 && p -> board[y - count][x + count] == 0; count++) {
			p -> board[y - count][x + count] = 3 - p -> who;
			return;
		}
		for(int count = 1; have > 2 && y + count < 15 && x - count > -1 && p -> board[y + count][x - count] == 0; count++) {
			p -> board[y + count][x - count] = 3 - p -> who;
			return;
		}
	}
	for(int count = 1;count < 3; count++) {
		int i;
		i = rand() % 5 + 1;
		if (i == 1 && x > 0 && p -> board[y][x - 1] == 0) {
			p -> board[y][x - 1] = 3 - p -> who;
			return;
		}
		else if (i == 2 && x < 14 && p -> board[y][x + 1] == 0) {
			p -> board[y][x + 1] = 3 - p -> who;
			return;
		}
		else if (i == 3 && y < 14 && p -> board[y + 1][x] == 0) {
			p -> board[y + 1][x] = 3 - p -> who;
			return;
		}
		else if (i == 4 && y > 0 && p -> board[y - 1][x] == 0) {
			p -> board[y - 1][x] = 3 - p -> who;
			return;
		}
	}
	
	return;
}


int ifWin(struct Chess *p) {
	int x = 1,y = 1;
	int have = 1;
	int count;

	x = p -> x - 1;
	y = p -> y - 1;

	for (count = 1; count < 6; count++) {         //x轴
		if (x - count > -1 && p -> board[y][x - count] == p -> who) {
			have++;
		}
		if (x + count < 15 && p -> board[y][x + count] == p -> who) {
			have++;
		}
		if (have == 5) {
			return p -> who;
		}
	}
	have = 1;
	for (count = 1; count < 6; count++) {         //y轴
		if (y - count > -1 && p -> board[y - count][x] == p -> who) {
			have++;
		}
		if (y + count < 15 && p -> board[y + count][x] == p -> who) {
			have++;
		}
		if (have == 5) {
			return p -> who;
		}
	}
	have = 1;
	for (count = 1; count < 6; count++) {         //左上右下
		if (y - count > -1 && x - count > -1 && p -> board[y - count][x - count] == p -> who) {
			have++;
		}
		if (y + count < 15 && x + count < 15 && p -> board[y + count][x + count] == p -> who) {
			have++;
		}
		if (have == 5) {
			return p -> who;
		}
	}
	have = 1;
	for (count = 1; count < 6; count++) {         //左下右上
		if (y + count < 15 && x - count > -1 && p -> board[y + count][x - count] == p -> who) {
			have++;
		}
		if (y - count > -1 && x + 1 < 15 && p -> board[y - count][x + count] == p -> who) {
			have++;
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
		perror("fopen");
		input();
		return;
	}
	fprintf(fp2,"%d",p -> count);
	fprintf(fp,Time);
	for (count = 0; count < Max ; count++) {    //打印棋盘到文件
		for (count2= 0; count2 < Max; count2++) {
			if (p -> board[count][count2] == 0) {
				fprintf(fp,"\033[37;40m + \033[0m");
			}
			else if (p -> board[count][count2] == 1) {
				fprintf(fp,"\033[30;47m @ \033[0m");
			}
			else if (p -> board[count][count2] == 2) {
				fprintf(fp,"\033[37;40m O \033[0m");
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
	int count;              //数数
	int b;                  //选择
	char a[3417];           //棋盘信息
	FILE *fp;               //文件指针

	if(p -> count == 0) {
		printf("\033[1;33mYou don't have a game record yet.\033[0m\nPress enter to return:\n");
		input();
		return;
	}
	fp = fopen(Save,"rb");
	if (!fp) {
		perror("\033[1;31mfopen\033[0m");
		printf("The arc hive could not be opened.\nPress enter to return:\n");
		input();
		return;
	}
	for (count = 0; count < p -> count; count++) {
		fread(a,3417,1,fp);
		printf("\033[1;1H");
		puts(a);
		printf("\033[1;31mPress \'w\' to view the last game,press \'s\' to view the next game\npress \'0\' to exit\033[0m\n");
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
				if (count == 0) {
					printf("\033[33mThis is the first record.\n\033[1;31mPress enter to return:\033[0m\n");
					fseek(fp,0L,0);
					count--;;
				}
				else {
					fseek(fp,-6834L,1);
					count -= 2;
					Clear
				}
				break;
			case 0x53:
			case 0x73:
				if (count == p -> count - 1) {
					printf("\033[33mThis is the last record.\033[1;31m\nPress enter to return:\033[0m\n");
					fseek(fp,-3417L,3);
					count--;
				}
				else {
					Clear
				}
				break;
			default:
				fseek(fp,-3417L,1);
				count--;
				Clear
				break;
		}
	}
	fclose(fp);
	return;
}

void help() {
	FILE *fp;
	int a = 0,count = 0;
	char b[1392];

	menu2("Game Help");
	printf("\033[7;4HIf you want to exit the game,press \'0\',\'q\',\'Q\',\'Esc\'");
	printf("\033[8;4HPress \'w\',\'a\',\'s\',\'d\' to control the movement of \033[9;8Hthe cursor");
	printf("\033[10;4H\'@\' is black chess,\'O\' is white chess,\'+\' is blank.");
	Menu2
	a = input();
	if(a == 0x1B) {
		if (kbhit_if() == 1) {
			getchar();
			a = getchar();
		}
		if(a == 0x42) {
			Clear
			fp = fopen(Help,"r");
			for (count = 0;count < 5; count++){
				fread(b,3417,1,fp);
				puts(b);
				printf("\033[17;1H\033[0;1;31mn下一步;N上一步,0退出\033[0m");
				a = input();
				switch (a) {
					case 0x1B:
					case 0x30:
					case 0x51:
					case 0x71:
						return;
						break;
					case 0x57:
					case 0x77:
						if (count == 0) {
							Clear
							fseek(fp,0L,0);
							count--;
						}
						else {
							fseek(fp,-6834L,1);
							count -= 2;
						}
						Clear
						break;
					case 0x53:
					case 0x73:
						if (count == 4) {
							Clear
							fseek(fp,-3417L,3);
							count--;
						}
						Clear
						break;
					default:
						fseek(fp,-3417L,1);
						count--;
						Clear
						break;
				}
			}
			fclose(fp);
		}
	}
	return;
}

void other() {
	FILE *fp,*fp2;
	int a;
	char c[10] = "nano";

	menu("Other options");
	printf("\033[8;11H\033[1;33m1.Clear all archives\033[8;33H2.Setting");
	printf("\033[9;11H\033[1;33m0.Return to the menu");
	Menu
	a = input();
	switch(a) {
		case 0x30:
		case 0x51:
		case 0x71:
			return;
			break;
		case 0x31:
			Clear
			printf("\033[1;33mPlease confirm clear your archives!You will be lost all archives!(Y/n)\n");
			a = input();
			if (a == 0x59 || a == 0x79) {
				fp = fopen(Data,"w");
				fp2 = fopen(Save,"w");
				if(!fp && !fp2) {
					perror("\033[1;31mfopen\033[0m");
					printf("\033[1;31mThe archive could not be opened\nPress enter to return:\033[0m");
					input();
				}
				return;
			}
			fprintf(fp,"0");
			fclose(fp);
			fclose(fp2);
			Clear
			printf("\033[1;33mThe purge was successful.\n\033[1;31mPress enter to return:\033[0m");
			input();
			Clear
			break;
		case 0x33:
			/* pass */
			break;
		default:
			return;
			break;
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
				printf("\033[37;40;2m + \033[0m");
			}
			else if (p -> board[count][count2] == 1) {
				printf("\033[30;47m @ \033[0m");
			}
			else if (p -> board[count][count2] == 2) {
				printf("\033[37;40m O \033[0m");
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
	return;
}

