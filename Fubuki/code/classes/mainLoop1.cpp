#include "basicMainLoop.h"
// 选关


void mainLoop1::beforeLoop() {
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
void mainLoop1::drawAll() {
	bt1.show();
	bt2.show();
	//bt3.show();
	//bt4.show();
	btEnd.show();
	tb1->onDraw();
}

void mainLoop1::onType() {
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

void mainLoop1::init(int type) {

	//gsframe = frame + 1;
	lstTime = -1000;
	thisTime = 0;

	//breakSign = 1;

	for (int i = 0; i < 3000; i++)
		muss->haltAllChk(i);

	fps->start();
	gsTime = fps->get_ticks() + dtTime;
}

void mainLoop1::onAfterPframe() {
	tb1->onLoop();

	if (gotoGame == 1) {
		init(0);
		insideNextLoop = new mainLoop2(myRenderer, pics, muss, fps);
		insideNextLoop->run();
		delete insideNextLoop;
		insideNextLoop = NULL;
		gotoGame = 0;

		muss->haltAllChk();
		muss->playChk(201);
	}
	if (gotoGame == 2) {
		init(0);
		insideNextLoop = new mainLoop_changeDt(myRenderer, pics, muss, fps);
		insideNextLoop->run();
		delete insideNextLoop;
		saveDtTime();
		insideNextLoop = NULL;
		gotoGame = 0;

		muss->haltAllChk();
		muss->playChk(201);
	}
	if (gotoGame == -1) {
		exitGame();
	}
}