#ifndef GLBFUC1_H_
#define GLBFUC1_H_

#include <cstring>
#include <algorithm>
#include <iostream>
#include <windows.h>
#include <fstream>

#include "glbvar.h"
#include "SDL2/SDL.h"
using namespace std;

 void exitGame();
 int stringToPn(string pss);
 char* localeToUTF8(char* src);
 wchar_t* cstringToUnicode(char* aSrc);

#endif
