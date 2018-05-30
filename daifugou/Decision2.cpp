#include "Decision2.h"
#include "DxLib.h"

int end;


Decision2::Decision2(ISceneChanger* changer) : BaseScene(changer) {
}

//初期化
void Decision2::Initialize() {
	mImageHandle = LoadGraph("images/Scene_Config.png");    //画像のロード
}

//更新
void swap4(int a, int b) {
	int temp;
	temp = type2[a];
	type2[a] = type2[b];
	type2[b] = temp;
	temp = Size2[a];
	Size2[a] = Size2[b];
	Size2[b] = temp;
}

void swap5(int a) {
	int min;
	for (int i = 1; i <= a - 1; i++) {
		min = i;
		for (int j = i + 1; j <= a; j++) {
			if (type2[i] == 4 || type2[j] == 4) {
				swap4(i, a);
			}
			if (Size2[min] > Size2[j])
				min = j;
		}
		if (Size2[min] != Size2[i])
			swap4(i, min);
	}
}

void swap6(int a) {
	int max;
	for (int i = 1; i <= a - 1; i++) {
		max = i;
		for (int j = i + 1; j <= a; j++) {
			if (type2[i] == 4 || type2[j] == 4) {
				swap4(i, a);
			}
			if (Size2[max] < Size2[j])
				max = j;
		}
		if (Size2[max] != Size2[i])
			swap4(i, max);
	}
}

void swap7(int a, int b) {
	if (b == 0)
		swap5(a);
	else
		swap6(a);
}

void Decision2::Update() {
	swap7(num2, kakumei);
	if (Key(KEY_INPUT_Y) == 1) {
		for (int i = 0; i < 5; i++)
			Del3[i] = Del[i];
		pass1 = 0;
		if (num2 == 4 && Size2[1] == Size2[2] || num2==1 && type2[1] == 4)
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
		player[no] = player[no] - num2;
		if (player[no] == 0)
			end++;
		if (clockwise == 0)
			no = (no + 1) % 4;
		else
			no = (no + (4 - 1)) % 4;
		UseCard2[0] = UseCard2[0] + num2;
		for (int i = 1; i <= num2; i++) {
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
		}
		num2 = 0;
		mSceneChanger->ChangeScene(eScene_Game);
	}
	if (Key(KEY_INPUT_N) == 1) {
		mSceneChanger->ChangeScene(eScene_types2);
	}
	if (Key(KEY_INPUT_ESCAPE) == 1) {
		for (int i = 0; i < 5; i++)
			Del[i] = Del3[i];
		for (int i = 0; i <= num2; i++)
			type2[i] = Size2[i] = 0;
		num2 = 0;
		mSceneChanger->ChangeScene(eScene_types2);
	}
}

//描画
void Decision2::Draw() {
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	for (int i = 1; i <= num2; i++)
		DrawGraph((i - 1) * 150 + 600, h / 2 - 150, card[type2[i] * 13 + Size2[i]], FALSE);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "player%d", no + 1);
	DrawFormatString(0, 64, GetColor(255, 255, 255), "枚数%d", num2);
	DrawString(0, 128, "Yを押すと次の画面に進む。", GetColor(255, 255, 255));
	DrawString(0, 192, "Nを押すと次のカードを選ぶ。", GetColor(255, 255, 255));
	DrawString(0, 256, "ESCを押すと選び直す。", GetColor(255, 255, 255));
}