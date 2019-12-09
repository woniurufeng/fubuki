#ifndef TALK_BOX_H_
#define TALK_BOX_H_

#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "commonfuc1.h"
#include "glbvar.h"
#include "SDL2/SDL.h"
#include "SDL_FontCache.h"
#include "pics.h"

static char chtName[10005];
static int lenthChtName, rlenthChtName;
static string his[100];
static int lhis;

static char inStream[10005];
static int nowShowNum, allShowNum, nextShowNum, showingNum;
static int nowRealNum, nextRealNum;
static char tmpDraw[10005];

static char tmpx[10];

class talkBox {
private :
	PICS* pics;
	SDL_Renderer* myRenderer;
	int fontSize;
	int boxn, bln, bmn, brn;
	int maxW, maxH, showSpeed;
	SDL_Rect boxr1, blr1, bmr1, brr1;
	SDL_Rect boxr2, blr2, bmr2, brr2, sttPos;
	FC_Font *font = NULL;
	string fileName;

	ifstream fin;
	
public :
	talkBox() {
		pics = NULL;
		myRenderer = NULL;
		boxn = bln = bmn = brn = 1004;
		fontSize = RR.ww(20);
		boxr1 = { 0, 21, 900, 110 - 21 };
		boxr2 = { 30, 600, 900, 110 - 21 };
		blr1 = { 0, 0, 11, 21 };
		bmr1 = { 50, 0, 10, 21 };
		brr1 = { 900 - 11, 0, 11, 21 };
		blr2 = { 30, 600 - 21, 11, 21 };
		bmr2 = { 30+11, 600 - 21, 0, 21 };
		brr2 = { 30+11, 600 - 21, 11, 21 };
		sttPos = { 40, 600 + 4, 0, 0 };

		maxH = 4;
		maxW = (900 - 20) / 10;
		showSpeed = 50;

	}
	void init(SDL_Renderer* myRenderer, PICS* pics, string fileName) {
		this->myRenderer = myRenderer;
		this->pics = pics; 
		this->fileName = fileName;

		font = FC_CreateFont();
		FC_LoadFont(font, myRenderer, "items/fonts/simsun.ttc", fontSize, FC_MakeColor(0, 0, 0, 255), TTF_STYLE_NORMAL);
		
		fin.open(fileName);

		read();
	}
	void onLoop() {
		showingNum += thisTime / showSpeed - lstTime / showSpeed;
		if (showingNum > nextShowNum)
			showingNum = nextShowNum;
	}
	void onType() {
		if (showingNum != nextShowNum)
			showingNum = nextShowNum;
		else {
			nowShowNum += nextShowNum;
			nowRealNum += nextRealNum;
			showingNum = 0;
			getNSN();
		}
	}
	void onDraw() {
		int lo = showingNum;
		int nowWt = 0, srn = 0, ltd = 0;
		while (lo--) {
			int xx = U8_charsize(inStream + nowRealNum + srn);
			if (xx == 1 && inStream[nowRealNum + srn] == '\n') {
				tmpDraw[ltd++] = '\n';
				srn++;
				nowWt = 0;
				continue;
			}
			nowWt += xx == 1 ? 1 : 2;
			if (nowWt > maxW) {
				tmpDraw[ltd++] = '\n';
				nowWt = xx == 1 ? 1 : 2;
			}
			while (xx--) {
				tmpDraw[ltd++] = inStream[nowRealNum + srn];
				srn++;
			}
		}
		tmpDraw[ltd] = '\0';
		//cout << tmpDraw << endl << endl;
		bmr2.w = fontSize / 2 * rlenthChtName + 2;
		brr2.x = 30 + 11 + bmr2.w;
		SDL_RenderCopy(myRenderer, pics->getPicText(bln), &blr1, RR.ll(&blr2));
		SDL_RenderCopy(myRenderer, pics->getPicText(bmn), &bmr1, RR.ll(&bmr2));
		SDL_RenderCopy(myRenderer, pics->getPicText(brn), &brr1, RR.ll(&brr2));
		SDL_RenderCopy(myRenderer, pics->getPicText(boxn), &boxr1, RR.ll(&boxr2));
		FC_Draw(font, myRenderer, RR.ww(bmr2.x+1), RR.hh(bmr2.y+1), "%s\n", chtName);
		FC_Draw(font, myRenderer, RR.ww(sttPos.x), RR.hh(sttPos.y), "%s\n", tmpDraw);
	}

private :
	void getNSN() {
		if (nowShowNum == allShowNum) {
			//cout << "-1" << endl;
			read();
			return;
		}
		int nowHt = 0, nowWt = 0;
		nextShowNum = 0;
		nextRealNum = 0;
		for (int i = nowShowNum; i < allShowNum; i++) {
			int xx = U8_charsize(inStream + nowRealNum + nextRealNum);
			if (xx == 1 && inStream[nowRealNum + nextRealNum] == '\n') {
				nowHt++;
				nowWt = 0;
				if (nowHt == maxH) {
					//cout << nextShowNum << ' ' << nextRealNum << endl;
					return;
				}
			}
			else {
				nowWt += xx == 1 ? 1 : 2;
				if (nowWt > maxW) {
					nowHt++;
					nowWt = xx == 1 ? 1 : 2;
					if (nowHt == maxH) {
						//cout<< nextShowNum <<' ' << nextRealNum << endl;
						return;
					}
				}
			}
			nextRealNum += xx;
			nextShowNum++;
		}
		//cout << nextShowNum << ' ' << nextRealNum << endl;
	}
	void loadNext() {
		cout << "hi" << endl;
		fin.close();
		fin.open(fileName);
		//fin.getline(tmpx, 2, ' ');
	}
	void read() {
		if (fin.getline(chtName, 10000, '\n')) {
			lenthChtName = U8_strlen(chtName);
			rlenthChtName = 0;
			int j = 0;
			for (int i = 0; i < lenthChtName; i++) {
				int xx = U8_charsize(chtName + j);
				j += xx;
				rlenthChtName += xx == 1 ? 1 : 2;
			}
			fin.getline(inStream, 10000, '`');
			fin.getline(tmpx, 1, '\n');

			nowRealNum = 0;
			nowShowNum = 0;
			showingNum = 0;
			allShowNum = U8_strlen(inStream);
			//cout << allShowNum << endl;
			getNSN();

			cout << lenthChtName << ' ' << rlenthChtName << ' ' << strlen(chtName) << endl;
			fout1 << chtName << endl << inStream << endl;
		}
		else {
			loadNext();
			read();
		}
		//cout << chtName << endl << inStream << endl;
	}
	void close() {
		fin.close();
	}
};



#endif
