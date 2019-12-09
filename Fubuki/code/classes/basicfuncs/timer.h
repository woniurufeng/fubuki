//帧数处理 

#ifndef TIMER_H_  
#define TIMER_H_

#include "SDL2/SDL.h"


class Timer
{
    private:
    //计时器启动时的时间
		int startTicks;
    
    //计时器暂停时保存的滴答数
		int pausedTicks;
    
    //计时器状态
    	bool paused;
    	bool started;
    
    
    public:
    //初始化变量
		Timer();
    
    //各种时钟动作
    	void start();
    	void stop();
    	void pause();
    	void unpause();
    
    //获取计时器时间
		int get_ticks();
    
    //检查计时器状态
    	bool is_started();
    	bool is_paused();    
};

#endif
