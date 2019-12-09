#include "basicMainLoop.h"

void basicMainLoop::playSound(int xj, int st) {
	//cout << thisTime << ' ' << lstTime << ' ' << xj << endl;
	if (st < 0 || st >= 6)
		return;
	xj %= loopLenth;
	for (int i = 1; i <= 8; i++)
		if (playSoundSystem[pmType + 1][xj][i][st] != -1) {
			pressPianoKey(i, playSoundSystem[pmType + 1][xj][i][st], muss);
			//cout << tmp_xj << ' ' << tmp_st << ' ' << i << ' ' << playSoundSystem[pmType + 1][tmp_xj][i][tmp_st] << ' ' << endl;
		}
}

void basicMainLoop::playSound(){
	int jpNum = (int)(1.0 * RRtime * BPM / 60000.0);
	double onePz = 60000.0 / BPM;
	int lstPzTime = (int)(1.0 * onePz * jpNum);

	if (musicType == 0) {
		for (int i = 0; i < 6; i++) {
			if (RRtime - lstPzTime > (int)(onePz * preSoundSystemSDST[i]) && LRRtime - lstPzTime <= (int)(onePz * preSoundSystemSDST[i]))
				playSound(jpNum, i);
		}
	}

	if (musicType == 1) {
		if (jpNum % loopLenth == 0 && RRtime - lstPzTime > 0 && LRRtime - lstPzTime <= 0) {
			int xxx = 0;
			muss->playChk(playSoundSystem2[pmType + 1], 100, 0);
			noMusic = 0;
			//cout << "hi1" << endl;
			for (int i = 0; i < 5; i++)
				if (playSoundSystem2[i] != playSoundSystem2[pmType + 1])
					xxx = max(xxx, muss->haltAllChk(playSoundSystem2[i]));
		}
		if (noMusic && RRtime - lstPzTime > 0 && LRRtime - lstPzTime <= 0) {
			int ddd = jpNum % loopLenth;
			ddd = (int)(1.0 * onePz * ddd + 0.5);
			int xxx = 0;
			/*if(xxx == 0 || zheng(ddd - xxx) > 100)
				muss->playChk(playSoundSystem2[pmType + 1], 100, ddd);
			else
				muss->playChk(playSoundSystem2[pmType + 1], 100, xxx);*/
			muss->playChk(playSoundSystem2[pmType + 1], 100, ddd);
			noMusic = 0;
			for (int i = 0; i < 5; i++)
				if (playSoundSystem2[i] != playSoundSystem2[pmType + 1])
					xxx = max(xxx, muss->haltAllChk(playSoundSystem2[i]));
			//cout << "hi2" << endl;
		}
	}
	
}

void basicMainLoop::run(){
	beforeLoop();
	while( 1 )
    {
		thisTime = fps->get_ticks();
		/*if (Rtime < 0) {
			SDL_SetRenderDrawColor(myRenderer, 255, 255, 255, 255);
			SDL_RenderClear(myRenderer);


			SDL_RenderPresent(myRenderer);
			lstTime = thisTime;
			continue;
		}*/

        onBegin();
        
     //�����¼���Ҫ����
        while( SDL_PollEvent( &event ) )
        {           
            onType();  
            //����û������˴������ϽǵĹرհ�ť
            if( event.type == SDL_QUIT )
            {
                //�˳�����
                exitGame();
                return ;
            }
        }
        onAfterType();
        
        
		
		//���»���
		if (!cap) {
			//����ػ� 
			SDL_SetRenderDrawColor(myRenderer, 255, 255, 255, 255);
			SDL_RenderClear(myRenderer);
			drawAll();
			SDL_RenderPresent(myRenderer);
			cout << "FPS = " << 1000.0 / (thisTime - lstRefreshTime) << endl;
			lstRefreshTime = thisTime;
		}
		else if (LRframe != Rframe) {
			//����ػ� 
			SDL_SetRenderDrawColor(myRenderer, 255, 255, 255, 255);
			SDL_RenderClear(myRenderer);
			drawAll();
			SDL_RenderPresent(myRenderer);
			//cout << "FPS = " << 1000.0 / (thisTime - lstRefreshTime) << endl;
			lstRefreshTime = thisTime;
		}
		// �������� 
		//if(LRframe != Rframe)
    	playSound();
		
        onAfterDraw();
        	
		//֡��������1
        /*frame++;
        //���������Ҫ����֡��
        if( ( cap == true ) && ( fps->get_ticks() < 1000 / FRAMES_PER_SECOND ) )
        {
            //����һ��ʱ�䣬ʱ��Ϊ��ǰ֡��ʣ��ʱ�䡣
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps->get_ticks() );
        }
        
		fps->start();*/
		
		onAfterPframe();
		if(breakSign)
			break;
		if(exitGameSign)
			return ;

		lstTime = thisTime;
	}
	onAfterLoop();
}
