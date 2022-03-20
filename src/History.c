#include "../include/head.h"

void History() {
	int count;              //数数
	int b = 0;              //选择
	int max = 0;
	char board[52][50];     //棋盘信息
	char *cp;
	int way = 0;           //文件的大小
	FILE * fp;

	fp = fopen(Save,"rb");
	if (!fp) {
		printf("无法打开存档，请自行确认存档文件是否存在！\n按任意按键返回\n");
		getch();
		return;
	}
	fseek(fp, 0L, 2);
	way = ftell(fp);
	fseek(fp, 0L, 0);
	cp = (char *)malloc(300);
	for (int i = 0; 1; ) {
		if(fgetc(fp) == '\n') {
			i++;
		}
		if (ftell(fp) == way) {
			way = i;
			break;
		}
	}
	free(cp);
	fseek(fp, 0L, 0);
	if(way == 0) {
		fontColorSet(1,33);
		printf("你还没有游戏记录，赶紧去玩一下吧！\n");
		fontColorSet(0,0);
		printf("输入任意按键返回\n");
		getch();
		return;
	}
	fseek(fp, 0L, 0);
	for (count = 0; count + 1 <= way; count++) {
		Clear2
		fseek(fp, 0L, 0);
		for (int i = 0; i <= count; i++) {
			fscanf(fp, "%d%d%d%d%d%d%d", &p -> t.year, &p -> t.mon, &p -> t.day, &p -> t.hour, &p -> t.min, &p -> t.sec, &max);
			for (int i = 0; i < max; i++) {
				fscanf(fp, "%s", board[i]);
			}
		}
		gotoxy(1,1); fontColorSet(1,31);
		printf(Time);
		fontColorSet(0,0);
		for (int i = 0; board[i][0] != '\0' && board[i][0] != EOF; i++) {
			for (int i2 = 0; board[i][i2] != '\0' && board[i][i2] != EOF; i2++) {
				if (board[i][i2] == '0') {
					fontColorSet(0,2); fontColorSet(37,40);
					printf(" + ");
					fontColorSet(0,0);
				}
				else if (board[i][i2] == '1') {
					fontColorSet(0,2); fontColorSet(30,47);
					printf(" @ ");
					fontColorSet(0,0);
				}
				else if (board[i][i2] == '2') {
					fontColorSet(0,2); fontColorSet(37,40);
					printf(" O ");
					fontColorSet(0,0);
				}
			}
			printf("\n");
		}
		fontColorSet(1,31);
		printf("按下L查看上一局，按下N查看下一局,0退出");
		fontColorSet(0,0);
		b = getch();
		if (b == 0x1B) {
			if (kbhit() == 1) {
				getchar();
				b = getch();
				if (b == 0x41 || b == 0x44) {
					b = 0x4C;
				}
				else if (b == 0x42 || b == 0x43) {
					b = 0x4E;
				}
			}
			else {
				return;
			}
		}
		switch (b) {
			case 0x30:
			case 0x51:
			case 0x71:
				return;
				break;
			case 0x4C:
			case 0x6C:
				if (count == 0) {
					count = -1;
				}
				else {
					count -= 2;
				}
				break;
			case 0x4E:
			case 0x6E:
				if (count + 1 >= way) {
					count--;
				}
				break;
			case 'r':
			case 'R':
				Clear2
				count = -1;
				break;
			default:
				count--;
				break;
		}
		kbhitGetchar();
		fontColorSet(0,0);
		gotoxy(2,1);
	}
	fclose(fp);
	return;
}
