#include "include.h"                         //头文件
#include <time.h>

#define LANGFILELINE 33

#define Time "%04d-%02d-%02d %02d:%02d:%02d\t布局大小:%d×%d\n",p -> t.year,p -> t.mon,p -> t.day,p -> t.hour,p -> t.min,p -> t.sec,Max,Max //开局时间标准格式
#define NowTime "\033[1;31m%04d-%02d-%02d %02d:%02d:%02d\t布局大小:%d×%d\n",p -> nt.year,p -> nt.mon,p -> nt.day,p -> nt.hour,p -> nt.min,p -> nt.sec,Max,Max //现在时间标准格式

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
	int board[50][50];     //棋盘信息
	int count;             //总局数
	int who;               //下棋的一方，1黑，2白
	int x;                 //新棋子的x轴
	int y;                 //新棋子的y轴
};

/* 定义结构体变量 */
extern struct Chess *p;

/* 文件位置 */
extern char Save[];
extern char Config[];
extern FILE * fp;

extern int Max;//棋盘大小
extern char LANG[LANGFILELINE][200];

/* 定义函数 */
int IfWin(int c);//是否胜利，返回1黑方胜，返回2白方胜
void Init();//初始化：创建文件、选择语言
void Game();//游戏主体
void AI();//AI下棋
void History();//查看历史局数信息
void Settings();//设置
void PrintBoard();//打印棋盘
void GetTime();//获取开局时间
void GetNowTime();//获取现在时间
void stop();//退出程序执行的

