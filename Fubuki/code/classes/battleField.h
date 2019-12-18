#pragma once

#ifndef BATTLE_FIELD_H_
#define BATTLE_FIELD_H_

#include "moster.h"

static int preCatMove_cat[20] = { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2 }; // 走路过程中20帧的行走图选择 
static int preXZT[4] = { 3, 2, 0, 1 }; // 行走图对应的上右下左 
class battleField {
public:
	int landMap[300][300];
	int mstNum;
	MONSTER* mstList[100];

	int backGroundPn, landPn[20], landType[20];
	// landType：0可通过 1不可通过
	SDL_Rect backGroundRect, landRect[20], backGroundOnMap;
	SDL_Rect *backGroundVRect, *landVRect[20];

	int gameType = 0, lstMstNum;

	int nowx, nowy, nextx, nexty, direct;
	
	int ifAttacked = 0, ifAttack = 0, movingProcess = 0;
	int nowMus = 0, nextMus = 0, musChangingProcess = 0;
	int mussNum[3], atkMus[3];

	int nowWp = 0; 
	vector<pair<int, int > > wpSize[5]; //坐标：假设面朝上，则为（上，右）

	int hp;

	battleField() {}
	void DbattleField() {
		for (int i = 0; i < 100; i++)
			if (mstList[i] != NULL)
				delete mstList[i];
	}
	void playSound() {
		int tt1 = GLBfps->get_ticks();
		GLBmuss->playChk(mussNum[0], -1, 0, 0);
		int tt2 = GLBfps->get_ticks();
		GLBmuss->playChk(mussNum[1], -1, tt2 - tt1 + 1, 0);
		GLBfps->get_ticks();
		GLBmuss->playChk(mussNum[2], -1, tt2 - tt1 + 1, 0);
		GLBmuss->changeLoud(mussNum[0], 200);
		fout1<< tt1 << ' ' << tt2 << endl;
	}
	void draw() {

		SDL_Rect TMP_rect1 = {0, 0, 120, 120};
		SDL_Rect TMP_rect2 = { 600, 320, 120, 120 };
		//sogr(1100, NULL, &TMP_rect1);
		// 绘制地形 
		
		if (backGroundPn != -1) {

		}
		for (int i = nowx - 5; i <= nowx + 5; i++)
			for (int j = nowy - 10; j <= nowy + 10; j++) {
				if (landPn[landMap[i][j]] == -1)
					continue;
				TMP_rect1.x = 1920 / 2 + (j - nowy) * 120 - 60;
				TMP_rect1.y = 1080 / 2 + (i - nowx) * 120 - 60;
				
				if (movingProcess != 0) {
					TMP_rect1.x -= (20 - movingProcess) * (120 / 20) * (nexty - nowy);
					TMP_rect1.y -= (20 - movingProcess) * (120 / 20) * (nextx - nowx);
				}
				sogr(landPn[landMap[i][j]], NULL, &TMP_rect1);
			}
		//绘制怪物
		for (int i = 1; i <= mstNum; i++) {
			if (mstList[i]->hp > 0) {
				if(mstList[i]->ifAttacked)
					GLBpics->changeAlpha(mstList[i]->picNum[mstList[i]->direct], 150);
				else
					GLBpics->changeAlpha(mstList[i]->picNum[mstList[i]->direct], 255);
				TMP_rect1.x = 1920 / 2 + (mstList[i]->nowy - nowy) * 120 - 60;
				TMP_rect1.y = 1080 / 2 + (mstList[i]->nowx - nowx) * 120 - 60;
				TMP_rect1.x -= (20 - movingProcess) * (120 / 20) * (nexty - nowy);
				TMP_rect1.y -= (20 - movingProcess) * (120 / 20) * (nextx - nowx);
				TMP_rect1.x += (20 - movingProcess) * (120 / 20) * (mstList[i]->nexty - mstList[i]->nowy);
				TMP_rect1.y += (20 - movingProcess) * (120 / 20) * (mstList[i]->nextx - mstList[i]->nowx);
				sogr(mstList[i]->picNum[mstList[i]->direct], mstList[i]->vrect[mstList[i]->direct], &TMP_rect1);
			}
			else if (mstList[i]->dying == 1 && movingProcess != 0) {
				GLBpics->changeAlpha(mstList[i]->picNum[mstList[i]->direct], 255 * movingProcess / 20);
				TMP_rect1.x = 1920 / 2 + (mstList[i]->nowy - nowy) * 120 - 60;
				TMP_rect1.y = 1080 / 2 + (mstList[i]->nowx - nowx) * 120 - 60;
				TMP_rect1.x -= (20 - movingProcess) * (120 / 20) * (nexty - nowy);
				TMP_rect1.y -= (20 - movingProcess) * (120 / 20) * (nextx - nowx);
				sogr(mstList[i]->picNum[mstList[i]->direct], mstList[i]->vrect[mstList[i]->direct], &TMP_rect1);
			}
		}

		//SDL_RenderCopy(GLBrenderer, GLBpics->getPicText(2000), NULL, &TMP_rect2);

		//画fbk
		TMP_rect1 = { 43, preXZT[direct] * 48, 43, 48 };
		TMP_rect2 = { 1920 / 2 - 43, 1080 / 2 - 48, 86, 96 };
		GLBpics->changeAlpha(2004, 255);
		if (movingProcess != 0) {
			if (nowx != nextx || nowy != nexty)
				TMP_rect1.x = 43 * preCatMove_cat[20 - movingProcess];
			if (ifAttacked == 1)
				GLBpics->changeAlpha(2004, 150);
		}
		sogr(2004, &TMP_rect1, &TMP_rect2);
	}

