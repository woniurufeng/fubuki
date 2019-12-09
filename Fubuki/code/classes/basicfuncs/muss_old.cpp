#include "muss.h"

//private


//puclic
void MUSS::insertMus( std::string FILE1, int musNum ){
	mus[musNum] = Mix_LoadMUS( FILE1.data() );
}
void MUSS::insertChk( std::string FILE1, int chkNum ){
	chk[chkNum] = Mix_LoadWAV( FILE1.data() );
}
int MUSS::init(){
	int ret = Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 );
	playingmus = 0;
	memset(channelHash, 0, sizeof channelHash);
	return ret;
}

void MUSS::playChk( int chkNum ){
	int channel = Mix_PlayChannel( -1, chk[chkNum], 0 );
	channelHash[channel] = chkNum;
}
void MUSS::playChk( int chkNum, int channel ){
	int channell = Mix_PlayChannel( channel, chk[chkNum], 0 );
	channelHash[channell] = chkNum;
}
void MUSS::pauseChk( int channel ){
	Mix_Pause( channel );
}
void MUSS::resumeChk( int channel ){
	Mix_Resume( channel );
}
void MUSS::haltChk( int channel ){
	Mix_HaltChannel( channel );
}

void MUSS::playMus( int musNum, int times ){
	Mix_PlayMusic( mus[musNum], times );
}
void MUSS::pauseMus(){
	Mix_PauseMusic();
}
void MUSS::resumeMus(){
	Mix_ResumeMusic();
}
void MUSS::haltMus(){
	Mix_HaltMusic();
}

MUSS::MUSS()
{
}
MUSS::~MUSS()
{
}


