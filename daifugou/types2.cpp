#include "types2.h"
#include "DxLib.h"

int types1, num2, num3, pass1;
int Size2[14], type2[14],type3[14],Size3[14];

const static int one_x = 62;
const static int two_x = 462;
const static int three_x = 862;
const static int four_x = 1262;
const static int five_x = 1662;
const static int one_y = h / 2 - 150;

typedef enum {
	eMenu_Clubs,
	eMenu_Diamonds,
	eMenu_Hearts,
	eMenu_Spades,
	eMenu_Joker,

	eMenu_Num,        //本項目の数
} eMenu;

static int NowSelect = eMenu_Clubs;    //現在の選択状態(初期はゲーム選択中)

types2::types2(ISceneChanger* changer) : BaseScene(changer) {
}

//初期化
void types2::Initialize() {
	mImageHandle = LoadGraph("images/Scene_Menu.png");    //画像のロード
}

//更新
void types2::Update() {
	for (int i = 0; i < 5; i++)
		if (NowSelect == i && Del[i] == 13 || i == 4 && Del[i] == 1 && NowSelect == i) {
			NowSelect = (NowSelect + 1) % eMenu_Num;
			i = -1;
		}
	if (Key(KEY_INPUT_RIGHT) == 1) {//右キーが押されていたら
		NowSelect = (NowSelect + 1) % eMenu_Num;//選択状態を一つ下げる
		for (int i = 0; i < 5; i++) {
			if (NowSelect == i && Del[i] == 13 || i == 4 && Del[i] == 1 && NowSelect == i) {
				NowSelect = (NowSelect + 1) % eMenu_Num;
				i = -1;
			}
		}
	}
	if (Key(KEY_INPUT_LEFT) == 1) {//左キーが押されていたら
		NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//選択状態を一つ上げる
		for (int i = 4; i >= 0; i--)
			if (NowSelect == i && Del[i] == 13 || i == 4 && Del[i] == 1 && NowSelect == i) {
				NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;
				i = 5;
			}
	}
	if (Key(KEY_INPUT_RETURN) == 1) {//エンターキーが押されたら
		switch (NowSelect) {//現在選択中の状態によって処理を分岐
		case eMenu_Joker:
			num2++;
			types1 = NowSelect;
			type2[num2] = types1;
			Size2[num2] = 0;
			Del[types1]++;
			Del2[Del[0] + Del[1] + Del[2] + Del[3] + Del[4]-1] = types1;
			mSceneChanger->ChangeScene(eScene_Decision2);
			break;
		default:
			types1 = NowSelect;
			mSceneChanger->ChangeScene(eScene_cards2);
			break;
		}
	}
	if (Key(KEY_INPUT_P) == 1) {
		if (clockwise == 0)
			no = (no + 1) % 4;
		else
			no = (no + (4 - 1)) % 4;
		pass1++;
		mSceneChanger->ChangeScene(eScene_Game);
	}
}

//描画
void types2::Draw() {
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	for (int i = 0; i < 13; i++) {
		Del4[i] = 0;
		for (int j = 0; j < Del[0] + Del[1] + Del[2] + Del[3] + Del[4]; j++)
			if (i == Del1[j] && Del2[j] == 0)
				Del4[i] = 1;
	}
	for (int i = Del[0]; i < 13; i++) {
		if (i == 12)
			for (int j = 12; j >= 0; j--)
				if (Del4[j] == 0) {
					DrawGraph(i * 2 + one_x, one_y, card[j], FALSE);
					break;
				}
		if (i != 12)
			DrawGraph(i * 2 + one_x, one_y, card[i], FALSE);
	}
	for (int i = 0; i < 13; i++) {
		Del4[i] = 0;
		for (int j = 0; j < Del[0] + Del[1] + Del[2] + Del[3] + Del[4]; j++)
			if (i == Del1[j] && Del2[j] == 1)
				Del4[i] = 1;
	}
	for (int i = Del[1]; i < 13; i++) {
		if (i == 12)
			for (int j = 12; j >= 0; j--)
				if (Del4[j] == 0) {
					DrawGraph(i * 2 + two_x, one_y, card[1 * 13 + j], FALSE);
					break;
				}
		if (i != 12)
			DrawGraph(i * 2 + two_x, one_y, card[1 * 13 + i], FALSE);
	}
	for (int i = 0; i < 13; i++) {
		Del4[i] = 0;
		for (int j = 0; j < Del[0] + Del[1] + Del[2] + Del[3] + Del[4]; j++)
			if (i == Del1[j] && Del2[j] == 2)
				Del4[i] = 1;
	}
	for (int i = Del[2]; i < 13; i++) {
		if (i == 12)
			for (int j = 12; j >= 0; j--)
				if (Del4[j] == 0) {
					DrawGraph(i * 2 + three_x, one_y, card[2 * 13 + j], FALSE);
					break;
				}
		if (i != 12)
			DrawGraph(i * 2 + three_x, one_y, card[2 * 13 + i], FALSE);
	}
	for (int i = 0; i < 13; i++) {
		Del4[i] = 0;
		for (int j = 0; j < Del[0] + Del[1] + Del[2] + Del[3] + Del[4]; j++)
			if (i == Del1[j] && Del2[j] == 3)
				Del4[i] = 1;
	}
	for (int i = Del[3]; i < 13; i++) {
		if (i == 12)
			for (int j = 12; j >= 0; j--)
				if (Del4[j] == 0) {
					DrawGraph(i * 2 + four_x, one_y, card[3 * 13 + j], FALSE);
					break;
				}
		if (i != 12)
			DrawGraph(i * 2 + four_x, one_y, card[3 * 13 + i], FALSE);
	}
	if (Del[4] != 1)
		DrawGraph(five_x, one_y, card[52], FALSE);
	DrawString(one_x, one_y + 340, "Clubs", GetColor(255, 255, 255));
	DrawString(two_x, one_y + 340, "Diamonds", GetColor(255, 255, 255));
	DrawString(three_x, one_y + 340, "Hearts", GetColor(255, 255, 255));
	DrawString(four_x, one_y + 340, "Spades", GetColor(255, 255, 255));
	DrawString(five_x, one_y + 340, "Joker", GetColor(255, 255, 255));
	int x = 0;
	switch (NowSelect) {//現在の選択状態に従って処理を分岐
	case eMenu_Clubs://ゲーム選択中なら
		x = one_x;    //ゲームの座標を格納
		break;
	case eMenu_Diamonds://設定選択中なら
		x = two_x;    //設定の座標を格納
		break;
	case eMenu_Hearts://設定選択中なら
		x = three_x;    //設定の座標を格納
		break;
	case eMenu_Spades://設定選択中なら
		x = four_x;    //設定の座標を格納
		break;
	case eMenu_Joker://設定選択中なら
		x = five_x;    //設定の座標を格納
		break;
	}
	DrawString(x, one_y + 404, "■", GetColor(255, 255, 255));
	DrawFormatString(0, 0, GetColor(255, 255, 255), "player%d", no + 1);
	DrawFormatString(0, 64, GetColor(255, 255, 255), "枚数%d", num2);
	DrawString(0, 128, "Pを押すとPASS。", GetColor(255, 255, 255));
}