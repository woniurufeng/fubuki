#include "basicMainLoop.h"
// µ÷½ÚÒôÓÎÆ«²î

void mainLoop4::beforeLoop() {
	//muss->haltAllChk();
	//muss->playChk(1000);
	//muss->playChk(201);
	btp1.set_button(myRenderer, pics, 4001, 0, 20, 20, 60, 60);
	btd1.set_button(myRenderer, pics, 4001, 0, 100, 20, 60, 60);
	btg0.set_button(myRenderer, pics, 4001, 0, 180, 20, 60, 60);
	btBack.set_button(myRenderer, pics, 4001, 0, 300, 20, 60, 60);
	//gotoGame = 0;
}

static SDL_Rect trect0 = { 0, 0, 60, 60 }, trect1 = { 0, 0, 60, 60 }, trect2 = { 0, 0, 1556, 1556 }, trect3 = { 0, 0, 120, 120 }, trect4 = { 0, 0, 750, 750 };
static SDL_Rect trect5, trect6 = { 0, 0, 60, 180 }, trect7 = { 0, 270, 60, 180 }, trect8 = { 0, 0, 80, 80 }, trect9 = { 110, 320, 80, 80 };
static SDL_Rect trect10 = { 0, 330, 60, 60 }, trect11 = { 10, 600, 120, 60 }, trect12 = { 0, 600, 60, 60 }, trect13 = { 0, 0, 120, 60 };
static SDL_Rect trect14 = { 0, 0, 43, 48 }, trect15 = { 0, 0, 43, 48 };
void mainLoop4::drawAll() {
	btp1.show();
	btd1.show();
	btg0.show();
	btBack.show();

	SDL_Rect* tmp0 = &trect0, * tmp1 = &trect1, * tmp2 = &trect2, * tmp3 = &trect3, * tmp4 = &trect4;
	SDL_Rect* tmp5 = &trect5, * tmp6 = &trect6, * tmp7 = &trect7, * tmp8 = &trect8, * tmp9 = &trect9;
	SDL_Rect* tmp10 = &trect10, * tmp11 = &trect11, * tmp12 = &trect12, * tmp13 = &trect13; 
	
	int jpNum = (int)(1.0 * Rtime * BPM / 60000.0);
	double onePz = 60000.0 / BPM;
	int lstPzTime = (int)(1.0 * onePz * jpNum);

	trect12.x = (int)(-120.0 * (Rtime - lstPzTime) / onePz);
	if (trect12.x <= -60)
		trect12.x += 120;
	trect12.x += 40;
	SDL_RenderCopy(myRenderer, pics->getPicText(1102), tmp13, RR.ll(tmp11));
	SDL_RenderCopy(myRenderer, pics->getPicText(3104), tmp0, RR.ll(tmp12));
	
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
	SDL_RenderCopy(myRenderer, pics->getPicText(3109), tmp0, RR.ll(tmp12));
}

void mainLoop4::onType() {
	if (btp1.handle_events(event) == 1)
		dtTime -= 10;
	if (btd1.handle_events(event) == 1)
		dtTime += 10;
	if (btg0.handle_events(event) == 1)
		dtTime = 0;
	if (btBack.handle_events(event) == 1)
		breakSign = 1;

	if (event.type == SDL_KEYDOWN) {
		pressTime = Rtime;
	}
}