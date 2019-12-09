// ͼƬ���������

#ifndef PICS_H_  
#define PICS_H_

#include "SDL2/SDL_image.h"
#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <unordered_map>

//1080 x 1527

		 
class PICS
{
	private :                                 // ���ʴ洢
    	SDL_Texture *texture[10005];
    	SDL_Texture *loadBMPasTexture( std::string FILE1 );          // ���϶����޴��ض�ȡͼƬ����ʱ�������д����汾
    	SDL_Texture *loadIMGasTexture( std::string FILE1 );          // ��ȡͼƬ
    	SDL_Texture *loadIMGasTexture( std::string FILE1, Uint32 colorKey );
    	SDL_Renderer *myRenderer;                                    // ��Ⱦ���ӿ�
    public :
        void insertPic( std::string FILE1, int TYPE1, int picNum );
		void insertPic( std::string FILE1, int picNum );
		void insertPic( std::string FILE1, int picNum, Uint32 colorKey );
		                                                             // ����һ��ͼƬ
        SDL_Texture *getPicText( int picNum );                       // ��ȡͼƬ����
        void distoryPic(int picNum);
        void distoryPic();
        void changeRenderer( SDL_Renderer *renderer );
        void changeAlpha( int picNum, Uint32 alpha ); 
		
        PICS( SDL_Renderer *renderer );                              // ����Ⱦ��������
        PICS();
        ~PICS();
};

#endif

