#include "Menu.h"
#include "DxLib.h"

int player[3];

typedef enum {
	eMenu_Player1,        
	eMenu_Player2,
	eMenu_Player3,
	eMenu_Player4,

	eMenu_Num,        //�{���ڂ̐�
} eMenu;

static int NowSelect = eMenu_Player1;    //���݂̑I�����(�����̓Q�[���I��)

Menu::Menu(ISceneChanger* changer) : BaseScene(changer) {
}

//������
void Menu::Initialize() {
	mImageHandle = LoadGraph("images/Scene_Menu.png");    //�摜�̃��[�h
}

//�X�V
void Menu::Update() {
	if (Key(KEY_INPUT_DOWN) == 1) {//���L�[��������Ă�����
		NowSelect = (NowSelect + 1) % eMenu_Num;//�I����Ԃ��������
	}
	if (Key(KEY_INPUT_UP) == 1) {//��L�[��������Ă�����
		NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//�I����Ԃ���グ��
	}
	if (Key(KEY_INPUT_RETURN) == 1) {//�G���^�[�L�[�������ꂽ��
		switch (NowSelect) {//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
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

//�`��
void Menu::Draw() {
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	DrawString(w/2-832, 214, "�㉺�L�[�������A14���J�[�h�����l��I��ł��������B", GetColor(255, 255, 255));
	DrawString(w/2-200, 406, "Player1", GetColor(255, 255, 255));
	DrawString(w/2-200, 500, "Player2", GetColor(255, 255, 255));
	DrawString(w/2-200, 594, "Player3", GetColor(255, 255, 255));
	DrawString(w/2-200, 688, "Player4", GetColor(255, 255, 255));
	int y = 0;
	switch (NowSelect) {//���݂̑I����Ԃɏ]���ď����𕪊�
	case eMenu_Player1://�Q�[���I�𒆂Ȃ�
		y = 406;    //�Q�[���̍��W���i�[
		break;
	case eMenu_Player2://�ݒ�I�𒆂Ȃ�
		y = 500;    //�ݒ�̍��W���i�[
		break;
	case eMenu_Player3://�ݒ�I�𒆂Ȃ�
		y = 594;    //�ݒ�̍��W���i�[
		break;
	case eMenu_Player4://�ݒ�I�𒆂Ȃ�
		y = 688;    //�ݒ�̍��W���i�[
		break;
	}
	DrawString(w / 2 - 300, y, "��", GetColor(255, 255, 255));
}