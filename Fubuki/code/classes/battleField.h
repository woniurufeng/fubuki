#pragma once

#ifndef BATTLE_FIELD_H_
#define BATTLE_FIELD_H_

#include "moster.h"

struct drawBlock {
	int picNum, alp, realy;
	SDL_Rect onPicR;
	SDL_Rect onMapR;
};
static drawBlock needDraw[3000];
static int ndn;


static bool cmp01(MONSTER* x, MONSTER* y) {
	if (y->hp <= 0 && y->dying == 0)
		return 1;
	if (x->hp <= 0 && x->dying == 0)
		return 0;
	return x->realy < y->realy;
}
static bool cmp02(drawBlock &x, drawBlock &y) {
	return x.realy < y.realy;
}


class battleField {
public:
	int landMap[300][300];
	// landMap：0可通过 1不可通过
	int mstNum;
	MONSTER* mstList[100];
	drawBlock firstDraw[100], afterDraw[500];
	int fdn, adn;
	int usex, usey, usen, usem;
	int camarax, camaray;

	int gameType = 0, lstMstNum;

	int nowx, nowy, nextx, nexty, direct;
	int weapeonXY[100];
	int weapeonPic[10] = { 10001,10002,10003,10004,10005 };
	
	int startmovingtime = 0;
	int startchangingmustime = 0;
	int ifTrymove = 0;
	int ifAttacked = 0, ifAttack = 0, movingProcess = 0, ifKill = 0, ifRealAttack = 0;
	int nowMus = 0, nextMus = 0, musChangingProcess = 0;
	int mussNum[3], atkMus[3];
	string FileName;

	int nowWp = 0; 
	vector<pair<int, int > > wpSize[5]; //坐标：假设面朝上，则为（上，右）

	int hp;

	battleField() {}
	void DbattleField() {
		aftLoadFile();
		for (int i = 0; i < 100; i++)
			if (mstList[i] != NULL)
				delete mstList[i];
	}
	void playSound() {
		/*int tt1 = GLBfps->get_ticks();
		GLBmuss->playChk(mussNum[0], -1, 0, 0);
		int tt2 = GLBfps->get_ticks();
		GLBmuss->playChk(mussNum[1], -1, tt2 - tt1 + 1, 0);
		GLBfps->get_ticks();
		GLBmuss->playChk(mussNum[2], -1, tt2 - tt1 + 1, 0);
		GLBmuss->changeLoud(mussNum[0], 200);
		fout1<< tt1 << ' ' << tt2 << endl;*/
		GLBmuss2->playChk(mussNum[0], 5, 0);
		GLBmuss2->playChk(mussNum[1], 6, 0);
		GLBmuss2->playChk(mussNum[2], 7, 0);
		GLBmuss2->changeLoud(5, 100);
	}

