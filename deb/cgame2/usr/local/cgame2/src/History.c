#include "../include/head.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void History() {
	int count;              //数数
	int b = 0;              //选择
	char board[52][50];     //棋盘信息
	long way = 0;           //文件的大小
	pid_t pid;

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
		Clear
		fgets(board[0],50,fp);
		for (int i = 1; board[i - 1][0] != '\n' && board[i - 1][0] != EOF && i < 52 && ftell(fp) <= way; i++) {
			fgets(board[i],50,fp);
		}
		printf("\033[H\033[1;31m%s\033[0m",board[0]);
		for (int i = 1; board[i][0] != '\n' && board[i][0] != EOF; i++) {
			for (int i2 = 0; board[i][i2] != '\n' && board[i][i2] != EOF; i2++) {
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
			printf("\n");
		}
		printf("%s",LANG[23]);
		b = Input();
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
					printf("\033[s");
					KbhitNoTime();
					pid = fork();
					if(pid == 0) {
						system("sleep 0.001");
						printf("\033[u%s",LANG[24]);
						exit(0);
					}
					fseek(fp,0L,0);
					count = -1;
				}
				else {
					fseek(fp, 0L, 0);
					for (int i = 0; i < count && ftell(fp) <= way; i++) {
						fgets(board[0],50,fp);
						for (int i2 = 1; board[i2 - 1][0] != '\n' && board[i2 - 1][0] != EOF && ftell(fp) <= way; i2++) {
							fgets(board[i2],50,fp);
						}
					}
					count -= 2;
				}
				break;
			case 0x4E:
			case 0x6E:
				if (ftell(fp) >= way) {
					printf("\033[s");
					KbhitNoTime();
					pid = fork();
					if(pid == 0) {
						system("sleep 0.001");
						printf("\033[u%s",LANG[25]);
						exit(0);
					}
					fseek(fp, 0L, 0);
					for (int i = 0; i < count && ftell(fp) <= way; i++) {
						fgets(board[0],50,fp);
						for (int i2 = 1; board[i2 - 1][0] != '\n' && board[i2 - 1][0] != EOF && ftell(fp) <= way; i2++) {
							fgets(board[i2],50,fp);
						}
					}
					count--;
				}
				break;
			case 'r':
			case 'R':
				Clear2
				fseek(fp, 0L, 0);
				count = -1;
				break;
			default:
				fseek(fp, 0L, 0);
				for (int i = 0; i < count && board[i - 1][0] != '\n' && board[i - 1][0] != EOF; i++) {
					fgets(board[0],50,fp);
					for (int i2 = 0; board[i2 - 1][0] != '\n' && board[i2 - 1][0] != EOF; i++) {
						fgets(board[i2],50,fp);
					}
				}
				count--;
				break;
		}
		KbhitNoTime();
		printf("\033[0m\033[2;1H");
	}
	fclose(fp);
	return;
}
