#include "basicMainLoop.h"
// 选关

void mainLoop5::beforeLoop() {
	muss->haltAllChk();
	muss->playChk(1000);
	muss->playChk(201);
	bt1.set_button(myRenderer, pics, 4001, 0, 20, 20, 60, 60);
	bt2.set_button(myRenderer, pics, 4001, 0, 100, 20, 60, 60);
	bt3.set_button(myRenderer, pics, 4001, 0, 180, 20, 60, 60);
	bt4.set_button(myRenderer, pics, 4001, 0, 260, 20, 60, 60);
	btEnd.set_button(myRenderer, pics, 4001, 0, 20, 100, 60, 60);
	gotoGame = 0;
	tb1 = new talkBox();
	tb1->init(myRenderer, pics, "items/test/test1.txt");

}

static string xxx;
static char xx[100][500], text[1000];
static int len[100], zlen[100], llen, lxxn;
void mainLoop5::drawAll() {
	bt1.show();
	bt2.show();
	bt3.show();
	bt4.show();
	btEnd.show();
	tb1->onDraw();
}

void mainLoop5::onType() {
	if (bt1.handle_events(event) == 1)
		gotoGame = 1;
	if (bt2.handle_events(event) == 1)
		gotoGame = 2;
	if (bt3.handle_events(event) == 1)
		gotoGame = 3;
	if (bt4.handle_events(event) == 1)
		gotoGame = 4;
	if (btEnd.handle_events(event) == 1)
		gotoGame = -1;
	if (gotoGame == 0 && event.type == SDL_MOUSEBUTTONDOWN)
		tb1->onType();
}

void mainLoop5::init(int type) {
	memset(dxMap, 0, sizeof dxMap);
	for (int i = 240; i <= 260; i++)
		for (int j = 240; j <= 260; j++)
			dxMap[i][j] = (i + j) % 2 + 1;

	for (int i = 1; i <= preMstNum; i++) {
		ztMst[i][0] = preMst[i - 1][0];
		ztMst[i][1] = preMst[i - 1][1];
		ztMst[i][2] = preMst[i - 1][2];
		ztMst[i][3] = 1;
	}

	nowx = 250;
	nowy = 250;
	gameType = 0;
	playerHp = 10;
	nowMstNum = preMstNum;
	siShift = -1;
	catMove = 0;
	pressFrame = -200;
	pressTime = -100000;
	pmType = -1;

	//gsframe = frame + 1;
	lstTime = -1000;
	thisTime = 0;

	load_musicScore(type);
	//breakSign = 1;

	for (int i = 0; i < 3000; i++)
		muss->haltAllChk(i);

	fps->start();
	gsTime = fps->get_ticks() + dtTime;
}

void mainLoop5::onAfterPframe() {
	tb1->onLoop();

	if (gotoGame == 1) {
		init(0);
		insideNextLoop = new mainLoop1(myRenderer, pics, muss, fps);
		insideNextLoop->run();
		delete insideNextLoop;
		insideNextLoop = NULL;
		gotoGame = 0;

		muss->haltAllChk();
		muss->playChk(201);
	}
	if (gotoGame == 2) {
		init(1);
		insideNextLoop = new mainLoop1(myRenderer, pics, muss, fps);
		insideNextLoop->run();
		delete insideNextLoop;
		insideNextLoop = NULL;
		gotoGame = 0;

		muss->haltAllChk();
		muss->playChk(201);
	}
	if (gotoGame == 3) {
		init(1);
		muss->haltAllChk();
		insideNextLoop = new mainLoop4(myRenderer, pics, muss, fps);
		insideNextLoop->run();
		delete insideNextLoop;
		insideNextLoop = NULL;
		gotoGame = 0;

		muss->haltAllChk();
		muss->playChk(201);
	}
	if (gotoGame == 4) {
		muss->haltAllChk();
		insideNextLoop = new mainLoop6(myRenderer, pics, muss, fps);
		insideNextLoop->run();
		delete insideNextLoop;
		insideNextLoop = NULL;
		gotoGame = 0;

		muss->haltAllChk();
		muss->playChk(201);
	}
	if (gotoGame == -1) {
		exitGame();
	}
}