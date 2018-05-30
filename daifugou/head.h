#ifndef _FRAME_H_
#define _FRAME_H_

#include <list>
using namespace std;


enum GAMESTATE{
	GAME_TITLE=1,GAME_MAIN,GAME_OVER,GAME_CLEAR,GAME_READY
};
enum CARDMARK{
	CLUB=1,HEART,DIA,SPADE,JOKER,
};

typedef struct{
	CARDMARK suit;	//�J�[�h�̎�ށi�X�y�[�h�A�_�C����
	int num;	//�J�[�h�̐����i�P�`�P�R
	int img;	//�J�[�h�̉摜
	int place;	//�J�[�h���ǂ��ɂ��邩(0=�R�D�A1=player1�A2=ply2�A3=ply3�A4=ply4�A5=�̂ĎD
	int trush_flag;	//��D����ɏo��(�̂Ă�)���ǂ����̃t���O -1=�̂ĂȂ� 1=�̂Ă�
}Card;

typedef struct{
	Card nowcard[4];

	int nowmaisuu;
	int turn;	//���N�̃^�[�����@0�`3
	int kaku_flag;	//�v�����N�����Ă��邩 0:�Ȃ� 1:����
}Ba;
typedef struct{
	char name[20];	//���O
	int num_tehuda;	//��D����
	list<Card> tehuda;		//��D�̃J�[�h���

	int dic_cnum;
	

}Player;


typedef struct{
	int hiscore;

}save_data;

int GetHitKeyStateAll_2(int[]);
void fps(unsigned int counter);
void wait_fanc();

class GameFrame
{
private:

	

public:

	//�f�o�b�O�p�ϐ�
	long int count;
	int modori;
	////////////////

	unsigned int counter;//�S�̂�ʂ��Ẵt���[����
	int starttime;		//��ԑJ�ڂ����Ƃ��̎���
	int Key[256];
	list<Card>::iterator it;

	Card card[53];	//�Q�[���Ɏg�����ׂẴJ�[�h
	Ba NowBa;
	Player player[4];


	int cursor;		//��D�I��p 
	

	int exit_flag;	//�Q�[���I���p
	save_data save;	//�Z�[�u�f�[�^

	int cursor_y;//�^�C�g���̃J�[�\�����W
	int white,red;	//�F

	/*    �O���t�B�b�N�n���h���p�ϐ�  */
	int gh_card[53];
	
	
	void drawGameTitle();	
	void drawGameReady();	//�v���C���[�̖��O�A�G�̐ݒ蓙
	void drawGameMain();
	void drawGameOver();
	void drawGameClear();
	void doMainLoop();
	void Reset();
	void LoadFiles();
	int CheckCardCorrect();	//�������ɏo���J�[�h�����[���ɉ����Ă邩�𒲂ׂ�@��:0�@��:-1
	
	void SetTehuda();	//�Q�[���J�n�A���v���C���ɃJ�[�h��z��

	GAMESTATE setGameState(GAMESTATE state);
	GAMESTATE gstate;

	~GameFrame(){};

	
};
#endif