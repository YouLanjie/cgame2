#include "../include/head.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void init() {
	unsigned short err = 0;

	if (strcmp(Save,"/usr/local/cgame2/data/save.txt") == 0) {   /* 在还为默认目录的情况下进行检测 */
		if (access("/usr/", 0) == EOF) {  /* 不存在/usr文件夹 */
			perror("\033[1;31m[init]: 不存在/usr/文件夹！\033[0m");
			printf("将使用当前目录作为软件数据存放目录\n");
			err = 1;
		}
		else {
			if (access("/usr/local", 0) == EOF) {
				perror("\033[1;31m[init]: 不存在/usr/local/文件夹！\033[0m");
				printf("将使用当前目录作为软件数据存放目录\n");
				err = 1;
			}
			else {
				if (access("/usr/local/cgame2", 0) == EOF) {
					perror("\033[1;31m[init](Game Dir): access \033[0m");
					strcpy(Data, "cgame2-data/data.txt");
					strcpy(Save, "cgame2-data/save.txt");
					printf("您可能没有安装deb包,将使用当前目录作为软件数据存放目录\n");
					err = 1;
				}
				else if(access("/usr/local/cgame2/data",0) == EOF) {
					mkdir("/usr/local/cgame2/data", 0777);
					if(access("/usr/local/cgame2/data",0) == EOF) {
						perror("\033[1;31m[init](Data Dir): fopen\033[0m");
						input();
						Clear2
						exit(1);
					}
				}
			}
		}
	}
	if (err == 1) {  /* 更改数据存放地址 */
		mkdir("./cgame2-data/", 0777);
		if (access("cgame2-data", 0) == EOF) {
			perror("\033[1;31m[init](mkdir)创建文件夹失败\033[0m");
			input();
			exit(1);
		}
		strcpy(Data, "./cgame2-data/data.txt");
		strcpy(Save, "./cgame2-data/save.txt");
		strcpy(Config, "./cgame2-data/config.txt");
		input();
	}
	if(access(Save,0) == EOF) {       /*创建Save文件*/
		fp = fopen(Save,"w");
		if (!fp) {
			perror("\033[1;31m[init](Save): fopen\033[0m");
			input();
			exit(1);
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
			exit(1);
		}
		fprintf(fp,"%d\n",p -> count);
		fclose(fp);
	}
	else {                            /*读取Data文件*/
		fp = fopen(Data,"r");
		fscanf(fp,"%d",&(p -> count));
		fclose(fp);
	}
	if(access(Config,0) == EOF) {       /*创建Save文件*/
		fp = fopen(Config,"w");
		if (!fp) {
			perror("\033[1;31m[init](Config): fopen\033[0m");
			input();
			exit(1);
		}
		fclose(fp);
		p -> count = 0;
		return;
	}
	return;
}

