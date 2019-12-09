#include "basicMainLoop.h"
// 音游部分qte


static int ttcolor[30] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

void mainLoop2::beforeLoop(){
	//sttFrame2 = (Rframe / jpFPS + 2) * jpFPS; 

	int SSTjpNum = (int)(1.0 * Rtime * BPM / 60000.0);
	double onePz = 60000.0 / BPM;
	sttTime2 = (int)(1.0 * onePz * (2.0 + SSTjpNum));

	pmType = -1;
	nowPlayNum2 = 1;
	siGame2[1] = 0;
	needPlay2[1] = 8;
	
	nowPress2 = 1;
	morePress2 = 0;
}

void mainLoop2::onBegin(){
	if(gameStep == 0){
		int jpNum = (int)(1.0 * Rtime * BPM / 60000.0);
		double onePz = 60000.0 / BPM;
		int lstPzTime = (int)(1.0 * onePz * jpNum);

		if (Rtime - lstPzTime > reTime && LRtime - lstPzTime <= reTime) {
			morePress2 = 0;
			//if (nowPress2 == -1 && Rframe > sttFrame2) {
			if (nowPress2 == -1 && Rtime > sttTime2) {
				checkNextPlay();
			}
			nowPress2 = -1;
		}
		if (Rtime - lstPzTime > (int)(onePz / 2.0) && LRtime - lstPzTime <= (int)(onePz / 2.0)) {
        	morePress2 = 0;
        	nowPress2 = -1;
		}

        /*if(Rframe % jpFPS == reFPS+1){
        	morePress2 = 0;
        	if(nowPress2 == -1 && Rframe > sttFrame2){
        		checkNextPlay();
			}
        	nowPress2 = -1;
		}
		if(Rframe % jpFPS == jpFPS / 2 + 1){
        	morePress2 = 0;
        	nowPress2 = -1;
		}*/
	}	
}

void mainLoop2::gameType1End(){
	greenShine = redShine = 0;
	ztMst[nowMst][3] = 0;
	nowMstNum--;
	
	gameType = 0;
}

void mainLoop2::onAfterPframe(){
	if(playerHp <= 0 || gameType == 0)
		breakSign = 1;
}

const int preSxOfT[6] = {0, 1, 4, 2, 5, 3}; 
void mainLoop2::preFtMst2(){
	greenShine = redShine = 0;
	
	if(morePress2 == 0){
		pmType = nowPress2; 
		if(nowPress2 != -1){
			greenShine = maxShine;
			if(musicType == 1 && playSoundSystem2[pmType + 1] != playSoundSystem2[0])
				noMusic = 1;
		}
	}
	memset(siPressPmList, 0, sizeof siPressPmList);
	memset(needPressPmList, 0, sizeof needPressPmList);
	int tmp_xj = (int)(1.0 * Rtime * BPM / 60000.0 + 0.5);
	double onePz = 60000.0 / BPM;
	//sttFrame2 = ((Rframe + jpFPS / 2) / jpFPS + 1) * jpFPS;
	sttTime2 = (int)(1.0 * onePz * (1.0 + tmp_xj));
	
	gameStep = 1;
	nowPlayNum2 = prePlayNum2;
	//int tmp_xj = (Rframe + jpFPS / 2) / jpFPS;
	for(int i = tmp_xj + 1; i <= tmp_xj + nowPlayNum2; i++)
		needPlay2[i - tmp_xj] = i % loopLenth;
	lNPPL = 0;
	nNPPL = 1;
	for(int i = 1; i <= nowPlayNum2; i++){
		for(int jj = 0; jj < 6; jj++){
			int j = preSxOfT[jj];
			if(pmSystem[ pmType+1 ][ needPlay2[i] ][j] != -1){
				++lNPPL;
				//needPressPmList[ lNPPL ][0] = sttFrame2 + (int)((preSoundSystemSDST[j]-1.0+i)*jpFPS);
				needPressPmList[lNPPL][0] = sttTime2 + (int)((preSoundSystemSDST[j] - 1.0 + i) * onePz);
				needPressPmList[ lNPPL ][1] = pmSystem[ pmType+1 ][ needPlay2[i] ][j];
			}
		}
	}
	nowPress2 = 1;
	morePress2 = 0;
}

