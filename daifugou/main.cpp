#include "DxLib.h"
#include "SceneMgr.h"

#define SCREEN_SIZE_X			(1920)
#define SCREEN_SIZE_Y			(1080)

int Handle;
int w = 1920, h = 1080;
int card[55];
bool kakumei=0;
int UseCard2[15] = { 0 };

void init()
{
	ChangeWindowMode(1);
	SetWindowSizeChangeEnableFlag(TRUE);
	SetGraphMode(1920, 1080, 32);
	SetWindowStyleMode(4);
	SetWindowPosition(0, 0);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	SetGraphMode(w, h, 16);
	SetMainWindowText("大富豪");                       //ウインドウのタイトルを変更する
	SetWindowSizeChangeEnableFlag(TRUE);			   //ウインドウモードの時にウインドウのサイズを自由に変更出来るようにするかどうかを設定する
	SetWindowSizeExtendRate(1);                        //ウインドウモードの時のウインドウの大きさと描画画面の大きさの比率を設定する
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
	init(); //ウィンドウモード変更と初期化と裏画面設定
	SetBackgroundColor(50, 50, 255);
	Handle = LoadDivGraph("card.jpg", 55, 13, 5, 200, 300, card);     //147,220
	SceneMgr sceneMgr;
	sceneMgr.Initialize();
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		SetFontSize(64);
		Keyboard_Update();    //キーボードの更新
		sceneMgr.Update();  //更新
		sceneMgr.Draw();    //描画
	}
	sceneMgr.Finalize();

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}