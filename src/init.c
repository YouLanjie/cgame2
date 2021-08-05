#include "../include/head.h"

void init() {
	unsigned short err = 0;
	int a;

	Clear
	if (strcmp(LANGFILE, "None") != 0) {
		fp = fopen(Config, "r");
		if (!fp) {
			a = 0;
		}
		else {
			fscanf(fp, "%d%d", &a, &a);
			fclose(fp);
			if (a == 1) {
				strcpy(LANGFILE, "/usr/local/cgame2/doc/LANG_en");
			}
			else {
				strcpy(LANGFILE, "/usr/local/cgame2/doc/LANG_ch");
			}
		}
		fp = fopen(LANGFILE, "r");
		if (!fp && strcmp(LANGFILE, "/usr/local/cgame2/doc/LANG_ch")) {
			printf("\033[1;31m不存在中文语言文件！尝试改用英文文件！\nNo Chinese language file exists! Try switching to English language files!\033[0m\n\n");
			strcpy(LANGFILE, "/usr/local/cgame2/doc/LANG_en");
			input();
		}
		fp = fopen(LANGFILE, "r");
		if (!fp) {
			printf("\033[1;31m因为不存在语言文件，使用内置中文，中英文设置失效！\nBecause there is no language file, use the built-in Chinese, Chinese and English settings fail!\n这可能是因为您没有安装deb包导致的,我们将尝试在当前目录寻找\"doc/LANG_ch\"文件，如果文件存在，我们将通知您\nWe will try to find the file \"doc/LANG_ch\" in the current directory, if it exists, we will inform you.\033[0m\n");
			strcpy(LANG[0], "\033[1;31m[init]: 不存在/usr/文件夹！\033[0m");
			strcpy(LANG[1], "\033[1;31m[init]: 不存在/usr/local/文件夹！\033[0m");
			strcpy(LANG[2], "\033[1;31m[init](Game Dir): access \033[0m");
			strcpy(LANG[3], "\033[1;31m[init](Data Dir): fopen\033[0m");
			strcpy(LANG[4], "\033[1;31m[init](mkdir)创建文件夹失败\033[0m");
			strcpy(LANG[5], "\033[1;31m[init](Save): fopen\033[0m");
			strcpy(LANG[6], "\033[1;31m[init](Data): fopen\033[0m");
			strcpy(LANG[7], "\033[1;31m[init](Config): fopen\033[0m");
			strcpy(LANG[8], "将使用当前目录作为软件数据存放目录\n");
			strcpy(LANG[9], "您可能没有安装deb包,将使用当前目录作为软件数据存放目录\n");
			strcpy(LANG[10], "\033[8;11H\033[1;33m1.开始游戏\033[8;37H2.游戏记录\033[9;11H3.游戏帮助\033[9;37H4.清除存档");
			strcpy(LANG[11], "\033[8;11H\033[1;33m5.设置\033[8;33H0.退出游戏\033[0m");
			strcpy(LANG[12], "游戏菜单");
			strcpy(LANG[13], "黑方下\n");
			strcpy(LANG[14], "白方下\n");
			strcpy(LANG[15], "\033[1;33m\033[20;1H你不能下在非空的格子!\033[0m\n");
			strcpy(LANG[16], "\033[1;33m请确认退出！本次游戏将不会记录！（Y/n）\n");
			strcpy(LANG[17], "\033[33m游戏结束，");
			strcpy(LANG[18], "黑方");
			strcpy(LANG[19], "白方");
			strcpy(LANG[20], "胜利！\n\033[31m按Enter返回\n\033[0m");
			strcpy(LANG[21], "\033[1;33m你还没有游戏记录，赶紧去玩一下吧！\033[0m\n输入任意按键返回\n");
			strcpy(LANG[22], "无法打开存档，请自行确认存档文件是否存在！\n按任意按键返回\n");
			strcpy(LANG[23], "\033[17;1H\033[0;1;31m按下L查看上一局，按下N查看下一局,0退出\033[0m");
			strcpy(LANG[24], "\033[18;1H\033[33m这已经是第一个记录了\033[0m\n");
			strcpy(LANG[25], "\033[18;1H\033[33m这已经是最后一个记录了\033[0m\n");
			strcpy(LANG[26], "\033[7;4H按下0,q,Q退出\033[8;4HW S A D或者方向键控制上下左右，空格下子\033[9;4H@为黑棋,O为白棋,+为空白");
			strcpy(LANG[27], "游戏帮助");
			strcpy(LANG[28], "\033[1;33m请确清除存档，您将失去您的所有记录！（Y/n）\n");
			strcpy(LANG[29], "\n由于使用的是当前目录，所以会删除数据文件夹\n");
			strcpy(LANG[30], "\033[1;31m[main](remove Data): \033[0m");
			strcpy(LANG[31], "\033[1;31m[main](remove Save): \033[0m");
			strcpy(LANG[32], "\033[1;31m[main](remove Config): \033[0m");
			strcpy(LANG[33], "是否直接退出游戏?否则将重新创建目录!(默认退出)Y/n\n");
			strcpy(LANG[34], "\033[?25h\033[2;25H\033[1;32m游戏设置\n\033[33mq键退出，退出保存\033[0m\n");
			strcpy(LANG[35], "游戏时是否启用AI\033[4;24H( )\033[1;31m\033[4;27H|\033[0m使用英语\033[4;48H( )\n");
			strcpy(LANGFILE, "doc/LANG_ch");
			fp = fopen(LANGFILE, "r");
			if (!fp) {
				strcpy(LANGFILE, "doc/LANG_en");
				fp = fopen(LANGFILE, "r");
				if(fp) {
					for (int i = 0; i < LANGFILELINE; i++) {
						fgets(LANG[i], 200, fp);
					}
					fclose(fp);
					printf("找到文件，加载完成！\nFind the file and load it!\n");
					input();
				}
				else {
					strcpy(LANGFILE, "None");
				}
			}
			else {
				for (int i = 0; i < LANGFILELINE; i++) {
					fgets(LANG[i], 200, fp);
				}
				fclose(fp);
				printf("找到文件，加载完成！\nFind the file and load it!\n");
				input();
			}
		}
		else {
			for (int i = 0; i < LANGFILELINE; i++) {
				fgets(LANG[i], 200, fp);
				LANG[i][strlen(LANG[i]) - 1] = '\0';
			}
			fclose(fp);
		}
	}
	if (strcmp(Save,"/usr/local/cgame2/data/save.txt") == 0) {   /* 在还为默认目录的情况下进行检测 */
		if (access("/usr/", 0) == EOF) {  /* 不存在/usr文件夹 */
			perror(LANG[0]);
			printf("%s",LANG[8]);
			err = 1;
		}
		else {
			if (access("/usr/local", 0) == EOF) {
				perror(LANG[1]);
				printf("%s",LANG[8]);
				err = 1;
			}
			else {
				if (access("/usr/local/cgame2", 0) == EOF) {
					perror(LANG[2]);
					strcpy(Data, "cgame2-data/data.txt");
					strcpy(Save, "cgame2-data/save.txt");
					printf("LANG[9]");
					err = 1;
				}
				else if(access("/usr/local/cgame2/data",0) == EOF) {
					mkdir("/usr/local/cgame2/data", 0777);
					if(access("/usr/local/cgame2/data",0) == EOF) {
						perror(LANG[3]);
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
			perror(LANG[4]);
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
			perror(LANG[5]);
			input();
			exit(1);
		}
		fclose(fp);
		p -> count = 0;
	}
	if(access(Data,0) == EOF) {       /*创建Data文件*/
		fp = fopen(Data,"w");
		if (!fp) {
			perror(LANG[6]);
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
	if(access(Config,0) == EOF) {       /* 创建Config文件 */
		fp = fopen(Config,"w");
		if (!fp) {
			perror(LANG[7]);
			input();
			exit(1);
		}
		fprintf(fp, "1 0");
		fclose(fp);
		p -> count = 0;
		return;
	}
	return;
}

