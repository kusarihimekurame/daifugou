#include "End.h"
#include "DxLib.h"

int i;

End::End(ISceneChanger* changer) : BaseScene(changer) {
}

//初期化
void End::Initialize() {
	mImageHandle = LoadGraph("images/Scene_Game.png");    //画像のロード
}

//更新
void End::Update() {
	if (i == 0)
		switch (end) {
		case 0:
			PlaySoundFile("dafugou.wav", DX_PLAYTYPE_BACK);
			i = 1;
			break;
		case 1:
			PlaySoundFile("fugou.wav", DX_PLAYTYPE_BACK);
			i = 1;
			break;
		case 2:
			PlaySoundFile("heminn.wav", DX_PLAYTYPE_BACK);
			i = 1;
			break;
		case 3:
			PlaySoundFile("daiheminn.wav", DX_PLAYTYPE_BACK);
			i = 1;
			break;
	}

}

//描画
void End::Draw() {
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	switch (end) {
	case 0:
		DrawString(w/2-96, h/2-32, "大富豪。", GetColor(255, 255, 255));
		break;
	case 1:
		DrawString(w/2-96, h/2-32, "富豪。", GetColor(255, 255, 255));
		break;
	case 2:
		DrawString(w/2-96, h/2-32, "貧民。", GetColor(255, 255, 255));
		break;
	case 3:
		DrawString(w/2-96, h/2-32, "大貧民。", GetColor(255, 255, 255));
		break;
	}
}