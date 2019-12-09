//֡������ 

#ifndef TIMER_H_  
#define TIMER_H_

#include "SDL2/SDL.h"


class Timer
{
    private:
    //��ʱ������ʱ��ʱ��
		int startTicks;
    
    //��ʱ����ͣʱ����ĵδ���
		int pausedTicks;
    
    //��ʱ��״̬
    	bool paused;
    	bool started;
    
    
    public:
    //��ʼ������
		Timer();
    
    //����ʱ�Ӷ���
    	void start();
    	void stop();
    	void pause();
    	void unpause();
    
    //��ȡ��ʱ��ʱ��
		int get_ticks();
    
    //����ʱ��״̬
    	bool is_started();
    	bool is_paused();    
};

#endif
