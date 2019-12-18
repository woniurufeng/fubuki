#include "basicMainLoop.h"

void basicMainLoop::playSound(int xj, int st) {
}

void basicMainLoop::playSound(){
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
