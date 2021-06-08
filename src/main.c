#include "headfile/head.h"                           //导入头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc,char * argv[]) {
	int a;
	int m = 1;

	printf("\033[?25l");
	p = (struct Chess *)malloc(sizeof(struct Chess));
	Clear2
	init(p);
	while (a != 0x1B && a != 0x30 && a != 0x51 && a != 0x71) {
		init(p);
		welcome(m);
		a = input();
		printf("\n\n\n\n");
		Clear2
		switch (a) {
			case 0x30:
			case 0x51:
			case 0x71:
				free(p);
				printf("\033[?25h");
				return 0;
				break;
			case 0x1B:
				if (kbhit_if() == 1) {
					getchar();
					a = getchar();
					if (a == 0x41 || a == 0x44) {
						if (m > 1) {
							m--;
						}
						else {
							printf("\a");
						}
					}
					else if (a == 0x42 || a == 0x43) {
						if (m < 2) {
							m++;
						}
						else {
							printf("\a");
						}
					}
				}
				else {
					free(p);
					printf("\033[?25h");
					return 0;
					break;
				}
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
				Clear
				printf("\033[1;33m请确清除存档，您将失去您的所有记录！（Y/n）\n");
				a = input();
				if (a == 0x59 || a == 0x79) {
					fp = fopen(Data,"w");
					if(!fp) {
						perror("\033[1;31m[othor]: \033[0m");
						input();
					}
					else {
						fprintf(fp, "0");
						fclose(fp);
					}
					fp = fopen(Save, "w");
					if(!fp) {
						perror("\033[1;31m[othor]: \033[0m");
						input();
					}
					else {
						fclose(fp);
					}
				}
				Clear
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

void init() {
	FILE *fp;
	int a = 0;            //保存转换后的数字
	int c = 0;            //语言选择的结果
	int count = 0;
	int If = 0;
	char d[5];            //查看语言
	char b[5];            //转换前的字符


	if (access("/usr/", 0) == EOF) {
		perror("\033[1;31m[init]: 不存在/usr/文件夹！\033[0m");
		printf("将使用当前目录作为软件数据存放目录\n");
		mkdir("./cgame2/", 0777);
		strcpy(Data, "./cgame2/data.txt");
		strcpy(Save, "./cgame2/save.txt");
		input();
	}
	else {
		if (access("/usr/local", 0) == EOF) {
			perror("\033[1;31m[init]: 不存在/usr/local/文件夹！\033[0m");
			printf("将使用当前目录作为软件数据存放目录\n");
			mkdir("./cgame2/", 0777);
			strcpy(Data, "./cgame2/data.txt");
			strcpy(Save, "./cgame2/save.txt");
			input();
		}
		else {
			if (access("/usr/local/cgame2", 0) == EOF) {
				perror("\033[1;31m[init]: \033[0m");
				strcpy(Data, "./cgame2/data.txt");
				strcpy(Save, "./cgame2/save.txt");
				if (access("./cgame2/", 0) == EOF) {
					printf("您可能没有安装deb包,将使用当前目录作为软件数据存放目录\n");
					mkdir("./cgame2/", 0777);
					input();
				}
				else {
					Clear
				}
			}
		}
	}
	if(access(Save,0) == EOF) {       /*创建Save文件*/
		fp = fopen(Save,"w");
		if (!fp) {
			perror("\033[1;31m[init](Save): fopen\033[0m");
			input();
			return;
		}
		fclose(fp);
		p -> count = 0;
		return;
	}
	if(access(Data,0) == EOF) {       /*创建Data文件*/
		fp = fopen(Data,"w");
		if (!fp) {
			perror("\033[1;31m[init](Data): fopen\033[0m");
			input();
			return;
		}
		fprintf(fp,"%d\n",p -> count);
		fclose(fp);
	}
	else {                            /*读取Data文件*/
		fp = fopen(Data,"r");
		fscanf(fp,"%s",b);
		a = atoi(b);
		p -> count = a;
		fclose(fp);
	}
	return;
}

void welcome(int a) {
	Clear
	menu("游戏菜单");
	if (a == 1){
		printf("\033[8;11H\033[1;33m1.开始游戏\033[8;37H2.游戏记录");
		printf("\033[9;11H3.游戏帮助\033[9;37H4.清除存档");		
	}
	else if (a == 2) {
		printf("\033[8;11H\033[1;33m5.设置\033[8;33H0.退出游戏\033[0m");
	}
	printf("\033[2;32m\033[6;26H↑\033[10;26H↓\033[11;52H\033[2;32m%d/2\033[1;33m",a);
	Menu
	return;
}

void game() {
	int count,count2;      //用于计数

	int error = 0;         //记录错误

	int x = 1,y = 1;       //当前坐标
	int way;               //光标移动方向
	int win  = 0;          //赢家，1黑，2白
	int who = 1;           //现在下子的玩家

	int a = 0;

	Clear
	printf("是否和AI下棋？（Y/n）\n");
	way = input();
	if (way == 0x59 || way == 0x79) {
		a = 1;
	}
	else {
		a = 0;
	}
	Clear

	gettime();

	while(win != 1 && win != 2) {
		getnowtime();
		printf(NowTime);
		printboard();
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
					error = 1;
					break;
				}
				else if (p -> board[y - 1][x - 1] == 0) {
					p -> board[y - 1][x - 1] = who;
					p -> who = who;
					p -> x = x;
					p -> y = y;
					win = ifWin();
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
		Clear
	}
	p -> count += 1;      //局数加一
	save();
	Clear
	return;
}

void AI() {
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


int ifWin() {
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

void save() {
	int count;
	int count2;

	fp = fopen(Save,"a");
	if (!fp) {
		perror("\033[1;31m[save]\033[0m");
		input();
		return;
	}
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
	fclose(fp);
	fp = fopen(Data,"w");
	if (!fp) {
		perror("\033[1;31m[save]\033[0m");
		input();
		return;
	}
	fprintf(fp,"%d",p -> count);
	fclose(fp);
	for (count = 0; count < Max ; count++) {
		for (count2= 0; count2 < Max; count2++) {
			p -> board[count][count2] = 0;
		}
	}
	return;
}

void history() {
	int count;              //数数
	int b;                  //选择
	char a[3417];           //棋盘信息

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
		fread(a,3417,1,fp);
		printf("\033[1;1H");
		puts(a);
		printf("\033[17;1H\033[0;1;31m按下W查看上一局，按下S查看下一局,0退出\033[0m");
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
					printf("\033[18;1H\033[33m这已经是第一个记录了\033[0m\n");
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
					printf("\033[18;1H\033[33m这已经是最后一个记录了\033[0m\n");
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

	menu2("游戏帮助");
	printf("\033[7;4H按下0,q,Q退出");
	printf("\033[8;4HW S A D或者方向键控制上下左右，空格下子");
	printf("\033[9;4H@为黑棋,O为白棋,+为空白");
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
			if(!fp) {
				perror("\033[1;31m[help]: fopen\033[0m");
				input();
				return;
			}
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

void printboard() {
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

void gettime() {
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

void getnowtime() {
	time_t timep;
	struct tm *tp;

	time(&timep);
	tp=gmtime(&timep);

	p -> nt.year = 1900+tp->tm_year;
	p -> nt.mon = 1+tp->tm_mon;
	p -> nt.day = tp->tm_mday;
	return;
}

void stop() {
	Clear2
	printf("退出程序中...\n");
	free(p);
}

