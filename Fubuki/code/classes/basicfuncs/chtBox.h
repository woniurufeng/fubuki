#pragma once
#ifndef CHT_BOX_H_
#define CHT_BOX_H_

#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "commonfuc1.h"
#include "glbvar.h"
#include "SDL2/SDL.h"
#include "SDL_FontCache.h"
#include "pics.h"

class chtBox {
public:
	int picW, picH, sfcW, sfcH;
	SDL_Rect nowBox, lstBox, stBox, sfcBox;
	SDL_Surface *sfc;
	chtBox() {
		sfc = NULL;
	}
	~chtBox() {
		if (sfc != NULL)
			SDL_FreeSurface(sfc);
	}
	void load(string file, int w, int h) {
		sfcW = w;
		sfcH = h;
		if (sfc != NULL)
			SDL_FreeSurface(sfc);
		sfc = IMG_Load(file.c_str());
		sfcBox = lstBox = nowBox = { 0, 0, sfcW, sfcH };
		stBox = { 0, 0, picW, picH };
	}
	void setSfcBox(int x, int y) {
		sfcBox = { x * sfcW, y * sfcH, sfcW, sfcH };
	}
	void check() {
		if (nowBox.x < 0)
			nowBox.x = 0;
		if (nowBox.y < 0)
			nowBox.y = 0;
		if (nowBox.y + nowBox.h > picH)
			nowBox.y = picH - nowBox.h;
		if (nowBox.x + nowBox.w > picW)
			nowBox.x = picW - nowBox.w;
	}
};

#endif // !1
