#include "../include/head.h"

void Init() {
	unsigned short error = 0;
	int config[3] = {1, 0, 0};    //是否使用英语

	Clear
	fp = fopen(Config, "r"); //打开配置文件
	if (!fp) {               //如果不存在，默认中文
		config[0] = 1;
		config[1] = 0;
		config[2] = 0;
		Max = 15;
	}
	else {
		fscanf(fp, "%d%d%d%d", &config[0], &config[1], &config[2], &Max);  //读取文件
		fclose(fp);
	}
	if (!config[1]) {
		//拷贝内置数据到变量里
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
		strcpy(LANG[35], "游戏时是否启用AI\033[4;24H( )\033[1;31m\033[4;27H|\033[0m使用英语\033[4;48H( )\n使用当前目录作为游戏目录\033[5;24H( )");
	}
	else {
		//拷贝内置数据到变量里
		strcpy(LANG[0], "\033[1;31m[init]: /usr/ folder does not exist! \033[0m");
		strcpy(LANG[1], "\033[1;31m[init]: /usr/local/ folder does not exist! \033[0m");
		strcpy(LANG[2], "\033[1;31m[init](Game Dir): access \033[0m");
		strcpy(LANG[3], "\033[1;31m[init](Data Dir): fopen\033[0m");
		strcpy(LANG[4], "\033[1;31m[init](mkdir) Failed to create folder \033[0m");
		strcpy(LANG[5], "\033[1;31m[init](Save): fopen\033[0m");
		strcpy(LANG[6], "\033[1;31m[init](Data): fopen\033[0m");
		strcpy(LANG[7], "\033[1;31m[init](Config): fopen\033[0m");
		strcpy(LANG[8], "The current directory will be used as the software data storage directory");
		strcpy(LANG[9], "You may not have the deb package installed, the current directory will be used as the software data storage directory");
		strcpy(LANG[10], "\033[8;11H\033[1;33m1.Start the game\033[8;37H2.Game history\033[9;11H3.Game help\033[9;37H4.Clear the archive");
		strcpy(LANG[11], "\033[8;11H\033[1;33m5.Setting(设置)\033[8;33H0.Quit the game\033[0m");
		strcpy(LANG[12], "Game menu");
		strcpy(LANG[13], "Black plays");
		strcpy(LANG[14], "White plays");
		strcpy(LANG[15], "\033[1;33m\033[20;1HYou can't play on non-empty squares! \033[0m");
		strcpy(LANG[16], "\033[1;33m Please make sure to quit! This game will not be recorded! (Y/n)");
		strcpy(LANG[17], "\033[33mThe game is over and");
		strcpy(LANG[18], "Black");
		strcpy(LANG[19], "White");
		strcpy(LANG[20], "wins! \n \033[31m Press Enter to return to \n \033[0m");
		strcpy(LANG[21], "\033[1;33mYou don't have a game record yet, so hurry up and play! \033[0m\nEnter any key to return");
		strcpy(LANG[22], "Can't open the archive, please check the archive file by yourself! \nPress any key to return to");
		strcpy(LANG[23], "\033[17;1H\033[0;1;31mPress L to view the previous game, press N to view the next game,0 to exit \033[0m");
		strcpy(LANG[24], "\033[18;1H\033[33mThis is the first record already \033[0m");
		strcpy(LANG[25], "\033[18;1H\033[33mThis has been the last record \033[0m");
		strcpy(LANG[26], "\033[7;4H Press 0,q,Q to exit \033[8;4HW S A D or arrow keys to control up and down, space to play \033[9;4H@ for black, O for white, + for blank");
		strcpy(LANG[27], "Game Help");
		strcpy(LANG[28], "\033[1;33m Please make sure to clear the archive, you will lose all your records! (Y/n)");
		strcpy(LANG[29], "\nThe data folder will be deleted because the current directory is used");
		strcpy(LANG[30], "\033[1;31m[main](remove Data): \033[0m");
		strcpy(LANG[31], "\033[1;31m[main](remove Save): \033[0m");
		strcpy(LANG[32], "\033[1;31m[main](remove Config): \033[0m");
		strcpy(LANG[33], "Do I exit the game directly? Otherwise the directory will be recreated! (Default exit)Y/n");
		strcpy(LANG[34], "\033[?25h\033[2;25H\033[1;32mGame settings\033[3;1H\033[33mq key to exit, exit save\033[0m");
		strcpy(LANG[35], "\033[4;1HWhether AI is enabled during game play \033[4;24H( )\033[1;31m\033[4;27H|\033[0m Use English \033[4;48H( )");
	}
	if (strcmp(Save,"/usr/local/cgame2/data/save.txt") == 0) {   /* 在还为默认目录的情况下进行检测文件是否还在 */
		if (access("/usr/", 0) == EOF) {  /* 不存在/usr文件夹(非Linux系统) */
			perror(LANG[0]);
			printf("%s",LANG[8]);
			error = 1;
		}
		else {
			if (access("/usr/local", 0) == EOF) {
				perror(LANG[1]);
				printf("%s",LANG[8]);
				error = 1;
			}
			else {
				if (access("/usr/local/cgame2", 0) == EOF) {
					perror(LANG[2]);
					strcpy(Data, "cgame2-data/data.txt");
					strcpy(Save, "cgame2-data/save.txt");
					printf("LANG[9]");
					error = 1;
				}
				else if(access("/usr/local/cgame2/data",0) == EOF) {
					mkdir("/usr/local/cgame2/data", 0777);
					if(access("/usr/local/cgame2/data",0) == EOF) {
						perror(LANG[3]);
						Input();
						Clear2
						exit(1);
					}
				}
			}
		}
	}
	if (error == 1 || config[2] == 1) {  /* 更改数据存放地址 */
		mkdir("./cgame2-data/", 0777);
		if (access("cgame2-data", 0) == EOF) {
			perror(LANG[4]);
			Input();
			exit(1);
		}
		fp = fopen("./cgame2-data/config.txt","w");
		if (!fp) {
			return;
		}
		else {
			fprintf(fp, "%d %d %d %d", config[0], config[1], config[2], Max);
			fclose(fp);
		}
		strcpy(Data, "./cgame2-data/data.txt");
		strcpy(Save, "./cgame2-data/save.txt");
		strcpy(Config, "./cgame2-data/config.txt");
		config[2] = 1;
	}
	else if (config[2] == 0) {  /* 更改数据存放地址 */
		fp = fopen("/usr/local/cgame2/data/config.txt","w");
		if (!fp) {
			return;
		}
		else {
			fprintf(fp, "%d %d %d %d", config[0], config[1], config[2], Max);
			fclose(fp);
		}
		strcpy(Data, "/usr/local/cgame2/data/data.txt");
		strcpy(Save, "/usr/local/cgame2/data/save.txt");
		strcpy(Config, "/usr/local/cgame2/data/config.txt");
	}
	if(access(Save,0) == EOF) {       /*创建Save文件*/
		fp = fopen(Save,"w");
		if (!fp) {
			perror(LANG[5]);
			Input();
			exit(1);
		}
		fclose(fp);
		p -> count = 0;
	}
	if(access(Data,0) == EOF) {       /*创建Data文件*/
		fp = fopen(Data,"w");
		if (!fp) {
			perror(LANG[6]);
			Input();
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
			Input();
			exit(1);
		}
		if (!config[2]) {
			fprintf(fp, "1 0 0 15");
		}
		else {
			fprintf(fp, "1 0 1 15");
		}
		fclose(fp);
		p -> count = 0;
		return;
	}
	return;
}

