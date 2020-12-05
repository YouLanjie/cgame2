#include "src/head.h"                           //导入头文件

int iffile(char a[50]) {
	int b = 1;
	FILE *fp;

	fp = fopen(a,"r");
	if(!fp) {
		b = 0;
		return b;
	}
	fclose(fp);
	return b;
}

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

void help() {
	int i;
	char b[200];
	FILE *fp;

	fp = fopen("~/.cgamefile/cgame2/help","r");
	if (!fp) {
		puts("\t\t\t\t 帮助文档缺失！");
		printf("按任意按键退出：\n");
		getchar();
		return;
	}
	else {
		for (i = 0; i < 10; i++) {
			fgets(b,200,fp);
			printf("%s",b);
		}
		fclose(fp);
	}
	return;
}

int main() {
	int a=0,b=0;

	if(iffile("~/.cgamefile/cgame2/help") == 0) {
		system("mkdir ~/.cgamefile");
		system("mkdir ~/.cgamefile/cgame2");
		system("touch ~/.cgamefile/cgame2/help");
		system("echo -e \"\\t\\t\\t游戏帮助\\n\" >> ~/.cgamefile/cgame2/help");
	}

	Clear
	while (welcome(a) <= 200) {
		b = getchar();
		getchar();
		switch (b) {
			case 0x1B:
			case 0x30:
				Clear
				return 0;
				break;
			case 0x31:
				Clear
				printf("暂未开发\n");
				getchar();
				break;
			case 0x32:
				Clear
				printf("暂未开发\n");
				getchar();
				break;
			case 0x33:
				Clear
				help();
				Clear
				break;
			default:
				Clear
				return 0;
				break;
		}
		Clear
	}
	Clear
	return 0;
}