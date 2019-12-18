#pragma once

#ifndef BASIC_MAIN_LOOP_H_
#define BASIC_MAIN_LOOP_H_

#include "basicfuncs.h"
#include "battleField.h"

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
	virtual void beforeDelete() {};

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
	friend class mainLoop_changeDt;
	//friend class mainLoop3;
	//friend class mainLoop4;
	//friend class mainLoop5;
	//friend class mainLoop6;
};


// ×ßÂ· 

class mainLoop1 : public basicMainLoop {
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
	mainLoop1() : basicMainLoop() {};
	mainLoop1(SDL_Renderer* myRenderer, PICS* pics, MUSS* muss, Timer* fps) : basicMainLoop(myRenderer, pics, muss, fps) {};
};

class mainLoop2 : public basicMainLoop {
private:
	int siShift = -1, ggSign = 0;
	int pressTime = 0, morePress, nowPress, lstPress;


	void beforeLoop();
	void onBegin();
	void onType();
	void onAfterType();
	void drawAll();
	void onAfterPframe();
	void playSound();  
	void beforeDelete();

	void pressKey(int key);
public:
	battleField *bf;
	mainLoop2() : basicMainLoop() {
	};
	mainLoop2(SDL_Renderer* myRenderer, PICS* pics, MUSS* muss, Timer* fps) : basicMainLoop(myRenderer, pics, muss, fps) {
	};
};

class mainLoop_changeDt : public basicMainLoop {
private:
	Button btp1, btd1, btBack, btg0;
	int pressTime = -1000, pressTime2 = -1000;

	void beforeLoop();
	void onType();
	void drawAll();
	void playSound();

public:
	mainLoop_changeDt() : basicMainLoop() {};
	mainLoop_changeDt(SDL_Renderer* myRenderer, PICS* pics, MUSS* muss, Timer* fps) : basicMainLoop(myRenderer, pics, muss, fps) {};
};


#endif

