#ifndef CLOTHS_DATA_H_wnrf_
#define CLOTHS_DATA_H_wnrf_

#include <bits/stdc++.h>
#define zheng(x) ((x)>0?(x):(-1*(x)))

// 变量定义 

// 主要变量 
int FRAMES_PER_SECOND = 60;
// 帧率 
int reFPS = 8;
// 音游部分击中误差帧数（正负） 
int jpFPS = 40;
//音游部分音乐速度（帧数/拍子） 

//跟踪当前帧的帧计数器
int frame = 0;
// 当前帧号 
int gsframe = 0;
// 进入游戏时的帧数编号
bool cap = true;  
//是否限制帧率

string pnss2[10][16] = {"A3", "C4", "E4", "A4", "G3", "B3", "D4", "G4", "F3", "A3", "C4", "A3", "E3", "B3", "E3", "G3",
						"E3", "A3", "A3", "E3", "D3", "G3", "D3", "E3", "C3", "C3", "F3", "C3", "B3", "G3", "A3", "B3", 
						"E3", "E3", "E3", "E3", "D3", "D3", "D3", "D3", "C3", "C3", "C3", "C3", "C3", "C3", "C3", "C3", 
						"A3", "A3", "A3", "A3", "G3", "G3", "G3", "G3", "F3", "F3", "F3", "F3", "E3", "F3", "E3", "E3", 
						"E3", "E3", "E3", "E3", "G3", "G3", "G3", "G3", "D3", "D3", "D3", "D3", "E3", "F3", "E3", "D3", };

char pm1[10][16] = 	  {	'w', 'w', 'w', 'w', 'a', 'a', 'a', 'a', 's', 's', 's', 's', 'd', 'd', 'd', 'd',
						'w', 'w', 's', 's', 'a', 'a', 'd', 'd', 'a', 'w', 'd', 's', 'w', 'a', 's', 'd',
						'd', 'd', 'a', 'a', 's', 's', 'w', 'w', 's', 'a', 'w', 'd', 'a', 's', 'd', 'w',
						's', 's', 'w', 'w', 'd', 'd', 'a', 'a', 'd', 's', 'a', 'w', 's', 'd', 'w', 'a',
						'a', 'a', 'd', 'd', 'w', 'w', 's', 's', 'w', 'd', 's', 'a', 'd', 'w', 'a', 's' };

double preSoundSystemSDST[6] = {0, 0.25, 0.5, 0.75, 1.0/3.0, 2.0/3.0};
// 对应开始时间 
int playSoundSystem[5][500][9][6];
// 五种变奏  八个声道  拍子数  0,1/4,1/2,3/4,1/3,2/3作为6种开始时间
int pmSystem[5][500][6];
bool siPmSystem[5][500][6];
// 不需要声道 
int loopLenth = 16;
// 音乐loop小节数 
string musicScoreList[1000]; 
// 存储音乐信息的文件名
int needPressPmList[1000], LNPPL;

int dxMap[500][500], mstMap[500][500];
int tmv[4][2] = {-1, 0, 0, 1, 1, 0, 0, -1};
int nowx, nowy;
int nowPress, morePress, lstPress, gameType, playerHp, catMove, pressFrame;
int preCatMove_cat[20] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2};
int preCatMove_jmp[20] = {5, 10, 15, 21, 26, 30, 35, 39, 43, 48, 52, 56, 59, 61, 62, 60, 51, 40, 28, 15};
int preCatMove = 20;
int moveDirect, moveStep;
int preXZT[4] = {3, 2, 0, 1};

int nowPress2, morePress2, sttFrame2, nowPlay2, nowMst2, pmType2, nowPlayNum2, gameStep2;
bool siGame2[100];
int siShift;
int needPlay2[100];
int prePlayNum2 = 8;
int preMst[100][3] = {1, 255, 255, 1, 245, 245, 2, 245, 255, 2, 255, 245};
int mstPic[100] = {2100, 2101}; 
int preMstNum = 4, nowMstNum;
int ztMst[100][5];
// 变量定义 结束 


// 加载声音系统 
string soundName[100] = {	"A0", "#A0", "B0", 
							"C1", "#C1", "D1", "#D1", "E1", "F1", "#F1", "G1", "#G1", "A1", "#A1", "B1", 
							"C2", "#C2", "D2", "#D2", "E2", "F2", "#F2", "G2", "#G2", "A2", "#A2", "B2", 
							"C3", "#C3", "D3", "#D3", "E3", "F3", "#F3", "G3", "#G3", "A3", "#A3", "B3", 
							"C4", "#C4", "D4", "#D4", "E4", "F4", "#F4", "G4", "#G4", "A4", "#A4", "B4", 
							"C5", "#C5", "D5", "#D5", "E5", "F5", "#F5", "G5", "#G5", "A5", "#A5", "B5", 
							"C6", "#C6", "D6", "#D6", "E6", "F6", "#F6", "G6", "#G6", "A6", "#A6", "B6", 
							"C7", "#C7", "D7", "#D7", "E7", "F7", "#F7", "G7", "#G7", "A7", "#A7", "B7", 
							"C8"	}; 
