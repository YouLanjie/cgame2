#include "../include/head.h"
#include <curses.h>

void Init() {
	int error = 0;
	FILE * fp;

#ifdef _WIN32
	changeDir("./cgame2-data/");
	config[1] = 1;
#endif
	if (access(GameDir, 0) == EOF) {    /* 判断是否有数据目录 */
		changeDir("./cgame2-data/");
		config[1] = 1;
		if (access(GameDir, 0) == EOF) {    /* 无则创建 */
#ifdef __linux
			mkdir(GameDir, 0777);
#endif
#ifdef _WIN32
			mkdir(GameDir);
#endif
		}
		config[1] = 1;
	}

	if(access(Config,0) == EOF) {       /* 是否有Config文件 */
		fp = fopen(Config, "w");    /* 创建Config文件 */
		if (!fp) {    /* 是否无法创建 */
#ifdef __linux
			endwin();
#endif
			perror("[init](Config): fopen");
			exit(-1);
		}
		fprintf(fp, "%d %d %d",config[0], config[1], Max);    /* 创建Config文件并写入配置 */
		fclose(fp);
	}
	else {
		fp = fopen(Config, "r");    /* 打开Config文件 */
		if (!fp) {
#ifdef __linux
			endwin();
#endif
			perror("Can't open file");
			exit(-1);
		}
		error = fscanf(fp,"%d%d%d", &config[0], &config[1], &Max);

		if (error == EOF) {    /* 如果读取错误 */
			perror("[init](Config): fscanf");
			fclose(fp);
			fp = fopen(Config, "w");    /* 则写入数据 */
			config[0] = config[1] = 0;
			Max = 15;
			fprintf(fp, "%d %d %d",config[0], config[1], Max);
		}
		fclose(fp);
	}

	if (config[1] == 1 && strcmp(Config, "/etc/cgame2/config.txt") == 0) {    /* 更改目录为当前目录 */
		changeDir("./cgame2-data/");    /* 更该目录为当前目录 */
		if ((fp = fopen(Config, "w"))) {    /* 拷贝当前的设置数据到更改后的目录 */
			fprintf(fp,"%d %d %d", config[0], config[1], Max);
			fclose(fp);
		}
		Init();    /* 重新读取 */
	}
#ifdef __linux
	else if (config[1] == 0 && strcmp(Config, "./cgame2-data/config.txt") == 0) {    /* 更改目录为系统目录（Linux限定） */
		changeDir("/etc/cgame2/");    /* 更改目录为系统目录 */
		if ((fp = fopen(Config, "w"))) {    /* 拷贝当前的设置数据到更改后的目录 */
			fprintf(fp,"%d %d %d", config[0], config[1], Max);
			fclose(fp);
		}
		Init();    /* 重新读取 */
	}
#endif
	if(access(Save, 0) == EOF) {       /* 如果没有Save文件则创建Save文件 */
		fp = fopen(Save,"w");
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
	GameDir = dir;
	strcpy(Config, GameDir);
	strcat(Config, "config.txt");
	strcpy(Save, GameDir);
	strcat(Save, "save.txt");
	return;
}

