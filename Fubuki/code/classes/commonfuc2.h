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

// ��ͼ����
void drawHp1(int hp);
void drawMusCircle1(int nowMus, int nextMus, int ds);
void drawBeat1();

//�洢����
void saveDtTime();

#endif 
