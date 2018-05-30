#include "Menu.h"
#include "DxLib.h"

int player[3];

typedef enum {
	eMenu_Player1,        
	eMenu_Player2,
	eMenu_Player3,
	eMenu_Player4,

	eMenu_Num,        //本項目の数
} eMenu;

static int NowSelect = eMenu_Player1;    //現在の選択状態(初期はゲーム選択中)

Menu::Menu(ISceneChanger* changer) : BaseScene(changer) {
}

//初期化
void Menu::Initialize() {
	mImageHandle = LoadGraph("images/Scene_Menu.png");    //画像のロード
}

//更新
void Menu::Update() {
	if (Key(KEY_INPUT_DOWN) == 1) {//下キーが押されていたら
		NowSelect = (NowSelect + 1) % eMenu_Num;//選択状態を一つ下げる
	}
	if (Key(KEY_INPUT_UP) == 1) {//上キーが押されていたら
		NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//選択状態を一つ上げる
	}
	if (Key(KEY_INPUT_RETURN) == 1) {//エンターキーが押されたら
		switch (NowSelect) {//現在選択中の状態によって処理を分岐
		case eMenu_Player1:
			player[0] = 14;
			player[1] = player[2] = player[3] = 13;
			break;
		case eMenu_Player2:
			player[1] = 14;
			player[0] = player[2] = player[3] = 13;
			break;
		case eMenu_Player3:
			player[2] = 14;
			player[0] = player[1] = player[3] = 13;
			break;
		case eMenu_Player4:
			player[3] = 14;
			player[0] = player[1] = player[2] = 13;
			break;
		}
		mSceneChanger->ChangeScene(eScene_types);
	}
}

//描画
void Menu::Draw() {
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	DrawString(w/2-832, 214, "上下キーを押し、14枚カードを持つ人を選んでください。", GetColor(255, 255, 255));
	DrawString(w/2-200, 406, "Player1", GetColor(255, 255, 255));
	DrawString(w/2-200, 500, "Player2", GetColor(255, 255, 255));
	DrawString(w/2-200, 594, "Player3", GetColor(255, 255, 255));
	DrawString(w/2-200, 688, "Player4", GetColor(255, 255, 255));
	int y = 0;
	switch (NowSelect) {//現在の選択状態に従って処理を分岐
	case eMenu_Player1://ゲーム選択中なら
		y = 406;    //ゲームの座標を格納
		break;
	case eMenu_Player2://設定選択中なら
		y = 500;    //設定の座標を格納
		break;
	case eMenu_Player3://設定選択中なら
		y = 594;    //設定の座標を格納
		break;
	case eMenu_Player4://設定選択中なら
		y = 688;    //設定の座標を格納
		break;
	}
	DrawString(w / 2 - 300, y, "■", GetColor(255, 255, 255));
}