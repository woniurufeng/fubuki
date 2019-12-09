#include "basicMainLoop.h"
// 音游部分地图行走


static int ttcolor[30] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
void mainLoop1::pressKey(int key){
	// 记录按键时间 
	//pressFrame = Rframe;
	pressTime = Rtime;
	// 地图行走中 
	int step = 1;
	if(siShift == 1){
		step = 2;
	}

	int jpNum = (int)(1.0 * Rtime * BPM / 60000.0);
	double onePz = 60000.0 / BPM;
	int lstPzTime = (int)(1.0 * onePz * jpNum);
	
	if(morePress == 1)
		return ;
	if(nowPress != -1){
		morePress = 1;
		return ;
	}
	if (Rtime - lstPzTime > reTime && Rtime - lstPzTime < (int)(onePz - reTime)) {
	//if(Rframe % jpFPS > reFPS && Rframe % jpFPS < jpFPS - reFPS){
		morePress = 1;
		return ;
	}	
	
	nowPress = lstPress = key;
	mstMove();
	if(dxMap[nowx + step*tmv[key][0]][nowy + step*tmv[key][1]] != 0){
		moveStep = step;
		moveDirect = key;
		catMove = preCatMove;
		return ;
	}
	step = 1;
	if(dxMap[nowx + tmv[key][0]][nowy + tmv[key][1]] != 0){
		moveStep = step;
		moveDirect = key;
		catMove = preCatMove;
		return ;
	}
	return ;
}

void mainLoop1::preFtMst1(int mstNum){
	nowMst = mstNum;
	gameStep = 0;
	gameType = 1;
}

void mainLoop1::onAfterType(){
	if(catMove != 0){
    	catMove -= Rframe - LRframe;
    	if(catMove <= 0){
			catMove = 0;
	    	nowx += moveStep*tmv[moveDirect][0];
			nowy += moveStep*tmv[moveDirect][1];
			if(mstMap[nowx][nowy] != 0){
				gameType = 1;
				preFtMst1(mstMap[nowx][nowy]);
			}
		}
	}
}

void mainLoop1::onAfterPframe(){
	if(gameType == 1){
		insideNextLoop = new mainLoop2(myRenderer, pics, muss, fps);
		insideNextLoop->run(); 
		delete insideNextLoop;
		insideNextLoop = NULL;
		reFreshMst();
		if(musicType == 1 && playSoundSystem2[ pmType + 1 ] != playSoundSystem2[0])
			noMusic = 1;
		pmType = -1;
	}
	if(playerHp <= 0 || nowMstNum == 0){
		insideNextLoop = new mainLoop3(myRenderer, pics, muss, fps);
		insideNextLoop->run(); 
		delete insideNextLoop;
		insideNextLoop = NULL;

		breakSign = 1;
	}
}

void mainLoop1::onBegin(){
	int jpNum = (int)(1.0 * Rtime * BPM / 60000.0);
	double onePz = 60000.0 / BPM;
	int lstPzTime = (int)(1.0 * onePz * jpNum);

	if (Rtime - lstPzTime > reTime && LRtime - lstPzTime <= reTime) {
		morePress = 0;
		if (nowPress == -1) {
			mstMove();
			if (mstMap[nowx][nowy] != 0) {
				gameType = 1;
				preFtMst1(mstMap[nowx][nowy]);
			}
		}
		nowPress = -1;
	}
	if(Rtime - lstPzTime > (int)(onePz / 2.0) && LRtime - lstPzTime <= (int)(onePz / 2.0)) {
		morePress = 0;
	}
	/*
	if(Rframe % jpFPS == reFPS+1){
    	morePress = 0;
    	if(nowPress == -1){
        	mstMove();
        	if(mstMap[nowx][nowy] != 0){
				gameType = 1;
				preFtMst1(mstMap[nowx][nowy]);
			}	
		}
    	nowPress = -1;
	}
	if(Rframe % jpFPS == jpFPS / 2 + 1){
    	morePress = 0;
	}
	*/
}

void mainLoop1::beforeLoop(){
	nowPress = -1;
	morePress = 0;
	lstPress = 2;
	noMusic = 0;

	fps->start();
	gsTime = fps->get_ticks() + 200;
	lstTime = gsTime - 1;
}

