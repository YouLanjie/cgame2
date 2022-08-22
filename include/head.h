#include "tools.h"                         //头文件
#include <time.h>

#define LANGFILELINE 33  /* 语言句数 */

#define Time "%04d-%02d-%02d %02d:%02d:%02d\t布局大小:%d×%d\n",p -> t.year,p -> t.mon,p -> t.day,p -> t.hour,p -> t.min,p -> t.sec,Max,Max //开局时间标准格式
#define NowTime "%04d-%02d-%02d %02d:%02d:%02d\t布局大小:%d×%d\n",p -> nt.year,p -> nt.mon,p -> nt.day,p -> nt.hour,p -> nt.min,p -> nt.sec,Max,Max //现在时间标准格式

#define spaceChess 0
#define blackChess 1
#define whiteChess 2
#define playerChess (3 - p -> who)
#define computerChess (p -> who)

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
	char board[52][52];    //棋盘信息
	int who;               //下棋的一方，1黑，2白
	int x;                 //新棋子的x轴
	int y;                 //新棋子的y轴
};

/* 定义结构体变量 */
extern struct Chess *p;

extern char Save[20];  /* 保存文件路径 */
extern char Config[25];  /* 选项文件路径 */
extern char * GameDir;  /* 使用的文件路径 */

extern int config[];  /* 选项的保存 */
extern int Max;  /* 棋盘大小 */

/* 定义函数 */
int IfWin(int c);               //是否胜利，返回1黑方胜，返回2白方胜
void Init();                    //初始化：创建文件、选择语言
void changeDir(char * dir);     //用于更改游戏目录
void Game();                    //游戏主体
void AI();                      //AI下棋
void History();                 //查看历史局数信息
void Settings();                //设置
void PrintBoard();              //打印棋盘
void GetTime();                 //获取开局时间
void GetNowTime();              //获取现在时间
void stop();                    //退出程序执行的

