#include "basicMainLoop.h"


static void init_BattleField1(battleField* bf) {
	memset(bf->landMap, 0, sizeof bf->landMap);
	bf->backGroundPn = -1;
	//0可通过蓝 1可通过粉色 2墙（灰块）3墙（黑块）
	bf->landPn[0] = 1000;
	bf->landPn[1] = 1003;
	bf->landPn[2] = 1001;
	bf->landPn[3] = 1002;
	bf->landType[0] = 0;
	bf->landType[1] = 0;
	bf->landType[2] = 1;
	bf->landType[3] = 1;
	bf->landVRect[0] = bf->landVRect[1] = bf->landVRect[2] = bf->landVRect[3] = NULL;
	for (int i = 0; i < 300; i++)
		for (int j = 0; j < 300; j++) {
			bf->landMap[i][j] = 2;
		}
	for (int i = 150 - 10; i <= 150 + 10; i++)
		for (int j = 150 - 10; j <= 150 + 10; j++) {
			bf->landMap[i][j] = (i + j) & 1;
		}
	bf->lstMstNum = bf->mstNum = 4;
	bf->mstList[0] = new MONSTER();
	bf->mstList[1] = new MONSTER_Yagoo(150 - 1, 150 - 1, 0);
	bf->mstList[2] = new MONSTER_Yagoo(150 - 1, 150 + 1, 1);
	bf->mstList[3] = new MONSTER_Yagoo(150 + 1, 150 - 1, 2);
	bf->mstList[4] = new MONSTER_Yagoo(150 + 1, 150 + 1, 3);
	bf->nextx = bf->nexty = bf->nowx = bf->nowy = 150;
	bf->direct = 2;
	bf->mussNum[0] = 301;
	bf->mussNum[1] = 302;
	bf->mussNum[2] = 303;
	bf->atkMus[0] = bf->atkMus[1] = bf->atkMus[2] = 50;
	bf->wpSize[0].push_back(make_pair(1, 0));
	bf->hp = 12;

	BPM = 132;
	loopLength = 36 * 4;
}
void mainLoop2::beforeDelete() {
	bf->DbattleField();
	delete bf;
}

void mainLoop2::playSound() {
	int jpNum = (int)(1.0 * RRtime * BPM / 60000.0);
	double onePz = 60000.0 / BPM;
	int lstPzTime = (int)(1.0 * onePz * jpNum);


	if (jpNum == 0 && RRtime - lstPzTime > 0 && LRRtime - lstPzTime <= 0) {
		bf->playSound();
	}
}

void mainLoop2::beforeLoop(){
	//sttFrame2 = (Rframe / jpFPS + 2) * jpFPS; 
	bf = new battleField();
	init_BattleField1(bf);

	nowPress = -1;
	morePress = 0;
	lstPress = 2;

	fps->start();
	gsTime = fps->get_ticks() + 200;
	lstTime = gsTime - 1;
}

void mainLoop2::onAfterType() {
	bf->onAfterType();
}

void mainLoop2::onBegin() {
	int jpNum = (int)(1.0 * Rtime * BPM / 60000.0);
	double onePz = 60000.0 / BPM;
	int lstPzTime = (int)(1.0 * onePz * jpNum);

	if (Rtime - lstPzTime > reTime && LRtime - lstPzTime <= reTime) {
		morePress = 0;
		if (nowPress == -1) {
			bf->tryMove();
		}
		nowPress = -1;
	}
	if (Rtime - lstPzTime > (int)(onePz * 2.0 / 3.0) && LRtime - lstPzTime <= (int)(onePz * 2.0 / 3.0)) {
		morePress = 0;
	}
}


void mainLoop2::pressKey(int key) {
	// 记录按键时间 
	//pressFrame = Rframe;
	pressTime = Rtime;
	// 地图行走中 

	int jpNum = (int)(1.0 * Rtime * BPM / 60000.0);
	double onePz = 60000.0 / BPM;
	int lstPzTime = (int)(1.0 * onePz * jpNum);

	if (morePress == 1)
		return;
	if (nowPress != -1) {
		morePress = 1;
		return;
	}
	if (Rtime - lstPzTime > reTime && Rtime - lstPzTime < (int)(onePz - reTime)) {
		//if(Rframe % jpFPS > reFPS && Rframe % jpFPS < jpFPS - reFPS){
		morePress = 1;
		return;
	}

	nowPress = lstPress = key;
	bf->trueTap(key, siShift);
	return;
}

void mainLoop2::onAfterPframe(){
	int jpNum = (int)(1.0 * Rtime * BPM / 60000.0);
	double onePz = 60000.0 / BPM;
	int lstPzTime = (int)(1.0 * onePz * jpNum);

	if(bf->gameType != 0 || 1.0 * loopLength * onePz <= RRtime)
		ggSign = 1;
}



void mainLoop2::onType(){
	if( event.type == SDL_KEYUP )
    	if(event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT)
    		siShift = -1;
    if( event.type == SDL_KEYDOWN ){
    	if( event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT )
    		siShift = 1;
    		
		if(!ggSign){
			if( event.key.keysym.sym == SDLK_UP )
	    		pressKey(0);
	    	if( event.key.keysym.sym == SDLK_RIGHT )
	    		pressKey(1);
	    	if( event.key.keysym.sym == SDLK_DOWN )
	    		pressKey(2);
			if (event.key.keysym.sym == SDLK_LEFT)
				pressKey(3);
			if (event.key.keysym.sym == SDLK_q)
				pressKey(4);
			if (event.key.keysym.sym == SDLK_w)
				pressKey(5);
		}
		else {
			if (event.key.keysym.sym == SDLK_w)
				breakSign = 1;
		}
	}
}

void mainLoop2::drawAll(){
	SDL_Rect TMP_rect1 = { 0, 0, 1920, 1080 };
	if (ggSign) {
		if (bf->gameType == -1)
			sogr(1100, NULL, &TMP_rect1);
		else if (bf->gameType == 1)
			sogr(1101, NULL, &TMP_rect1);
		else
			sogr(1102, NULL, &TMP_rect1);
		return;
	}

	//游戏战斗场景
	bf->draw();
	
	//画遮罩
	//int ddd = zheng(Rframe % 256 - 256 / 2);
	//GLBpics->changeAlpha(1005, ddd + 127);
	sogr(1005, NULL, &TMP_rect1);

	//画黑条
	TMP_rect1 = { 0, 0, 1920, 111 };
	sogr(1002, NULL, &TMP_rect1);
	TMP_rect1 = { 0, 1080 - 111, 1920, 111 };
	sogr(1002, NULL, &TMP_rect1);
	TMP_rect1 = { 1920, 0, 1920, 1080 };
	sogr(1002, NULL, &TMP_rect1);

	//画血条
	drawHp1(bf->hp);

	//画圆圈
	drawMusCircle1(bf->nowMus, bf->nextMus, bf->musChangingProcess);

	//画节奏条
	drawBeat1();
}
