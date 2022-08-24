#include "../include/head.h"

void Settings() {
	menuData data = menuDataInit();
	FILE * fp;

	fp = fopen(Config, "r"); /* 读取文件 */
	fscanf(fp, "%d%d%d%d", &config[0], &config[1], &config[2], &Max);
	fclose(fp);


	data.title = "游戏设置";
	data.cfg   = 3;
	if (!config[2]) {
		data.addText(&data,
			"自动下棋",
			"当前目录",
			"棋盘大小",
			"调试功能（扩展）",
			NULL
		);
		data.addTextData(&data, 0,
			"%s %s %s %s",
			"%z使用算法人机对战%z",
			"%z更改游戏数据的目录为当前目录（仅在%zLinux%z安装了软件包后可以关闭）%z",
			"%z更改棋盘的大小（格式为%znxn%z）%z",
			"%z调试选项显示开关，会保存%z"
		);
		data.addTextData(&data, 1,
			"%s %s %s %s",
			2,  2, 1, 2
		);
		data.addTextData(&data, 2,
			"%s         %s          %s    %s",
			&config[0], &config[1], &Max, &config[2]
		);
	}
	else {
		data.addText(&data,
			"自动下棋",
			"当前目录",
			"棋盘大小",
			"调试功能（扩展）",
			"	全自动下棋",
			"	绘图",
			"		棋盘重置",
			"	更多的棋盘大小",
			NULL
		);
		data.addTextData(&data, 0,
			"%s %s %s %s %s %s %s %s",
			"%z使用算法人机对战%z",
			"%z更改游戏数据的目录为当前目录（仅在%zLinux%z安装了软件包后可以关闭）%z",
			"%z更改棋盘的大小（格式为%znxn%z）%z",
			"%z调试选项显示开关，会保存%z",
			"%z测试功能，两方均使用自动下棋，不保存，会自动开启自动下棋\n按下空格让系统下棋，按下回车人工干预手动下棋%z",
			"%z测试功能，抛弃五子棋胜负判断而保存棋盘形状，不保存%z",
			"%z在开启绘图后，每切换到新的棋盘时清空整个棋盘%z",
			"%z部分解除棋盘大小的限制，最小值由%z15%z减少至%z0%z，最大值则不变（主要是因为棋盘的数组没有预设很多）%z"
		);
		data.addTextData(&data, 1,
			"%s %s %s %s %s %s %s %s",
			2,  2, 1, 2, 2, 2, 2, 2
		);
		data.addTextData(&data, 2,
			"%s         %s          %s    %s          %s          %s          %s          %s",
			&config[0], &config[1], &Max, &config[2], &config[3], &config[4], &config[5], &config[6]
		);
	}
	data.addTextData(&data, menuTextDataSetMax, "N N %s", 51);
	if (config[6]) {
		data.addTextData(&data, menuTextDataSetMin, "N N %s", 0);
	}
	else {
		data.addTextData(&data, menuTextDataSetMin, "N N %s", 15);
	}

	data.menuShow(&data);

#ifdef _WIN32
	config[1] = 1;
#endif

	if (config[3] == 1) {
		config[0] = 1;
	}

	fp = fopen(Config, "w");
	if (fp) {
		fprintf(fp,"%d %d %d %d", config[0], config[1], config[2], Max);
		fclose(fp);
	}
	return;
}

