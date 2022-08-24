#include "../include/head.h"

void History() {
	int count;              //数数
	int chose = 0;              //选择
	int max = 0;
	char *cp;
	int line = 0;           //文件的大小
	FILE * fp;

	fp = fopen(Save,"rb");
	if (!fp) {
		printf("无法打开存档，请自行确认存档文件是否存在！\n按任意按键返回\n");
		getch();
		return;
	}
	fseek(fp, 0L, 2);
	line = ftell(fp);
	fseek(fp, 0L, 0);
	cp = (char *)malloc(300);
	for (int i = 0; 1; ) {
		if(fgetc(fp) == '\n') {
			i++;
		}
		if (ftell(fp) == line) {
			line = i;
			break;
		}
	}
	free(cp);
	fseek(fp, 0L, 0);
	if(line == 0) {
		fontColorSet(1,33);
		printf("你还没有游戏记录，赶紧去玩一下吧！\n");
		fontColorSet(0,0);
		printf("输入任意按键返回\n");
		getch();
		return;
	}
	fseek(fp, 0L, 0);
	p = (struct Chess *)malloc(sizeof(struct Chess));
	max = Max;
	Clear2
	for (count = 0; count + 1 <= line; count++) {
		fontColorSet(37,44);
		Clear
		fontColorSet(0,0);
		fseek(fp, 0L, 0);
		kbhitGetchar();
		for (int i = 0; i <= count; i++) {
			fscanf(fp, "%d%d%d%d%d%d%d", &p -> t.year, &p -> t.mon, &p -> t.day, &p -> t.hour, &p -> t.min, &p -> t.sec, &Max);
			for (int i = 0; i < Max; i++) {
				fscanf(fp, "%s", p -> board[i]);
				p -> board[i + 1][0] = '\0';
			}
		}
		gotoxy(1,1);
		fontColorSet(0,44);
		fontColorSet(1,37);
		printf(Time);
		fontColorSet(0,0);
		for (int i = 0; p -> board[i][0] != '\0' && p -> board[i][0] != EOF; i++) {
			for (int i2 = 0; p -> board[i][i2] != '\0' && p -> board[i][i2] != EOF; i2++) {
				if (p -> board[i][i2] == '0') {
					fontColorSet(37,44);
					printf("::");
				}
				else if (p -> board[i][i2] == '1') {
					fontColorSet(30,44);
					printf("@@");
				}
				else if (p -> board[i][i2] == '2') {
					fontColorSet(37,44);
					printf("OO");
				}
				fontColorSet(37,44);
				printf(" ");
			}
			printf("\n");
		}
		fontColorSet(0,44);
		fontColorSet(1,37);
		printf("(%02d/%02d)\n按下wahk查看上一局，按下sdjl查看下一局,0q退出", count + 1, line);
		fontColorSet(0,0);
		chose = getch();
		if (chose == 0x1B) {
			if (kbhit() == 1) {
				getchar();
				chose = getch();
				if (chose == 0x41 || chose == 0x44) {
					chose = 0x4C;
				}
				else if (chose == 0x42 || chose == 0x43) {
					chose = 0x4E;
				}
			}
			else {
				free(p);
				return;
			}
		}
		switch (chose) {
			case 0x30:
			case 0x51:
			case 0x71:
				free(p);
				return;
				break;
			case 'w':
			case 'a':
			case 'l':
			case 'k':
				if (count == 0) {
					count = -1;
				}
				else {
					count -= 2;
				}
				break;
			case 's':
			case 'd':
			case 'h':
			case 'j':
				if (count + 1 >= line) {
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
	Max = max;
	free(p);
	return;
}