int directName[200];
void load_musData( MUSS *hello ){
	hello->init();
	
	for(int i = 0; i <= 51; i++)
		hello->insertChk( "items/musics/"+soundName[i]+".mp3", i );
	hello->insertChk("items/musics/snare.mp3", 101);
	hello->insertChk("items/musics/kick.mp3", 102);
	
	//hello->insertMus("items/musics/karoi.mp3", 1);
	//hello->playMus(1, 1);
}
// 加载声音系统 结束
 

// 加载图片 
void load_picData(PICS *hello){
	//设置透明色 
    SDL_Surface *transprt = IMG_Load("items/pictures/transprt.png");
    Uint32 colorKey = SDL_MapRGB(transprt->format, 0x00, 0xff, 0xff);
	
	ifstream fin("items/lists/pictureList.gdata");
	string tmp_str;
	int tmp_num;
	while(fin >> tmp_str){
		fin >> tmp_num;
		hello->insertPic(tmp_str, tmp_num, colorKey);
	}
	fin.close();
}
// 加载图片 结束


// 真实帧数计算
#define Rframe (frame - gsframe)
// 真实帧数计算 结束 


// 音频处理部分 
// 清空音频 
void clearSound( MUSS * hello ){
	for(int i = 1; i <= 8; i++)
		hello->haltChk( i );
}
// 音名转音频号 
int stringToPn( string pss ){
	int psn = -1;
	for(int i = 0; i < 88; i++)
		if( pss == soundName[i] ){
			psn = i;
			break;
		}
	if( pss.compare("STOP") == 0 || pss.compare("stop") == 0 )
		psn = -2;
	return psn;
}
// 播放钢琴键 
void pressPianoKey( int chnl, int psn, MUSS * hello){
	if(psn >= 0){
		hello->playChk( psn , chnl );
	}
	if(psn == -2){
		hello->haltChk( chnl );
	}
}
void pressPianoKey( int chnl, string pss, MUSS * hello){
	int psn = stringToPn(pss);
	pressPianoKey( chnl, psn, hello );
}
// 播放下一个声音 
void playNextSound(MUSS * hello){
	int tmp_xj = Rframe / jpFPS;
	hello->playChk(102, 1);
	pressPianoKey(2, pnss2[0][tmp_xj % loopLenth], hello);
	if(gameType == 1 && pmType2 != -1)
		pressPianoKey(3, pnss2[ pmType2+1 ][tmp_xj % loopLenth], hello);
	tmp_xj++;
}
void playNextSound2 (MUSS * hello){
	int tmp_xj = Rframe / jpFPS;
	int tmp_st = -1;
	int tmp_ms = Rframe % jpFPS;
	for(int i = 0; i < 6; i++){
		if( (int)(preSoundSystemSDST[i] * jpFPS) == tmp_ms ){
			tmp_st = i;
			break;
		}
	}
	if(tmp_st == -1)
		return;
		
	for(int i = 1; i <= 8; i++)
		pressPianoKey(i, playSoundSystem[ pmType2+1 ][tmp_xj][i][tmp_ms], hello);
}
// 音频处理部分 结束 


 
void init_all(){
	memset(directName, 0, sizeof directName);
	for(int i = 0; i <= 128; i++)
		directName[i] = -1;
	directName['w'] = directName['W'] = directName['u'] = directName['U'] = 0;
	directName['d'] = directName['D'] = directName['r'] = directName['R'] = 1;
	directName['s'] = directName['S'] = directName['d'] = directName['D'] = 2;
	directName['a'] = directName['A'] = directName['l'] = directName['L'] = 3;
	
	memset(dxMap, 0, sizeof dxMap);
	for(int i = 240; i <= 260; i++)
		for(int j = 240; j <= 260; j++)
			dxMap[i][j] = (i + j) % 2 + 1;
	
	for(int i = 1; i <= preMstNum; i++){
		ztMst[i][0] = preMst[i-1][0];
		ztMst[i][1] = preMst[i-1][1];
		ztMst[i][2] = preMst[i-1][2];
		ztMst[i][3] = 1;
	}
	
	nowx = 250;
	nowy = 250;
	nowPress = -1;
	morePress = 0;
	lstPress = 3;
	gameType = 0;
	playerHp = 10;
	nowMstNum = preMstNum;
	siShift = -1;
	catMove = 0;
	pressFrame = -200;
	
	//frame = 0;
	gsframe = frame;
}