	void insertNeedDraw(int picNum, int alp, SDL_Rect* r1, SDL_Rect* r2) {
		if ((*r2).x > 1920 || (*r2).y > 1080 || (*r2).x + (*r2).w < 0 || (*r2).y + (*r2).h < 0)
			return;
		ndn++;
		if (r1 == NULL)
			needDraw[ndn].onPicR = { -1, -1, -1, -1 };
		else
			needDraw[ndn].onPicR = *r1;
		needDraw[ndn].onMapR = *r2;
		needDraw[ndn].alp = alp;
		needDraw[ndn].picNum = picNum;
		needDraw[ndn].realy = needDraw[ndn].onMapR.y + needDraw[ndn].onMapR.h;
	}
	void insertNeedDraw(int picNum, int alp, SDL_Rect* r1, SDL_Rect* r2, int rly) {
		if ((*r2).x > 1920 || (*r2).y > 1080 || (*r2).x + (*r2).w < 0 || (*r2).y + (*r2).h < 0)
			return;
		ndn++;
		if (r1 == NULL)
			needDraw[ndn].onPicR = { -1, -1, -1, -1 };
		else
			needDraw[ndn].onPicR = *r1;
		needDraw[ndn].onMapR = *r2;
		needDraw[ndn].alp = alp;
		needDraw[ndn].picNum = picNum;
		needDraw[ndn].realy = rly;
	}
	void insertNeedDraw(drawBlock &db, int type) {
		if (type == 1) {
			SDL_Rect r2 = { 1920 / 2 + db.onMapR.x - camarax, 1080 / 2 + db.onMapR.y - camaray, db.onMapR.w, db.onMapR.h };
			if (r2.x > 1920 || r2.y > 1080 || r2.x + r2.w < 0 || r2.y + r2.h < 0)
				return;
			ndn++;
			
			needDraw[ndn].onPicR = db.onPicR;
			needDraw[ndn].onMapR = r2;
			needDraw[ndn].alp = db.alp;
			needDraw[ndn].picNum = db.picNum;
			needDraw[ndn].realy = needDraw[ndn].onMapR.y + needDraw[ndn].onMapR.h;
		}
	}
	void draw() {
		ndn = 0;
		int gzpx = 130;
		SDL_Rect TMP_rect1 = { 0, 0, gzpx + 1, gzpx + 1 };
		SDL_Rect TMP_rect2 = { 720 - gzpx , 540 - gzpx, gzpx, gzpx };
		int dtonegz = (Rtime - startmovingtime) * gzpx / (20 * Rmovingtime);
		//sogr(1100, NULL, &TMP_rect1);

		camarax = (nowy - usey) * gzpx + gzpx / 2;
		camaray = (nowx - usex) * gzpx + gzpx / 2;
		if (movingProcess != 0) {
			camarax += dtonegz * (nexty - nowy);
			camaray += dtonegz * (nextx - nowx);
		}


		GLBpics->changeAlpha(1002, 255);
		sogr(1002, NULL, NULL);

		// 画地形，物品
		int ssn = 1;
		for (int i = 1; i <= fdn; i++)
			insertNeedDraw(firstDraw[i], 1);
		ssn = ndn;
		for (int i = 1; i <= adn; i++)
			insertNeedDraw(afterDraw[i], 1);

		//绘制怪物
		for (int i = 1; i <= mstNum; i++) {
			if (mstList[i]->hp > 0) {
				int talp;
				//if (mstList[i]->ifAttacked)
				//	talp = 150;
				//else
					talp = 255;
				TMP_rect1.x = 1920 / 2 + (mstList[i]->nowy - nowy) * gzpx - gzpx / 2 + mstList[i]->maprect.x;
				TMP_rect1.y = 1080 / 2 + (mstList[i]->nowx - nowx) * gzpx - gzpx / 2 + mstList[i]->maprect.y;
				TMP_rect1.w = mstList[i]->maprect.w;
				TMP_rect1.h = mstList[i]->maprect.h;
				if (movingProcess != 0) {
					TMP_rect1.x -= dtonegz * (nexty - nowy);
					TMP_rect1.y -= dtonegz * (nextx - nowx);
					TMP_rect1.x += dtonegz * (mstList[i]->nexty - mstList[i]->nowy);
					TMP_rect1.y += dtonegz * (mstList[i]->nextx - mstList[i]->nowx);
				}
				//sogr(mstList[i]->picNum[mstList[i]->direct], mstList[i]->vrect[mstList[i]->direct], &TMP_rect1);
				if(mstList[i]->moving == 1)
					insertNeedDraw(mstList[i]->picNum[mstList[i]->direct], talp, mstList[i]->vrect[mstList[i]->direct][movingProcess], &TMP_rect1);
				else
					insertNeedDraw(mstList[i]->picNum[mstList[i]->direct], talp, mstList[i]->vrect[mstList[i]->direct][0], &TMP_rect1);
			}
			else if (mstList[i]->dying == 1 && movingProcess != 0) {
				int talp = 255 * movingProcess / 20;
				TMP_rect1.x = 1920 / 2 + (mstList[i]->nowy - nowy) * gzpx - gzpx / 2 + mstList[i]->maprect.x;
				TMP_rect1.y = 1080 / 2 + (mstList[i]->nowx - nowx) * gzpx - gzpx / 2 + mstList[i]->maprect.y;
				TMP_rect1.w = mstList[i]->maprect.w;
				TMP_rect1.h = mstList[i]->maprect.h;
				if (movingProcess != 0) {
					TMP_rect1.x -= dtonegz * (nexty - nowy);
					TMP_rect1.y -= dtonegz * (nextx - nowx);
				}
				//sogr(mstList[i]->picNum[mstList[i]->direct], mstList[i]->vrect[mstList[i]->direct], &TMP_rect1);
				insertNeedDraw(mstList[i]->picNum[mstList[i]->direct], talp, mstList[i]->vrect[mstList[i]->direct][0], &TMP_rect1);
			}
		}

		//画fbk

		int talp = 255;
		TMP_rect1 = { 60, preXZT[direct] * 127, 60, 120 };
		TMP_rect2 = { 1920 / 2 - 60, 1080 / 2 - 180, 120, 240 };
		if (movingProcess != 0) {
			if(ifTrymove == 1)
				TMP_rect1.x = 60 * preCatMove_cat[20 - movingProcess];
			if (ifRealAttack == 1)
				TMP_rect1.x = 0;
			//if (nowx != nextx || nowy != nexty)
			//	TMP_rect2.y -= preCatMove_jmp[20 - movingProcess] * 2, TMP_rect1.x = 60;
			if (ifAttacked == 1)
				talp = 150;
		}
		//sogr(2004, &TMP_rect1, &TMP_rect2);
		insertNeedDraw(2004, talp, &TMP_rect1, &TMP_rect2, 1080 / 2 - 180 + 240);

		//真正地画
		sort(needDraw + ssn + 1, needDraw + ndn + 1, cmp02);
		for (int i = 1; i <= ndn; i++) {
			GLBpics->changeAlpha(needDraw[i].picNum, needDraw[i].alp);
			SDL_Rect *vtmpop = &needDraw[i].onPicR;
			if (needDraw[i].onPicR.x == -1 && needDraw[i].onPicR.y == -1 && needDraw[i].onPicR.w == -1 && needDraw[i].onPicR.h == -1)
				vtmpop = NULL;
			sogr(needDraw[i].picNum, vtmpop, &needDraw[i].onMapR);
		}
		
		/*
		//不可走的格
		GLBpics->changeAlpha(1002, 100);
		TMP_rect1 = { 0, 0, gzpx + 1, gzpx + 1 };
		for (int i = nowx - 5; i <= nowx + 5; i++)
			for (int j = nowy - 10; j <= nowy + 10; j++) {
				TMP_rect1.x = 1920 / 2 + (j - nowy) * gzpx - gzpx / 2;
				TMP_rect1.y = 1080 / 2 + (i - nowx) * gzpx - gzpx / 2;
				if (movingProcess != 0) {
					TMP_rect1.x -= dtonegz * (nexty - nowy);
					TMP_rect1.y -= dtonegz * (nextx - nowx);
				}
				
				if(landMap[i][j] == 1)
					sogr(1002, NULL, &TMP_rect1);
			}
		*/
		//拉刀光
		if (movingProcess != 0 && ifRealAttack == 1) {
			TMP_rect1 = { 0, 0, gzpx + 1, gzpx + 1 };
			int pcnm = weapeonPic[4 - (movingProcess - 1) / 4];
			for (int i = 1; i <= weapeonXY[0]; i++) {
				TMP_rect1.x = 1920 / 2 + (weapeonXY[i * 2] - nowy) * gzpx - gzpx / 2;
				TMP_rect1.y = 1080 / 2 + (weapeonXY[i * 2 - 1] - nowx) * gzpx - gzpx / 2;
				TMP_rect1.x -= dtonegz * (nexty - nowy);
				TMP_rect1.y -= dtonegz * (nextx - nowx);
				sogr(pcnm, NULL, &TMP_rect1);
			}
		}
	}