void mainLoop2::checkNextPlay(){
	if(gameStep == 0){
		preFtMst2();
		return ;
	}
	double onePz = 60000.0 / BPM;
	if(gameStep == 1){

		if(nNPPL > lNPPL){
			//if(Rframe == sttFrame2 + jpFPS * nowPlayNum2 - 1)
			if(Rtime >= sttTime2 + (int)(onePz * nowPlayNum2) - 1)
				gameType1End();
			if(nowPress2 != -1){
				nowPress2 = -1;
				redShine = maxShine;
			}
			return ;
		}
		while(nNPPL < lNPPL){
			if(Rtime >= needPressPmList[nNPPL+1][0]){
				siPressPmList[nNPPL] = -1;
				playerHp--;
				nNPPL++;
				redShine = maxShine;
			}
			else
				break;
		}
		//if(Rframe - needPressPmList[nNPPL][0] > reFPS){
		if (Rtime - needPressPmList[nNPPL][0] > reTime) {
			siPressPmList[nNPPL] = -1;
			playerHp--;
			nNPPL++;
			redShine = maxShine;
		}
		if(nNPPL > lNPPL){
			if (Rtime >= sttTime2 + (int)(onePz * nowPlayNum2) - 1)
				gameType1End();
			return ;
		}
		//if(Rframe == sttFrame2 + jpFPS * nowPlayNum2 - 1){
		if (Rtime >= sttTime2 + (int)(onePz * nowPlayNum2) - 1){
			if(nowPress2 != needPressPmList[lNPPL][1])
				playerHp--;
			gameType1End();
			return ;
		}
		
		if(nowPress2 != -1){
			//if(needPressPmList[nNPPL][0] - Rframe > reFPS && needPressPmList[nNPPL][0] - Rframe <= jpFPS / 2){
			if (needPressPmList[nNPPL][0] - Rtime > reTime && needPressPmList[nNPPL][0] - Rtime <= onePz / 2) {
				siPressPmList[nNPPL] = -1;
				playerHp--;
				nNPPL++;
				redShine = maxShine;
			}
			else if( zheng( needPressPmList[nNPPL][0] - Rtime ) <= reTime){
				if(nowPress2 == needPressPmList[nNPPL][1]){
					siPressPmList[nNPPL] = 1;
					nNPPL++;
					greenShine = maxShine;	
				}
				else{
					siPressPmList[nNPPL] = -1;
					playerHp--;
					nNPPL++;
					redShine = maxShine;	
				}
			}
			else{
				redShine = maxShine;
			}
			nowPress2 = -1;
		}
	}
}

void mainLoop2::pressKey(int key){
	if(gameStep == 1){
		nowPress2 = key;
		checkNextPlay();
		return ;
	}
	
	if(morePress2 == 1)
		return ;
	
	if(nowPress2 != -1){
		morePress2 = 1;
		return ;
	}

	int jpNum = (int)(1.0 * Rtime * BPM / 60000.0);
	double onePz = 60000.0 / BPM;
	int lstPzTime = (int)(1.0 * onePz * jpNum);

	if (Rtime - lstPzTime > reTime && Rtime - lstPzTime < (int)(onePz - reTime)) {
	//if(Rframe % jpFPS > reFPS && Rframe % jpFPS < jpFPS - reFPS){
		morePress2 = 1;
		return ;
	}
	nowPress2 = key;
	checkNextPlay();
}

