#pragma once

#ifndef BASIC_MAIN_LOOP_H_
#define BASIC_MAIN_LOOP_H_

#include "basicfuncs.h"
#include "battleField.h"

class basicMainLoop{
private:
	bool breakSign;
	basicMainLoop *insideNextLoop;
	bool noMusic;
	int gameStarting = 1;
	
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
		insideNextLoop = NULL;
		
		breakSign = 0;
		//noMusic = 1;
	};
	
	virtual void run();

	virtual void set_initBF(void (*init)(battleField*)) {};
	
	friend class mainLoop1;
	friend class mainLoop_battle1;
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
};

class mainLoop_battle1 : public basicMainLoop {
private:
	int siShift = -1, ggSign = 0;
	int pressTime = 0, morePress, nowPress, lstPress;
	void (*init_BattleField)(battleField*);

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
	mainLoop_battle1() : basicMainLoop() {};
	void set_initBF(void (*init)(battleField*)) { init_BattleField = init; }
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
};


#endif

