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

FC_Font* GLBfont1;

//FC_Font* font1 = NULL;

ofstream fout1;

realRect RR;

