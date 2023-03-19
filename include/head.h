#include "lib/include/tools.h"                         //头文件
#include "specialChar.h"
#include <sys/time.h>

#define LANGFILELINE 33  /* 语言句数 */

#define Time "%04d-%02d-%02d %02d:%02d:%02d\t布局大小:%d×%d", GameInfo->chess->t.year, GameInfo->chess->t.mon, GameInfo->chess->t.day, GameInfo->chess->t.hour, GameInfo->chess->t.min, GameInfo->chess->t.sec, GameInfo->config.max, GameInfo->config.max //开局时间标准格式
#define NowTime "%04d-%02d-%02d %02d:%02d:%02d\t布局大小:%d×%d", GameInfo->chess->nt.year, GameInfo->chess->nt.mon, GameInfo->chess->nt.day, GameInfo->chess->nt.hour, GameInfo->chess->nt.min, GameInfo->chess->nt.sec, GameInfo->config.max, GameInfo->config.max //现在时间标准格式

/* 选项的保存/读取格式 */
#define ConfigWrite fprintf(fp, "%d %d %d %d %d %d %d %d %d %d %d", GameInfo->config.use_AI, GameInfo->config.chdir, GameInfo->config.debug, GameInfo->config.max, GameInfo->config.all_AI, GameInfo->config.draw, GameInfo->config.draw_reset, GameInfo->config.more_max, GameInfo->config.newest_history, GameInfo->config.show_count, GameInfo->config.more_info)  //保存选项格式
#define ConfigRead fscanf(fp,"%d%d%d%d%d%d%d%d%d%d%d", &GameInfo->config.use_AI, &GameInfo->config.chdir, &GameInfo->config.debug, &GameInfo->config.max, &GameInfo->config.all_AI, &GameInfo->config.draw, &GameInfo->config.draw_reset, &GameInfo->config.more_max, &GameInfo->config.newest_history, &GameInfo->config.show_count, &GameInfo->config.more_info)  //读取选项格式

#define spaceChess 0     /* 空棋 */
#define blackChess 1     /* 黑棋 */
#define whiteChess 2     /* 白棋 */
#define errorChess -1    /* 错误 */

#define myChess (((GameInfo->chess->count < 0) ? -1 : (GameInfo->chess->count % 2) ? 1 : (GameInfo->chess->count ? 2 : 0)))             /* 我方 */
#define otherChess (3 - ((GameInfo->chess->count < 0) ? -1 : ((GameInfo->chess->count % 2) ? 1 : (GameInfo->chess->count ? 2 : 0))))    /* 敌方 */

/* 定义结构体 */
struct time {                                //存储时间信息
	int year;      //年
	int mon;       //月
	int day;       //日
	int hour;      //小时
	int min;       //分钟
	int sec;       //秒
};

typedef struct {              //游戏信息大杂烩
	int board[52][52];    //棋盘信息
	int x;                //新棋子的x轴（1开始）
	int y;                //新棋子的y轴
	int way;              //记录连成一线的方向
	int count;            //序列数值
	struct time t;        //开局时间，精确到秒
	struct time nt;       //现在时间，精确到分
} Chess;

typedef struct {
	char *Save;       /* 保存文件路径 */
	char *Config;     /* 选项文件路径 */
	char *GameDir;    /* 使用的文件路径 */
	int use_AI;
	int chdir;
	int max;
	int newest_history;
	int debug;
	int all_AI;
	int draw;
	int draw_reset;
	int more_max;
	int show_count;
	int more_info;
} Config;

typedef struct {           //游戏信息大杂烩
	Config config;
	Chess * chess;     /* 棋盘信息 */
} Games;

/* 定义结构体变量 */
extern Games *GameInfo;

/* 定义函数 */
void Init();                    //初始化
void readConfig();              //初始化：创建文件
void changeDir(char * dir);     //用于更改游戏目录

#define GetChessVal(y, x) (GameInfo->chess->board[y - 1][x - 1])
#define GetChessVal2(y, x) (GameInfo->chess->board[y][x])
int GetChessPlayer(int y, int x);
void InitChess();
void Move(int way, int * x, int * y, int Way[4]);
int PutChess(int input);
void Undo();
void PrintBoard();              //打印棋盘
void hiChess();

void Game();                    //游戏主体
void AI();                      //AI下棋
int IfWin();                    //是否胜利，返回1黑方胜，返回2白方胜
void GetTime();                 //获取开局时间
void GetNowTime();              //获取现在时间

void History();                 //查看历史局数信息
void Settings();                //设置

void stop();                    //退出程序执行的

