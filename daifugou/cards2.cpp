#include "cards2.h"
#include "DxLib.h"


typedef enum {
	eMenu_1,
	eMenu_2,
	eMenu_3,
	eMenu_4,
	eMenu_5,
	eMenu_6,
	eMenu_7,
	eMenu_8,
	eMenu_9,
	eMenu_10,
	eMenu_J,
	eMenu_Q,
	eMenu_K,

	eMenu_Num,        //�{���ڂ̐�
} eMenu;

static int NowSelect = eMenu_1;    //���݂̑I�����(�����̓Q�[���I��)

cards2::cards2(ISceneChanger* changer) : BaseScene(changer) {
}

//������
void cards2::Initialize() {
	mImageHandle = LoadGraph("images/Scene_Menu.png");    //�摜�̃��[�h
}

//�X�V
void cards2::Update() {
	for (int i = 0; i < Del[0]+ Del[1]+Del[2]+Del[3]+Del[4]; i++)
		if (NowSelect == Del1[i] && types1 == Del2[i]) {
			NowSelect = (NowSelect + 1) % eMenu_Num;
			i = -1;
		}
	if (Key(KEY_INPUT_RIGHT) == 1) {//�E�L�[��������Ă�����
		NowSelect = (NowSelect + 1) % eMenu_Num;//�I����Ԃ��������
		for (int i = 0; i < Del[0] + Del[1] + Del[2] + Del[3] + Del[4]; i++)
			if (NowSelect == Del1[i] && types1 == Del2[i]) {
				NowSelect = (NowSelect + 1) % eMenu_Num;
				i = -1;
			}
	}
	if (Key(KEY_INPUT_LEFT) == 1) {//���L�[��������Ă�����
		NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//�I����Ԃ���グ��
		for (int i = Del[0] + Del[1] + Del[2] + Del[3] + Del[4] - 1; i >= 0; i--)
			if (NowSelect == Del1[i] && types1 == Del2[i]) {
				NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;
				i = Del[0] + Del[1] + Del[2] + Del[3] + Del[4];
			}
	}
	if (Key(KEY_INPUT_RETURN) == 1) {//�G���^�[�L�[�������ꂽ��
		Del1[Del[0] + Del[1] + Del[2] + Del[3] + Del[4]] = NowSelect;
		Del2[Del[0] + Del[1] + Del[2] + Del[3] + Del[4]] = types1;
		Del[types1]++;
		num2++;
		Size2[num2] = NowSelect;
		type2[num2] = types1;
		mSceneChanger->ChangeScene(eScene_Decision2);
	}
}

//�`��
void cards2::Draw() {
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	for (int i = 0; i < 13; i++) {
		if (i == NowSelect)
			DrawGraph(i * 147, h / 2 - 150 - 25, card[types1 * 13 + i], FALSE);
		else {
			for (int j = 0; j < Del[0] + Del[1] + Del[2] + Del[3] + Del[4]; j++)
				if (i == Del1[j] && types1 == Del2[j])
					b = 1;
			if (b == 1) {
				b = 0;
				continue;
			}
			DrawGraph(i * 147, h / 2 - 150, card[types1 * 13 + i], FALSE);
		}
	}
	DrawFormatString(0, 0, GetColor(255, 255, 255), "player%d", no + 1);
	DrawFormatString(0, 64, GetColor(255, 255, 255), "����%d", num2);
}