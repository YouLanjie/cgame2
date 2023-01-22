#include "../include/head.h"

void Settings() {
	ctools_menu_t * data = NULL;
	FILE * fp;

	fp = fopen(GameInfo->config.Config, "r"); /* 读取文件 */
	ConfigRead;
	fclose(fp);


	ctools_menu_t_init(&data);
	data -> title = "游戏设置";
	data -> cfg   = 3;
	data -> text  = NULL;
	if (!GameInfo->config.debug) {
		ctools_menu_AddText(data,
			"自动下棋",
			"当前目录",
			"棋盘大小",
			"历史默认最新",
			"调试功能（扩展）",
			NULL
		);
		ctools_menu_AddTextData(data, ctools_menu_TextDataDescribe,
			"%s %s %s %s %s",
			"使用算法人机对战",
			"更改游戏数据的目录为当前目录（仅在Linux安装了软件包后可以关闭）",
			"更改棋盘的大小N的值（格式为N x N）",
			"在查看历史记录时默认查看最后一个记录",
			"调试选项显示开关"
		);
		ctools_menu_AddTextData(data, ctools_menu_TextDataSetType,
			"%s %s %s %s %s",
			2,  2, 1, 2, 2
		);
		ctools_menu_AddTextData(data, ctools_menu_TextDataSetVar,
			"%s %s %s %s %s",
			&GameInfo->config.use_AI,
			&GameInfo->config.chdir,
			&GameInfo->config.max,
			&GameInfo->config.newest_history,
			&GameInfo->config.debug
		);
	} else {
		ctools_menu_AddText(data,
			"自动下棋",
			"当前目录",
			"棋盘大小",
			"历史默认最新",
			"调试功能（扩展）",
			"	全自动下棋",
			"	绘图",
			"		棋盘重置",
			"	更多的棋盘大小",
			"	显示下棋顺序",
			"	显示调试信息",
			NULL
		);
		ctools_menu_AddTextData(data, 0,
			"%s %s %s %s %s %s %s %s %s %s",
			"使用算法人机对战",
			"更改游戏数据的目录为当前目录（仅在Linux安装了软件包后可以关闭）",
			"更改棋盘的大小（格式为nxn）",
			"在查看历史记录时默认查看最后一个记录",
			"调试选项显示开关",
			"测试功能，两方均使用自动下棋，会自动开启自动下棋\n按下空格让系统下棋，按下回车人工干预手动下棋",
			"测试功能，抛弃五子棋胜负判断而保存棋盘形状注意，该功能可能与棋局回放冲突。",
			"在开启绘图后，每切换到新的棋盘时清空整个棋盘。注意，该功能可能与棋局回放冲突。",
			"部分解除棋盘大小的限制，最小值由15减少至0，最大值则不变（主要是因为棋盘的数组没有预设很多）",
			"显示下棋的顺序",
			"显示游戏内部的一些变量的值，方便调试"
		);
		ctools_menu_AddTextData(data, 1,
			"%s %s %s %s %s %s %s %s %s %s %s",
			2,  2, 1, 2, 2, 2, 2, 2, 2, 2, 2 );
		ctools_menu_AddTextData(data, 2,
			"%s %s %s %s %s %s %s %s %s %s %s",
			&GameInfo->config.use_AI,
			&GameInfo->config.chdir,
			&GameInfo->config.max,
			&GameInfo->config.newest_history,
			&GameInfo->config.debug,
			&GameInfo->config.all_AI,
			&GameInfo->config.draw,
			&GameInfo->config.draw_reset,
			&GameInfo->config.more_max,
			&GameInfo->config.show_count,
			&GameInfo->config.more_info
		);
	}

	/* 设置棋盘大小上下限 */
	ctools_menu_AddTextData(data, ctools_menu_TextDataSetMax, "N N %s", 51);
	if (GameInfo->config.more_max) {
		ctools_menu_AddTextData(data, ctools_menu_TextDataSetMin, "N N %s", 0);
	} else {
		ctools_menu_AddTextData(data, ctools_menu_TextDataSetMin, "N N %s", 15);
		if (GameInfo->config.max < 15) {
			GameInfo->config.max = 15;
		}
	}

	ctools_menu_Show(data);

#ifdef _WIN32
	config[1] = 1;
#endif
	if (GameInfo->config.all_AI == 1) {
		GameInfo->config.use_AI = 1;
	}
	if (GameInfo->config.debug == 0) {
		GameInfo->config.all_AI = 0;
		GameInfo->config.draw   = 0;
		GameInfo->config.draw_reset = 0;
		GameInfo->config.more_max   = 0;
		GameInfo->config.show_count = 0;
		GameInfo->config.more_info  = 0;
	}

	fp = fopen(GameInfo->config.Config, "w");
	if (fp) {
		ConfigWrite;
		fclose(fp);
	}
	return;
}

