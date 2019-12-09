// 图片读入与调用

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
	private :                                 // 材质存储
    	SDL_Texture *texture[10005];
    	SDL_Texture *loadBMPasTexture( std::string FILE1 );          // 古老而又愚蠢地读取图片，有时间拿这个写低配版本
    	SDL_Texture *loadIMGasTexture( std::string FILE1 );          // 读取图片
    	SDL_Texture *loadIMGasTexture( std::string FILE1, Uint32 colorKey );
    	SDL_Renderer *myRenderer;                                    // 渲染器接口
    public :
        void insertPic( std::string FILE1, int TYPE1, int picNum );
		void insertPic( std::string FILE1, int picNum );
		void insertPic( std::string FILE1, int picNum, Uint32 colorKey );
		                                                             // 插入一张图片
        SDL_Texture *getPicText( int picNum );                       // 获取图片材质
        void distoryPic(int picNum);
        void distoryPic();
        void changeRenderer( SDL_Renderer *renderer );
        void changeAlpha( int picNum, Uint32 alpha ); 
		
        PICS( SDL_Renderer *renderer );                              // 把渲染器丢过来
        PICS();
        ~PICS();
};

#endif

