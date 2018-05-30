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
	CARDMARK suit;	//カードの種類（スペード、ダイヤ等
	int num;	//カードの数字（１～１３
	int img;	//カードの画像
	int place;	//カードがどこにあるか(0=山札、1=player1、2=ply2、3=ply3、4=ply4、5=捨て札
	int trush_flag;	//手札を場に出す(捨てる)かどうかのフラグ -1=捨てない 1=捨てる
}Card;

typedef struct{
	Card nowcard[4];

	int nowmaisuu;
	int turn;	//今誰のターンか　0～3
	int kaku_flag;	//革命が起こっているか 0:ない 1:ある
}Ba;
typedef struct{
	char name[20];	//名前
	int num_tehuda;	//手札枚数
	list<Card> tehuda;		//手札のカード情報

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

	//デバッグ用変数
	long int count;
	int modori;
	////////////////

	unsigned int counter;//全体を通してのフレーム数
	int starttime;		//状態遷移したときの時間
	int Key[256];
	list<Card>::iterator it;

	Card card[53];	//ゲームに使うすべてのカード
	Ba NowBa;
	Player player[4];


	int cursor;		//手札選択用 
	

	int exit_flag;	//ゲーム終了用
	save_data save;	//セーブデータ

	int cursor_y;//タイトルのカーソル座標
	int white,red;	//色

	/*    グラフィックハンドル用変数  */
	int gh_card[53];
	
	
	void drawGameTitle();	
	void drawGameReady();	//プレイヤーの名前、敵の設定等
	void drawGameMain();
	void drawGameOver();
	void drawGameClear();
	void doMainLoop();
	void Reset();
	void LoadFiles();
	int CheckCardCorrect();	//今から場に出すカードがルールに沿ってるかを調べる　正:0　誤:-1
	
	void SetTehuda();	//ゲーム開始、リプレイ時にカードを配る

	GAMESTATE setGameState(GAMESTATE state);
	GAMESTATE gstate;

	~GameFrame(){};

	
};
#endif