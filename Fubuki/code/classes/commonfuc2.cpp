
#include "commonfuc2.h"

// 音频处理部分 
// 清空音频 
void clearSound( MUSS * muss ){
	for(int i = 1; i <= 8; i++)
		muss->haltChk( i );
}
// 播放钢琴键 
void pressPianoKey( int chnl, int psn, MUSS * muss){
	if(psn >= 0){
		muss->playChk(psn, pre_max_dLength, 0);
		//muss->playChk( psn , chnl );
	}
	if(psn == -2){
		muss->haltChk( chnl );
	}
}
void pressPianoKey( int chnl, string pss, MUSS * muss){
	int psn = stringToPn(pss);
	pressPianoKey( chnl, psn, muss );
}

// 读取谱面 
void load_puMian(string pmFILE){
	ifstream fin(pmFILE);
	int loadType, x, y, z;
	char xx;
	fin >> loadType ;
	for(int i = 0; i < 5; i++)
		for(int j = 0; j < loopLenth; j++)
			for(int k = 0; k < 6; k++)
				pmSystem[i][j][k] = -1;
	while(fin >> x){
		if(loadType == 0){
			fin >> y >> z >> xx;
			pmSystem[x][y][z] = directName[xx];
			//cout << x << ' ' << y << ' ' << z << ' ' << directName[xx] << endl;
		}
	}
	fin.close();
}
// 读取乐谱 
void load_musicScore(int msNUM){
	ifstream fin(musicScoreList[msNUM]);
	string tmp_str;
	int loadType, x, y, z, xx, yy;
	fin >> tmp_str >> BPM >> loopLenth >> musicType >> loadType;
	
	load_puMian( tmp_str ); 
	if(loadType == 0){
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < loopLenth; j++)
				for (int k = 1; k <= 8; k++)
					for (int ii = 0; ii < 6; ii++)
						playSoundSystem[i][j][k][ii] = -1;

		while(fin >> x){
			fin >> y >> z >> xx >> tmp_str;
			playSoundSystem[x][y][z][xx] = stringToPn(tmp_str);
			if(playSoundSystem[x][y][z][xx] == -3){
				fin >> yy;
				playSoundSystem[x][y][z][xx] = yy;
			}
		}
	}
	if (loadType == 1) {
		for (int i = 0; i < 5; i++)
			playSoundSystem2[i] = -1;
		while (fin >> x) {
			fin >> y;
			playSoundSystem2[y] = x;
		}
	}
	fin.close();
}
// 加载声音系统 结束
