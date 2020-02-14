// 图片读入与调用
#include "pics.h"
//1080 x 1527

// private
static std::unordered_map<int, int > picsNumMap;
SDL_Texture* texture[10005];
static int nowPicNum; static bool vis[10005];


static void getNowPicNum(int picNumm) {
	for (int i = 0; i <= 10000; i++) {
		if (!vis[i]) {
			vis[i] = 1;
			nowPicNum = i;
			picsNumMap[picNumm] = nowPicNum;
			return;
		}
	}
}

SDL_Texture *PICS::loadBMPasTexture( std::string FILE1 )
{
	SDL_Surface *tmp1 = SDL_LoadBMP( FILE1.data() );
	SDL_Texture *tmp2 = SDL_CreateTextureFromSurface( this -> myRenderer, tmp1 );
	SDL_FreeSurface( tmp1 );
	return tmp2;
}

SDL_Texture *PICS::loadIMGasTexture( std::string FILE1 )
{
	SDL_Texture *tmp1 = IMG_LoadTexture( this -> myRenderer, FILE1.data() );
	return tmp1;
}

SDL_Texture *PICS::loadIMGasTexture( std::string FILE1, Uint32 colorKey )
{
	SDL_Surface *tmp1 = IMG_Load(FILE1.data());
	SDL_SetColorKey(tmp1, 1, colorKey);
	SDL_Texture *tmp2 = SDL_CreateTextureFromSurface( this -> myRenderer, tmp1 );
	SDL_FreeSurface(tmp1);
	return tmp2;
}

// public
void PICS::insertPic( std::string FILE1, int TYPE1, int picNumm )
{
	getNowPicNum(picNumm);

	if( TYPE1 == 0 )
	    texture[nowPicNum] = loadBMPasTexture( FILE1 );
	if( TYPE1 == 1 )
		texture[nowPicNum] = loadIMGasTexture( FILE1 );
}
void PICS::insertPic( std::string FILE1, int picNumm )
{
	getNowPicNum(picNumm);
	texture[nowPicNum] = loadIMGasTexture( FILE1 );
}
void PICS::insertPic( std::string FILE1, int picNumm, Uint32 colorKey )
{
	getNowPicNum(picNumm);
	texture[nowPicNum] = loadIMGasTexture( FILE1, colorKey );
}
SDL_Texture *PICS::getPicText( int picNumm )
{
	int picNum = picsNumMap[picNumm];
	return texture[picNum];
}

void PICS::changeRenderer( SDL_Renderer *renderer )
{
	this -> myRenderer = renderer;
}
void PICS::changeAlpha( int picNumm, Uint32 alpha )
{
	int picNum = picsNumMap[picNumm];
	SDL_SetTextureAlphaMod( texture[picNum], alpha );
}
void PICS::distoryPic(int picNumm)
{
	int picNum = picsNumMap[picNumm];
	if(texture[picNum] != NULL && vis[picNum])
	{
		vis[picNum] = 0;
		SDL_DestroyTexture(texture[picNum]);
		texture[picNum] = NULL;
	}
}
void PICS::distoryPic()
{
	this -> myRenderer = NULL;
	for(int i = 0; i <= 10000; i++)
	{
		if(texture[i] != NULL && vis[i])
		{
			SDL_DestroyTexture(texture[i]);
			texture[i] = NULL;
			vis[i] = 0;
		}
	}
}

PICS::PICS( SDL_Renderer *renderer )
{
	picsNumMap.clear();
	nowPicNum = 0;
	this -> myRenderer = renderer;
	for(int i = 0; i <= 10000; i++)
	    texture[i] = NULL;
}
PICS::PICS()
{
	picsNumMap.clear();
	nowPicNum = 0;
	this -> myRenderer = NULL;
	for(int i = 0; i <= 10000; i++)
	    texture[i] = NULL;
}
PICS::~PICS()
{
}


