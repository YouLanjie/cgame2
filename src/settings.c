#include "../include/head.h"

void Settings() {
	cmenu data;
	FILE * fp;

	fp = fopen(GameInfo->config.Config, "r"); /* 读取文件 */
	ConfigRead;
	fclose(fp);

	data = cmenu_create();
	cmenu_set_title(data, "游戏设置");
	cmenu_set_type(data, "setting");
	cmenu_add_text(data, 0, "自动下棋", "使用算法人机对战", NULL, &GameInfo->config.use_AI, "button", 0, 0, 0);
	cmenu_add_text(data, 0, "当前目录", "更改游戏数据的目录为当前目录（仅在Linux安装了软件包后可以关闭）", NULL, &GameInfo->config.chdir, "button", 0, 0, 0);
	cmenu_add_text(data, 0, "棋盘大小", "更改棋盘的大小N的值（格式为N x N）", NULL, &GameInfo->config.max, "number", 0, 51, 15);
	cmenu_add_text(data, 0, "历史默认最新", "在查看历史记录时默认查看最后一个记录", NULL, &GameInfo->config.newest_history, "button", 0, 0, 0);
	cmenu_add_text(data, 0, "调试功能（扩展）", "调试选项显示开关（重新进入设置界面生效）", NULL, &GameInfo->config.debug, "button", 0, 0, 0);
	if (GameInfo->config.debug) {
		cmenu_add_text(data, 0, "  全自动下棋", "测试功能，两方均使用自动下棋，会自动开启自动下棋\n按下空格让系统下棋，按下回车人工干预手动下棋", NULL, &GameInfo->config.all_AI, "button", 0, 0, 0);
		cmenu_add_text(data, 0, "  绘图", "测试功能，抛弃五子棋胜负判断而保存棋盘形状注意，该功能可能与棋局回放冲突。", NULL, &GameInfo->config.draw, "button", 0, 0, 0);
		cmenu_add_text(data, 0, "  棋盘重置", "在开启绘图后，每切换到新的棋盘时清空整个棋盘。注意，该功能可能与棋局回放冲突。", NULL, &GameInfo->config.draw_reset, "button", 0, 0, 0);
		cmenu_add_text(data, 0, "  更多的棋盘大小", "部分解除棋盘大小的限制，最小值由15减少至0，最大值则不变（主要是因为棋盘的数组没有预设很多）", NULL, &GameInfo->config.more_max, "button", 0, 0, 0);
		cmenu_add_text(data, 0, "  显示下棋顺序", "显示下棋的顺序", NULL, &GameInfo->config.show_count, "button", 0, 0, 0);
		cmenu_add_text(data, 0, "  显示调试信息", "显示游戏内部的一些变量的值，方便开发调试", NULL, &GameInfo->config.more_info, "button", 0, 0, 0);
	}

	if (GameInfo->config.more_max) {
		cmenu_set_text(data, 3, "min", 0);
	} else {
		cmenu_set_text(data, 15, "min", 0);
		if (GameInfo->config.max < 15) {
			GameInfo->config.max = 15;
		}
	}

	cmenu_show(data);

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

