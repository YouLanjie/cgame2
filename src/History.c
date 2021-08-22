#include "../include/head.h"

void History() {
	int count;              //数数
	int b;                  //选择
	char a[3417];           //棋盘信息

	if(p -> count == 0) {
		printf("%s",LANG[21]);
		Input();
		return;
	}
	fp = fopen(Save,"rb");
	if (!fp) {
		printf("%s",LANG[22]);
		Input();
		return;
	}
	for (count = 0; count < p -> count; count++) {
		fread(a,3417,1,fp);
		printf("\033[1;1H");
		puts(a);
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
					count--;;
				}
				else {
					fseek(fp,-6834L,1);
					count -= 2;
				}
				break;
			case 0x4E:
			case 0x6E:
				if (count == p -> count - 1) {
					printf("%s",LANG[25]);
					fseek(fp,-3417L,3);
					count--;
				}
				break;
			default:
				fseek(fp,-3417L,1);
				count--;
				break;
		}
	}
	fclose(fp);
	return;
}

