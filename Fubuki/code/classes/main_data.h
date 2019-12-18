#ifndef MAIN_DATA_H_
#define MAIN_DATA_H_

#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "basicfuncs.h"
#include "commonfuc2.h"

//extern void load_musData(Muss *muss);
static void load_musData( MUSS *muss ){
	muss->init();

	ifstream fin("items/lists/musicList.gdata");

	string tmp_str;
	int tmp_num;
	while (fin >> tmp_str) {
		fin >> tmp_num;
		muss->insertChk(tmp_str, tmp_num);
	}
	fin.close();
	
	//muss->playMus(1, 1);

}
 

// 加载图片 
static void load_picData(PICS *pics){
	//设置透明色 
    SDL_Surface *transprt = IMG_Load("items/pictures/transprt.png");
	blueColorKey = SDL_MapRGB(transprt->format, 0x00, 0xff, 0xff);
	
	ifstream fin("items/lists/pictureList.gdata");
	string tmp_str;
	int tmp_num;
	while(fin >> tmp_str){
		fin >> tmp_num;
		pics->insertPic(tmp_str, tmp_num, blueColorKey);
	}
	fin.close();
}
// 加载图片 结束

 
static void init_all(Timer *fps){

	
	//gsframe = frame;

	gsTime = fps->get_ticks() + 1000;
}


#endif

//当用户还没退出时 (main 旧) 
    /*
	while( 1 )
    {
    	
        //启动帧计时器
        fps.start();
        if(playerHp > 0){
	        if(gameType == 0){
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
			}
			if(gameType == 1 && gameStep2 == 0){
		        if(Rframe % jpFPS == reFPS+1){
		        	morePress2 = 0;
		        	if(nowPress2 == -1 && Rframe > sttFrame2){
		        		checkNextPlay();
					}
		        	nowPress2 = -1;
				}
				if(Rframe % jpFPS == jpFPS / 2 + 1){
		        	morePress2 = 0;
		        	nowPress2 = -1;
				}
			}	
		}
        
		
        
     //当有事件需要处理
        while( SDL_PollEvent( &event ) )
        {             
            //如果有一个按键被按下
            if( event.type == SDL_KEYUP )
            	if(event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT)
            		siShift = -1;
            if( event.type == SDL_KEYDOWN ){
            	if( event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT )
            		siShift = 1;
            	if(playerHp > 0 && nowMstNum > 0){
            		if(catMove == 0){
	            		if( event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP ){
		            		pressKey(0);
						}
		            	if( event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT ){
		            		pressKey(1);
						}
		            	if( event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN ){
		            		pressKey(2);
						}
		            	if( event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT ){
		            		pressKey(3);
						}	
					}
				}
				else{
					if( event.key.keysym.sym == SDLK_w ){
						init_all();
					}
				}
            	
			}
            //如果用户单击了窗口右上角的关闭按钮
            if( event.type == SDL_QUIT )
            {
                //退出程序
                exitGame();
                return 0;
            }
        }
        if(playerHp > 0){
	        if(gameType == 1 && gameStep2 == 1)
				checkNextPlay(); 
	        
	        if(catMove != 0){
	        	catMove--;
	        	if(catMove == 0)
	        		catMoveIs0();
			}
			if(greenShine != 0)
				greenShine--;
			if(redShine != 0)
				redShine--;	
		}
        
        
        //清空重绘 
        SDL_SetRenderDrawColor ( myRenderer , 255, 255, 255, 255 );
		SDL_RenderClear( myRenderer );
        draw_All(myRenderer, pics);
		
		
        //更新画面
		SDL_RenderPresent( myRenderer );
		
		// 播放声音 
        playNextSound(muss);
        	
		//帧计数器加1
        frame++;
        //如果我们需要限制帧率
        if( ( cap == true ) && ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) )
        {
            //休眠一段时间，时长为当前帧的剩余时间。
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
        
	}
	*/