	void trueMove() {
		nowx = nextx;
		nowy = nexty;
		ifAttack = 0;
		ifAttacked = 0;
		ifRealAttack = 0;
		ifTrymove = 0;
		ifKill = 0;
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
		if (hp <= 0)
			gameType = -1;
		//if (lstMstNum <= 0)
		//	gameType = 1; 
	}

	void onAfterType() {
		if (movingProcess != 0) {
			movingProcess = 20 - (Rtime - startmovingtime) / Rmovingtime;
			if (movingProcess <= 0) {
				movingProcess = 0;
				trueMove();
			}
		}
		if (musChangingProcess != 0 && nowMus != nextMus) {
			musChangingProcess = 200 - (Rtime - startchangingmustime) / Rmovingtime;
			if (musChangingProcess <= 0) {
				musChangingProcess = 0;
				nowMus = nextMus;
				GLBmuss2->changeLoud(5 + nowMus, 200);
				for (int i = 0; i < 3; i++)
					if (i != nowMus)
						GLBmuss2->changeLoud(5 + i, 0);
				cout << "end" << endl;
			}
			else {
				int oth = 3 - nowMus - nextMus;
				GLBmuss2->changeLoud(5 + oth, 0);
				GLBmuss2->changeLoud(5 + nextMus, 100 - musChangingProcess / 2);
				GLBmuss2->changeLoud(5 + nowMus, musChangingProcess / 2);
				//cout << oth << " 0, " << nextMus << " " << 100 - musChangingProcess / 2 << ", " << nowMus << " " << musChangingProcess / 2 << endl;
			}
		}
	}
	void fbkAttack() {
		double datk = atkMus[nowMus];
		weapeonXY[0] = 0;
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
					ifRealAttack = 1;
					if (mstList[j]->hp <= 0)
						ifKill = 1;
					
					weapeonXY[0]++;
					weapeonXY[weapeonXY[0] * 2 - 1] = atkx;
					weapeonXY[weapeonXY[0] * 2] = atky;
				}
		}
	}
	void playAttackSound() {
		if (ifRealAttack)
			GLBmuss2->playChk(3, 1);
		if (ifKill)
			GLBmuss2->playChk(1, 2);
		if (ifAttacked)
			;
	}
	void tryMove() {
		nextx = nowx;
		nexty = nowy;
		TtryMove();
	}
	void TtryMove() {
		if (movingProcess != 0) {
			movingProcess = 0;
			trueMove();
		}

		if (ifAttack) {
			fbkAttack();
			playAttackSound();
		}
		movingProcess = 20;
		startmovingtime = Rtime;

		// 怪物尝试移动，撞墙回头，要动的moving=1，不要的=0
		for (int i = 1; i <= mstNum; i++)
			if (mstList[i]->hp > 0) {
				mstList[i]->tryMove();
				//if (landType[landMap[mstList[i]->nextx][mstList[i]->nexty]] == 1) {
				if(landMap[mstList[i]->nextx][mstList[i]->nexty] == 1){
					mstList[i]->nextx = mstList[i]->wantx = mstList[i]->nowx;
					mstList[i]->nexty = mstList[i]->wanty = mstList[i]->nowy;
					mstList[i]->turn();
				}
			}
		//fbk尝试移动，撞墙不动
		if (landMap[nextx][nexty] == 1 || ifRealAttack == 1) {
			nextx = nowx;
			nexty = nowy;
		}
		for(int i = 1; i <= mstNum; i++)
			if (mstList[i]->hp > 0 && nextx == mstList[i]->nowx && nexty == mstList[i]->nowy) {
				nextx = nowx;
				nexty = nowy;
				break;
			}

		mstList[0]->nowx = mstList[0]->nextx = nextx;
		mstList[0]->nowy = mstList[0]->nexty = nexty;
		mstList[0]->hp = 1;
		//加入fbk位置后判断冲突
		int tws = 1;
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
			if (mstList[i]->hp > 0 && mstList[i]->moving == 1 && ((mstList[i]->wantx == nextx && mstList[i]->wanty == nexty))) {
				atkSum += mstList[i]->attack;
				mstList[i]->ifAttack = 1;
			}
		if (atkSum != 0) {
			ifAttacked = 1;
			hp -= atkSum;
		}

		/*
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

			playAttackSound();
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
		playAttackSound();
		//被卡所以不移动
		nextx = nowx;
		nexty = nowy;
		*/
	}
	void trueTap(int tapped, int shiftSign) {
		//0123方向键 45切换颜色 67切换支援角色
		//GLBmuss2->playChk(3, 3);
		if (tapped >= 0 && tapped < 4) {
			ifTrymove = 1;
			nextx = nowx + PRE_DXY[tapped][0];
			nexty = nowy + PRE_DXY[tapped][1];
			ifAttack = 1;
			direct = tapped;
			TtryMove();
			fout1 << nextx << ' ' << nexty << endl;
			return;
		}
		if (tapped == 4 || tapped == 5) {
			if (musChangingProcess == 0) {
				musChangingProcess = 200;
				startchangingmustime = Rtime;
				nextMus = (nowMus + 6 - tapped) % 3;
			}
			tryMove();
		}
	}

	void preLoadFile(string file) {
		fdn = 0;
		adn = 0;
		FileName = file;
		ifstream fin(file);
		fin >> usen >> usem >> nowx >> nowy;
		usex = 150 - usen / 2;
		usey = 150 - usem / 2;
		nowx += usex;
		nowy += usey;
		for (int i = 0; i < 300; i++)
			for (int j = 0; j < 300; j++)
				landMap[i][j] = 1;
		for (int i = usex; i < usex + usen; i++)
			for (int j = usey; j < usey + usem; j++)
				fin >> landMap[i][j];
		int tmpk, tmp_num;
		string tmp_str;
		fin >> tmpk;
		for (int i = 1; i <= tmpk; i++) {
			fin >> tmp_str >> tmp_num;
			GLBpics->insertPic(tmp_str, tmp_num, blueColorKey);
		}
		fin >> fdn;
		for (int i = 1; i <= fdn; i++) {
			fin >> firstDraw[i].picNum >> firstDraw[i].alp
				>> firstDraw[i].onPicR.x >> firstDraw[i].onPicR.y >> firstDraw[i].onPicR.w >> firstDraw[i].onPicR.h
				>> firstDraw[i].onMapR.x >> firstDraw[i].onMapR.y >> firstDraw[i].onMapR.w >> firstDraw[i].onMapR.h;
		}
		fin >> adn;
		for (int i = 1; i <= adn; i++) {
			fin >> afterDraw[i].picNum >> afterDraw[i].alp
				>> afterDraw[i].onPicR.x >> afterDraw[i].onPicR.y >> afterDraw[i].onPicR.w >> afterDraw[i].onPicR.h
				>> afterDraw[i].onMapR.x >> afterDraw[i].onMapR.y >> afterDraw[i].onMapR.w >> afterDraw[i].onMapR.h;
		}
		fin.close();
	}
	void aftLoadFile() {
		ifstream fin(FileName);
		fin >> usen >> usem >> nowx >> nowy;
		usex = 150 - usen / 2;
		usey = 150 - usem / 2;
		nowx += usex;
		nowy += usey;
		for (int i = usex; i < usex + usen; i++)
			for (int j = usey; j < usey + usem; j++)
				fin >> landMap[i][j];
		int tmpk, tmp_num;
		string tmp_str;
		fin >> tmpk;
		for (int i = 1; i <= tmpk; i++) {
			fin >> tmp_str >> tmp_num;
			GLBpics->distoryPic(tmp_num);
		}
		fin.close();
	}
};



#endif