// 绘制所有图像
SDL_Rect trect0 = {0, 0, 60, 60}, trect1 = {0, 0, 60, 60}, trect2 = {0, 0, 1556, 1556}, trect3 = {0, 0, 120, 120}, trect4 = {0, 0, 750, 750};
SDL_Rect trect5, trect6 = {0, 0, 60, 180}, trect7 = {0, 270, 60, 180}, trect8 = {0, 0, 80, 80}, trect9 = {110, 320, 80, 80};
SDL_Rect trect10 = {0, 330, 60, 60}, trect11 = {10, 600, 120, 60}, trect12 = {0, 600, 60, 60}, trect13 = {0, 0, 120, 60};
SDL_Rect trect14 = {0, 0, 43, 48}, trect15 = {0, 0, 43, 48};
void draw_All(SDL_Renderer *myrenderer, PICS *hello){
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
			SDL_RenderCopy ( myrenderer, hello->getPicText(drawnum), tmp0, tmp1);
			
			if(mstMap[i][j] != 0){
				drawnum = mstPic[ ztMst[mstMap[i][j]][0] - 1 ];
				SDL_RenderCopy ( myrenderer, hello->getPicText(drawnum), tmp4, tmp1);
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
	SDL_RenderCopy ( myrenderer, hello->getPicText(2004), tmp14, tmp15);
	
	// 绘制在地图行走时的一些杂物 
	if(gameType == 0){
		// 绘制左上角标记 
		if(morePress != 0)
			SDL_RenderCopy ( myrenderer, hello->getPicText(3000), tmp0, tmp3);
		else if(nowPress != -1)
			SDL_RenderCopy ( myrenderer, hello->getPicText(3001), tmp0, tmp3);
		
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
		SDL_RenderCopy ( myrenderer, hello->getPicText(1102), tmp13, tmp11);
		SDL_RenderCopy ( myrenderer, hello->getPicText(3104), tmp0, tmp12);
		
		int tmp_alp = 255 - 8 * (Rframe - pressFrame);
		if(tmp_alp < 0) tmp_alp = 0;
		hello->changeAlpha(3109, tmp_alp);
		trect12.x = pressFrame % jpFPS;
		if(trect12.x > jpFPS / 2) trect12.x -= jpFPS;
		trect12.x *= -2;
		if(zheng(trect12.x) > 60)
			trect12.x = -200;
		trect12.x += 40;
		SDL_RenderCopy ( myrenderer, hello->getPicText(3109), tmp0, tmp12);
	}
	
	// 绘制音游谱面 
	if(gameType == 1){
		// 绘制谱面背景 
		trect5.x = 0; trect5.w = 960; trect5.y = (720 - 180) / 2 - 20; trect5.h = 20;
		SDL_RenderCopy ( myrenderer, hello->getPicText(1002), tmp0, tmp5);
		trect5.x = 0; trect5.w = 960; trect5.y = (720 + 180) / 2; trect5.h = 20;
		SDL_RenderCopy ( myrenderer, hello->getPicText(1002), tmp0, tmp5);
		trect5.x = 0; trect5.w = 960; trect5.y = (720 - 180) / 2; trect5.h = 180;
		SDL_RenderCopy ( myrenderer, hello->getPicText(3006+pmType2), tmp0, tmp5);
		
		// 画谱面 
		int tmp_spd = 5;
		if(gameStep2 == 0)
			tmp_spd = 1;
		// 版本 1 
		trect7.x = trect10.x = 120 + tmp_spd * (sttFrame2 - Rframe);
		for(int i = 1; i <= nowPlayNum2; i++){
			SDL_RenderCopy ( myrenderer, hello->getPicText(3104), tmp6, tmp7);
			if(!siGame2[i]){
				if(sttFrame2 - Rframe + (i-1)*jpFPS < -1 * reFPS)
					SDL_RenderCopy ( myrenderer, hello->getPicText(3200+needPlay2[i]), tmp0, tmp10);
				else
					SDL_RenderCopy ( myrenderer, hello->getPicText(3100+needPlay2[i]), tmp0, tmp10);
			}
			trect7.x += tmp_spd*jpFPS;
			trect10.x += tmp_spd*jpFPS;
		}
		// 版本 2 
		/*int tmp_xx = 120 + tmp_spd * (sttFrame2 - Rframe);
		for(int i = 1; i <= nowPlayNum2; i++){
			trect7.x = tmp_xx + tmp_spd * (i-1) * jpFPS;
			SDL_RenderCopy ( myrenderer, hello->getPicText(3104), tmp6, tmp7);
			for(int j = 0; j < 6; j++){
				if(siPmSystem[ pmType2+1 ][ needPlay2[i] ][j] && pmSystem[ pmType2+1 ][ needPlay2[i] ][j] != -1){
					int tmp_dx = (int)((preSoundSystemSDST[j]-1.0+i) * jpFPS);
					trect10.x = tmp_xx + tmp_spd * tmp_dx;
					if(sttFrame2 - Rframe + tmp_dx < -1 * reFPS)
						SDL_RenderCopy ( myrenderer, hello->getPicText(3200+needPlay2[i]), tmp0, tmp10);
					else
						SDL_RenderCopy ( myrenderer, hello->getPicText(3200+needPlay2[i]), tmp0, tmp10);
				}
			}
		}*/
		
		// 画判定线 
		trect7.x = 120;
		SDL_RenderCopy ( myrenderer, hello->getPicText(3105), tmp6, tmp7);
		if(morePress2 != 0)
			SDL_RenderCopy ( myrenderer, hello->getPicText(3106), tmp8, tmp9);
		else if(nowPress2 != -1 && needPlay2[nowPlay2] != -1)
			SDL_RenderCopy ( myrenderer, hello->getPicText(3107), tmp8, tmp9);
	}
	
	// 绘制左下角生命值 
	if(playerHp > 0){
		trect1.x = 0, trect1.y = 720 - 60;
		for(int i = 0; i < playerHp; i++){
			SDL_RenderCopy ( myrenderer, hello->getPicText(3002), tmp0, tmp1);
			trect1.x += 60;
		}
	}
	
	// 失败 
	if(playerHp <= 0){
		trect5.x = 0; trect5.w = 960; trect5.y = 0; trect5.h = 720;
		SDL_RenderCopy ( myrenderer, hello->getPicText(1100), tmp5, tmp5);
	}
	// 胜利 
	if(nowMstNum <= 0){
		trect5.x = 0; trect5.w = 960; trect5.y = 0; trect5.h = 720;
		SDL_RenderCopy ( myrenderer, hello->getPicText(1101), tmp5, tmp5);
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
// 怪物移动
void mstMove(){ 
	
	reFreshMst();
}
// 怪物动作处理 结束 


// 遇怪后预处理
// 第一次预处理，准备选择谱面 
void preFtMst1(int mstNum){
	//memset(siGame2, 0, sizeof siGame2);
	sttFrame2 = ((Rframe + 2 * reFPS) / jpFPS + 1) * jpFPS;
	nowPlay2 = 0;
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
void preFtMst2(){
	if(morePress2 == 0)
		pmType2 = nowPress2;
	memset(siGame2, 0, sizeof siGame2);
	sttFrame2 = ((Rframe + 2 * reFPS) / jpFPS + 1) * jpFPS;
	nowPlay2 = 0;
	
	gameStep2 = 1;
	nowPlayNum2 = prePlayNum2;
	int tmp_xj = (Rframe + jpFPS / 2) / jpFPS;
	for(int i = tmp_xj + 1; i <= tmp_xj + nowPlayNum2; i++)
		needPlay2[i - tmp_xj] = directName[ pm1[ pmType2+1 ][i % loopLenth] ];
	
	nowPress2 = 1;
	morePress2 = 0;
}
void preFtMst22(){
	if(morePress2 == 0)
		pmType2 = nowPress2;
	memset(siPmSystem, 0, sizeof siPmSystem);
	sttFrame2 = ((Rframe + 2 * reFPS) / jpFPS + 1) * jpFPS;
	nowPlay2 = 0;
	
	gameStep2 = 1;
	nowPlayNum2 = prePlayNum2;
	int tmp_xj = (Rframe + jpFPS / 2) / jpFPS;
	for(int i = tmp_xj + 1; i <= tmp_xj + nowPlayNum2; i++)
		needPlay2[i - tmp_xj] = i % loopLenth;
	
	nowPress2 = 1;
	morePress2 = 0;
}
// 遇怪后预处理 结束 


// 音游部分有效输入后反应 
void checkNextPlay(){
	nowPlay2++;
	if(gameStep2 == 1){
		if(nowPress2 != needPlay2[nowPlay2] && needPlay2[nowPlay2] != -1){
			morePress2 = 1;
			playerHp--;
		}
		else
			siGame2[nowPlay2] = 1;
		if(nowPlay2 == nowPlayNum2){
			gameType = 0;
			nowPress = lstPress;
			morePress = 0;
			ztMst[nowMst2][3] = 0;
			nowMstNum--;
			reFreshMst(); 
		}
		return ;
	}
	if(gameStep2 == 0){
		preFtMst2();
		return ;
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

#endif
