#include <stdio.h>                           //标准库
#include <stdlib.h>                          //system();srand();rand();malloc();free();
#include <string.h>                          //strcmp();
#include <unistd.h>
#include <time.h>

#include "kbhit_input.h"                     //无延迟输入
#include "menu.h"                            //菜单模板

#define Clear system("clear");               //清屏，方便移植
#define Max 15                               //棋盘大小

#define Save "/usr/local/cgame2/data/save.txt"          //文件位置
#define Data "/usr/local/cgame2/data/data.txt"          //文件位置
#define Lang "/usr/local/cgame2/data/lang.txt"          //文件位置
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

int init(struct Chess *p);     //初始化：创建文件、选择语言
void welcome();                //开始界面
void game(struct Chess *p);    //游戏主体
void AI(struct Chess *p);      //AI下棋
void save(struct Chess *p);    //保存棋盘信息
void history(struct Chess *p); //查看历史局数信息
void help();                   //帮助信息
void other();     //其他选项
void printboard(struct Chess *p); //打印棋盘
void gettime(struct Chess *p);    //获取开局时间
void getnowtime(struct Chess *p); //获取现在时间


/*------------------------------English---------------------------------*/
/*------------------------------English---------------------------------*/
/*------------------------------English---------------------------------*/
/*------------------------------English---------------------------------*/
/*------------------------------English---------------------------------*/
#define en_Time "\033[1;31m%d-%d-%d %d:%d:%d\n",p -> t.year,p -> t.mon,p -> t.day,p -> t.hour,p -> t.min,p -> t.sec
#define en_NowTime "\033[1;31mtime:%d-%d-%d\n",p -> nt.year,p -> nt.mon,p -> nt.day
#define en_Menu printf("\033[0m\033[11;18H");
#define en_Menu2 printf("\033[0m\033[11;26H");

struct en_time {
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
};

struct en_Chess {
	struct en_time t;         //开局时间
	struct en_time nt;        //现在时间
	int board[Max][Max];   //棋盘
	int count;             //一共有多少局
	int who;               //下棋的一方，1黑，2白
	int x;                 //新棋子的x轴
	int y;                 //新棋子的y轴
};

extern int English();
extern int en_ifWin(struct en_Chess *p);
extern int en_init(struct en_Chess *p);

extern void en_welcome();
extern void en_game(struct en_Chess *p);
extern void en_save(struct en_Chess *p);
extern void en_history(struct en_Chess *p);
extern void en_help();
extern void en_other();
extern void en_printboard(struct en_Chess *p);
extern void en_gettime(struct en_Chess *p);
extern void en_getnowtime(struct en_Chess *p);
extern void en_menu();
extern void en_menu2();
extern int en_kbhit();
extern int en_input();

