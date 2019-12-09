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


double preSoundSystemSDST[6] = {0, 0.25, 0.5, 0.75, 1.0/3.0, 2.0/3.0}; // ��Ӧ��ʼʱ�� 
int playSoundSystem[5][500][9][6]; // ���ֱ���  �˸�����  ������  0,1/4,1/2,3/4,1/3,2/3��Ϊ6�ֿ�ʼʱ��
int playSoundSystem2[5];
int pmSystem[5][500][6]; // ����Ҫ���� 
int loopLenth = 16; // ����loopС���� 

string musicScoreList[1000]; // �洢������Ϣ���ļ���
int needPressPmList[1000][2], lNPPL, nNPPL; // ��Ҫ���µİ�������  lNPPL : ��Ҫ���İ�������  nNPPL ����ǰҪ���İ�ť��� 
int siPressPmList[1000];  // �����Ƿ�ɹ����µı�� 

int dxMap[500][500], mstMap[500][500]; // ���ε�ͼ�͹����ͼ 
int mstMapNext[500][500]; // ��һ���ĵ�ͼ 
int tmv[4][2] = {-1, 0, 0, 1, 1, 0, 0, -1}; // ������������һ����xy�������� 
int nowx, nowy; // FBK xy����
int gameType, playerHp, catMove, pressFrame, pressTime;
// ��ǰ���� �Ƿ��ж��ఴ�°��� ��һ����Ч���� ��Ϸ���ͣ�0 ��ͼ 1 ���棩 FBKѪ�� FBK��ͼ����֡��� ��һ�ΰ�������֡�� ��һ�ΰ�������ʱ��
int preCatMove_cat[20] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2}; // ��·������20֡������ͼѡ�� 
int preCatMove_jmp[20] = {5, 10, 15, 21, 26, 30, 35, 39, 43, 48, 52, 56, 59, 61, 62, 60, 51, 40, 28, 15}; // ��Ծ������20֡����Ծ�߶� 
int preCatMove = 20; // ����/��Ծ������Ҫ20֡ 
int moveDirect, moveStep; // ��һ�������߷���Ͳ��� 
int mstMovDXYe[100][2]; // ����Ҫ�ߵ�xy���� 
int preXZT[4] = {3, 2, 0, 1}; // ����ͼ��Ӧ���������� 

int musicType;
// �������ֵķ�ʽ 0Ϊ��Ϸ�ڲ������棬1Ϊֱ�Ӳ���MP3
int pmType, gameStep, nowMst;
//int nowPress2, morePress2, sttFrame2, nowMst2, pmType2, nowPlayNum2, gameStep2;
//�ڴ���������еģ� ��ǰ���� �Ƿ��ж��ఴ�°��� ���濪ʼ֡�� ��ǰС�ں� �������ͱ�ţ�-1~4)  ��Ҫ���С�ڳ��� ��Ϸ���裨0��ѡ���� 1�����ף� 
int greenShine, redShine, maxShine = 20;  //��������Ȧ������ʱ�� 
bool siGame2[100];
int siShift;
int needPlay2[100];
int prePlayNum2 = 8;
int preMst[100][3] = {1, 255, 255, 1, 245, 245, 2, 245, 255, 2, 255, 245};
int mstPic[100] = {2100, 2101}; 
int preMstNum = 4, nowMstNum;
int ztMst[100][5];
// �������� ���� 

// ��������ϵͳ 
string soundName[100] = {	"A0", "#A0", "B0", 
							"C1", "#C1", "D1", "#D1", "E1", "F1", "#F1", "G1", "#G1", "A1", "#A1", "B1", 
							"C2", "#C2", "D2", "#D2", "E2", "F2", "#F2", "G2", "#G2", "A2", "#A2", "B2", 
							"C3", "#C3", "D3", "#D3", "E3", "F3", "#F3", "G3", "#G3", "A3", "#A3", "B3", 
							"C4", "#C4", "D4", "#D4", "E4", "F4", "#F4", "G4", "#G4", "A4", "#A4", "B4", 
							"C5", "#C5", "D5", "#D5", "E5", "F5", "#F5", "G5", "#G5", "A5", "#A5", "B5", 
							"C6", "#C6", "D6", "#D6", "E6", "F6", "#F6", "G6", "#G6", "A6", "#A6", "B6", 
							"C7", "#C7", "D7", "#D7", "E7", "F7", "#F7", "G7", "#G7", "A7", "#A7", "B7", 
							"C8"	}; 
int directName[200];

//FC_Font* font1 = NULL;

ofstream fout1;

realRect RR;

