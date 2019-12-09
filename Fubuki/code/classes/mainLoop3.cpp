#include "basicMainLoop.h"
// gg»­Ãæ

void mainLoop3::onType(){
	if( event.type == SDL_KEYUP )
    	if(event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT)
    		siShift = -1;
    if( event.type == SDL_KEYDOWN ){
    	if( event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT )
    		siShift = 1;
    	
    	if( event.key.keysym.sym == SDLK_w ){
    		//init();
			breakSign = 1;
		}
    }
}

static SDL_Rect trect0 = {0, 0, 60, 60}, trect1 = {0, 0, 60, 60}, trect2 = {0, 0, 1556, 1556}, trect3 = {0, 0, 120, 120}, trect4 = {0, 0, 750, 750};
static SDL_Rect trect5, trect6 = {0, 0, 60, 180}, trect7 = {0, 270, 60, 180}, trect8 = {0, 0, 80, 80}, trect9 = {110, 320, 80, 80};
static SDL_Rect trect10 = {0, 330, 60, 60}, trect11 = {10, 600, 120, 60}, trect12 = {0, 600, 60, 60}, trect13 = {0, 0, 120, 60};
static SDL_Rect trect14 = {0, 0, 43, 48}, trect15 = {0, 0, 43, 48};
void mainLoop3::drawAll(){
	SDL_Rect *tmp0 = &trect0, *tmp1 = &trect1, *tmp2 = &trect2, *tmp3 = &trect3, *tmp4 = &trect4;
	SDL_Rect *tmp5 = &trect5, *tmp6 = &trect6, *tmp7 = &trect7, *tmp8 = &trect8, *tmp9 = &trect9;
	SDL_Rect *tmp10 = &trect10, *tmp11 = &trect11, *tmp12 = &trect12, *tmp13 = &trect13;
	
	// Ê§°Ü 
	if(playerHp <= 0){
		trect5.x = 0; trect5.w = 960; trect5.y = 0; trect5.h = 720;
		SDL_RenderCopy ( myRenderer, pics->getPicText(1100), tmp5, RR.ll(tmp5));
	}
	// Ê¤Àû 
	if(nowMstNum <= 0){ 
		trect5.x = 0; trect5.w = 960; trect5.y = 0; trect5.h = 720;
		SDL_RenderCopy ( myRenderer, pics->getPicText(1101), tmp5, RR.ll(tmp5));
	}
}

void mainLoop3::init(){
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
	gameType = 0;
	playerHp = 10;
	nowMstNum = preMstNum;
	siShift = -1;
	catMove = 0;
	pressFrame = -200;
	pmType = -1;
	
	//gsframe = frame + 1;
	lstTime = -1000;
	thisTime = 0;
	
	load_musicScore(0);
	breakSign = 1;

	for (int i = 0; i < 3000; i++)
		muss->haltAllChk(i);

	fps->start();
	gsTime = fps->get_ticks();
}
