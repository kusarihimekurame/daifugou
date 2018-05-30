#include "Turn.h"
#include "DxLib.h"

int  no;
bool clockwise;

typedef enum {
	eMenu_Player2,
	eMenu_Player3,
	eMenu_Player4,

	eMenu_Num,        //本項目の数
} eMenu;


static int NowSelect = eMenu_Player2;    //現在の選択状態(初期はゲーム選択中)


Turn::Turn(ISceneChanger* changer) : BaseScene(changer) {
}

//初期化
void Turn::Initialize() {
	mImageHandle = LoadGraph("images/Scene_Menu.png");    //画像のロード
}

//更新
void Turn::Update() {
	if (NowSelect != 10) {
		if (Key(KEY_INPUT_DOWN) == 1) {//下キーが押されていたら
			NowSelect = (NowSelect + 1) % eMenu_Num;//選択状態を一つ下げる
		}
		if (Key(KEY_INPUT_UP) == 1) {//上キーが押されていたら
			NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//選択状態を一つ上げる
		}
		if (Key(KEY_INPUT_RETURN) == 1) {//エンターキーが押されたら
			no = NowSelect + 1;
			clockwise = 1;
			mSceneChanger->ChangeScene(eScene_Game);
		}
	}
}

//描画
void Turn::Draw() {
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	DrawString(w / 2 - 512, 150, "プレイヤーの順番を決めて下さい。", GetColor(255, 255, 255));
	DrawString(w / 2 - 200, 406, "Player2", GetColor(255, 255, 255));
	DrawString(w / 2 - 200, 500, "Player3", GetColor(255, 255, 255));
	DrawString(w / 2 - 200, 594, "Player4", GetColor(255, 255, 255));
	int y = 0;
	switch (NowSelect) {//現在の選択状態に従って処理を分岐
	case eMenu_Player2://設定選択中なら
		y = 406;    //設定の座標を格納
		break;
	case eMenu_Player3://設定選択中なら
		y = 500;    //設定の座標を格納
		break;
	case eMenu_Player4://設定選択中なら
		y = 594;    //設定の座標を格納
		break;
	}
	DrawString(w / 2 - 300, y, "■", GetColor(255, 255, 255));
}