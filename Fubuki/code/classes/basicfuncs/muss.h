#pragma once
#ifndef MUSS_H
#define MUSS_H

#include "glbvar.h"

#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <shellapi.h>
#include <digitalv.h>

#include "CThread.h"

#pragma comment(lib,"winmm.lib")


class playMusThread : public CThread
{
public:
	playMusThread(const std::string& strName)
		: m_strThreadName(strName)
	{
		playSign = 0;
		mciOpen = NULL;
		mciPlay = NULL;
		son = NULL;
		max_dLength = -1;
		DeviceID = -1;
	}

	~playMusThread()
	{
	}

public:
	int halt(CMutex* g_metux) {
		//CLock lock(g_metux);
		if (playSign) {
			MCI_STATUS_PARMS mciStatusParms;
			mciStatusParms.dwItem = MCI_STATUS_POSITION;
			mciSendCommand(DeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)& mciStatusParms);//关键,取得位置
			int m_dPosition = mciStatusParms.dwReturn;

			playSign = 0;
			mciSendCommand(DeviceID, MCI_STOP, NULL, NULL);
			//mciSendCommand(DeviceID, MCI_CLOSE, MCI_NOTIFY | MCI_WAIT, NULL);
			return m_dPosition;
		}
		return 0;
	}
	int halt() {
		if (playSign) {
			MCI_STATUS_PARMS mciStatusParms;
			mciStatusParms.dwItem = MCI_STATUS_POSITION;
			mciSendCommand(DeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)& mciStatusParms);//关键,取得位置
			int m_dPosition = mciStatusParms.dwReturn;

			playSign = 0;
			mciSendCommand(DeviceID, MCI_STOP, NULL, NULL);
			//mciSendCommand(DeviceID, MCI_CLOSE, MCI_NOTIFY | MCI_WAIT, NULL);
			return m_dPosition;
		}
		return 0;
	}
	int haltAll(CMutex* g_metux) {
		if (son != NULL)
			son->haltAll(g_metux);
		if (playSign) {
			MCI_STATUS_PARMS mciStatusParms;
			mciStatusParms.dwItem = MCI_STATUS_POSITION;
			mciSendCommand(DeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)& mciStatusParms);//关键,取得位置
			int m_dPosition = mciStatusParms.dwReturn;

			playSign = 0;
			mciSendCommand(DeviceID, MCI_STOP, NULL, NULL);
			//mciSendCommand(DeviceID, MCI_CLOSE, MCI_NOTIFY | MCI_WAIT, NULL);
			return m_dPosition;
		}
		return 0;
	}
	void changeLoud(int loud) {
		if (!check())
			return;
		MCI_DGV_SETAUDIO_PARMS mciSetAudioPara;
		mciSetAudioPara.dwItem = MCI_DGV_SETAUDIO_VOLUME;
		mciSetAudioPara.dwValue = loud;
		mciSendCommand(DeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)& mciSetAudioPara);
	}
	void play(std::string FILE1, CMutex *g_metux, int max_dLength_, int fromTime, int loud) {
		//CLock lock(g_metux);
		//std::cout << m_strThreadName << std::endl;

		if (check()) {
			char str[100];
			if (son == NULL) {
				sprintf_s(str, "tmp/%s_.mp3", m_strThreadName.c_str());
				fstream _file;
				_file.open(str, ios::in);
				if (!_file)
					CopyFile(FILE1.c_str(), str, true);//false代表覆盖，true不覆盖
				else
					_file.close();
				sprintf_s(str, "%s_", m_strThreadName.c_str());
				std::string s = str;
				son = new playMusThread(s);
			}
			sprintf_s(str, "tmp/%s_.mp3", m_strThreadName.c_str());
			std::string s = str;
			son->play(str, g_metux, max_dLength_, fromTime, loud);
				return;
		}
		else {
			playSign = 1;
			if (mciOpen == NULL) {
				mciOpen = new MCI_OPEN_PARMS;
				mciOpen->lpstrDeviceType = "mpegvideo";
				mciOpen->lpstrElementName = FILE1.c_str();

				mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)mciOpen);
				DeviceID = mciOpen->wDeviceID;
			}
		}
		changeLoud(loud);

		mciPlay = new MCI_PLAY_PARMS;
		mciPlay->dwFrom = fromTime;
		mciSendCommand(DeviceID, MCI_PLAY, MCI_FROM, (DWORD)mciPlay);

		this->max_dLength = max_dLength_;

		//std::cout << m_strThreadName <<"end" << std::endl;
	};
	bool check() {
		//CLock lock(g_metux);
		if (!playSign)
			return 0;

		MCI_STATUS_PARMS mciStatusParms;
		mciStatusParms.dwItem = MCI_STATUS_POSITION;
		mciSendCommand(DeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)& mciStatusParms);//关键,取得位置
		int m_dPosition = mciStatusParms.dwReturn;
		mciStatusParms.dwItem = MCI_STATUS_LENGTH;
		mciSendCommand(DeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)& mciStatusParms);//关键,取得长度
		int m_dLength = mciStatusParms.dwReturn;
		if (m_dLength == m_dPosition || (max_dLength != -1 && m_dPosition >= max_dLength))
			return 0;
		return 1;
	};
	virtual void Run(CMutex* g_metux) {
		while (playSign) {
			CLock lock(g_metux);
			if (!check())
				halt();
		}
	}