void mainLoop1::onType(){
	if( event.type == SDL_KEYUP )
    	if(event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT)
    		siShift = -1;
    if( event.type == SDL_KEYDOWN ){
    	if( event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT )
    		siShift = 1;
	
		if(catMove == 0  && gameType == 0){
			if( event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP )
	    		pressKey(0);
	    	if( event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT )
	    		pressKey(1);
	    	if( event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN )
	    		pressKey(2);
	    	if( event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT )
	    		pressKey(3);
		}
	}
}

// 怪物动作处理 
// 刷新怪物位置 
void mainLoop1::reFreshMst(){
	// 刷新怪物位置 
	memset(mstMap, 0, sizeof mstMap);
	for(int i = 1; i <= preMstNum; i++){
		if(ztMst[i][3] == 1){
			mstMap[ztMst[i][1]][ztMst[i][2]] = i;
		}
	}
	
}
// 怪物移动 (将怪要走的步长处理好存在mstMoveDXY中， 可以拿mstMapNext计算下一步地图） 
void mainLoop1::mstMove(){ 
	
	reFreshMst();
}
// 怪物动作处理 结束 

static SDL_Rect trect0 = {0, 0, 60, 60}, trect1 = {0, 0, 60, 60}, trect2 = {0, 0, 1556, 1556}, trect3 = {0, 0, 120, 120}, trect4 = {0, 0, 750, 750};
static SDL_Rect trect5, trect6 = {0, 0, 60, 180}, trect7 = {0, 270, 60, 180}, trect8 = {0, 0, 80, 80}, trect9 = {110, 320, 80, 80};
static SDL_Rect trect10 = {0, 330, 60, 60}, trect11 = {10, 600, 120, 60}, trect12 = {0, 600, 60, 60}, trect13 = {0, 0, 120, 60};
static SDL_Rect trect14 = {0, 0, 43, 48}, trect15 = {0, 0, 43, 48};
void mainLoop1::drawAll(){
	SDL_Rect *tmp0 = &trect0, *tmp1 = &trect1, *tmp2 = &trect2, *tmp3 = &trect3, *tmp4 = &trect4;
	SDL_Rect *tmp5 = &trect5, *tmp6 = &trect6, *tmp7 = &trect7, *tmp8 = &trect8, *tmp9 = &trect9;
	SDL_Rect *tmp10 = &trect10, *tmp11 = &trect11, *tmp12 = &trect12, *tmp13 = &trect13;

	int jpNum = (int)(1.0 * Rtime * BPM / 60000.0);
	double onePz = 60000.0 / BPM;
	int lstPzTime = (int)(1.0 * onePz * jpNum);
	
	// 绘制地形和怪物 
	SDL_Rect *tmp14 = &trect14, *tmp15 = &trect15;
	for(int i = nowx - 20; i <= nowx + 20; i++)
		for(int j = nowy - 20; j <= nowy + 20; j++){
			int drawnum;
			if(i < 0 || j < 0 || i > 499 || j > 499)
				drawnum = 1002;
			else if(dxMap[i][j] == 0)
				drawnum = 1001;
			else if(dxMap[i][j] == 1)
				drawnum = 1000;
			else
				drawnum = 1003;
			trect1.x = 1280 / 2 + (j - nowy) * 60 - 30;
			trect1.y = 720 / 2 + (i - nowx) * 60 - 30;
			if(catMove != 0){
				trect1.y -= (preCatMove - catMove) * (60 / preCatMove) * moveStep * tmv[moveDirect][0];
				trect1.x -= (preCatMove - catMove) * (60 / preCatMove) * moveStep * tmv[moveDirect][1];
			}
			SDL_RenderCopy ( myRenderer, pics->getPicText(drawnum),tmp0, RR.rr(tmp1));
			
			if(mstMap[i][j] != 0){
				drawnum = mstPic[ ztMst[mstMap[i][j]][0] - 1 ];
				SDL_RenderCopy ( myRenderer, pics->getPicText(drawnum), tmp4, RR.rr(tmp1));
			}
		}
	
	// 绘制FBK 
	trect14.x = 43;
	trect14.y = preXZT[lstPress] * 48;
	trect15.x = 1280 / 2 - 43 / 2;
	trect15.y = 720 / 2 - 48 / 2;
	if(catMove != 0){
		if(moveStep == 2)
			trect15.y -= preCatMove_jmp[ preCatMove - catMove ];
		else
			trect14.x = 43 * preCatMove_cat[preCatMove - catMove];
	}
	SDL_RenderCopy ( myRenderer, pics->getPicText(2004), tmp14, RR.rr(tmp15));
	
	// 绘制在地图行走时的一些杂物 


	// 加特技
	/*SDL_Rect ttrect1 = { 0, 0, 1280, 720 };
	if (lstTime / 30 != thisTime / 30) {
		ttcolor[0] = (thisTime / 30) % 240;
		if (ttcolor[0] > 120)
			ttcolor[0] = 240 - ttcolor[0];
		ttcolor[0] -= 20;
		if (ttcolor[0] > 80)
			ttcolor[0] = 80;
		if (ttcolor[0] < 0)
			ttcolor[0] = 0;
	}
	for (int i = 0; i < 20; i++) {
		pics->changeAlpha(1005, 20 + ttcolor[i]);
		SDL_RenderCopy(myRenderer, pics->getPicText(1005), NULL, RR.rr(&ttrect1));
		ttrect1.x -= 16 * 14;
		ttrect1.w += 32 * 14;
		ttrect1.y -= 9 * 14;
		ttrect1.h += 18 * 14;
	}*/
	

	// 绘制左上角标记 
	if(morePress != 0)
		SDL_RenderCopy ( myRenderer, pics->getPicText(3000), tmp0, RR.rr(tmp3));
	else if(nowPress != -1)
		SDL_RenderCopy ( myRenderer, pics->getPicText(3001), tmp0, RR.rr(tmp3));
	
	// 绘制左下角判定提示 
	/*int tmp_spd;
	for(tmp_spd = 1; tmp_spd * jpFPS < 120; tmp_spd++);
	if(tmp_spd * jpFPS - 120 > 120 - tmp_spd * jpFPS + jpFPS)
		tmp_spd--;
	trect12.x = Rframe % jpFPS;
	if(trect12.x > jpFPS / 2) trect12.x -= jpFPS;
	trect12.x *= -1 * tmp_spd;
	if(zheng(trect12.x) > 60)
		trect12.x = -200;
	trect12.x += 40;*/
	trect12.x = (int)(-120.0 * (Rtime - lstPzTime) / onePz);
	if (trect12.x <= -60)
		trect12.x += 120;
	trect12.x += 40;
	SDL_RenderCopy ( myRenderer, pics->getPicText(1102), tmp13, RR.rr(tmp11));
	SDL_RenderCopy ( myRenderer, pics->getPicText(3104), tmp0, RR.rr(tmp12));
	
	/*int tmp_alp = 255 - 8 * (Rframe - pressFrame);
	if(tmp_alp < 0) tmp_alp = 0;
	pics->changeAlpha(3109, tmp_alp);
	trect12.x = pressFrame % jpFPS;
	if(trect12.x > jpFPS / 2) trect12.x -= jpFPS;
	trect12.x *= -2;
	if(zheng(trect12.x) > 60)
		trect12.x = -200;
	trect12.x += 40;
	*/
	int jpNumT = (int)(1.0 * pressTime * BPM / 60000.0);
	int lstPzTimeT = (int)(1.0 * onePz * jpNumT); 
	trect12.x = (int)(-120.0 * (pressTime - lstPzTimeT) / onePz);
	if (trect12.x <= -60)
		trect12.x += 120;
	trect12.x += 40;
	int tmp_alp = 255 - (int)((Rtime - pressTime) * 255.0 / onePz);
	//cout << Rtime - pressTime << endl;
	if (tmp_alp < 0) tmp_alp = 0;
	pics->changeAlpha(3109, tmp_alp);
	SDL_RenderCopy ( myRenderer, pics->getPicText(3109), tmp0, RR.rr(tmp12));

	// 绘制左下角生命值 
	if(playerHp > 0){
		trect1.x = 0, trect1.y = 720 - 60;
		int tx = playerHp / 3;
		for(int i = 0; i < tx; i++){
			SDL_RenderCopy ( myRenderer, pics->getPicText(3010), NULL, RR.rr(tmp1));
			trect1.x += 60;
		}
		tx = playerHp - 3 * tx;
		if (tx != 0) {
			SDL_RenderCopy(myRenderer, pics->getPicText(3013 - tx), NULL, RR.rr(tmp1));
		}
	}

}


