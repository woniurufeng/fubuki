#include "muss.h"

//private


//puclic
/*
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

void MUSS::init() {
	memset(chkHash, 0, sizeof chkHash);
	memset(DeviceID, 0, sizeof DeviceID);
	memset(channelHash, 0, sizeof channelHash);
}

void MUSS::insertChk(std::string FILE1, int chkNum) {
	chk[chkNum] = FILE1;
	chkHash[chkNum] = 1;
}

void MUSS::haltChk(int channel) {
	if (channelHash[channel]) {
		mciSendCommand(DeviceID[channel], MCI_STOP, NULL, NULL);
		mciSendCommand(DeviceID[channel], MCI_CLOSE, MCI_NOTIFY | MCI_WAIT, NULL);
		delete mciOpen[channel];
		mciOpen[channel] = NULL;
		delete mciPlay[channel];
		mciPlay[channel] = NULL;
		channelHash[channel] = 0;
	}
}

void MUSS::playChk(int chkNum, int channel) {
	if (channelHash[channel]) {
		haltChk(channel);
	}
	channelHash[channel] = 1;
	mciOpen[channel] = new MCI_OPEN_PARMS;
	mciOpen[channel]->lpstrDeviceType = "mpegvideo";
	mciOpen[channel]->lpstrElementName = chk[chkNum].c_str();

	mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD) mciOpen[channel]);
	DeviceID[channel] = mciOpen[channel]->wDeviceID;

	mciSetAudioPara.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mciSetAudioPara.dwValue = 200;
	mciSendCommand(DeviceID[channel], MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)& mciSetAudioPara);

	mciPlay[channel] = new MCI_PLAY_PARMS;
	mciPlay[channel]->dwFrom = 0;
	mciSendCommand(DeviceID[channel], MCI_PLAY, MCI_FROM, (DWORD) mciPlay[channel]);
}

void MUSS::playChk(int chkNum) {
	for (int i = 0; i < 100; i++) {
		if (channelHash[i] == 0) {
			playChk(chkNum, i);
			return ;
		}
		mciStatusParms.dwItem = MCI_STATUS_POSITION;
		mciSendCommand(DeviceID[i], MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)& mciStatusParms);//关键,取得位置
		int m_dPosition = mciStatusParms.dwReturn;
		mciStatusParms.dwItem = MCI_STATUS_LENGTH;
		mciSendCommand(DeviceID[i], MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)& mciStatusParms);//关键,取得长度
		int m_dLength = mciStatusParms.dwReturn;
		if (m_dLength == m_dPosition) {
			playChk(chkNum, i);
			return ;
		}
	}
}

MUSS::MUSS()
{
	init();
}
MUSS::~MUSS()
{
}


*/