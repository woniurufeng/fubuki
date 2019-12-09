//֡������ 
#include "timer.h"

Timer::Timer()
{
    //��ʼ�����ֱ���
    this -> startTicks = 0;
    this -> pausedTicks = 0;
    this -> paused = false;
    this -> started = false;    
}

void Timer::start()
{
    //������ʱ��
    this -> started = true;
    
    //����ʱ����Ϊ����ͣ״̬
    this -> paused = false;
    
    //��ȡ��ǰʱ��ʱ��
    this -> startTicks = SDL_GetTicks();    
}

void Timer::stop()
{
    //ֹͣ��ʱ��
    this -> started = false;
    
    //����ʱ����Ϊ����ͣ״̬
    this -> paused = false;    
}

int Timer::get_ticks()
{
    //�����ʱ����������
    if( this -> started == true )
    {
        //�����ʱ����ͣ��
        if( this -> paused == true )
        {
            //���ؼ�ʱ����ͣʱ�ĵδ���
            return this -> pausedTicks;
        }
        else
        {
            //���ص�ǰʱ���ȥ����ʱ��Ĳ�ֵ
            return SDL_GetTicks() - this -> startTicks;
        }    
    }
    
    //�����ʱ��û��������
    return 0;    
}

void Timer::pause()
{
    //�����ʱ���������е�û����ͣ
    if( ( started == true ) && ( paused == false ) )
    {
        //��ͣ��ʱ��
        this -> paused = true;
    
        //������ͣʱ�ĵδ���
        this -> pausedTicks = SDL_GetTicks() - this -> startTicks;
    }
}

void Timer::unpause()
{
    //�����ʱ����ͣ��
    if( paused == true )
    {
        //ȡ����ͣ
        this -> paused = false;
    
        //���ÿ�ʼʱ��
        this -> startTicks = SDL_GetTicks() - this -> pausedTicks;
        
        //������ͣʱ��
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
