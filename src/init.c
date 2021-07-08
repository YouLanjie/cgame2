#include "../include/head.h"
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

void init() {
	FILE *fp;
	int a = 0;            //保存转换后的数字
	int c = 0;            //语言选择的结果
	int count = 0;
	int If = 0;
	char d[5];            //查看语言
	char b[5];            //转换前的字符

	if (strcmp(Save,"./cgame2/save.txt") != 0) {
		if (access("/usr/", 0) == EOF) {
			perror("\033[1;31m[init]: 不存在/usr/文件夹！\033[0m");
			printf("将使用当前目录作为软件数据存放目录\n");
			mkdir("./cgame2/", 0777);
			strcpy(Data, "./cgame2/data.txt");
			strcpy(Save, "./cgame2/save.txt");
			input();
		}
		else {
			if (access("/usr/local", 0) == EOF) {
				perror("\033[1;31m[init]: 不存在/usr/local/文件夹！\033[0m");
				printf("将使用当前目录作为软件数据存放目录\n");
				mkdir("./cgame2/", 0777);
				strcpy(Data, "./cgame2/data.txt");
				strcpy(Save, "./cgame2/save.txt");
				input();
			}
			else {
				if (access("/usr/local/cgame2", 0) == EOF) {
					perror("\033[1;31m[init]: \033[0m");
					strcpy(Data, "./cgame2/data.txt");
					strcpy(Save, "./cgame2/save.txt");
					if (access("./cgame2/", 0) == EOF) {
						printf("您可能没有安装deb包,将使用当前目录作为软件数据存放目录\n");
						mkdir("./cgame2/", 0775);
						input();
					}
					else {
						Clear
					}
				}
				else if(access("/usr/local/cgame2/data",0) == EOF) {
					mkdir("/usr/local/cgame2/data", 0777);
					if(access("/usr/local/cgame2/data",0) == EOF) {
						perror("\033[1;31m[init](Data Dir): fopen\033[0m");
						input();
					}
				}
			}
		}
	}
	if (strcmp(Save,"./cgame2/save.txt") == 0) {
		mkdir("cgame2", 0775);
		if (strcmp(Save,"./cgame2/save.txt") == 0) {
			perror("\033[1;31m[init](Data Dir): fopen\033[0m");
			input();
		}
	}
	if(access(Save,0) == EOF) {       /*创建Save文件*/
		fp = fopen(Save,"w");
		if (!fp) {
			perror("\033[1;31m[init](Save): fopen\033[0m");
			input();
			return;
		}
		fclose(fp);
		p -> count = 0;
		return;
	}
	if(access(Data,0) == EOF) {       /*创建Data文件*/
		fp = fopen(Data,"w");
		if (!fp) {
			perror("\033[1;31m[init](Data): fopen\033[0m");
			input();
			return;
		}
		fprintf(fp,"%d\n",p -> count);
		fclose(fp);
	}
	else {                            /*读取Data文件*/
		fp = fopen(Data,"r");
		fscanf(fp,"%s",b);
		a = atoi(b);
		p -> count = a;
		fclose(fp);
	}
	return;
}


