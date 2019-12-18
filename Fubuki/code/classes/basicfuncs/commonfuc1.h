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
 char* localeToUTF8(char* src);
 wchar_t* cstringToUnicode(char* aSrc);
 void sogr(int picNum, SDL_Rect* r1, SDL_Rect* r2); //show on GLBrenderer

#endif
