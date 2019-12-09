#include "glbvar.h"

// 变量定义 

// 主要变量 
int exitGameSign = 0;
double windowsW = 1280, windowsH = 720;
int FRAMES_PER_SECOND = 60; // 帧率 
//int reFPS = 8; // 音游部分击中误差帧数（正负） 
//int jpFPS = 40; //音游部分音乐速度（帧数/拍子） 

int pre_max_dLength = 1000; //音符最长播放毫秒数

//跟踪当前帧的帧计数器
//int frame = 0; // 当前帧号 
//int gsframe = 0; // 进入游戏时的帧数编号
bool cap = false;  //是否限制帧率

Uint32 blueColorKey;

double BPM = 100; //歌曲bpm
int reTime = 100; //误差时间
int gsTime; // 进入游戏时的时间
int dtTime;
int lstRefreshTime = -1000;
int lstTime = -1000; // 上一次循环时间
int thisTime; //这次进入循环时间


double preSoundSystemSDST[6] = {0, 0.25, 0.5, 0.75, 1.0/3.0, 2.0/3.0}; // 对应开始时间 
int playSoundSystem[5][500][9][6]; // 五种变奏  八个声道  拍子数  0,1/4,1/2,3/4,1/3,2/3作为6种开始时间
int playSoundSystem2[5];
int pmSystem[5][500][6]; // 不需要声道 
int loopLenth = 16; // 音乐loop小节数 

string musicScoreList[1000]; // 存储音乐信息的文件名
int needPressPmList[1000][2], lNPPL, nNPPL; // 需要按下的按键队列  lNPPL : 需要按的案件总数  nNPPL ：当前要按的按钮编号 
int siPressPmList[1000];  // 按键是否成功按下的标记 

int dxMap[500][500], mstMap[500][500]; // 地形地图和怪物地图 
int mstMapNext[500][500]; // 下一步的地图 
int tmv[4][2] = {-1, 0, 0, 1, 1, 0, 0, -1}; // 往上右下左走一步的xy坐标增量 
int nowx, nowy; // FBK xy坐标
int gameType, playerHp, catMove, pressFrame, pressTime;
// 当前按键 是否有多余按下按键 上一次有效按键 游戏类型（0 地图 1 谱面） FBK血量 FBK走图动画帧标号 上一次按按键的帧数 上一次按按键的时间
int preCatMove_cat[20] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2}; // 走路过程中20帧的行走图选择 
int preCatMove_jmp[20] = {5, 10, 15, 21, 26, 30, 35, 39, 43, 48, 52, 56, 59, 61, 62, 60, 51, 40, 28, 15}; // 跳跃过程中20帧的跳跃高度 
int preCatMove = 20; // 行走/跳跃动画需要20帧 
int moveDirect, moveStep; // 这一步的行走方向和步长 
int mstMovDXYe[100][2]; // 怪物要走的xy距离 
int preXZT[4] = {3, 2, 0, 1}; // 行走图对应的上右下左 

int musicType;
// 播放音乐的方式 0为游戏内播放谱面，1为直接播放MP3
int pmType, gameStep, nowMst;
//int nowPress2, morePress2, sttFrame2, nowMst2, pmType2, nowPlayNum2, gameStep2;
//在打谱面过程中的： 当前按键 是否有多余按下按键 谱面开始帧数 当前小节号 谱面类型编号（-1~4)  需要打的小节长度 游戏步骤（0：选谱面 1：打谱） 
int greenShine, redShine, maxShine = 20;  //亮叉子亮圈和亮的时长 
bool siGame2[100];
int siShift;
int needPlay2[100];
int prePlayNum2 = 8;
int preMst[100][3] = {1, 255, 255, 1, 245, 245, 2, 245, 255, 2, 255, 245};
int mstPic[100] = {2100, 2101}; 
int preMstNum = 4, nowMstNum;
int ztMst[100][5];
// 变量定义 结束 

// 加载声音系统 
string soundName[100] = {	"A0", "#A0", "B0", 
							"C1", "#C1", "D1", "#D1", "E1", "F1", "#F1", "G1", "#G1", "A1", "#A1", "B1", 
							"C2", "#C2", "D2", "#D2", "E2", "F2", "#F2", "G2", "#G2", "A2", "#A2", "B2", 
							"C3", "#C3", "D3", "#D3", "E3", "F3", "#F3", "G3", "#G3", "A3", "#A3", "B3", 
							"C4", "#C4", "D4", "#D4", "E4", "F4", "#F4", "G4", "#G4", "A4", "#A4", "B4", 
							"C5", "#C5", "D5", "#D5", "E5", "F5", "#F5", "G5", "#G5", "A5", "#A5", "B5", 
							"C6", "#C6", "D6", "#D6", "E6", "F6", "#F6", "G6", "#G6", "A6", "#A6", "B6", 
							"C7", "#C7", "D7", "#D7", "E7", "F7", "#F7", "G7", "#G7", "A7", "#A7", "B7", 
							"C8"	}; 
int directName[200];

//FC_Font* font1 = NULL;

ofstream fout1;

realRect RR;

