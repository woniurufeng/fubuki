#include "basicMainLoop.h"
// 选关


void mainLoop1::beforeLoop() {
	GLBmuss2->haltChk();
	GLBmuss2->playChk(1000, 1);
	GLBmuss2->playChk(201, 1);
	bt1.set_button(4001, 0, 20, 20, 60, 60);
	bt2.set_button(4001, 0, 100, 20, 60, 60);
	bt3.set_button(4001, 0, 180, 20, 60, 60);
	bt4.set_button(4001, 0, 260, 20, 60, 60);
	btEnd.set_button(4001, 0, 20, 100, 60, 60);
	gotoGame = 0;
	tb1 = new talkBox();
	tb1->init(GLBrenderer, GLBpics, "items/test/test1.txt");

}

static string xxx;
static char xx[100][500], text[1000];
static int len[100], zlen[100], llen, lxxn;
void mainLoop1::drawAll() {
	SDL_Rect trect1 = { 0, 0, 816, 624 };
	sogr(6001, NULL, &trect1);
	sogr(6004, NULL, &trect1);

	SDL_SetTextureBlendMode(GLBpics->getPicText(6005), SDL_BlendMode_Sub);
	sogr(6005, NULL, &trect1);
	SDL_SetTextureBlendMode(GLBpics->getPicText(6002), SDL_BLENDMODE_ADD);
	sogr(6002, NULL, &trect1);
	sogr(6005, NULL, &trect1);
	
	SDL_SetTextureBlendMode(GLBpics->getPicText(6003), SDL_BLENDMODE_ADD);
	sogr(6003, NULL, &trect1);



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
		GLBmuss2->haltChk(i);

	GLBfps->start();
	gsTime = GLBfps->get_ticks() + dtTime;
}

void init_BattleField1(battleField* bf) {
	bf->preLoadFile("items/pictures/map001/map001.gdata");

	bf->lstMstNum = bf->mstNum = 4;
	bf->mstList[0] = new MONSTER();
	bf->mstList[1] = new MONSTER_Yagoo(bf->usex + 4, bf->usey + 1, 1);
	bf->mstList[2] = new MONSTER_Yagoo(bf->usex + 8, bf->usey + 11, 2);
	bf->mstList[3] = new MONSTER_Yagoo(bf->usex + 11, bf->usey + 7, 2);
	bf->mstList[4] = new MONSTER_Yagoo(bf->usex + 3, bf->usey + 10, 3);
	//bf->nextx = bf->nexty = bf->nowx = bf->nowy = 150;
	bf->direct = 2;
	bf->mussNum[0] = 301;
	bf->mussNum[1] = 302;
	bf->mussNum[2] = 303;
	bf->atkMus[0] = bf->atkMus[1] = bf->atkMus[2] = 50;
	bf->wpSize[0].push_back(make_pair(1, 0));
	bf->hp = 12;

	//BPM = 80;
	BPM = 132;
	loopLength = 36 * 4;
}

void mainLoop1::onAfterPframe() {
	tb1->onLoop();

	if (gotoGame == 1) {
		init(0);
		//clearEvent();
		insideNextLoop = new mainLoop_battle1();
		insideNextLoop->set_initBF(init_BattleField1);
		insideNextLoop->run();
		insideNextLoop->beforeDelete();
		delete insideNextLoop;
		//clearEvent();
		insideNextLoop = NULL;
		gotoGame = 0;

		GLBmuss2->haltChk();
		GLBmuss2->playChk(201);
	}
	if (gotoGame == 2) {
		init(0);
		//clearEvent();
		insideNextLoop = new mainLoop_changeDt();
		insideNextLoop->run();
		delete insideNextLoop;
		//clearEvent();
		saveDtTime();
		insideNextLoop = NULL;
		gotoGame = 0;

		GLBmuss2->haltChk();
		GLBmuss2->playChk(201);
	}
	if (gotoGame == -1) {
		exitGame();
	}
}