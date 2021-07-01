#include "../include/head.h"

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


