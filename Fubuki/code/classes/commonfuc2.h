#ifndef GLBFUC2_H_
#define GLBFUC2_H_

#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "basicfuncs.h"

using namespace std;

void clearSound(MUSS *muss);

// 画图方面
void drawHp1(int hp);
void drawMusCircle1(int nowMus, int nextMus, int ds);
void drawBeat1();

//存储方面
void saveDtTime();

#endif 
