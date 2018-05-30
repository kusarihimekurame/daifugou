#include "Decision.h"
#include "DxLib.h"


Decision::Decision(ISceneChanger* changer) : BaseScene(changer) {
}

//初期化
void Decision::Initialize() {
	mImageHandle = LoadGraph("images/Scene_Config.png");    //画像のロード
}

//更新
void swap(int a, int b) {
	int temp;

	temp = type1[a];
	type1[a] = type1[b];
	type1[b] = temp;
	temp = Size[a];
	Size[a] = Size[b];
	Size[b] = temp;
}

void swap1(int a) {
	int min;
	for (int i = 1; i <= a - 1; i++) {
		min = i;
		for (int j = i + 1; j <= a; j++) {
			if (type1[i] == 4) {
				swap(i, a);
			}
			if (type1[j] == 4)
				if (j == a)break;
				else swap(j, a);
			if (Size[min] > Size[j])
				min = j;
		}
		if (Size[min] != Size[i])
			swap(i, min);
	}
}

void swap2(int a) {
	int max;
	for (int i = 1; i <= a - 1; i++) {
		max = i;
		for (int j = i + 1; j <= a; j++) {
			if (type1[i] == 4 || type1[j] == 4) {
				swap(i, a);
			}
			if (type1[j] == 4)
				if (j == a)break;
				else swap(j, a);
			if (Size[max] < Size[j])
				max = j;
		}
		if (Size[max] != Size[i])
			swap(i, max);
	}
}

void swap3(int a, bool b) {
	if (b == 0)
		swap1(a);
	else
		swap2(a);
}

void Decision::Update() {
	swap3(num, kakumei);
	if (Key(KEY_INPUT_Y) == 1) {
		for (int i = 0; i < 5; i++)
			Del3[i] = Del[i];
		num = 0;
		for (int i = 1; i <= player[0]; i++)
			if (Size[i] == 0 && type1[i] == 1) {
				clockwise = 1;
				no = 0;
				mSceneChanger->ChangeScene(eScene_Game);
				break;
			}
			else
				mSceneChanger->ChangeScene(eScene_Turn);
	}
	if (Key(KEY_INPUT_ESCAPE) == 1) {
		num = 0;
		for (int i = 0; i < 5; i++)
			Del[i] = 0;
		mSceneChanger->ChangeScene(eScene_types);
	}
}

//描画
void Decision::Draw() {
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	DrawString(0, 64, "Yを押すと次の画面に進む。", GetColor(255, 255, 255));
	DrawString(0, 128, "ESCを押すと選び直す。", GetColor(255, 255, 255));
	DrawFormatString(0, 0, GetColor(255, 255, 255), "枚数%d", num);
	for (int i = 1; i <= num; i++) 
		DrawGraph((i-1) * 137 , h / 2 - 150, card[type1[i]*13+Size[i]], FALSE);
}