void mainLoop2::onType(){
	if( event.type == SDL_KEYUP )
    	if(event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT)
    		siShift = -1;
    if( event.type == SDL_KEYDOWN ){
    	if( event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT )
    		siShift = 1;
    		
		if(playerHp > 0 && gameType == 1){
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

void mainLoop2::onAfterType(){
	if(playerHp > 0){
        if(gameType == 1 && gameStep == 1)
			checkNextPlay(); 

		if(greenShine != 0)
			greenShine -= Rframe - LRframe;
		if(redShine != 0)
			redShine -= Rframe - LRframe;
		if (greenShine < 0)
			greenShine = 0;
		if (redShine < 0)
			redShine = 0;
	}
}
static SDL_Rect trect0 = {0, 0, 60, 60}, trect1 = {0, 0, 60, 60}, trect2 = {0, 0, 1556, 1556}, trect3 = {0, 0, 120, 120}, trect4 = {0, 0, 750, 750};
static SDL_Rect trect5, trect6 = {0, 0, 60, 180}, trect7 = {0, 270, 60, 180}, trect8 = {0, 0, 80, 80}, trect9 = {110, 320, 80, 80};
static SDL_Rect trect10 = {0, 330, 60, 60}, trect11 = {10, 600, 120, 60}, trect12 = {0, 600, 60, 60}, trect13 = {0, 0, 120, 60};
static SDL_Rect trect14 = {0, 0, 43, 48}, trect15 = {0, 0, 43, 48};
void mainLoop2::drawAll(){
	SDL_Rect *tmp0 = &trect0, *tmp1 = &trect1, *tmp2 = &trect2, *tmp3 = &trect3, *tmp4 = &trect4;
	SDL_Rect *tmp5 = &trect5, *tmp6 = &trect6, *tmp7 = &trect7, *tmp8 = &trect8, *tmp9 = &trect9;
	SDL_Rect *tmp10 = &trect10, *tmp11 = &trect11, *tmp12 = &trect12, *tmp13 = &trect13;
	SDL_Rect *tmp14 = &trect14, *tmp15 = &trect15;
	// 绘制地形和怪物 
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

			SDL_RenderCopy ( myRenderer, pics->getPicText(drawnum), tmp0, RR.rr(tmp1));
			
			if(mstMap[i][j] != 0){
				drawnum = mstPic[ ztMst[mstMap[i][j]][0] - 1 ];
				SDL_RenderCopy ( myRenderer, pics->getPicText(drawnum),tmp4, RR.rr(tmp1));
			}
		}
	// 加特技
	/*
	SDL_Rect ttrect1 = { 0, 0, 1280, 720 };
	if (lstTime / 30 != thisTime / 30) {
		ttcolor[0] = (thisTime / 30) % 160;
		if (ttcolor[0] > 80)
			ttcolor[0] = 160 - ttcolor[0];
	}
	for (int i = 0; i < 20; i++) {
		pics->changeAlpha(1005, 20 + ttcolor[i]);
		SDL_RenderCopy(myRenderer, pics->getPicText(1005), NULL, RR.rr(&ttrect1));
		ttrect1.x -= 16 * 14;
		ttrect1.w += 32 * 14;
		ttrect1.y -= 9 * 14;
		ttrect1.h += 18 * 14;
	}
	*/
	
	
	// 绘制音游谱面 
	// 绘制谱面背景 
	trect5.x = 0; trect5.w = 1280; trect5.y = (720 - 180) / 2 - 20; trect5.h = 20;
	SDL_RenderCopy ( myRenderer, pics->getPicText(1002), tmp0, RR.rr(tmp5));
	trect5.x = 0; trect5.w = 1280; trect5.y = (720 + 180) / 2; trect5.h = 20;
	SDL_RenderCopy ( myRenderer, pics->getPicText(1002), tmp0, RR.rr(tmp5));
	trect5.x = 0; trect5.w = 1280; trect5.y = (720 - 180) / 2; trect5.h = 180;
	SDL_RenderCopy ( myRenderer, pics->getPicText(3006+pmType), tmp0, RR.rr(tmp5));
	
	// 画谱面 
	//int tmp_spd = (int)(1.0 * jpFPS / 8.0 + 0.5);
	double onePz = 60000.0 / BPM;

	double tmp_spd = 0.4;

	// 版本 1 
	if(gameStep == 0)
	{
		for(int i = 1; i <= nowPlayNum2; i++){
			trect7.x = trect10.x = (int)(120.0 + tmp_spd * (sttTime2 - Rtime) + (i - 1.0) * onePz);

			SDL_RenderCopy ( myRenderer, pics->getPicText(3104), RR.ll(tmp6), RR.rr(tmp7));
			if(!siGame2[i]){
				//if(sttFrame2 - Rframe + (i-1)*jpFPS < -1 * reFPS)
				if(sttTime2 - Rtime + (int)((i-1.0)*onePz) < -1 * reTime)
					SDL_RenderCopy ( myRenderer, pics->getPicText(3200+needPlay2[i]), RR.ll(tmp0), RR.rr(tmp10));
				else
					SDL_RenderCopy ( myRenderer, pics->getPicText(3100+needPlay2[i]), RR.ll(tmp0), RR.rr(tmp10));
			}
		}
	}
	// 版本 2
	if(gameStep == 1){
		//int tmp_xx = 120 + tmp_spd * (sttFrame2 - Rframe);
		for(int i = 0; i <= nowPlayNum2; i++){
			trect7.x = (int)(120.0 + tmp_spd * (sttTime2 - Rtime) + tmp_spd * i * onePz);

			SDL_RenderCopy ( myRenderer, pics->getPicText(3104), RR.ll(tmp6), RR.rr(tmp7));
		}
		for(int i = 1; i <= lNPPL; i++){
			trect10.x = (int)(120.0 + tmp_spd * (needPressPmList[i][0] - Rtime));
			if(siPressPmList[i] == 0)
				SDL_RenderCopy ( myRenderer, pics->getPicText(3100+needPressPmList[i][1]),tmp0, RR.rr(tmp10));
			if(siPressPmList[i] == -1)
				SDL_RenderCopy ( myRenderer, pics->getPicText(3200+needPressPmList[i][1]), tmp0, RR.rr(tmp10));
		}
		
	}
	
	// 画判定线 
	trect7.x = 120;
	SDL_RenderCopy ( myRenderer, pics->getPicText(3105), tmp6, RR.rr(tmp7));
	
	// 画反馈
	if(greenShine != 0 || redShine != 0){
		int tmp_alp = 255 - (maxShine - max(greenShine, redShine)) * (255 / maxShine + 1);
		pics->changeAlpha(3106, tmp_alp);
		pics->changeAlpha(3107, tmp_alp);
		if(greenShine >= redShine)
			SDL_RenderCopy ( myRenderer, pics->getPicText(3107), tmp8, RR.rr(tmp9));
		else
			SDL_RenderCopy ( myRenderer, pics->getPicText(3106), tmp8, RR.rr(tmp9));
	}
		
	// 绘制左下角生命值 
	if (playerHp > 0) {
		trect1.x = 0, trect1.y = 720 - 60;
		int tx = playerHp / 3;
		for (int i = 0; i < tx; i++) {
			SDL_RenderCopy(myRenderer, pics->getPicText(3010), NULL, RR.rr(tmp1));
			trect1.x += 60;
		}
		tx = playerHp - 3 * tx;
		if (tx != 0) {
			SDL_RenderCopy(myRenderer, pics->getPicText(3013 - tx), NULL, RR.rr(tmp1));
		}
	}
}