	void trueMove() {
		nowx = nextx;
		nowy = nexty;
		ifAttack = 0;
		ifAttacked = 0;
		for (int i = 0; i <= mstNum; i++) {
			if (mstList[i]->hp <= 0) {
				if(mstList[i]->dying == 1)
					mstList[i]->dying = 0, lstMstNum--;
			}
			else {
				mstList[i]->nowx = mstList[i]->nextx;
				mstList[i]->nowy = mstList[i]->nexty;
				mstList[i]->ifAttack = 0;
				mstList[i]->ifAttacked = 0;
			}
		}
		if (lstMstNum <= 0)
			gameType = 1;
		else if (hp <= 0)
			gameType = -1;
	}

	void onAfterType() {
		if (movingProcess != 0) {
			movingProcess -= Rmovingframe - LRmovingframe;
			if (movingProcess <= 0) {
				movingProcess = 0;
				trueMove();
			}
		}
		if (musChangingProcess != 0 && nowMus != nextMus) {
			musChangingProcess -= Rmovingframe - LRmovingframe;
			if (musChangingProcess <= 0) {
				musChangingProcess = 0;
				nowMus = nextMus;
				GLBmuss->changeLoud(mussNum[nowMus], 200);
				for (int i = 0; i < 3; i++)
					if (i != nowMus)
						GLBmuss->changeLoud(mussNum[i], 0);
			}
			else {
				int oth = 3 - nowMus - nextMus;
				GLBmuss->changeLoud(mussNum[oth], 0);
				GLBmuss->changeLoud(mussNum[nextMus], 200 - musChangingProcess);
				GLBmuss->changeLoud(mussNum[nowMus], musChangingProcess);
			}
		}
	}
	void fbkAttack() {
		double datk = atkMus[nowMus];
		for (int i = 0; i < wpSize[nowWp].size(); i++) {
			int atkx = wpSize[nowWp][i].first * PRE_DXY[direct][0] + wpSize[nowWp][i].second * PRE_DXY[(direct + 1) % 4][0] + nowx;
			int atky = wpSize[nowWp][i].first * PRE_DXY[direct][1] + wpSize[nowWp][i].second * PRE_DXY[(direct + 1) % 4][1] + nowy;
			for(int j = 1; j <= mstNum; j++)
				if (mstList[j]->hp > 0 && mstList[j]->nowx == atkx && mstList[j]->nowy == atky) {
					int ratk = mstList[j]->harmD[nowMus] * datk;
					if (ratk < 1)
						ratk = 1;
					mstList[j]->hp -= ratk;
					mstList[j]->ifAttacked = 1;
					ifAttack = 1;
				}
		}
	}
	void tryMove() {
		if (movingProcess != 0) {
			movingProcess = 0;
			trueMove();
		}

		if (ifAttack) {
			fbkAttack();
		}
		movingProcess = 20;
		// 怪物尝试移动，撞墙回头，要动的moving=1，不要的=0
		for (int i = 1; i <= mstNum; i++)
			if (mstList[i]->hp > 0) {
				mstList[i]->tryMove();
				if (landType[landMap[mstList[i]->nextx][mstList[i]->nexty]] == 1) {
					mstList[i]->nextx = mstList[i]->wantx = mstList[i]->nowx;
					mstList[i]->nexty = mstList[i]->wanty = mstList[i]->nowy;
					mstList[i]->turn();
				}
			}
		//fbk尝试移动，撞墙不动
		if (landType[landMap[nextx][nexty]] == 1) {
			nextx = nowx;
			nexty = nowy;
		}
		//怪物之间冲突检测，如果多个怪想进入同一个就都卡着
		int tws = 1;
		while (tws) {
			tws = 0;
			for (int i = 1; i < mstNum && tws == 0; i++)
				if (mstList[i]->hp > 0)
					for(int j = i + 1; j <= mstNum && tws == 0; j++)
						if (mstList[j]->hp > 0) {
							if (mstList[i]->nextx == mstList[j]->nextx && mstList[i]->nexty == mstList[j]->nexty) {
								tws = 1;
								int changex = mstList[i]->nextx, changey = mstList[i]->nexty;
								mstList[i]->nextx = mstList[i]->nowx;
								mstList[i]->nexty = mstList[i]->nowy;
								for (int k = j; k <= mstNum; k++) {
									if (mstList[k]->nextx == changex && mstList[k]->nexty == changey) {
										mstList[k]->nextx = mstList[k]->nowx;
										mstList[k]->nexty = mstList[k]->nowy;
									}
								}
							}
						}
		}
		//检测fbk前进路线是否被卡，同时不可和怪物互换位置
		tws = 1;
		for (int i = 1; i <= mstNum; i++)
			if (mstList[i]->hp > 0 && ((mstList[i]->nextx == nextx && mstList[i]->nexty == nexty) 
			|| (mstList[i]->nextx == nowx && mstList[i]->nexty == nowy && mstList[i]->nowx == nextx && mstList[i]->nowy == nexty) )) {
				tws = 0;
				break;
			}
		//如果没有被卡
		if (tws == 1) {
			//计算被攻击伤害
			int atkSum = 0;
			for (int i = 1; i <= mstNum; i++)
				if (mstList[i]->hp > 0 && mstList[i]->moving == 1 && mstList[i]->wantx == nextx && mstList[i]->wanty == nexty) {
					atkSum += mstList[i]->attack;
					mstList[i]->ifAttack = 1;
				}
			if (atkSum != 0) {
				ifAttacked = 1;
				hp -= atkSum;
			}
			return;
		}
		//如果被卡
		mstList[0]->nowx = mstList[0]->nextx = nowx;
		mstList[0]->nowy = mstList[0]->nexty = nowy;
		mstList[0]->hp = 1;
		//加入fbk位置后判断冲突
		tws = 1;
		while (tws) {
			tws = 0;
			for (int i = 0; i < mstNum && tws == 0; i++)
				if (mstList[i]->hp > 0)
					for (int j = i + 1; j <= mstNum && tws == 0; j++)
						if (mstList[j]->hp > 0) {
							if (mstList[i]->nextx == mstList[j]->nextx && mstList[i]->nexty == mstList[j]->nexty) {
								tws = 1;
								int changex = mstList[i]->nextx, changey = mstList[i]->nexty;
								mstList[i]->nextx = mstList[i]->nowx;
								mstList[i]->nexty = mstList[i]->nowy;
								for (int k = j; k <= mstNum; k++) {
									if (mstList[k]->nextx == changex && mstList[k]->nexty == changey) {
										mstList[k]->nextx = mstList[k]->nowx;
										mstList[k]->nexty = mstList[k]->nowy;
									}
								}
							}
						}
		}
		//计算被攻击伤害
		int atkSum = 0;
		for (int i = 1; i <= mstNum; i++)
			if (mstList[i]->hp > 0 && mstList[i]->moving == 1 && ((mstList[i]->wantx == nowx && mstList[i]->wanty == nowy) ||
			(mstList[i]->wantx == mstList[i]->nextx && mstList[i]->wanty == mstList[i]->nexty && mstList[i]->wantx == nextx && mstList[i]->wanty == nexty))) {
				atkSum += mstList[i]->attack;
				mstList[i]->ifAttack = 1;
			}
		if (atkSum != 0) {
			ifAttacked = 1;
			hp -= atkSum;
		}
		//被卡所以不移动
		nextx = nowx;
		nexty = nowy;
	}
	void trueTap(int tapped, int shiftSign) {
		//0123方向键 45切换颜色 67切换支援角色
		if (tapped >= 0 && tapped < 4) {
			
			nextx = nowx + PRE_DXY[tapped][0];
			nexty = nowy + PRE_DXY[tapped][1];
			ifAttack = 1;
			direct = tapped;
			tryMove();
			fout1 << nextx << ' ' << nexty << endl;
			return;
		}
		if (tapped == 4 || tapped == 5) {
			if (musChangingProcess == 0) {
				musChangingProcess = 200;
				nextMus = (nowMus + 6 - tapped) % 3;
			}
			tryMove();
		}
	}
};



#endif