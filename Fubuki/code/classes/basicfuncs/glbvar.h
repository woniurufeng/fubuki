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

extern double preSoundSystemSDST[6]; // ��Ӧ��ʼʱ�� 
extern int playSoundSystem[5][500][9][6]; // ���ֱ���  �˸�����  ������  0,1/4,1/2,3/4,1/3,2/3��Ϊ6�ֿ�ʼʱ��
extern int playSoundSystem2[5];
extern int pmSystem[5][500][6]; // ����Ҫ���� 
extern int loopLenth; // ����loopС���� 

extern string musicScoreList[1000]; // �洢������Ϣ���ļ���
extern int needPressPmList[1000][2], lNPPL, nNPPL; // ��Ҫ���µİ�������  lNPPL : ��Ҫ���İ�������  nNPPL ����ǰҪ���İ�ť��� 
extern int siPressPmList[1000];  // �����Ƿ�ɹ����µı�� 

extern int dxMap[500][500], mstMap[500][500]; // ���ε�ͼ�͹����ͼ 
extern int mstMapNext[500][500]; // ��һ���ĵ�ͼ 
extern int tmv[4][2]; // ������������һ����xy�������� 
extern int nowx, nowy; // FBK xy���� 
extern int gameType, playerHp, catMove, pressFrame, pressTime;
// ��ǰ���� �Ƿ��ж��ఴ�°��� ��һ����Ч���� ��Ϸ���ͣ�0 ��ͼ 1 ���棩 FBKѪ�� FBK��ͼ����֡��� ��һ�ΰ�������֡�� ��һ�ΰ�������ʱ��
extern int preCatMove_cat[20]; // ��·������20֡������ͼѡ�� 
extern int preCatMove_jmp[20]; // ��Ծ������20֡����Ծ�߶� 
extern int preCatMove; // ����/��Ծ������Ҫ20֡ 
extern int moveDirect, moveStep; // ��һ�������߷���Ͳ��� 
extern int mstMovDXYe[100][2]; // ����Ҫ�ߵ�xy���� 
extern int preXZT[4]; // ����ͼ��Ӧ���������� 

extern int musicType;
// �������ֵķ�ʽ 0Ϊ��Ϸ�ڲ������棬1Ϊֱ�Ӳ���MP3
extern int pmType, gameStep, nowMst;
//extern int nowPress2, morePress2, sttFrame2, nowMst2, pmType2, nowPlayNum2, gameStep2;
//�ڴ���������еģ� ��ǰ���� �Ƿ��ж��ఴ�°��� ���濪ʼ֡�� ��ǰС�ں� �������ͱ�ţ�-1~4)  ��Ҫ���С�ڳ��� ��Ϸ���裨0��ѡ���� 1�����ף� 
extern int greenShine, redShine, maxShine;  //��������Ȧ������ʱ�� 
extern bool siGame2[100];
extern int siShift;
extern int needPlay2[100];
extern int prePlayNum2;
extern int preMst[100][3];
extern int mstPic[100]; 
extern int preMstNum, nowMstNum;
extern int ztMst[100][5];
// �������� ���� 


// ��������ϵͳ 
extern string soundName[100]; 
extern int directName[200];


//extern FC_Font* font1;

extern ofstream fout1;

// ��ʵ֡������
//#define Rframe (frame - gsframe)
#define Rframe ((thisTime - gsTime) * FRAMES_PER_SECOND / 1000)
#define LRframe ((lstTime - gsTime) * FRAMES_PER_SECOND / 1000)

#define Rtime (thisTime - gsTime - dtTime)
#define LRtime (lstTime - gsTime - dtTime)
#define RRtime (thisTime - gsTime)
#define LRRtime (lstTime - gsTime)
// ��ʵ֡������ ���� 

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
