#include "../include/head.h"

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


