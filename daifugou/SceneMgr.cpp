#include "DxLib.h"
#include "types.h"
#include "types2.h"
#include "cards.h"
#include "cards2.h"
#include "Decision.h"
#include "Decision2.h"
#include "Turn.h"
#include "Game.h"
#include "End.h"
#include "Menu.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr() :
	mNextScene(eScene_None) //���̃V�[���Ǘ��ϐ�
{
	mScene = (BaseScene*) new Menu(this);
}

//������
void SceneMgr::Initialize() {
	mScene->Initialize();
}

//�I������
void SceneMgr::Finalize() {
	mScene->Finalize();
}

//�X�V
void SceneMgr::Update() {
	if (mNextScene != eScene_None) {    //���̃V�[�����Z�b�g����Ă�����
		mScene->Finalize();//���݂̃V�[���̏I�����������s
		delete mScene;
		switch (mNextScene) {       //�V�[���ɂ���ď����𕪊�
		case eScene_Menu:        //���̉�ʂ����j���[�Ȃ�
			mScene = (BaseScene*) new Menu(this);   //���j���[��ʂ̃C���X�^���X�𐶐�����
			break;
		case eScene_Game:
			mScene = (BaseScene*) new Game(this);
			break;
		case eScene_types:
			mScene = (BaseScene*) new types(this);
			break;
		case eScene_cards:
			mScene = (BaseScene*) new cards(this);
			break;
		case eScene_Decision:
			mScene = (BaseScene*) new Decision(this);
			break;
		case eScene_Turn:
			mScene = (BaseScene*) new Turn(this);
			break;
		case eScene_types2:
			mScene = (BaseScene*) new types2(this);
			break;
		case eScene_cards2:
			mScene = (BaseScene*) new cards2(this);
			break;
		case eScene_Decision2:
			mScene = (BaseScene*) new Decision2(this);
			break;
		case eScene_End:
			mScene = (BaseScene*) new End(this);
			break;
		}
		mNextScene = eScene_None;    //���̃V�[�������N���A

		mScene->Initialize();    //�V�[����������
	}

	mScene->Update(); //�V�[���̍X�V
}

//�`��
void SceneMgr::Draw() {
	mScene->Draw(); //�V�[���̕`��
}

// ���� nextScene �ɃV�[����ύX����
void SceneMgr::ChangeScene(eScene NextScene) {
	mNextScene = NextScene;    //���̃V�[�����Z�b�g����
}