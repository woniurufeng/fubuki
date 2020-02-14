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

int PRE_DXY[4][2] = { -1, 0, 0, 1, 1, 0, 0, -1 };  //0123 上右下左
int preCatMove_jmp[20] = { 5, 10, 15, 21, 26, 30, 35, 39, 43, 48, 52, 56, 59, 61, 62, 60, 51, 40, 28, 15 }; // 跳跃过程中20帧的跳跃高度
int preXZT[4] = { 3, 2, 0, 1 }; // 行走图对应的上右下左 
int preCatMove_cat[20] = { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2 }; // 走路过程中20帧的行走图选择 

FC_Font* GLBfont1;
SDL_Color GLBttfColor = { 0, 0, 0 };

//FC_Font* font1 = NULL;

SDL_BlendMode GLBblendmode01 = SDL_ComposeCustomBlendMode(SDL_BLENDFACTOR_SRC_ALPHA, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_SUBTRACT,
	SDL_BLENDFACTOR_ZERO, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_SUBTRACT);
SDL_BlendMode GLBblendmode02 = SDL_ComposeCustomBlendMode(SDL_BLENDFACTOR_SRC_ALPHA, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_MAXIMUM,
	SDL_BLENDFACTOR_ZERO, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_ADD);
SDL_BlendMode GLBblendmode03 = SDL_ComposeCustomBlendMode(SDL_BLENDFACTOR_SRC_ALPHA, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_ADD,
	SDL_BLENDFACTOR_ZERO, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_ADD);

ofstream fout1;

realRect RR;

