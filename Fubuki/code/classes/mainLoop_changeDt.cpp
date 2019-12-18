#include "basicMainLoop.h"
// µ÷½ÚÒôÓÎÆ«²î

void mainLoop_changeDt::beforeLoop() {
	//muss->haltAllChk();
	//muss->playChk(1000);
	//muss->playChk(201);
	btp1.set_button(myRenderer, pics, 4001, 0, 20, 20, 60, 60);
	btd1.set_button(myRenderer, pics, 4001, 0, 100, 20, 60, 60);
	btg0.set_button(myRenderer, pics, 4001, 0, 180, 20, 60, 60);
	btBack.set_button(myRenderer, pics, 4001, 0, 300, 20, 60, 60);

	loopLength = 144;
	BPM = 132;
	pressTime = -1000;

	fps->start();
	gsTime = fps->get_ticks() + 200;
	lstTime = gsTime - 1;
	//gotoGame = 0;
}
void mainLoop_changeDt::playSound() {
	int jpNum = (int)(1.0 * RRtime * BPM / 60000.0);
	double onePz = 60000.0 / BPM;
	int lstPzTime = (int)(1.0 * onePz * jpNum);

	if (jpNum % loopLength == 0 && RRtime - lstPzTime > 0 && LRRtime - lstPzTime <= 0) {
		muss->playChk(301);
	}
}

static void drawDtTime(SDL_Renderer *myRenderer) {
	char tmpDraw[20];
	int cdt[20], lcdt = 0, tdt = dtTime;
	tmpDraw[0] = '+';
	if (tdt < 0)
		tdt *= -1, tmpDraw[0] = '-';
	while (tdt != 0)
		cdt[++lcdt] = tdt % 10, tdt /= 10;
	if (lcdt == 0)
		lcdt = 1, cdt[1] = 0;
	for (int i = 0; i < lcdt; i++)
		tmpDraw[i + 1] = cdt[lcdt - i] + '0';
	tmpDraw[lcdt + 1] = 'm', tmpDraw[lcdt + 2] = 's', tmpDraw[lcdt + 3] = '\0';
	FC_Draw(GLBfont1, myRenderer, RR.ww(200), RR.hh(200), "%s\n", tmpDraw);
}

void mainLoop_changeDt::drawAll() {
	btp1.show();
	btd1.show();
	btg0.show();
	btBack.show();

	drawDtTime(myRenderer);

	SDL_Rect TMP_rect1;
	int jpNum = (int)(1.0 * pressTime * BPM / 60000.0);
	double onePz = 60000.0 / BPM;
	int lstPzTime = (int)(1.0 * onePz * jpNum);

	int tred = 200.0 * reTime / onePz;
	TMP_rect1 = { 1920 / 2, 1080 - 84 - 74, tred, 74 };
	sogr(3008, NULL, &TMP_rect1);
	TMP_rect1.x -= 200;
	sogr(3008, NULL, &TMP_rect1);
	TMP_rect1.x += 200 - tred;
	sogr(3008, NULL, &TMP_rect1);
	TMP_rect1.x += 200;
	sogr(3008, NULL, &TMP_rect1);

	drawBeat1();

	pics->changeAlpha(3001, min0(255 - (RRtime - pressTime2) / 2));
	TMP_rect1 = { 0, 1080 - 84 - 74, 18, 74 };
	TMP_rect1.x = 200 + (int)(-200 * (pressTime - lstPzTime) / onePz) + 1920 / 2 - 9;
	sogr(3001, NULL, &TMP_rect1);
	TMP_rect1.x = -200 + (int)(200 * (pressTime - lstPzTime) / onePz) + 1920 / 2 - 9;
	sogr(3001, NULL, &TMP_rect1);

	TMP_rect1 = { 1920 / 2 - 2, 1080 - 84 - 74, 4, 74 };
	sogr(1002, NULL, &TMP_rect1);
	TMP_rect1.x -= 200;
	sogr(1002, NULL, &TMP_rect1);
	TMP_rect1.x += 400;
	sogr(1002, NULL, &TMP_rect1);

}

void mainLoop_changeDt::onType() {
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
		pressTime2 = RRtime;
		double onePz = 60000.0 / BPM;
		int tlst = 1.0 * pressTime / onePz;
		tlst = pressTime - 1.0 * tlst * onePz;
		int tds = 1;
		if (tlst > onePz / 2)
			tds = -1;
		tlst = zheng(onePz / 2 - tlst);
		fout1 << tlst << endl;
		dtTime += tds * (tlst + 2) / 10;
		if (dtTime < onePz)
			dtTime += onePz;
		tlst = dtTime / onePz;
		dtTime = dtTime - tlst * onePz;
	}
}