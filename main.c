#include "src/head.h"                           //导入头文件

int welcome(int a) {
	puts("\t\t\t\t     欢迎\n");
	puts("\t\t\t\t  1.开始游戏");
	puts("\t\t\t\t  2.游戏记录");
	puts("\t\t\t\t  3.游戏帮助");
	puts("\t\t\t\t  0.退出游戏");
	printf("请选择：");
	a++;
	return a;
}

int main() {
	int a=0;

	Clear
	while (welcome(a) != 200) {
		a = getchar();
		switch (a) {
		case 0x30:
			return 0;
			break;
		
		default:
			return 0;
			break;
		}
		Clear
	}
	Clear
	return 0;
}