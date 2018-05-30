#include "End.h"
#include "DxLib.h"

int i;

End::End(ISceneChanger* changer) : BaseScene(changer) {
}

//������
void End::Initialize() {
	mImageHandle = LoadGraph("images/Scene_Game.png");    //�摜�̃��[�h
}

//�X�V
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

//�`��
void End::Draw() {
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	switch (end) {
	case 0:
		DrawString(w/2-96, h/2-32, "��x���B", GetColor(255, 255, 255));
		break;
	case 1:
		DrawString(w/2-96, h/2-32, "�x���B", GetColor(255, 255, 255));
		break;
	case 2:
		DrawString(w/2-96, h/2-32, "�n���B", GetColor(255, 255, 255));
		break;
	case 3:
		DrawString(w/2-96, h/2-32, "��n���B", GetColor(255, 255, 255));
		break;
	}
}