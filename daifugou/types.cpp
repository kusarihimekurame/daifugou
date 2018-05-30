#include "types.h"
#include "DxLib.h"

int type,num;
const static int one_x = 62;    
const static int two_x = 462;   
const static int three_x = 862;    
const static int four_x = 1262;   
const static int five_x = 1662;  
const static int one_y = h/2-150;

typedef enum {
	eMenu_Clubs,
	eMenu_Diamonds,
	eMenu_Hearts,
	eMenu_Spades,
	eMenu_Joker,

	eMenu_Num,        //�{���ڂ̐�
} eMenu;

static int NowSelect = eMenu_Clubs;    //���݂̑I�����(�����̓Q�[���I��)

types::types(ISceneChanger* changer) : BaseScene(changer) {
}

//������
void types::Initialize() {
	mImageHandle = LoadGraph("images/Scene_Menu.png");    //�摜�̃��[�h
}

//�X�V
void types::Update() {
	for (int i = 0; i < 5; i++)
		if (NowSelect == i && Del[i] == 13 || i == 4 && Del[i] == 1 && NowSelect == i) {
			NowSelect = (NowSelect + 1) % eMenu_Num;
			i = -1;
		}
	if (Key(KEY_INPUT_RIGHT) == 1) {//�E�L�[��������Ă�����
		NowSelect = (NowSelect + 1) % eMenu_Num;//�I����Ԃ��������
		for (int i = 0; i < 5; i++) {
			if (NowSelect == i && Del[i] == 13 || i == 4 && Del[i] == 1 && NowSelect ==i) {
				NowSelect = (NowSelect + 1) % eMenu_Num;
				i = -1;
			}
		}
	}
	if (Key(KEY_INPUT_LEFT) == 1) {//���L�[��������Ă�����
		NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//�I����Ԃ���グ��
		for (int i = 4; i >= 0; i--)
			if (NowSelect == i && Del[i] == 13 || i == 4 && Del[i] == 1 && NowSelect == i) {
				NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;
				i = 5;
			}
	}
	if (Key(KEY_INPUT_RETURN) == 1) {//�G���^�[�L�[�������ꂽ��
		switch (NowSelect) {//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
		case eMenu_Joker:
			num++;
			type = NowSelect;
			type1[num] = type;
			Size[num] = 0;
			Del[type]++;
			Del2[num-1] = type;
			if (num < player[0])
				mSceneChanger->ChangeScene(eScene_types);
			else {
				mSceneChanger->ChangeScene(eScene_Decision);
			}
			break;
		default:
			type = NowSelect;
			mSceneChanger->ChangeScene(eScene_cards);
			break;
		}
	}
}

//�`��
void types::Draw() {
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	for (int i = 0; i < 13; i++) {
		Del4[i] = 0;
		for (int j = 0; j < num; j++)
			if (i == Del1[j] && Del2[j] == 0)
				Del4[i] = 1;
	}
	for (int i = Del[0]; i < 13; i++) {
		if (i == 12) 
			for (int j = 12; j >= 0; j--)
				if (Del4[j] == 0) {
					DrawGraph(i * 2 +one_x, one_y, card[j], FALSE);
					break;
				}
		if (i != 12)
			DrawGraph(i * 2 + one_x, one_y, card[i], FALSE);
	}
	for (int i = 0; i < 13; i++) {
		Del4[i] = 0;
		for (int j = 0; j < num; j++)
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
		for (int j = 0; j < num; j++)
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
		for (int j = 0; j < num; j++)
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
	switch (NowSelect) {//���݂̑I����Ԃɏ]���ď����𕪊�
	case eMenu_Clubs://�Q�[���I�𒆂Ȃ�
		x = one_x;    //�Q�[���̍��W���i�[
		break;
	case eMenu_Diamonds://�ݒ�I�𒆂Ȃ�
		x = two_x;    //�ݒ�̍��W���i�[
		break;
	case eMenu_Hearts://�ݒ�I�𒆂Ȃ�
		x = three_x;    //�ݒ�̍��W���i�[
		break;
	case eMenu_Spades://�ݒ�I�𒆂Ȃ�
		x = four_x;    //�ݒ�̍��W���i�[
		break;
	case eMenu_Joker://�ݒ�I�𒆂Ȃ�
		x = five_x;    //�ݒ�̍��W���i�[
		break;
	}
	DrawString(x, one_y+404, "��", GetColor(255, 255, 255));
	DrawFormatString(0, 0, GetColor(255, 255, 255), "����%d", num);
}