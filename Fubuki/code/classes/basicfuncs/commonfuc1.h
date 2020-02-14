#ifndef GLBFUC1_H_
#define GLBFUC1_H_

#include <cstring>
#include <algorithm>
#include <iostream>
#include <windows.h>
#include <fstream>

#include "glbvar.h"
#include "glbvar2.h"
#include "SDL2/SDL.h"
using namespace std;

 void exitGame();
 void clearEvent();
 char* U2G(const char* utf8);
 char* localeToUTF8(char* src);
 char* localeToUTF8(const char* src);
 wchar_t* cstringToUnicode(char* aSrc);

 void sogr_wnc(int picNum, SDL_Rect* r1, SDL_Rect* r2);
 void sogr(int picNum, SDL_Rect* r1, SDL_Rect* r2); //show on GLBrenderer

#endif
