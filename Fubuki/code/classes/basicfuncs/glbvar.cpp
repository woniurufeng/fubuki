#include "glbvar.h"

// �������� 

// ��Ҫ���� 
int exitGameSign = 0;
double windowsW = 1280, windowsH = 720;
int FRAMES_PER_SECOND = 60; // ֡�� 
//int reFPS = 8; // ���β��ֻ������֡���������� 
//int jpFPS = 40; //���β��������ٶȣ�֡��/���ӣ� 

int pre_max_dLength = 1000; //��������ź�����

//���ٵ�ǰ֡��֡������
//int frame = 0; // ��ǰ֡�� 
//int gsframe = 0; // ������Ϸʱ��֡�����
bool cap = false;  //�Ƿ�����֡��

Uint32 blueColorKey;

double BPM = 100; //����bpm
int reTime = 100; //���ʱ��
int gsTime; // ������Ϸʱ��ʱ��
int dtTime;
int lstRefreshTime = -1000;
int lstTime = -1000; // ��һ��ѭ��ʱ��
int thisTime; //��ν���ѭ��ʱ��

int loopLength = 100;

int PRE_DXY[4][2] = { -1, 0, 0, 1, 1, 0, 0, -1 };  //0123 ��������
int preCatMove_jmp[20] = { 5, 10, 15, 21, 26, 30, 35, 39, 43, 48, 52, 56, 59, 61, 62, 60, 51, 40, 28, 15 }; // ��Ծ������20֡����Ծ�߶�
int preXZT[4] = { 3, 2, 0, 1 }; // ����ͼ��Ӧ���������� 
int preCatMove_cat[20] = { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2 }; // ��·������20֡������ͼѡ�� 

FC_Font* GLBfont1;
SDL_Color GLBttfColor = { 0, 0, 0 };

//FC_Font* font1 = NULL;

SDL_BlendMode GLBblendmode01 = SDL_ComposeCustomBlendMode(SDL_BLENDFACTOR_SRC_ALPHA, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_SUBTRACT,
	SDL_BLENDFACTOR_ZERO, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_SUBTRACT);
SDL_BlendMode GLBblendmode02 = SDL_ComposeCustomBlendMode(SDL_BLENDFACTOR_SRC_ALPHA, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_MAXIMUM,
	SDL_BLENDFACTOR_ZERO, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_ADD);
SDL_BlendMode GLBblendmode03 = SDL_ComposeCustomBlendMode(SDL_BLENDFACTOR_SRC_ALPHA, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_ADD,
	SDL_BLENDFACTOR_ZERO, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_ADD);

ofstream fout1;

realRect RR;

