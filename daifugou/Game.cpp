#include "Game.h"
#include "DxLib.h"

int a,x;

Game::Game(ISceneChanger* changer) : BaseScene(changer) {
}

//初期化
void Game::Initialize() {
	mImageHandle = LoadGraph("images/Scene_Game.png");    //画像のロード
}

//更新
void SetAiData()
{
	int L0,L1;

	// ----- 手札情報
	CardNum = player[0];

	for (L0 = 0; L0<15; L0++) 
		for (L1 = 0; L1 < 6; L1++)
			Card[L0][L1] = 0;
	for (L0 = 1; L0<=player[0]; L0++) {
			if(type1[L0]==4)
				Card[14][5]++;
			else
				Card[Size[L0]+1][type1[L0]+1]++;
	}

	// ----- 場札情報
	if (type3[1] == 4)
		FieldCard[1] = 14;
	else
		for (L0 = 1; L0 <= num3; L0++)
			FieldCard[L0] = Size3[L0]+1;
	FieldNum = num3;
	UseNum = UseCard2[0];
	for (L0 = 0; L0<15; L0++) {
		UseCard[L0] = UseCard2[L0];
	}

	// ----- 他プレイヤー情報
	PlayerNum = 0;
	for (L0 = 0; L0<4; L0++) {
		if (player[L0] == 0 || L0 == 0) continue;
		PlayerCard[PlayerNum] = player[L0];
		PlayerNum++;
	}
}

void Game::Update() {
	if (x == 0) {
		PlaySoundFile("1.wav", DX_PLAYTYPE_NORMAL);
		x = 1;
	}
	if (player[0] == 0) {
		mSceneChanger->ChangeScene(eScene_End);
	}
	if (pass1 == 3) {
		for (int i = 1; i <= num3; i++) {
			Size3[i] = 0;
			type3[i] = 0;
		}
		num3 = 0;
		pass1 = 0;
	}
	if (player[no] == 0)
		if (clockwise == 0)
			no = (no + 1) % 4;
		else
			no = (no + (4 - 1)) % 4;
	if (no != 0) {
		if (Key(KEY_INPUT_RETURN) == 1) {
			mSceneChanger->ChangeScene(eScene_types2);
		}
	}
	else
	{
		SetAiData();
		AI();
		for (int i = 1; i <= num2; i++)
			Size2[i] = aCard[i]-1;
		for (int i = 1; i <= num2;i++)
			type2[i] = pmark[i]-1;
		if (type2[1] == 4)
			Size2[1] = 0;
		UseCard2[0] = UseCard2[0] + num2;
		for (int i = 0; i < num2; i++) {
			if (type2[i] == 4)
				UseCard2[14]++;
			else
				UseCard2[Size2[i] + 1]++;
		}
		if (num2 != 0) {
			for (int i = 1; i <= num2; i++) {
				type3[i] = type2[i];
				Size3[i] = Size2[i];
			}
			num3 = num2;
			pass1 = 0;
			while (a != num2) {
				a = 0;
				for (int i = player[no]; i > player[no] - num2; i--)
					for (int j = 1; j <= num2; j++)
						if (type1[i] == type3[j] && Size[i] == Size3[j])
							a++;
				for (int i = 1; i < player[no]; i++)
					for (int j = 1; j <= num2; j++)
						if (type1[i] == type3[j] && Size[i] == Size3[j]) {
							for (int z = i; z < player[no]; z++)
								swap(z, z + 1);
						}
			}
			a = 0;
			player[no] = player[no] - num2;
		}
		else 
			pass1++;
		if (num2 == 4 && Size2[1] == Size2[2] || num2 == 1 && type2[1] == 4) 
			switch (kakumei) {
			case 0:
				PlaySoundFile("kakumei.wav", DX_PLAYTYPE_BACK);
				kakumei = !kakumei;
				break;
			case 1:
				PlaySoundFile("!kakumei.wav", DX_PLAYTYPE_BACK);
				kakumei = !kakumei;
				break;
			}
		num2 = 0;
		if (clockwise == 0)
			no = (no + 1) % 4;
		else
			no = (no + (4 - 1)) % 4;
	}
	if (player[1]==0 && player[2]==0 && player[3]==0)
		mSceneChanger->ChangeScene(eScene_End);
}

//描画
void Game::Draw() {
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	for (int i = 0; i < player[1]; i++)
		DrawGraph(120, i * 25 + h/4, card[54], TRUE);	                                //player2
	for (int i = 0; i < player[2]; i++)
		DrawGraph(i * 50 + 500, 40, card[54], TRUE);									//player3
	for (int i = 0; i < player[3]; i++)
		DrawGraph(1600, i * 25 + h/4, card[54], TRUE);									//player4
	for (int i = 1; i <= player[0]; i++)
		DrawGraph((i - 1) * 50 + 500, h*3/4-70, card[type1[i] * 13 + Size[i]], TRUE);		//player1
	for (int i = 1; i <= num3; i++)
		DrawGraph((i - 1) * 150 + 600, h/2-150, card[type3[i] * 13 + Size3[i]], TRUE);		//場札
	DrawFormatString(0, 0, GetColor(255, 255, 255), "player%d", no+1);
	DrawFormatString(0, 64, GetColor(255, 255, 255), "場札の枚数%d", num3);
	DrawFormatString(0, 128, GetColor(255, 255, 255), "passの回数%d", pass1);
	if (kakumei == 1)
		DrawString(0, 192, "革命", GetColor(255, 255, 255));
}