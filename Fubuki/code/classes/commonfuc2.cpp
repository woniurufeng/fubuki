
#include "commonfuc2.h"

// 音频处理部分 


//画图方面
void drawHp1(int playerHp) {
	// 绘制左下角生命值 
	if (playerHp > 0) {
		SDL_Rect TMP_rect1 = { 1920 - 170, 80, 90, 90 };
		int tx = playerHp / 3;
		for (int i = 0; i < tx; i++) {
			sogr(3010, NULL, &TMP_rect1);
			TMP_rect1.x -= 90;
		}
		tx = playerHp - 3 * tx;
		if (tx != 0) {
			sogr(3013 - tx, NULL, &TMP_rect1);
		}
	}
}
void drawBeat1() {
	int jpNum = (int)(1.0 * Rtime * BPM / 60000.0);
	double onePz = 60000.0 / BPM;
	int lstPzTime = (int)(1.0 * onePz * jpNum);

	SDL_Rect TMP_rect1 = { 0, 1080 - 84 - 74, 18, 74 };
	TMP_rect1.x = 200 + (int)(-200 * (Rtime - lstPzTime) / onePz) + 1920 / 2 - 9;
	for (int i = 1; i <= 10; i++) {
		sogr(3000, NULL, &TMP_rect1);
		TMP_rect1.x += 200;
	}
	TMP_rect1.x = -200 + (int)(200 * (Rtime - lstPzTime) / onePz) + 1920 / 2 - 9;
	for (int i = 1; i <= 10; i++) {
		sogr(3000, NULL, &TMP_rect1);
		TMP_rect1.x -= 200;
	}
}

void drawMusCircle1(int nowMus, int nextMus, int ds) {
	double agl = 0;
	SDL_Rect TMP_rect1 = { 1920 / 2 - 124 / 2, 1080 - 84 - 74 / 2 - 124 / 2, 124, 124 };
	if (ds != 0 && nowMus != nextMus) {
		if(nextMus == (nowMus + 1) % 3 )
			agl = nowMus * 120.0 + 120 * (200.0 - ds) / 200.0;
		else
			agl = nowMus * 120.0 - 120 * (200.0 - ds) / 200.0;
		SDL_RenderCopyEx(GLBrenderer, GLBpics->getPicText(3107), NULL, RR.rr(&TMP_rect1), agl, NULL, SDL_FLIP_NONE);
	}
	else {
		agl = nowMus * 120;
		SDL_RenderCopyEx(GLBrenderer, GLBpics->getPicText(3107), NULL, RR.rr(&TMP_rect1), agl, NULL ,SDL_FLIP_NONE);
	}
}



//存储方面
void saveDtTime() {
	ofstream fout("save/dtTime.txt");
	fout << dtTime << endl;
	fout.close();
}