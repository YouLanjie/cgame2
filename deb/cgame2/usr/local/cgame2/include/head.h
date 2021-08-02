#include "include.h"                         //头文件

#include <time.h>

#define Clear printf("\033[2J\033[1;1H");    //清屏，方便移植
#define Clear2 system("clear");              //清屏x2，方便移植
#define Max 15                               //棋盘大小

#define Time "\033[1;31m%4d-%2d-%2d %2d:%2d:%2d\n",p -> t.year,p -> t.mon,p -> t.day,p -> t.hour,p -> t.min,p -> t.sec //开局时间标准格式
#define NowTime "\033[1;31m日期：%4d-%2d-%2d\n",p -> nt.year,p -> nt.mon,p -> nt.day //现在时间标准格式

/* 定义结构体 */
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

/* 定义结构体变量 */
extern struct Chess *p;

/* 文件位置 */
extern char Save[];
extern char Data[];
extern char Help[];
extern char Config[];
extern FILE * fp;

/* 定义函数 */
int ifWin(int c);              //是否胜利，返回1黑方胜，返回2白方胜
void init();                   //初始化：创建文件、选择语言
void welcome(short p,short a); //开始界面
void game();                   //游戏主体
void AI();                     //AI下棋
void save();                   //保存棋盘信息
void history();                //查看历史局数信息
void help();                   //帮助信息
void settings();
void printboard();             //打印棋盘
void gettime();                //获取开局时间
void getnowtime();             //获取现在时间
void stop();                   //退出程序执行的