private:
	int max_dLength;
	bool playSign;
	UINT DeviceID;
	MCI_OPEN_PARMS* mciOpen;
	MCI_PLAY_PARMS* mciPlay;
	//MCIERROR mciError;
	//MCI_STATUS_PARMS mciStatusParms;
	//MCI_DGV_SETAUDIO_PARMS mciSetAudioPara;
private:
	std::string m_strThreadName;
	playMusThread* son;
};



class MUSS{
private:
	/*Mix_Music* mus[10005];
	Mix_Chunk* chk[10005];
	int channelHash[1000];
	int playingmus;*/
	std::string chk[10005];
	int chkHash[10005];

	playMusThread* pmt[10005];
	int channelHash[10005];

	CMutex g_metux;

public:
	/*void insertMus( std::string FILE1, int musNum );
	
	void playMus( int musNum, int times );
	void pauseMus();
	void resumeMus();
	void haltMus();
	
	void pauseChk( int channel );
	void resumeChk( int channel );
	void haltChk( int channel );*/
	void insertChk(std::string FILE1, int chkNum) {
		chk[chkNum] = FILE1;
		chkHash[chkNum] = 1;
	};
	void playChk(int chkNum, int max_dLength, int fromTime, int loud) {

		if (!chkHash[chkNum])
			return;
		if (!channelHash[chkNum] || pmt[chkNum] == NULL) {
			char str[100];
			sprintf_s(str, "%d", chkNum);
			std::string s = str;
			pmt[chkNum] = new playMusThread(s);
		}
		channelHash[chkNum] = 1;
		pmt[chkNum]->play(chk[chkNum], &g_metux, max_dLength, fromTime, loud);
	}
	void playChk(int chkNum) {
		playChk(chkNum, -1, 0, 200);
	}
	int haltChk(int channel) {
		int ret = 0;
		if (pmt[channel] != NULL) {
			ret = pmt[channel]->halt(&g_metux);
		}
		return ret;
	}
	int haltAllChk(int channel) {
		int ret = 0;
		if (pmt[channel] != NULL)
			ret = pmt[channel]->haltAll(&g_metux);
		return ret;
	}
	void haltAllChk() {
		for (int i = 0; i < 10000; i++)
			haltAllChk(i);
	}
	void changeLoud(int channel, int loud) {
		if (pmt[channel] != NULL)
			pmt[channel]->changeLoud(loud);
	}
	
	void init() {
		memset(chkHash, 0, sizeof chkHash);
		memset(channelHash, 0, sizeof channelHash);
		for (int i = 0; i < 10000; i++)
			pmt[i] = NULL;
	}
	MUSS() {
		init();
	}
};


#endif
