#include "../include/head.h"

extern const ctools_menu CT_MENU;

void Settings() {
	const ctools_menu *m = &CT_MENU;
	struct ctools_menu_t * data = NULL;
	FILE * fp;

	fp = fopen(GameInfo->config.Config, "r"); /* 读取文件 */
	ConfigRead;
	fclose(fp);


	m->data_init(&data);
	m->set_title(data, "游戏设置");
	m->set_type(data, "setting");
	m->set_text(data,
		"自动下棋",
		"当前目录",
		"棋盘大小",
		"历史默认最新",
		"调试功能（扩展）",
		NULL
	);
	m->set_text_data(data, "describe",
		"%s %s %s %s %s",
		"使用算法人机对战",
		"更改游戏数据的目录为当前目录（仅在Linux安装了软件包后可以关闭）",
		"更改棋盘的大小N的值（格式为N x N）",
		"在查看历史记录时默认查看最后一个记录",
		"调试选项显示开关（重新进入设置界面生效）"
	);
	m->set_text_data(data, "type",
		"%s %s %s %s %s",
		2,  2, 1, 2, 2
	);

	if (!GameInfo->config.debug) {
		m->set_text_data(data, "var",
			"%s %s %s %s %s",
			&GameInfo->config.use_AI,
			&GameInfo->config.chdir,
			&GameInfo->config.max,
			&GameInfo->config.newest_history,
			&GameInfo->config.debug
		);
	} else {
		m->add_text(data, "	全自动下棋");
		m->add_text(data, "	绘图");
		m->add_text(data, "		棋盘重置");
		m->add_text(data, "	更多的棋盘大小");
		m->add_text(data, "	显示下棋顺序");
		m->add_text(data, "	显示调试信息");

		m->add_text_data(data, "describe", "测试功能，两方均使用自动下棋，会自动开启自动下棋\n按下空格让系统下棋，按下回车人工干预手动下棋");
		m->add_text_data(data, "describe", "测试功能，抛弃五子棋胜负判断而保存棋盘形状注意，该功能可能与棋局回放冲突。");
		m->add_text_data(data, "describe", "在开启绘图后，每切换到新的棋盘时清空整个棋盘。注意，该功能可能与棋局回放冲突。");
		m->add_text_data(data, "describe", "部分解除棋盘大小的限制，最小值由15减少至0，最大值则不变（主要是因为棋盘的数组没有预设很多）");
		m->add_text_data(data, "describe", "显示下棋的顺序");
		m->add_text_data(data, "describe", "显示游戏内部的一些变量的值，方便开发调试");

		m->set_text_data(data, "type",
			"%s %s %s %s %s %s %s %s %s %s %s",
			2,  2, 1, 2, 2, 2, 2, 2, 2, 2, 2
		);

		m->set_text_data(data, "var",
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
	m->set_text_data(data, "max", "N N %s", 51);
	if (GameInfo->config.more_max) {
		m->set_text_data(data, "min", "N N %s", 0);
	} else {
		m->set_text_data(data, "min", "N N %s", 15);
		if (GameInfo->config.max < 15) {
			GameInfo->config.max = 15;
		}
	}

	m->show(data);

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

