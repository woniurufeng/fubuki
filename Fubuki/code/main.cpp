﻿
#include "classes/allClasses.h"

using std::string;

int windowSet;
// windowSet   pic:620*877
SDL_Window *myWindow = NULL;  //窗口
SDL_Renderer *myRenderer = NULL;  //渲染器

extern basicMainLoop *nowLoop, *nextLoop;
basicMainLoop *nowLoop = NULL, *nextLoop = NULL;

bool preset_window()
{
	if(SDL_Init ( SDL_INIT_EVERYTHING ) < 0)
		return 0;
	// 建立窗口

	bool fsc = 0;

	ifstream fin("save/set.txt");
	fin >> windowsW >> windowsH >> fsc;
	fin.close();
	fin.open("save/dtTime.txt");
	fin >> dtTime;
	fin.close();

	//SDL_SetHintWithPriority(SDL_HINT_RENDER_DRIVER, "direct3d11", SDL_HINT_OVERRIDE);
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
	if(fsc)
		myWindow = SDL_CreateWindow("Fubuki test", 15, 40, windowsW, windowsH, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
	else
		myWindow = SDL_CreateWindow("Fubuki test", 15, 40, windowsW, windowsH, SDL_WINDOW_SHOWN);
	RR.init();
	windowSet = 1;
	myRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);//|SDL_RENDERER_PRESENTVSYNC);
	

	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

	if(myRenderer == NULL)
		return 0;
	return 1;
}

int main(int argc, char * argv[])
{
	if(!preset_window())
		return 0;
	fout1.open("items/test/debug.txt");
	//int result = Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 );

	int fontSize = RR.ww(20);
	fout1 << fontSize << endl;
	GLBfont1 = FC_CreateFont();
	FC_LoadFont(GLBfont1, myRenderer, "items/fonts/simsun.ttc", fontSize, FC_MakeColor(0, 0, 0, 255), TTF_STYLE_NORMAL);


	//载入图片
	PICS* pics = new PICS(myRenderer);
	pics->insertPic("items/pictures/0000.png", 0000);
	sogr(0000, NULL, NULL);
	SDL_RenderPresent(GLBrenderer);
	load_picData(pics);

	//载入BGM
	//MUSS *muss = new MUSS();
	MUSS2* muss2 = new MUSS2();
	GLBmuss2 = muss2;
	load_musData();

	//SDL_Event event;

	//帧率调节器
	Timer fps;
	GLBfps = &fps;

	//读取存档
	//DATA sdata;
	//load_data(&sdata);

	//初始化
	GLBpics = pics;
	//GLBmuss = muss;
	GLBrenderer = myRenderer;
	fps.start();
	init_all(&fps);

	muss2->playChk(1000);

	//进入游戏

	init_all(&fps);
	nowLoop = new mainLoop1();
	nowLoop->run();

	return 0;
}