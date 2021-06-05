#include <stdio.h>                           //标准库
#include <stdlib.h>                          //system();srand();rand();malloc();free();
#include <string.h>                          //strcmp();
#include <unistd.h>
#include <time.h>

#include "kbhit_input.h"                     //无延迟输入
#include "menu.h"                            //菜单模板

#define Clear printf("\033[2J\033[1;1H");               //清屏，方便移植
#define Clear2 system("clear");               //清屏，方便移植
#define Max 15                               //棋盘大小

#define Save "/usr/local/cgame2/data/save.txt"          //文件位置
#define Data "/usr/local/cgame2/data/data.txt"          //文件位置
#define Help "/usr/local/cgame2/data/help.txt"          //文件位置

#define Time "\033[1;31m%4d-%2d-%2d %2d:%2d:%2d\n",p -> t.year,p -> t.mon,p -> t.day,p -> t.hour,p -> t.min,p -> t.sec //开局时间标准格式
#define NowTime "\033[1;31m日期：%4d-%2d-%2d\n",p -> nt.year,p -> nt.mon,p -> nt.day //现在时间标准格式

struct time {                                //存储时间信息
	int year;      //年
	int mon;       //月
	int day;       //日
	int hour;      //小时
	int min;       //分钟
	int sec;       //秒
};

struct Chess {            //游戏信息大杂烩
	struct time t;         //开局时间，精确到秒
	struct time nt;        //现在时间，精确到分
	int board[Max][Max];   //棋盘信息
	int count;             //总局数
	int who;               //下棋的一方，1黑，2白
	int x;                 //新棋子的x轴
	int y;                 //新棋子的y轴
};

int ifWin(struct Chess *p);    //是否胜利，返回1黑方胜，返回2白方胜

void init(struct Chess *p);     //初始化：创建文件、选择语言
void welcome();                //开始界面
void game(struct Chess *p);    //游戏主体
void AI(struct Chess *p);      //AI下棋
void save(struct Chess *p);    //保存棋盘信息
void history(struct Chess *p); //查看历史局数信息
void help();                   //帮助信息
void other();                  //其他选项
void printboard(struct Chess *p); //打印棋盘
void gettime(struct Chess *p);    //获取开局时间
void getnowtime(struct Chess *p); //获取现在时间

