#include "basicMainLoop.h"
// 选关

void mainLoop6::beforeLoop() {
	memset(kot, 0, sizeof kot);

	muss->haltAllChk();
	muss->playChk(1000);
	muss->playChk(201);
	moveW = 0;
	moveH = 0;

	gotoGame = 0;

	tmp1 = IMG_Load("items/test/6001.png");
	tmp2 = IMG_Load("items/test/6002.png");
	tmp3 = IMG_Load("items/test/6003.png");
	tmp4 = IMG_Load("items/test/6004.png");
	//锁定surface
	SDL_LockSurface(tmp1);
	SDL_LockSurface(tmp2);
	SDL_LockSurface(tmp3);
	SDL_LockSurface(tmp4);

	//surface像素地址
	Uint32* pixel = (Uint32*)tmp1->pixels;
	Uint32* pixe2 = (Uint32*)tmp2->pixels;
	Uint32* pixe3 = (Uint32*)tmp3->pixels;
	Uint32* pixe4 = (Uint32*)tmp4->pixels;

	ttext1 = SDL_CreateTexture(myRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, picW, picH);

	Uint32* pix;
	int pitch;
	SDL_LockTexture(ttext1, NULL, (void**)& pix, &pitch);

	format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

	//cout << pitch << endl;
	//一个像素4个字节,要除以4
	for (int i = 0; i < pitch / 4 * picH; i++) {
		r1.color = pixel[i];
		r1.ctrgba();

		r2.color = pixe4[i];
		r2.ctrgba();
		double x;
		r1.r = 1.0 * (255 - r2.a) / 255.0 * r1.r + 1.0 * r2.a / 255.0 * r2.r;
		r1.g = 1.0 * (255 - r2.a) / 255.0 * r1.g + 1.0 * r2.a / 255.0 * r2.g;
		r1.b = 1.0 * (255 - r2.a) / 255.0 * r1.b + 1.0 * r2.a / 255.0 * r2.b;
		r1.rgbatc();

		r2.color = pixe2[i];
		r2.ctrgba();
		r1.r = r1.r + r2.r - 255;
		r1.g = r1.g + r2.g - 255;
		r1.b = r1.b + r2.b - 255;
		r1.rgbatc();

		r2.color = pixe3[i];
		r2.ctrgba();
		r1.r = r1.r + r2.r;
		r1.g = r1.g + r2.g;
		r1.b = r1.b + r2.b;
		r1.rgbatc();

		Uint32 color = SDL_MapRGBA(format, r1.b, r1.g, r1.r, r1.a);

		pix[i] = color;
	}
	SDL_UnlockTexture(ttext1);

	chtb1.picH = picH;
	chtb1.picW = picW;
	chtb1.load("items/pictures/2004.png", 43, 48);
	SDL_LockSurface(chtb1.sfc);
}
void mainLoop6::onAfterLoop() {
	SDL_FreeSurface(tmp1);
	SDL_FreeSurface(tmp2);
	SDL_FreeSurface(tmp3);
	SDL_FreeSurface(tmp4);
	SDL_DestroyTexture(ttext1);
}

