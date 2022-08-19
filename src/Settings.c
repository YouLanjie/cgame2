#include "../include/head.h"

void Settings() {
	menuData data = menuDataInit();
	FILE * fp;

	fp = fopen(Config, "r"); /* 读取文件 */
	fscanf(fp, "%d%d%d", &config[0], &config[1], &Max);
	fclose(fp);


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
	if (fp) {
		fprintf(fp,"%d %d %d", config[0], config[1], Max);
		fclose(fp);
	}
	return;
}

