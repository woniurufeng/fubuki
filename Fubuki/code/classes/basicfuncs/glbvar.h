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

extern int loopLength;

extern int PRE_DXY[4][2];

extern FC_Font* GLBfont1;

extern ofstream fout1;

// 真实帧数计算
#define Rtime (thisTime - gsTime - dtTime)
#define LRtime (lstTime - gsTime - dtTime)
#define RRtime (thisTime - gsTime)
#define LRRtime (lstTime - gsTime)

//#define Rframe (frame - gsframe)
#define Rframe (Rtime * FRAMES_PER_SECOND / 1000)
#define LRframe (LRtime * FRAMES_PER_SECOND / 1000)

#define Rmovingframe (Rtime / ((int)((60000.0/BPM-2.0*reTime)/20.0)-1) )
#define LRmovingframe (LRtime / ((int)((60000.0/BPM-2.0*reTime)/20.0)-1) )

static SDL_Rect rect, rect1;
class realRect {
private:
	double x, y, w, h;
	double x1, y1, w1, h1;
	double reW, reH;
public:
	void init() {
		x = y = w = h = 0;
		reW = 1920;
		reH = 1080;
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
