#ifndef BASIC_MAIN_LOOP_H_
#define BASIC_MAIN_LOOP_H_

#include "basicfuncs.h"
#include "commonfuc2.h"

class basicMainLoop{
private:
	SDL_Renderer *myRenderer;
	PICS *pics;
	MUSS *muss;
	Timer *fps;
	bool breakSign;
	basicMainLoop *insideNextLoop;
	bool noMusic;
	
	SDL_Event event;
	
	virtual void beforeLoop() {};
	virtual void onBegin() {};
	virtual void onType() {};
	virtual void onAfterType() {};
	virtual void drawAll() {};
	virtual void playSound();
	virtual void playSound(int xj, int st);
	virtual void onAfterDraw() {};
	virtual void onAfterPframe() {};
	virtual void onAfterLoop() {};

public :
	basicMainLoop() {
		myRenderer = NULL;
		pics = NULL;
		muss = NULL;
		fps = NULL;
		insideNextLoop = NULL;
		
		breakSign = 0;
		//noMusic = 1;
	};
	basicMainLoop(SDL_Renderer *myRenderer, PICS *pics, MUSS * muss, Timer *fps){
		this->myRenderer = myRenderer;
		this->pics = pics;
		this->muss = muss;
		this->fps = fps;
		insideNextLoop = NULL;
		
		breakSign = 0;
		//noMusic = 1
		RR.init();
	};
	
	virtual void run();
	
	friend class mainLoop1;
	friend class mainLoop2;
	friend class mainLoop3;
	friend class mainLoop4;
	friend class mainLoop5;
	friend class mainLoop6;
};


// ×ßÂ· 

class mainLoop1 : public basicMainLoop{
private:
	int nowPress, morePress, lstPress;
	void beforeLoop();
	void onBegin();
	void onType();
	void onAfterType();
	void drawAll();
	void onAfterPframe();
	
	void pressKey(int key);
	void reFreshMst();
	void mstMove();
	void preFtMst1(int mstNum);
	
public:
	mainLoop1() : basicMainLoop() {
		nowPress = 0; morePress = 0; lstPress = 0; };
	mainLoop1(SDL_Renderer *myRenderer, PICS *pics, MUSS * muss, Timer *fps) : basicMainLoop(myRenderer, pics, muss, fps){
		nowPress = 0; morePress = 0; lstPress = 0; };
};


class mainLoop2 : public basicMainLoop{
private:
	int nowPress2, morePress2, nowPlayNum2;
	int sttTime2;//, sttFrame2;
	
	void beforeLoop();
	void onBegin();
	void onType();
	void onAfterType();
	void drawAll();
	void onAfterPframe();
	
	void checkNextPlay();
	void pressKey(int key);
	void gameType1End();
	void preFtMst2();
public:
	mainLoop2() : basicMainLoop(){
		nowPress2 = 0, morePress2 = 0, nowPlayNum2 = 0; };
	mainLoop2(SDL_Renderer *myRenderer, PICS *pics, MUSS * muss, Timer *fps) : basicMainLoop(myRenderer, pics, muss, fps) {
		nowPress2 = 0, morePress2 = 0, nowPlayNum2 = 0;};
};


class mainLoop3 : public basicMainLoop{
private:
	void onType();
	void drawAll();
	
	void init();
public:
	mainLoop3() : basicMainLoop(){};
	mainLoop3(SDL_Renderer *myRenderer, PICS *pics, MUSS * muss, Timer *fps) : basicMainLoop(myRenderer, pics, muss, fps){};
};


class mainLoop4 : public basicMainLoop {
private:
	Button btp1, btd1, btBack, btg0;
	void beforeLoop();
	void onType();
	void drawAll();

public:
	mainLoop4() : basicMainLoop() {};
	mainLoop4(SDL_Renderer* myRenderer, PICS* pics, MUSS* muss, Timer* fps) : basicMainLoop(myRenderer, pics, muss, fps) {};
};


class mainLoop5 : public basicMainLoop {
private:
	talkBox *tb1;
	Button bt1, bt2, bt3, bt4, btEnd;
	int gotoGame;
	void init(int type);

	void beforeLoop();
	void onType();
	void drawAll();
	void onAfterPframe();
	void playSound() {};

public:
	mainLoop5() : basicMainLoop() {};
	mainLoop5(SDL_Renderer* myRenderer, PICS* pics, MUSS* muss, Timer* fps) : basicMainLoop(myRenderer, pics, muss, fps) {};
};


class mainLoop6 : public basicMainLoop {
private:
	int picW = 816;
	int picH = 624;
	SDL_Rect ttrect1 = { 0, 0, picW, picH };
	SDL_Rect ttrect2 = { 0, 0, picW, picH };
	SDL_Surface* tmp1, * tmp2, * tmp3, * tmp4;
	SDL_Texture* ttext1;
	SDL_PixelFormat* format;
	RGBA r1, r2;
	int moveW, moveH, moveWW[4] = { 1, 2, 1, 0 };
	int kot[6];

	chtBox chtb1;
	int gotoGame;

	void beforeLoop();
	void onType();
	void drawAll();
	void onAfterPframe();
	void playSound() {};
	void onAfterLoop();

public:
	mainLoop6() : basicMainLoop() {};
	mainLoop6(SDL_Renderer* myRenderer, PICS* pics, MUSS* muss, Timer* fps) : basicMainLoop(myRenderer, pics, muss, fps) {};
};

#endif

