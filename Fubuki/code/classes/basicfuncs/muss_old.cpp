#include "muss_old.h"

//private


//puclic
void MUSS2::insertMus( std::string FILE1, int musNum ){
	mus[musNum] = Mix_LoadMUS( FILE1.data() );
}
void MUSS2::insertChk( std::string FILE1, int chkNum ){
	chk[chkNum] = Mix_LoadWAV( FILE1.data() );
}
int MUSS2::init(){
	int ret = Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 );
	playingmus = 0;
	memset(channelHash, 0, sizeof channelHash);
	return ret;
}

void MUSS2::playChk( int chkNum ){
	int channel = Mix_PlayChannel( -1, chk[chkNum], 0 );
	channelHash[channel] = chkNum;
}
void MUSS2::playChk( int chkNum, int channel ){
	int channell = Mix_PlayChannel( channel, chk[chkNum], 0 );
	channelHash[channell] = chkNum;
}
void MUSS2::pauseChk( int channel ){
	Mix_Pause( channel );
}
void MUSS2::resumeChk( int channel ){
	Mix_Resume( channel );
}
void MUSS2::haltChk( int channel ){
	Mix_HaltChannel( channel );
}

void MUSS2::playMus( int musNum, int times ){
	Mix_PlayMusic( mus[musNum], times );
}
void MUSS2::pauseMus(){
	Mix_PauseMusic();
}
void MUSS2::resumeMus(){
	Mix_ResumeMusic();
}
void MUSS2::haltMus(){
	Mix_HaltMusic();
}

MUSS2::MUSS2()
{
}
MUSS2::~MUSS2()
{
}


