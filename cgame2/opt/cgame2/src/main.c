#include "headfile/head.h"                           //导入头文件

int main() {
	int a;
	int b;
	struct Chess *p;
	
	p = (struct Chess *)malloc(sizeof(struct Chess));
	Clear
	b = init(p);
	if (b == 1) {
		free(p);
		Clear
		return 0;
	}
	while (a != 0x1B && 0x30 && 0x51 && 0x71) {
		b = init(p);
		if (b == 1) {
			free(p);
			Clear
			return 0;
		}
		welcome();
		a = input();
		printf("\n\n\n");
		Clear
		switch (a) {
			case 0x1B:
			case 0x30:
			case 0x51:
			case 0x71:
				free(p);
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
				printf("\033[2;25H\033[1;32m错误！\n");
				printf("\033[4;2H\033[1;31m  按任意按键返回：\033[0m\033[4;19H");
				input();
				break;
		}
		Clear
	}
	free(p);
	Clear
	return 0;
}

int init(struct Chess *p) {
	FILE *fp;
	int a = 0;            //保存转换后的数字
	int c = 0;            //语言选择的结果
	int count = 0;
	int If = 0;
	char d[5];            //查看语言
	char b[5];            //转换前的字符

	if (access(Save,0) == EOF) {
		fp = fopen(Save,"w");
		fclose(fp);
		p -> count = 0;
		return 0;
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
	if (access(Lang,0) == EOF) {
		fp = fopen(Lang,"w");
		fclose(fp);
	}
	fp = fopen(Lang,"r");
	fscanf(fp,"%s",d);
	c = atoi(d);
	if (c != 1 && c != 2) {
		while (count < 50 && c != 1 && c != 2) {
			fp = fopen(Lang,"r");
			fscanf(fp,"%s",d);
			c = atoi(d);
			if (c != 1 && c != 2) {
				fclose(fp);
				fp = fopen(Lang,"w");
				Clear
				menu("选择语言\n\033[3;19HSelect the language");
				printf("\033[8;2H\033[34m\033[1;33m       1.中文(Chinese)             2.English          \033[0;34m|\033[0m\n");
				Menu
				scanf("%d",&c);
				fprintf(fp,"%d",c);
				fclose(fp);
				Clear
			}
			count++;
		}
		if (count > 0) {
			getchar();
		}
	}
	if (c == 2) {
		If = English();
		return If;
	}
	return 0;
}

void welcome() {
	Clear
	menu("游戏菜单");
	printf("\033[8;11H\033[1;33m1.开始游戏\033[8;37H2.游戏记录");
	printf("\033[9;11H3.游戏帮助\033[9;37H4.更多选项");
	printf("\033[10;11H0.退出游戏");
	Menu
	return;
}

void game(struct Chess *p) {
	int count,count2;      //用于计数

	int error = 0;         //记录错误

	int x = 1,y = 1;       //当前坐标
	int way;               //光标移动方向
	int win  = 0;          //赢家，1黑，2白
	int who = 1;           //现在下子的玩家

	gettime(p);

	while(win != 1 && win != 2) {
		getnowtime(p);
		printf(NowTime);
		printboard(p);
		if (who == 1) {
			printf("黑方下\n");
		}
		else if (who == 2) {
			printf("白方下\n");
		}
		if (error == 1) {
			printf("\033[1;33m\033[20;1H你不能下在非空的格子!\033[0m\n");
			error = 0;
		}
		printf("\033[%d;%dH\033[31m",y + 2,x * 3);
		way = input();
		switch (way) {
			case 0x1B:
			case 0x30:
			case 0x51:
			case 0x71:
				Clear
				printf("\033[1;33m请确认退出！本次游戏将不会记录！（Y/n）\n");
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
				if (p -> board[y -1][x - 1] == 1 || p -> board[y -1][x - 1] == 2) {
					error = 1;
					break;
				}
				else if (p -> board[y -1][x - 1] == 0) {
					p -> board[y - 1][x - 1] = who;
					p -> who = who;
					p -> x = x;
					p -> y = y;
					win = ifWin(p);
					if (win == who) {
						Clear
						printf("\033[33m游戏结束，");
						if (who == 1) {
							printf("黑方");
						}
						else if (who == 2) {
							printf("白方");
						}
						printf("胜利！\n\033[31m按Enter返回\n\033[0m");
						input();
					}
					who = 3 - who;
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
	have = 1;
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
	have = 1;
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
	have = 1;
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
	int count;              //数数
	int b;                  //选择
	char a[3192];           //棋盘信息
	FILE *fp;               //文件指针

	if(p -> count == 0) {
		printf("\033[1;33m你还没有游戏记录，赶紧去玩一下吧！\033[0m\n输入任意按键返回\n");
		input();
		return;
	}
	fp = fopen(Save,"rb");
	if (!fp) {
		printf("无法打开存档，请自行确认存档文件是否存在！\n按任意按键返回\n");
		input();
		return;
	}
	for (count = 0; count < p -> count; count++) {
		fread(a,3192,1,fp);
		printf("\033[1;33m%s\033[0m",a);
		printf("\033[0;1;31m按下W查看上一局，按下S查看下一局,0退出\033[0m\n");
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
					Clear
					printf("\033[33m这已经是第一个记录了\n\033[1;31m按下任意键继续\033[0m\n");
					fseek(fp,0L,0);
					count--;
					input();
				}
				else {
					fseek(fp,-6384L,1);
					count -= 2;
				}
				Clear
				break;
			case 0x53:
			case 0x73:
				if (count == p -> count - 1) {
					Clear
					printf("\033[33m这已经是最后一个记录了\033[1;31m\n按下任意键继续\033[0m\n");
					fseek(fp,-3192L,3);
					count--;
					input();
				}
				Clear
				break;
			default:
				fseek(fp,-3192L,1);
				count--;
				Clear
				break;
		}
	}
	fclose(fp);
	return;
}

void help() {
	menu2("游戏帮助");
	printf("\033[7;4H如果想要退出，0、q、Q、Esc都可以哦");
	printf("\033[8;4HW S A D控制上下左右，空格下子");
	printf("\033[9;4H@为黑棋,O为白棋,+为空白");
	Menu2
	input();
	return;
}

void other() {
	FILE *fp,*fp2;
	int a;

	menu("其他选项");
	printf("\033[8;11H\033[1;33m1.清除存档\033[8;37H2.设置语言\033[9;33H(Set the language)");
	printf("\033[9;2H\033[1;33m         0.返回菜单");
	Menu
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
	else if (a == 0x32) {
		fp = fopen(Lang,"w");
		fclose(fp);
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
	return;
}



/*------------------------------English---------------------------------*/
/*------------------------------English---------------------------------*/
/*------------------------------English---------------------------------*/
/*------------------------------English---------------------------------*/
/*------------------------------English---------------------------------*/

extern int English() {
	int a;
	int b;
	struct en_Chess *p;
	
	p = (struct en_Chess *)malloc(sizeof(struct en_Chess));
	Clear
	en_init(p);
	while (a != 0x1B && 0x30 && 0x51 && 0x71) {
		b = en_init(p);
		if (b == 1) {
			return 0;
		}
		en_welcome();
		a = input();
		printf("\n\n\n");
		Clear
		switch (a) {
			case 0x1B:
			case 0x30:
			case 0x51:
			case 0x71:
				free(p);
				return 1;
				break;
			case 0x31:
				en_game(p);
				break;
			case 0x32:
				en_history(p);
				break;
			case 0x33:
				en_help();
				break;
			case 0x34:
				en_other();
				break;
			default:
				puts("\n\t\t\t\t    Error!");
				printf("\033[31m\tPress enter to return:");
				input();
				break;
		}
		Clear
	}
	free(p);
	Clear
	return 0;
}

extern int en_init(struct en_Chess *p) {
	FILE *fp;
	int a = 0;
	int c = 0;
	int count = 0;
	char d[5];
	char b[5];

	if (access(Save,0) == EOF) {
		fp = fopen(Save,"w");
		fclose(fp);
		p -> count = 0;
		return 0;
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
	if (access(Lang,0) == EOF) {
		fp = fopen(Lang,"w");
		fclose(fp);
	}
	fp = fopen(Lang,"r");
	fscanf(fp,"%s",d);
	c = atoi(d);
	if (c != 1 && c != 2) {
		while (count < 50 && c != 1 && c != 2) {
			fp = fopen(Lang,"r");
			fscanf(fp,"%s",d);
			c = atoi(d);
			if (c != 1 && c != 2) {
				fclose(fp);
				fp = fopen(Lang,"w");
				Clear
				en_menu("选择语言\n\033[3;19HSelect the language");
				printf("\033[8;2H\033[34m\033[1;33m       1.中文(Chinese)             2.English          \033[0;34m|\033[0m\n");
				en_Menu
				scanf("%d",&c);
				fprintf(fp,"%d",c);
				fclose(fp);
				Clear
			}
			count++;
		}
		if (count > 0) {
			getchar();
		}
	}
	if (c == 1) {
		return 1;
	}
	return 0;
}

extern void en_welcome() {
	Clear
	en_menu("Game menu");
	printf("\033[8;11H\033[1;33m1.Start the game\033[8;37H2.Game record");
	printf("\033[9;11H3.Game help\033[9;37H4.Other options");
	printf("\033[10;11H0.Exit the game");
	en_Menu
	return;
}

extern void en_game(struct en_Chess *p) {
	int count,count2;

	int x = 1,y = 1;
	int way;
	int win  = 0;
	int who = 1;

	en_gettime(p);

	while(win != 1 && win != 2) {
		en_getnowtime(p);
		printf(en_NowTime);
		en_printboard(p);
		if (who == 1) {
			printf("Now:black play chess\n");
		}
		else if (who == 2) {
			printf("Now:white play chess\n");
		}
		printf("\033[%d;%dH\033[31m",y + 2,x * 3);
		way = input();
		switch (way) {
			case 0x1B:
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
			case 0x57:
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
				if (p -> board[y -1][x - 1] == 1 || p -> board[y -1][x - 1] == 2) {
					break;
				}
				else if (p -> board[y -1][x - 1] == 0) {
					p -> board[y - 1][x - 1] = who;
					p -> who = who;
					p -> x = x;
					p -> y = y;
					win = en_ifWin(p);
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
					who = 3 - who;
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
	p -> count += 1;
	en_save(p);
	Clear
	return;
}

extern int en_ifWin(struct en_Chess *p) {
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
	have = 1;
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
	have = 1;
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
	have = 1;
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

extern void en_save(struct en_Chess *p) {
	int count;
	int count2;
	FILE *fp;
	FILE *fp2;

	fp = fopen(Save,"a");
	fp2 = fopen(Data,"w");
	if (!fp && !fp2) {
		printf("Can't save\nPress enter to return:\n");
		input();
		return;
	}
	fprintf(fp2,"%d",p -> count);
	fprintf(fp,en_Time);
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

extern void en_history(struct en_Chess *p) {
	int count;
	int b;
	char a[3192];
	FILE *fp;

	if(p -> count == 0) {
		printf("\033[1;33mYou don't have a game record yet.\033[0m\nPress enter to return:\n");
		input();
		return;
	}
	fp = fopen(Save,"r");
	if (!fp) {
		printf("The arc hive could not be opened.\nPress enter to return:\n");
		input();
		return;
	}
	for (count = 0; count < p -> count; count++) {
		fread(a,3191,1,fp);
		printf("\033[1;33m%s\033[0m",a);
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
					Clear
					printf("\033[33mThis is the first record.\n\033[1;31mPress enter to return:\033[0m\n");
					fseek(fp,-3190L,1);
					count--;
					input();
				}
				else {
					fseek(fp,-6380L,1);
					count -= 2;
				}
				Clear
				break;
			case 0x53:
			case 0x73:
				if (count == p -> count - 1) {
					Clear
					printf("\033[33mThis is the last record.\033[1;31m\nPress enter to return:\033[0m\n");
					fseek(fp,-3190L,2);
					count--;
					input();
				}
				Clear
				break;
			default:
				fseek(fp,-3190L,1);
				count--;
				Clear
				break;
		}
	}
	fclose(fp);
	return;
}

extern void en_help() {
	en_menu2("Game help");
	printf("\033[7;4HIf you want to exit the game,press \'0\',\'q\',\'Q\',\'Esc\'");
	printf("\033[8;4HPress \'w\',\'a\',\'s\',\'d\' to control the movement of \033[9;8Hthe cursor");
	printf("\033[10;4H\'@\' is black chess,\'O\' is white chess,\'+\' is blank.");
	en_Menu2
	input();
	return;
}

extern void en_other() {
	FILE *fp,*fp2;
	int a;

	en_menu("Other options");
	printf("\033[8;11H\033[1;33m1.Clear all archives\033[8;33H2.Set the language\033[9;35H（设置语言）");
	printf("\033[9;11H\033[1;33m0.Return to the menu");
	en_Menu
	a = input();
	if(a == 0x1B || a == 0x30 || a == 0x51 || a == 0x71) {
		return;
	}
	else if(a == 0x31) {
		fp = fopen(Data,"w");
		fp2 = fopen(Save,"w");
		if(!fp && !fp2) {
			printf("\033[1;31mThe archive could not be opened\nPress enter to return:\033[0m");
			input();
			return;
		}
		else {
			fprintf(fp,"0");
			fclose(fp);
			fclose(fp2);
			Clear
			printf("\033[1;33mThe purge was successful.\n\033[1;31mPress enter to return:\033[0m");
			input();
		}
	}
	else if (a == 0x32) {
		fp = fopen(Lang,"w");
		fclose(fp);
	}
	else {
		return;
	}
	return;
}

extern void en_printboard(struct en_Chess *p) {
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

extern void en_gettime(struct en_Chess *p) {
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

extern void en_getnowtime(struct en_Chess *p) {
	time_t timep;
	struct tm *tp;

	time(&timep);
	tp=gmtime(&timep);

	p -> nt.year = 1900+tp->tm_year;
	p -> nt.mon = 1+tp->tm_mon;
	p -> nt.day = tp->tm_mday;
	return;
}

extern void en_menu(char a[50]) {
	printf("\033[2;25H\033[1;32m%s",a);
	printf("\033[5;1H\033[34m--------------------------------------------------------");
	printf("\033[6;1H\033[34m|\033[6;56H|");
	printf("\033[7;1H|\033[7;56H|");
	printf("\033[8;1H|\033[8;56H|");
	printf("\033[9;1H|\033[9;56H|");
	printf("\033[10;1H|\033[10;56H|");
	printf("\033[11;1H|\033[11;56H|");
	printf("\033[12;1H|\033[12;56H|");
	printf("\033[13;1H--------------------------------------------------------\033[0m\033[11;11H");
	printf("\033[11;4H\033[1;31mPlease select:\033[0m\033[11;18H");
	return;
}

extern void en_menu2(char a[50]) {
	printf("\033[2;25H\033[1;32m%s",a);
	printf("\033[5;1H\033[34m--------------------------------------------------------");
	printf("\033[6;1H\033[34m|\033[6;56H|");
	printf("\033[7;1H|\033[7;56H|");
	printf("\033[8;1H|\033[8;56H|");
	printf("\033[9;1H|\033[9;56H|");
	printf("\033[10;1H|\033[10;56H|");
	printf("\033[11;1H|\033[11;56H|");
	printf("\033[12;1H|\033[12;56H|");
	printf("\033[13;1H--------------------------------------------------------\033[0m\033[11;11H");
	printf("\033[11;4H\033[1;31mPress enter yo return:\033[0m\033[11;24H");
	return;
}
