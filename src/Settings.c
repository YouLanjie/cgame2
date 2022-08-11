#include "../include/head.h"

void Settings() {
#ifdef __linux
	struct winsize size;
#endif
	menuData data;
	FILE * fp;

	fp = fopen(Config, "r"); /* 读取文件 */
	fscanf(fp, "%d%d%d", &config[0], &config[1], &Max);
	fclose(fp);
#ifdef __linux
	printf("\033[?25h");
#endif

	menuDataInit(&data);
	data.title = "游戏设置";
	data.cfg   = 3;
	data.addText(&data, "自动下棋", "当前目录", "棋盘大小", NULL);
	data.addTextData(&data, 1, "%s%s%s", 2, 2, 1);
	data.addTextData(&data, 2, "%s%s%s", &config[0], &config[1], &Max);

	data.menuShow(&data);

#ifdef _WIN32
	config[1] = 1;
#endif
	fp = fopen(Config, "w");
	fprintf(fp,"%d %d %d", config[0], config[1], Max);
	fclose(fp);
	if (config[1] == 1 && strcmp(Config, "/etc/cgame2/config.txt") == 0) {
		changeDir("./cgame2-data/");
	}
	else if (config[1] == 0 && strcmp(Config, "./cgame2-data/config.txt") == 0) {
		changeDir("/etc/cgame2/");
	}
	if ((fp = fopen(Config, "w"))) {
		fprintf(fp,"%d %d %d", config[0], config[1], Max);
		fclose(fp);
	}
#ifdef __linux
	printf("\033[?25l");
#endif
	return;
}

