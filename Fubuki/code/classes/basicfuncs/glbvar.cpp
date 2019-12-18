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

int loopLength = 100;

int PRE_DXY[4][2] = { -1, 0, 0, 1, 1, 0, 0, -1 };  //0123 上下左右

FC_Font* GLBfont1;

//FC_Font* font1 = NULL;

ofstream fout1;

realRect RR;