void mainLoop6::drawAll() {

	SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, 255);
	SDL_RenderClear(myRenderer);

	chtb1.check();

	//surface像素地址
	Uint32* pixel = (Uint32*)tmp1->pixels;
	Uint32* pixe2 = (Uint32*)tmp2->pixels;
	Uint32* pixe3 = (Uint32*)tmp3->pixels;
	Uint32* pixe4 = (Uint32*)tmp4->pixels;
	Uint32* pixe5 = (Uint32*)chtb1.sfc->pixels;

	Uint32* pix;
	int pitch;
	SDL_LockTexture(ttext1, NULL, (void**)& pix, &pitch);

	format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

	//cout << pitch << endl;
	//一个像素4个字节,要除以4
	for(int ix = 0; ix < chtb1.lstBox.h; ix++)
		for(int iy = 0; iy < chtb1.lstBox.w; iy++)
		{
			int i = (ix + chtb1.lstBox.y) * picW + (iy + chtb1.lstBox.x);
			r1.color = pixel[i];
			r1.ctrgba();

			r2.color = pixe4[i];
			r2.ctrgba();
			double x;
			r1.r = 1.0 * (255 - r2.a) / 255.0 * r1.r + 1.0 * r2.a / 255.0 * r2.r;
			r1.g = 1.0 * (255 - r2.a) / 255.0 * r1.g + 1.0 * r2.a / 255.0 * r2.g;
			r1.b = 1.0 * (255 - r2.a) / 255.0 * r1.b + 1.0 * r2.a / 255.0 * r2.b;
			r1.rgbatc();

			r2.color = pixe2[i];
			r2.ctrgba();
			r1.r = r1.r + r2.r - 255;
			r1.g = r1.g + r2.g - 255;
			r1.b = r1.b + r2.b - 255;
			r1.rgbatc();

			r2.color = pixe3[i];
			r2.ctrgba();
			r1.r = r1.r + r2.r;
			r1.g = r1.g + r2.g;
			r1.b = r1.b + r2.b;
			r1.rgbatc();

			Uint32 color = SDL_MapRGBA(format, r1.b, r1.g, r1.r, r1.a);

			pix[i] = color;
		}
	
	if (kot[0] || kot[1] || kot[2] || kot[3]) {
		moveW += RRtime - LRRtime;
	}
	else
		moveW = 0;
	chtb1.setSfcBox(moveWW[(moveW / (600 - kot[5] * 400)) % 4], moveH);
	//cout << kot[5] << endl;
	
	for (int ix = 0; ix < chtb1.nowBox.h; ix++)
		for (int iy = 0; iy < chtb1.nowBox.w; iy++)
		{
			int i = (ix + chtb1.nowBox.y) * picW + iy + chtb1.nowBox.x;
			int j = (ix + chtb1.sfcBox.y) * chtb1.sfc->w + iy + chtb1.sfcBox.x;
			r1.color = pixel[i];
			r1.ctrgba();

			r2.color = pixe5[j];
			if (r2.color != blueColorKey) {
				r2.ctrgba();
				double x;
				r1.r = 1.0 * (255 - r2.a) / 255.0 * r1.r + 1.0 * r2.a / 255.0 * r2.r;
				r1.g = 1.0 * (255 - r2.a) / 255.0 * r1.g + 1.0 * r2.a / 255.0 * r2.g;
				r1.b = 1.0 * (255 - r2.a) / 255.0 * r1.b + 1.0 * r2.a / 255.0 * r2.b;
				r1.rgbatc();
			}

			r2.color = pixe4[i];
			r2.ctrgba();
			double x;
			r1.r = 1.0 * (255 - r2.a) / 255.0 * r1.r + 1.0 * r2.a / 255.0 * r2.r;
			r1.g = 1.0 * (255 - r2.a) / 255.0 * r1.g + 1.0 * r2.a / 255.0 * r2.g;
			r1.b = 1.0 * (255 - r2.a) / 255.0 * r1.b + 1.0 * r2.a / 255.0 * r2.b;
			r1.rgbatc();

			r2.color = pixe2[i];
			r2.ctrgba();
			r1.r = r1.r + r2.r - 255;
			r1.g = r1.g + r2.g - 255;
			r1.b = r1.b + r2.b - 255;
			r1.rgbatc();

			r2.color = pixe3[i];
			r2.ctrgba();
			r1.r = r1.r + r2.r;
			r1.g = r1.g + r2.g;
			r1.b = r1.b + r2.b;
			r1.rgbatc();

			Uint32 color = SDL_MapRGBA(format, r1.b, r1.g, r1.r, r1.a);

			pix[i] = color;
		}
	
	SDL_UnlockTexture(ttext1);
	chtb1.lstBox = chtb1.nowBox;


	SDL_RenderCopy(myRenderer, ttext1, NULL, RR.ll(&ttrect2));
	//SDL_DestroyTexture(ttext1);

}

void mainLoop6::onType() {

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_LSHIFT)
			kot[5] = 1;
		if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
			chtb1.nowBox.y -= 1 + 2 * kot[5], moveH = 3, kot[0] = 1;
		if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
			chtb1.nowBox.x += 1 + 2 * kot[5], moveH = 2, kot[1] = 1;
		if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
			chtb1.nowBox.y += 1 + 2 * kot[5], moveH = 0, kot[2] = 1;
		if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
			chtb1.nowBox.x -= 1 + 2 * kot[5], moveH = 1, kot[3] = 1;
		if (event.key.keysym.sym == SDLK_ESCAPE)
			breakSign = 1;
	}
	if (event.type == SDL_KEYUP) {
		if (event.key.keysym.sym == SDLK_LSHIFT)
			kot[5] = 0;
		if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
			kot[0] = 0;
		if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
			kot[1] = 0;
		if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
			kot[2] = 0;
		if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
			kot[3] = 0;
	}

}

void mainLoop6::onAfterPframe() {

	if (gotoGame == 4) {
		exitGame();
	}
}