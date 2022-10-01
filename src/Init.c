#include "../include/head.h"

void Init()
{
	if (GameInfo == NULL) {
		GameInfo = (Games *)malloc(sizeof(Games));
		GameInfo->config.GameDir = (char *)malloc(40);
		GameInfo->config.Config  = (char *)malloc(40);
		GameInfo->config.Save    = (char *)malloc(40);
		changeDir("/etc/cgame2/");
	}
	if (GameInfo != NULL) {
		GameInfo->config.use_AI  = 0;
		GameInfo->config.chdir   = 0;
		GameInfo->config.max     = 15;
		GameInfo->config.newest_history = 1;
		GameInfo->config.debug   = 0;
		GameInfo->config.all_AI  = 0;
		GameInfo->config.draw    = 0;
		GameInfo->config.draw_reset = 0;
		GameInfo->config.more_max   = 0;
		GameInfo->config.show_count = 0;
	}
	return;
}

void readConfig()
{
	int error = 0;
	FILE * fp;

#ifdef _WIN32
	changeDir("./cgame2-data/");
	GameInfo->config.chdir = 1;
#endif
	if (access(GameInfo->config.GameDir, 0) == EOF) {    /* 判断是否有数据目录 */
		changeDir("./cgame2-data/");
		GameInfo->config.chdir = 1;
		if (access(GameInfo->config.GameDir, 0) == EOF) {    /* 无则创建 */
#ifdef __linux
			mkdir(GameInfo->config.GameDir, 0777);
#endif
#ifdef _WIN32
			mkdir(GameInfo->config.GameDir);
#endif
		}
		if (access(GameInfo->config.GameDir, 0) == EOF) {    /* 再无就退出 */
			endwin();
			perror("无法创建游戏数据文件夹");
			exit(-1);
		}
		GameInfo->config.chdir = 1;
	}

	if(access(GameInfo->config.Config,0) == EOF) {       /* 是否有Config文件 */
		fp = fopen(GameInfo->config.Config, "w");    /* 创建Config文件 */
		if (!fp) {    /* 是否无法创建 */
#ifdef __linux
			endwin();
#endif
			perror("[init](Config): fopen");
			exit(-1);
		}
		ConfigWrite;    /* 创建Config文件并写入配置 */
		fclose(fp);
	} else {
		fp = fopen(GameInfo->config.Config, "r");    /* 打开Config文件 */
		if (!fp) {
#ifdef __linux
			endwin();
#endif
			perror("Can't open file");
			exit(-1);
		}
		error = ConfigRead;

		if (error == EOF) {    /* 如果读取错误 */
			perror("[init](Config): fscanf");
			fclose(fp);
			fp = fopen(GameInfo->config.Config, "w");    /* 则写入数据 */
			Init();
			ConfigWrite;
		}
		fclose(fp);
	}

	if (GameInfo->config.chdir == 1 && strcmp(GameInfo->config.Config, "/etc/cgame2/config.txt") == 0) {    /* 更改目录为当前目录 */
		changeDir("./cgame2-data/");    /* 更该目录为当前目录 */
		if ((fp = fopen(GameInfo->config.Config, "w"))) {    /* 拷贝当前的设置数据到更改后的目录 */
			ConfigWrite;
			fclose(fp);
		}
		Init();    /* 重新读取 */
	}
#ifdef __linux
	else if (GameInfo->config.chdir == 0 && strcmp(GameInfo->config.Config, "./cgame2-data/config.txt") == 0) {    /* 更改目录为系统目录（Linux限定） */
		changeDir("/etc/cgame2/");    /* 更改目录为系统目录 */
		if ((fp = fopen(GameInfo->config.Config, "w"))) {    /* 拷贝当前的设置数据到更改后的目录 */
			ConfigWrite;
			fclose(fp);
		}
		readConfig();    /* 重新读取 */
	}
#endif
	if(access(GameInfo->config.Save, 0) == EOF) {       /* 如果没有Save文件则创建Save文件 */
		fp = fopen(GameInfo->config.Save,"w");
		if (!fp) {
#ifdef __linux
			endwin();
#endif
			perror("\033[1;31m[init](Save): fopen\033[0m");
			exit(-1);
		}
		fclose(fp);
	}
	return;
}

void changeDir(char * dir) {    /* 更改文件夹的函数 */
	if (dir != NULL) {
		strcpy(GameInfo->config.GameDir, dir);
	}

	strcpy(GameInfo->config.Config, GameInfo->config.GameDir);
	strcat(GameInfo->config.Config, "config.txt");

	strcpy(GameInfo->config.Save, GameInfo->config.GameDir);
	strcat(GameInfo->config.Save, "save.txt");
	return;
}

