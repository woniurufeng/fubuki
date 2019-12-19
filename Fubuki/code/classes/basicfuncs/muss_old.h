
#ifndef MUSS_OLD_H
#define MUSS_OLD_H

#include "SDL2/SDL_mixer.h"

#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>

class MUSS2{
private:
	Mix_Music* mus[10005];
	Mix_Chunk* chk[10005];
	int channelHash[1000];
	int playingmus;
public:
	void insertMus( std::string FILE1, int musNum );
	void insertChk( std::string FILE1, int chkNum );
	
	void playMus( int musNum, int times );
	void pauseMus();
	void resumeMus();
	void haltMus();
	
	void playChk( int chkNum );
	void playChk( int chkNum, int channel );
	void pauseChk( int channel );
	void resumeChk( int channel );
	void haltChk( int channel );
	void haltChk();
	
	int init();
	MUSS2();
	~MUSS2();
};


#endif
