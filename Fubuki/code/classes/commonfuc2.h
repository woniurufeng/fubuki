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
void pressPianoKey( int chnl, int psn, MUSS * muss);
void pressPianoKey( int chnl, string pss, MUSS * muss);

void load_puMian(string pmFILE);
void load_musicScore(int msNUM); 

#endif 
