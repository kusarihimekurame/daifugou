#include "Turn.h"
#include "DxLib.h"

int  no;
bool clockwise;

typedef enum {
	eMenu_Player2,
	eMenu_Player3,
	eMenu_Player4,

	eMenu_Num,        //�{���ڂ̐�
} eMenu;


static int NowSelect = eMenu_Player2;    //���݂̑I�����(�����̓Q�[���I��)


Turn::Turn(ISceneChanger* changer) : BaseScene(changer) {
}

//������
void Turn::Initialize() {
	mImageHandle = LoadGraph("images/Scene_Menu.png");    //�摜�̃��[�h
}

//�X�V
void Turn::Update() {
	if (NowSelect != 10) {
		if (Key(KEY_INPUT_DOWN) == 1) {//���L�[��������Ă�����
			NowSelect = (NowSelect + 1) % eMenu_Num;//�I����Ԃ��������
		}
		if (Key(KEY_INPUT_UP) == 1) {//��L�[��������Ă�����
			NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//�I����Ԃ���グ��
		}
		if (Key(KEY_INPUT_RETURN) == 1) {//�G���^�[�L�[�������ꂽ��
			no = NowSelect + 1;
			clockwise = 1;
			mSceneChanger->ChangeScene(eScene_Game);
		}
	}
}

//�`��
void Turn::Draw() {
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	DrawString(w / 2 - 512, 150, "�v���C���[�̏��Ԃ����߂ĉ������B", GetColor(255, 255, 255));
	DrawString(w / 2 - 200, 406, "Player2", GetColor(255, 255, 255));
	DrawString(w / 2 - 200, 500, "Player3", GetColor(255, 255, 255));
	DrawString(w / 2 - 200, 594, "Player4", GetColor(255, 255, 255));
	int y = 0;
	switch (NowSelect) {//���݂̑I����Ԃɏ]���ď����𕪊�
	case eMenu_Player2://�ݒ�I�𒆂Ȃ�
		y = 406;    //�ݒ�̍��W���i�[
		break;
	case eMenu_Player3://�ݒ�I�𒆂Ȃ�
		y = 500;    //�ݒ�̍��W���i�[
		break;
	case eMenu_Player4://�ݒ�I�𒆂Ȃ�
		y = 594;    //�ݒ�̍��W���i�[
		break;
	}
	DrawString(w / 2 - 300, y, "��", GetColor(255, 255, 255));
}