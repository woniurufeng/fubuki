//帧数处理 
#include "timer.h"

Timer::Timer()
{
    //初始化各种变量
    this -> startTicks = 0;
    this -> pausedTicks = 0;
    this -> paused = false;
    this -> started = false;    
}

void Timer::start()
{
    //启动计时器
    this -> started = true;
    
    //将计时器设为非暂停状态
    this -> paused = false;
    
    //获取当前时钟时间
    this -> startTicks = SDL_GetTicks();    
}

void Timer::stop()
{
    //停止计时器
    this -> started = false;
    
    //将计时器设为非暂停状态
    this -> paused = false;    
}

int Timer::get_ticks()
{
    //如果计时器正在运行
    if( this -> started == true )
    {
        //如果计时器暂停中
        if( this -> paused == true )
        {
            //返回计时器暂停时的滴答数
            return this -> pausedTicks;
        }
        else
        {
            //返回当前时间减去启动时间的差值
            return SDL_GetTicks() - this -> startTicks;
        }    
    }
    
    //如果计时器没有在运行
    return 0;    
}

void Timer::pause()
{
    //如果计时器正在运行但没有暂停
    if( ( started == true ) && ( paused == false ) )
    {
        //暂停计时器
        this -> paused = true;
    
        //计算暂停时的滴答数
        this -> pausedTicks = SDL_GetTicks() - this -> startTicks;
    }
}

void Timer::unpause()
{
    //如果计时器暂停中
    if( paused == true )
    {
        //取消暂停
        this -> paused = false;
    
        //重置开始时间
        this -> startTicks = SDL_GetTicks() - this -> pausedTicks;
        
        //重置暂停时间
        this -> pausedTicks = 0;
    }
}

bool Timer::is_started()
{
    return this -> started;    
}
 
bool Timer::is_paused()
{
    return this -> paused;    
}
