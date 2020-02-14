#pragma once

#ifndef MONSTER_H_
#define MONSTER_H_
#include "commonfuc2.h"

class MONSTER{
public:
	int picNum[4];
	SDL_Rect* vrect[4][25], maprect;
	int realy;
	int nowx, nowy;
	int nextx, nexty;
	int wantx, wanty;
	int moving = 0;
	int fbkx, fbky;
	int direct; // 0123иосробвС
	double harmD[3]; // 012╨Лю╤бл
	int hp, attack, dying;
	int ifAttacked = 0, ifAttack = 0;
	MONSTER(int pn[], int nx, int ny, int dt, double hd[], int hpp, int atk) {
		for (int i = 0; i < 4; i++)
			picNum[i] = pn[i];
		wantx = nextx = nowx = nx;
		wanty = nexty = nowy = ny;
		direct = dt;
		fbkx = fbky = 0;
		for (int i = 0; i < 3; i++)
			harmD[i] = hd[i];
		hp = hpp;
		attack = atk;
		dying = 1;
	}
	MONSTER(int nx, int ny, int dt) {
		nextx = nowx = nx;
		nexty = nowy = ny;
		direct = dt;
		fbkx = fbky = 0;
		dying = 1;

	}
	MONSTER(){}
	virtual void tryMove() {

	}
	virtual void turn() {

	}
	void move() {
		nowx = nextx;
		nowy = nexty;
	}
};

class MONSTER_Yagoo : public MONSTER {
public:
	int step = 0;
	SDL_Rect rrect[4][3];
	MONSTER_Yagoo() : MONSTER() {};
	MONSTER_Yagoo(int pn[], int nx, int ny, int dt, double hd[], int hp, int atk) : MONSTER(pn, nx, ny, dt, hd, hp, atk) {};
	MONSTER_Yagoo(int nx, int ny, int dt) : MONSTER(nx, ny, dt) {
		hp = 100;
		attack = 1;
		picNum[0] = 2005;
		picNum[1] = 2005;
		picNum[2] = 2005;
		picNum[3] = 2005;
		harmD[0] = harmD[1] = harmD[2] = 1;
		maprect = { 5, -115, 120, 240 };
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 3; j++)
				rrect[i][j] = { j * 60,i * 127, 60, 120 };
		for (int i = 0; i < 4; i++) {
			vrect[i][0] = &rrect[preXZT[i]][1];
			for (int j = 1; j <= 20; j++)
				vrect[i][j] = &rrect[preXZT[i]][preCatMove_cat[20 - j]];
		}
	}
	void tryMove() {
		moving = 0;
		if (step & 1) {
			wantx = nextx = nowx + PRE_DXY[direct][0];
			wanty = nexty = nowy + PRE_DXY[direct][1];
			moving = 1;
		}
		step++;
	}
	virtual void turn() {
		direct += 2;
		direct %= 4;
	}
};


#endif