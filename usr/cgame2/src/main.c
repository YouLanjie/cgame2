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
		fp = fopen("Save","w");
		fclose(fp);
		p -> count = 0;
		return;
	}
	if (access(Data,0) == EOF) {
		fp = fopen("Data","w");
		fprintf(fp,"%d\n",p -> count);
		fclose(fp);
	}
	else {
		fp = fopen("Data","r");
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
	p -> count += 1;
	int count = 1;
	int x,y;

	gettime(p);

	while(count < 9) {
		gettime(p);
		printf(Time);
		free(time);
		printboard(p);
		if (count % 2 != 0) {
			printf("黑方下\n");
			printf("x：");
			scanf("%d",&x);
			printf("y：");
			scanf("%d",&y);
			p -> board[y - 1][x - 1] = 1;
		}
		else if (count % 2 == 0) {
			printf("白方下\n");
			printf("x：");
			scanf("%d",&x);
			printf("y：");
			scanf("%d",&y);
			p -> board[y - 1][x - 1] = 2;
		}
		else {
			return;
		}
		count++;
		Clear
	}
	save(p);
	Clear
	return;
}

void save(struct Chess *p) {
	int count;
	int count2;
	FILE *fp;
	FILE *fp2;

	fp = fopen(".save","a");
	fp2 = fopen(".data","w");
	if (!fp && !fp2) {
		printf("无法保存\n按任意按键返回\n");
		input();
		return;
	}
	gettime(p);
	fprintf(fp2,"%d",p -> count);
	fprintf(fp,Time);
	free(ctime);
	for (count = 0; count < Max ; count++) {    //打印棋盘到文件
		for (count2= 0; count2 < Max; count2++) {
			if (p -> board[count][count2] == 0) {
				fprintf(fp," + ");
			}
			else if (p -> board[count][count2] == 1) {
				fprintf(fp,"⚫ ");
			}
			else if (p -> board[count][count2] == 2) {
				fprintf(fp,"⚪ ");
			}
		}
		fprintf(fp,"\n");
	}
	fclose(fp2);
	fclose(fp);
	return;
}

void history(struct Chess *p) {
	int count;
	int b;
	char a[p -> count * (Max + 1)][100];
	FILE *fp;

	if(p -> count == 0) {
		printf("\033[1;33m你还没有游戏记录，赶紧去玩一下吧！\033[0m\n输入任意按键返回\n");
		input();
		return;
	}
	fp = fopen("Save","r");
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
						count -= Max + 1;
						input();
					}
					else {
						count -= 2 * (Max + 1);
						input();
					}
					Clear
					break;
				case 0x53:
				case 0x73:
					if ((count + 1) / (Max + 1)== p -> count) {
						Clear
						printf("\033[33m这已经是最后一个记录了\033[1;31m\n按下任意键继续\033[0m\n");
						count -= Max + 1;
						input();
					}
					Clear
					break;
				default:
					count -= Max + 1;
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

void printboard(struct Chess *p) {
	int count;
	int count2;

	printf("\033[1;33m-----------------------------------------------\n");
	for (count = 0; count < Max; count++) {    //打印棋盘
		printf("|\033[0m");
		for (count2= 0; count2 < Max; count2++) {
			if (p -> board[count][count2] == 0) {
				printf(" + ");
			}
			else if (p -> board[count][count2] == 1) {
				printf("⚫ ");
			}
			else if (p -> board[count][count2] == 2) {
				printf("⚪ ");
			}
		}
		printf("\033[1;33m|\n");
	}
	printf("-----------------------------------------------\033[0m\n");
	return;
}

void gettime(struct Chess *p2) {
	time_t timep;
	struct tm *p;
	time(&timep);

	p2 -> t.year = 1900+p->tm_year;
	p2 -> t.mon = 1+p->tm_mon;
	p2 -> t.day = p->tm_mday;
	p2 -> t.hour = p->tm_mday;
	p2 -> t.min = p->tm_min;
	p2 -> t.sec = p->tm_min;
	return;
}
