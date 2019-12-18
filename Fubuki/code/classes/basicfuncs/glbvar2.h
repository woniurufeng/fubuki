#pragma once
#ifndef GLBVAR_2_H_
#define GLBVAR_2_H_

#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "SDL_FontCache.h"

#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"
#include "glbvar.h"

#include "pics.h"
#include "muss.h"
#include "muss_old.h"
#include "timer.h"

extern PICS* GLBpics;
extern MUSS* GLBmuss;
extern MUSS2* GLBmuss2;
extern SDL_Renderer* GLBrenderer;
extern Timer *GLBfps;


#endif