/*


// 播放下一个声音 
static void playNextSound (MUSS * muss){
	int tmp_xj = (Rframe / jpFPS) % loopLenth;
	int tmp_st = -1;
	int tmp_ms = Rframe % jpFPS;
	for(int i = 0; i < 6; i++){
		if( (int)(preSoundSystemSDST[i] * jpFPS + 0.5) == tmp_ms ){
			tmp_st = i;
			break;
		}
	}
	if(tmp_st == -1)
		return;
	for(int i = 1; i <= 8; i++)
		if(playSoundSystem[ pmType+1 ][tmp_xj][i][tmp_st] != -1){
			pressPianoKey(i, playSoundSystem[ pmType+1 ][tmp_xj][i][tmp_st], muss);
			//fout1 << playSoundSystem[ pmType2+1 ][tmp_xj][i][tmp_st] << ' ' << pmType2+1 << ' ' << tmp_xj << ' ' << i << ' ' << tmp_st << endl;
		}
			
}
// 音频处理部分 结束 


// 绘制所有图像
SDL_Rect trect0 = {0, 0, 60, 60}, trect1 = {0, 0, 60, 60}, trect2 = {0, 0, 1556, 1556}, trect3 = {0, 0, 120, 120}, trect4 = {0, 0, 750, 750};
SDL_Rect trect5, trect6 = {0, 0, 60, 180}, trect7 = {0, 270, 60, 180}, trect8 = {0, 0, 80, 80}, trect9 = {110, 320, 80, 80};
SDL_Rect trect10 = {0, 330, 60, 60}, trect11 = {10, 600, 120, 60}, trect12 = {0, 600, 60, 60}, trect13 = {0, 0, 120, 60};
SDL_Rect trect14 = {0, 0, 43, 48}, trect15 = {0, 0, 43, 48};
void draw_All(SDL_Renderer *myrenderer, PICS *pics){
	SDL_Rect *tmp0 = &trect0, *tmp1 = &trect1, *tmp2 = &trect2, *tmp3 = &trect3, *tmp4 = &trect4;
	SDL_Rect *tmp5 = &trect5, *tmp6 = &trect6, *tmp7 = &trect7, *tmp8 = &trect8, *tmp9 = &trect9;
	SDL_Rect *tmp10 = &trect10, *tmp11 = &trect11, *tmp12 = &trect12, *tmp13 = &trect13;
	
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
			trect1.x = 960 / 2 + (j - nowy) * 60 - 30;
			trect1.y = 720 / 2 + (i - nowx) * 60 - 30;
			if(catMove != 0){
				trect1.y -= (preCatMove - catMove) * (60 / preCatMove) * moveStep * tmv[moveDirect][0];
				trect1.x -= (preCatMove - catMove) * (60 / preCatMove) * moveStep * tmv[moveDirect][1];
			}
			SDL_RenderCopy ( myrenderer, pics->getPicText(drawnum), tmp0, tmp1);
			
			if(mstMap[i][j] != 0){
				drawnum = mstPic[ ztMst[mstMap[i][j]][0] - 1 ];
				SDL_RenderCopy ( myrenderer, pics->getPicText(drawnum), tmp4, tmp1);
			}
		}
	
	// 绘制FBK 
	trect14.x = 43;
	trect14.y = preXZT[lstPress] * 48;
	trect15.x = 960 / 2 - 43 / 2;
	trect15.y = 720 / 2 - 48 / 2;
	if(catMove != 0){
		if(moveStep == 2)
			trect15.y -= preCatMove_jmp[ preCatMove - catMove ];
		else
			trect14.x = 43 * preCatMove_cat[preCatMove - catMove];
	}
	SDL_RenderCopy ( myrenderer, pics->getPicText(2004), tmp14, tmp15);
	
	// 绘制在地图行走时的一些杂物 
	if(gameType == 0){
		// 绘制左上角标记 
		if(morePress != 0)
			SDL_RenderCopy ( myrenderer, pics->getPicText(3000), tmp0, tmp3);
		else if(nowPress != -1)
			SDL_RenderCopy ( myrenderer, pics->getPicText(3001), tmp0, tmp3);
		
		// 绘制左下角判定提示 
		int tmp_spd;
		for(tmp_spd = 1; tmp_spd * jpFPS < 120; tmp_spd++);
		if(tmp_spd * jpFPS - 120 > 120 - tmp_spd * jpFPS + jpFPS)
			tmp_spd--;
		trect12.x = Rframe % jpFPS;
		if(trect12.x > jpFPS / 2) trect12.x -= jpFPS;
		trect12.x *= -1 * tmp_spd;
		if(zheng(trect12.x) > 60)
			trect12.x = -200;
		trect12.x += 40;
		SDL_RenderCopy ( myrenderer, pics->getPicText(1102), tmp13, tmp11);
		SDL_RenderCopy ( myrenderer, pics->getPicText(3104), tmp0, tmp12);
		
		int tmp_alp = 255 - 8 * (Rframe - pressFrame);
		if(tmp_alp < 0) tmp_alp = 0;
		pics->changeAlpha(3109, tmp_alp);
		trect12.x = pressFrame % jpFPS;
		if(trect12.x > jpFPS / 2) trect12.x -= jpFPS;
		trect12.x *= -2;
		if(zheng(trect12.x) > 60)
			trect12.x = -200;
		trect12.x += 40;
		SDL_RenderCopy ( myrenderer, pics->getPicText(3109), tmp0, tmp12);
	}
	
	// 绘制音游谱面 
	if(gameType == 1){
		// 绘制谱面背景 
		trect5.x = 0; trect5.w = 960; trect5.y = (720 - 180) / 2 - 20; trect5.h = 20;
		SDL_RenderCopy ( myrenderer, pics->getPicText(1002), tmp0, tmp5);
		trect5.x = 0; trect5.w = 960; trect5.y = (720 + 180) / 2; trect5.h = 20;
		SDL_RenderCopy ( myrenderer, pics->getPicText(1002), tmp0, tmp5);
		trect5.x = 0; trect5.w = 960; trect5.y = (720 - 180) / 2; trect5.h = 180;
		SDL_RenderCopy ( myrenderer, pics->getPicText(3006+pmType2), tmp0, tmp5);
		
		// 画谱面 
		int tmp_spd = (1.0 * jpFPS / 8.0 + 0.5);
		if(gameStep2 == 0)
			tmp_spd = 2;
		// 版本 1 
		if(gameStep2 == 0)
		{
			trect7.x = trect10.x = 120 + tmp_spd * (sttFrame2 - Rframe);
			for(int i = 1; i <= nowPlayNum2; i++){
				SDL_RenderCopy ( myrenderer, pics->getPicText(3104), tmp6, tmp7);
				if(!siGame2[i]){
					if(sttFrame2 - Rframe + (i-1)*jpFPS < -1 * reFPS)
						SDL_RenderCopy ( myrenderer, pics->getPicText(3200+needPlay2[i]), tmp0, tmp10);
					else
						SDL_RenderCopy ( myrenderer, pics->getPicText(3100+needPlay2[i]), tmp0, tmp10);
				}
				trect7.x += tmp_spd*jpFPS;
				trect10.x += tmp_spd*jpFPS;
			}
		}
		// 版本 2
		if(gameStep2 == 1){
			int tmp_xx = 120 + tmp_spd * (sttFrame2 - Rframe);
			for(int i = 0; i <= nowPlayNum2; i++){
				trect7.x = tmp_xx + tmp_spd * i * jpFPS;
				SDL_RenderCopy ( myrenderer, pics->getPicText(3104), tmp6, tmp7);
			}
			for(int i = 1; i <= lNPPL; i++){
				trect10.x = 120 + tmp_spd * (needPressPmList[i][0] - Rframe);
				if(siPressPmList[i] == 0)
					SDL_RenderCopy ( myrenderer, pics->getPicText(3100+needPressPmList[i][1]), tmp0, tmp10);
				if(siPressPmList[i] == -1)
					SDL_RenderCopy ( myrenderer, pics->getPicText(3200+needPressPmList[i][1]), tmp0, tmp10);
			}
			
		}
		
		// 画判定线 
		trect7.x = 120;
		SDL_RenderCopy ( myrenderer, pics->getPicText(3105), tmp6, tmp7);
		
		// 画反馈
		if(greenShine != 0 || redShine != 0){
			int tmp_alp = 255 - (maxShine - max(greenShine, redShine)) * (255 / maxShine + 1);
			pics->changeAlpha(3106, tmp_alp);
			pics->changeAlpha(3107, tmp_alp);
			if(greenShine >= redShine)
				SDL_RenderCopy ( myrenderer, pics->getPicText(3107), tmp8, tmp9);
			else
				SDL_RenderCopy ( myrenderer, pics->getPicText(3106), tmp8, tmp9);
		}
	}
	
	// 绘制左下角生命值 
	if(playerHp > 0){
		trect1.x = 0, trect1.y = 720 - 60;
		for(int i = 0; i < playerHp; i++){
			SDL_RenderCopy ( myrenderer, pics->getPicText(3002), tmp0, tmp1);
			trect1.x += 60;
		}
	}
	
	// 失败 
	if(playerHp <= 0){
		trect5.x = 0; trect5.w = 960; trect5.y = 0; trect5.h = 720;
		SDL_RenderCopy ( myrenderer, pics->getPicText(1100), tmp5, tmp5);
	}
	// 胜利 
	if(nowMstNum <= 0){ 
		trect5.x = 0; trect5.w = 960; trect5.y = 0; trect5.h = 720;
		SDL_RenderCopy ( myrenderer, pics->getPicText(1101), tmp5, tmp5);
	}
}
// 绘制所有图像结束 


// 怪物动作处理 
// 刷新怪物位置 
void reFreshMst(){
	// 刷新怪物位置 
	memset(mstMap, 0, sizeof mstMap);
	for(int i = 1; i <= preMstNum; i++){
		if(ztMst[i][3] == 1){
			mstMap[ztMst[i][1]][ztMst[i][2]] = i;
		}
	}
	
}
// 怪物移动 (将怪要走的步长处理好存在mstMoveDXY中， 可以拿mstMapNext计算下一步地图） 
void mstMove(){ 
	
	reFreshMst();
}
// 怪物动作处理 结束 


// 遇怪后预处理
// 第一次预处理，准备选择谱面 
void preFtMst1(int mstNum){
	//memset(siGame2, 0, sizeof siGame2);
	//sttFrame2 = ((Rframe + jpFPS / 2) / jpFPS + 1) * jpFPS;
	sttFrame2 = (Rframe / jpFPS + 2) * jpFPS;
	pmType2 = -1;
	nowMst2 = mstNum;
	gameStep2 = 0;
	nowPlayNum2 = 1;
	siGame2[1] = 0;
	needPlay2[1] = 8;
	
	nowPress2 = 1;
	morePress2 = 0;
}
// 确定谱面后第二次预处理，存储谱面
int preSxOfT[6] = {0, 1, 4, 2, 5, 3};
void preFtMst2(){
	greenShine = redShine = 0;
	
	if(morePress2 == 0){
		pmType2 = nowPress2; 
		if(nowPress2 != -1)
			greenShine = maxShine;
	}
	memset(siPressPmList, 0, sizeof siPressPmList);
	memset(needPressPmList, 0, sizeof needPressPmList);
	sttFrame2 = ((Rframe + jpFPS / 2) / jpFPS + 1) * jpFPS;
	
	gameStep2 = 1;
	nowPlayNum2 = prePlayNum2;
	int tmp_xj = (Rframe + jpFPS / 2) / jpFPS;
	for(int i = tmp_xj + 1; i <= tmp_xj + nowPlayNum2; i++)
		needPlay2[i - tmp_xj] = i % loopLenth;
	lNPPL = 0;
	nNPPL = 1;
	for(int i = 1; i <= nowPlayNum2; i++){
		for(int jj = 0; jj < 6; jj++){
			int j = preSxOfT[jj];
			if(pmSystem[ pmType2+1 ][ needPlay2[i] ][j] != -1){
				++lNPPL;
				needPressPmList[ lNPPL ][0] = sttFrame2 + (int)((preSoundSystemSDST[j]-1.0+i)*jpFPS);
				needPressPmList[ lNPPL ][1] = pmSystem[ pmType2+1 ][ needPlay2[i] ][j];
			}
		}
	}
	//fout1 << lNPPL << endl << nNPPL << endl;
	nowPress2 = 1;
	morePress2 = 0;
}
// 遇怪后预处理 结束 


// 音游部分有效输入后反应 
void gameType1End(){
	greenShine = redShine = 0;
	gameType = 0;
	gameStep2 = 0;
	nowPress = lstPress;
	morePress = 0;
	ztMst[nowMst2][3] = 0;
	nowMstNum--;
	pmType2 = -1;
	reFreshMst(); 
}
void checkNextPlay(){
	if(gameStep2 == 0){
		preFtMst2();
		return ;
	}
	if(gameStep2 == 1){
		if(nNPPL > lNPPL){
			if(Rframe == sttFrame2 + jpFPS * nowPlayNum2 - 1)
				gameType1End();
			if(nowPress2 != -1){
				nowPress2 = -1;
				redShine = maxShine;
			}
			return ;
		}
		while(nNPPL < lNPPL){
			if(Rframe >= needPressPmList[nNPPL+1][0]){
				siPressPmList[nNPPL] = -1;
				playerHp--;
				nNPPL++;
				redShine = maxShine;
			}
			else
				break;
		}
		if(Rframe - needPressPmList[nNPPL][0] > reFPS){
			siPressPmList[nNPPL] = -1;
			playerHp--;
			nNPPL++;
			redShine = maxShine;
		}
		if(nNPPL > lNPPL){
			if(Rframe == sttFrame2 + jpFPS * nowPlayNum2 - 1)
				gameType1End();
			return ;
		}
		if(Rframe == sttFrame2 + jpFPS * nowPlayNum2 - 1){
			if(nowPress2 != needPressPmList[lNPPL][1])
				playerHp--;
			gameType1End();
			return ;
		}
		
		if(nowPress2 != -1){
			if(needPressPmList[nNPPL][0] - Rframe > reFPS && needPressPmList[nNPPL][0] - Rframe <= jpFPS / 2){
				siPressPmList[nNPPL] = -1;
				playerHp--;
				nNPPL++;
				redShine = maxShine;
			}
			else if(needPressPmList[nNPPL][0] - Rframe <= reFPS){
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

// 地图行走时动画结束后实际进行位移 
void catMoveIs0(){
	nowx += moveStep*tmv[moveDirect][0];
	nowy += moveStep*tmv[moveDirect][1];
	if(mstMap[nowx][nowy] != 0){
		gameType = 1;
		preFtMst1(mstMap[nowx][nowy]);
	}
}

// 按键后反应 
void pressKey(int key){
	// 记录按键时间 
	pressFrame = Rframe;
	// 地图行走中 
	if(gameType == 0){
		
		int step = 1;
		if(siShift == 1){
			step = 2;
		}
		
		if(morePress == 1)
			return ;
		if(nowPress != -1){
			morePress = 1;
			return ;
		}
		if(Rframe % jpFPS > reFPS && Rframe % jpFPS < jpFPS - reFPS){
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
	// 音游中 
	if(gameType == 1){
		if(gameStep2 == 1){
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
		if(Rframe % jpFPS > reFPS && Rframe % jpFPS < jpFPS - reFPS){
			morePress2 = 1;
			return ;
		}
		nowPress2 = key;
		checkNextPlay();
	}
}
*/
