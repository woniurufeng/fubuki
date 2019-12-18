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

// �������� 

// ��Ҫ���� 
extern int exitGameSign;

extern double windowsW, windowsH;

extern int FRAMES_PER_SECOND; // ֡�� 
//extern int reFPS; // ���β��ֻ������֡���������� 
//extern int jpFPS; //���β��������ٶȣ�֡��/���ӣ� 

extern int pre_max_dLength; //��������ź�����

//���ٵ�ǰ֡��֡������
//extern int frame; // ��ǰ֡�� 
//extern int gsframe; // ������Ϸʱ��֡�����
extern bool cap;  //�Ƿ�����֡��

extern Uint32 blueColorKey;

extern double BPM; //����bpm
extern int reTime; //���ʱ��
extern int gsTime; // ������Ϸʱ��ʱ��
extern int dtTime; //��λʱ��
extern int lstRefreshTime;
extern int lstTime; // ��һ��ѭ��ʱ��
extern int thisTime; //��ν���ѭ��ʱ��

extern int loopLength;

extern int PRE_DXY[4][2];

extern FC_Font* GLBfont1;

extern ofstream fout1;

// ��ʵ֡������
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
