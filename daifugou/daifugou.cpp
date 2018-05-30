#include "DxLib.h"
#include<Windows.h>	

int Key[256];
int Handle;
int w = 640, h = 480;
int card[55];
int player[4];

void init()
{
	ChangeWindowMode(TRUE);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	SetGraphMode(w, h, 16);
	SetMainWindowText("大富豪");                       //ウインドウのタイトルを変更する
	SetWindowSizeChangeEnableFlag(TRUE);			   //ウインドウモードの時にウインドウのサイズを自由に変更出来るようにするかどうかを設定する
	SetWindowSizeExtendRate(2);                        //ウインドウモードの時のウインドウの大きさと描画画面の大きさの比率を設定する
}

int UpdateKey() {
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) {
			Key[i]++;
		}
		else {
			Key[i] = 0;
		}
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	int i = 0;
	int z,x,c;
	init();
	Handle = LoadDivGraph("card.png", 55, 13, 5, 49, 71, card);
	SetBackgroundColor(50, 50, 255);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && UpdateKey() == 0)
	{
		DrawString(w / 2 - 35, h * 1 / 8, "牌数の選択", 0xff0000);
		if (Key[KEY_INPUT_1] == 1)
		{
			player[0] = 14;
			player[1] = player[2] = player[3] = 13;
		}
		else if (Key[KEY_INPUT_2] == 1)
		{
			player[1] = 14;
			player[0] = player[2] = player[3] = 13;
		}
		else if (Key[KEY_INPUT_3] == 1)
		{
			player[2] = 14;
			player[0] = player[1] = player[3] = 13;
		}
		else if (Key[KEY_INPUT_4] == 1)
		{
			player[3] = 14;
			player[0] = player[1] = player[2] = 13;
		}
		DrawString(w / 2 - 35, h * 1 / 8, "player1の牌", 0xff0000);
		while (i = player[0])
		{
			DrawString(w / 2 - 35, h * 2 / 8, "カードの種類", 0xff0000);
			scanf("%d", &z);
			DrawString(w / 2 - 35, h * 3 / 8, "カードの大きさ", 0xff0000);
			scanf("%d", &x);
			DrawString(w / 2 - 35, h * 4 / 8, "枚数", 0xff0000);
			scanf("%d", &c);
			i = i + c;
			if (i > player[0])
			{
				DrawString(w / 2 - 35, h * 5 / 8, "player1の牌", 0xff0000);
				i = 0;
			}
		}
		for (int i = 0; i < player[1]; i++)
			DrawGraph(100, i * 9 + 150, card[i], TRUE);
		for (int i = 0; i < player[2]; i++)
			DrawGraph(i * 9 + 250, 50, card[i], TRUE);
		for (int i = 0; i < player[3]; i++)
			DrawGraph(500, i * 9 + 150, card[i], TRUE);
	}
	return 0;
}