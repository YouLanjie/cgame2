#include "../include/head.h"
#include <stdio.h>

void History() {
	int count;              //数数
	int b = 0;              //选择
	char board[52][50];     //棋盘信息
	int i = 0, i2 = 0;
	long way = 0;

	fp = fopen(Save,"rb");
	if (!fp) {
		printf("%s",LANG[22]);
		Input();
		return;
	}
	fseek(fp, 0L, 2);
	way = ftell(fp);
	fseek(fp, 0L, 0);
	if(ftell(fp) == way) {
		printf("%s",LANG[21]);
		Input();
		return;
	}
	fseek(fp, 0L, 0);
	for (count = 0; ftell(fp) <= way; count++) {
		fgets(board[0],50,fp);
		for (i = 1; board[i - 1][0] != '\n' && i < 52; i++) {
			fgets(board[i],50,fp);
		}
		Clear
		printf("\033[1;31m%s\033[0m",board[0]);
		for (i = 1; board[i][0] != '\n' && board[i][0] != EOF; i++) {
			for (i2 = 0; board[i][i2] != '\n' && board[i][i2] != EOF; i2++) {
				if (board[i][i2] == '0') {
					printf("\033[37;40;2m + \033[0m");
				}
				else if (board[i][i2] == '1') {
					printf("\033[30;47m @ \033[0m");
				}
				else if (board[i][i2] == '2') {
					printf("\033[37;40m O \033[0m");
				}
			}
			printf("%c",board[i][i2]);
		}
		printf("%s",LANG[23]);
		b = Input();
		Clear2
		if (b == 0x1B) {
			if (KbhitHas() == 1) {
				getchar();
				b = Input();
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
					printf("%s",LANG[24]);
					fseek(fp,0L,0);
					count--;
				}
				else {
					fseek(fp, 0L, 0);
					count -= 2;
					for (i = 0; i < count; i++) {
						for (i = 0; board[i][0] != '\n'; i++) {
							fgets(board[i],50,fp);
						}
					}
				}
				break;
			case 0x4E:
			case 0x6E:
				if (ftell(fp) == way) {
					printf("%s",LANG[25]);
					count--;
					for (i = 0; i < count - 1; i++) {
						for (i = 0; board[i][0] != '\n'; i++) {
							fgets(board[i],50,fp);
						}
					}
				}
				break;
			default:
				fseek(fp, 0L, 0);
				count--;
				for (i = 0; i < count - 1; i++) {
					for (i = 0; board[i][0] != '\n'; i++) {
						fgets(board[i],50,fp);
					}
				}
				break;
		}
	}
	fclose(fp);
	return;
}
