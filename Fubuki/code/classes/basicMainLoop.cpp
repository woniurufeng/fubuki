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
        
     //当有事件需要处理
        while( SDL_PollEvent( &event ) )
        {           
            onType();  
            //如果用户单击了窗口右上角的关闭按钮
            if( event.type == SDL_QUIT )
            {
                //退出程序
                exitGame();
                return ;
            }
        }
        onAfterType();
        
        
		
		//更新画面
		if (!cap) {
			//清空重绘 
			SDL_SetRenderDrawColor(myRenderer, 255, 255, 255, 255);
			SDL_RenderClear(myRenderer);
			drawAll();
			SDL_RenderPresent(myRenderer);
			cout << "FPS = " << 1000.0 / (thisTime - lstRefreshTime) << endl;
			lstRefreshTime = thisTime;
		}
		else if (LRframe != Rframe) {
			//清空重绘 
			SDL_SetRenderDrawColor(myRenderer, 255, 255, 255, 255);
			SDL_RenderClear(myRenderer);
			drawAll();
			SDL_RenderPresent(myRenderer);
			//cout << "FPS = " << 1000.0 / (thisTime - lstRefreshTime) << endl;
			lstRefreshTime = thisTime;
		}
		// 播放声音 
		//if(LRframe != Rframe)
    	playSound();
		
        onAfterDraw();
        	
		//帧计数器加1
        /*frame++;
        //如果我们需要限制帧率
        if( ( cap == true ) && ( fps->get_ticks() < 1000 / FRAMES_PER_SECOND ) )
        {
            //休眠一段时间，时长为当前帧的剩余时间。
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
