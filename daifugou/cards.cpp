#include "cards.h"
#include "DxLib.h"

int Size[15],type1[15];
int Del1[55],Del2[55],Del[5],Del3[5],Del4[13];
int b;

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

cards::cards(ISceneChanger* changer) : BaseScene(changer) {
}

//������
void cards::Initialize() {
	mImageHandle = LoadGraph("images/Scene_Menu.png");    //�摜�̃��[�h
}

//�X�V
void cards::Update() {
	for (int i = 0; i < num; i++)
		if (NowSelect == Del1[i] && type == Del2[i]) {
			NowSelect = (NowSelect + 1) % eMenu_Num;
			i = -1;
		}
	if (Key(KEY_INPUT_RIGHT) == 1) {//�E�L�[��������Ă�����
		NowSelect = (NowSelect + 1) % eMenu_Num;//�I����Ԃ��������
		for (int i = 0; i < num; i++)
			if (NowSelect == Del1[i] && type == Del2[i]) {
				NowSelect = (NowSelect + 1) % eMenu_Num;
				i = -1;
			}
	}
	if (Key(KEY_INPUT_LEFT) == 1) {//���L�[��������Ă�����
		NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//�I����Ԃ���グ��
		for (int i = num-1; i >= 0; i--)
			if (NowSelect == Del1[i] && type == Del2[i]) {
				NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;
				i = num;
			}
	}
	if (Key(KEY_INPUT_RETURN) == 1) {//�G���^�[�L�[�������ꂽ��
		Del1[num] = NowSelect;
		Del2[num] = type;
		Del[type]++;
		num++;
		Size[num] = NowSelect;
		type1[num] = type;
		if (num < player[0])
			mSceneChanger->ChangeScene(eScene_types);
		else {
			mSceneChanger->ChangeScene(eScene_Decision);
		}
	}
}

//�`��
void cards::Draw() {
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	for (int i = 0; i < 13; i++) {
		if (i == NowSelect)
			DrawGraph(i * 147 , h / 2 - 150 - 25, card[type * 13 + i], FALSE);
		else {
			for (int j = 0; j < num; j++)
				if (i == Del1[j] && type == Del2[j])
					b = 1;
			if (b == 1) {
				b = 0;
				continue;
			}
			DrawGraph(i * 147 , h / 2 - 150, card[type * 13 + i], FALSE);
		}
	}
	DrawFormatString(0, 0, GetColor(255,255,255),"����%d", num);
}