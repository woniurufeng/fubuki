#ifndef GLBVAR_H_
#define GLBVAR_H_

#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "SDL_FontCache.h"

#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"
using namespace std;

#define zheng(x) ((x)>0?(x):(-1*(x)))
#define min0(x) ((x)>0?(x):(0))
#define max255(x) ((x)<255?(x):(255))

// 变量定义 

// 主要变量 
extern int exitGameSign;

extern double windowsW, windowsH;

extern int FRAMES_PER_SECOND; // 帧率 
//extern int reFPS; // 音游部分击中误差帧数（正负） 
//extern int jpFPS; //音游部分音乐速度（帧数/拍子） 

extern int pre_max_dLength; //音符最长播放毫秒数

//跟踪当前帧的帧计数器
//extern int frame; // 当前帧号 
//extern int gsframe; // 进入游戏时的帧数编号
extern bool cap;  //是否限制帧率

extern Uint32 blueColorKey;

extern double BPM; //歌曲bpm
extern int reTime; //误差时间
extern int gsTime; // 进入游戏时的时间
extern int dtTime; //错位时间
extern int lstRefreshTime;
extern int lstTime; // 上一次循环时间
extern int thisTime; //这次进入循环时间

extern double preSoundSystemSDST[6]; // 对应开始时间 
extern int playSoundSystem[5][500][9][6]; // 五种变奏  八个声道  拍子数  0,1/4,1/2,3/4,1/3,2/3作为6种开始时间
extern int playSoundSystem2[5];
extern int pmSystem[5][500][6]; // 不需要声道 
extern int loopLenth; // 音乐loop小节数 

extern string musicScoreList[1000]; // 存储音乐信息的文件名
extern int needPressPmList[1000][2], lNPPL, nNPPL; // 需要按下的按键队列  lNPPL : 需要按的案件总数  nNPPL ：当前要按的按钮编号 
extern int siPressPmList[1000];  // 按键是否成功按下的标记 

extern int dxMap[500][500], mstMap[500][500]; // 地形地图和怪物地图 
extern int mstMapNext[500][500]; // 下一步的地图 
extern int tmv[4][2]; // 往上右下左走一步的xy坐标增量 
extern int nowx, nowy; // FBK xy坐标 
extern int gameType, playerHp, catMove, pressFrame, pressTime;
// 当前按键 是否有多余按下按键 上一次有效按键 游戏类型（0 地图 1 谱面） FBK血量 FBK走图动画帧标号 上一次按按键的帧数 上一次按按键的时间
extern int preCatMove_cat[20]; // 走路过程中20帧的行走图选择 
extern int preCatMove_jmp[20]; // 跳跃过程中20帧的跳跃高度 
extern int preCatMove; // 行走/跳跃动画需要20帧 
extern int moveDirect, moveStep; // 这一步的行走方向和步长 
extern int mstMovDXYe[100][2]; // 怪物要走的xy距离 
extern int preXZT[4]; // 行走图对应的上右下左 

extern int musicType;
// 播放音乐的方式 0为游戏内播放谱面，1为直接播放MP3
extern int pmType, gameStep, nowMst;
//extern int nowPress2, morePress2, sttFrame2, nowMst2, pmType2, nowPlayNum2, gameStep2;
//在打谱面过程中的： 当前按键 是否有多余按下按键 谱面开始帧数 当前小节号 谱面类型编号（-1~4)  需要打的小节长度 游戏步骤（0：选谱面 1：打谱） 
extern int greenShine, redShine, maxShine;  //亮叉子亮圈和亮的时长 
extern bool siGame2[100];
extern int siShift;
extern int needPlay2[100];
extern int prePlayNum2;
extern int preMst[100][3];
extern int mstPic[100]; 
extern int preMstNum, nowMstNum;
extern int ztMst[100][5];
// 变量定义 结束 


// 加载声音系统 
extern string soundName[100]; 
extern int directName[200];


//extern FC_Font* font1;

extern ofstream fout1;

// 真实帧数计算
//#define Rframe (frame - gsframe)
#define Rframe ((thisTime - gsTime) * FRAMES_PER_SECOND / 1000)
#define LRframe ((lstTime - gsTime) * FRAMES_PER_SECOND / 1000)

#define Rtime (thisTime - gsTime - dtTime)
#define LRtime (lstTime - gsTime - dtTime)
#define RRtime (thisTime - gsTime)
#define LRRtime (lstTime - gsTime)
// 真实帧数计算 结束 

static SDL_Rect rect, rect1;
class realRect {
private:
	double x, y, w, h;
	double x1, y1, w1, h1;
	double reW, reH;
public:
	void init() {
		x = y = w = h = 0;
		reW = 1280;
		reH = 720;
	}
	realRect() {
		init();
	}
	SDL_Rect* rr(SDL_Rect* r) {
		x = 1.0 * (r->x) * windowsW / reW;
		w = 1.0 * (r->w) * windowsW / reW;
		y = 1.0 * (r->y) * windowsH / reH;
		h = 1.0 * (r->h) * windowsH / reH;
		rect.x = (int)x;
		rect.y = (int)y;
		rect.w = (int)w;
		rect.h = (int)h;
		//cout << windowsW / reW << ' ' << windowsH / reH << endl;
		return &rect;
	}
	SDL_Rect* ll(SDL_Rect* r) {
		x1 = 1.0 * (r->x) * windowsW / reW;
		w1 = 1.0 * (r->w) * windowsW / reW;
		y1 = 1.0 * (r->y) * windowsH / reH;
		h1 = 1.0 * (r->h) * windowsH / reH;
		rect1.x = (int)x1;
		rect1.y = (int)y1;
		rect1.w = (int)w1;
		rect1.h = (int)h1;
		return &rect1;
	}
	int ww(int ww) {
		w = 1.0 * (ww) * windowsW / reW;
		return w;
	}
	int hh(int hh) {
		h = 1.0 * (hh) * windowsH / reH;
		return h;
	}
};

struct RGBA {
	int r, g, b, a;
	Uint32 color;
	void rgbatc() {
		a = max255(a);
		a = min0(a);
		r = max255(r);
		r = min0(r);
		g = max255(g);
		g = min0(g);
		b = max255(b);
		b = min0(b);

		color = (a << 24) | (r << 16) | (g << 8) | b;
	}
	void ctrgba() {
		r = (color & 0xff0000) >> 16;
		g = (color & 0xff00) >> 8;
		b = color & 0xff;
		a = color >> 24;
	}
};
extern realRect RR;


#endif
