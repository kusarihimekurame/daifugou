#pragma once

typedef enum {
	eScene_Menu,    //���j���[���
	eScene_Game,    //�Q�[�����
	eScene_types,  
	eScene_cards,
	eScene_Decision,
	eScene_Turn,
	eScene_types2,
	eScene_cards2,
	eScene_Decision2,
	eScene_End,

	eScene_None,    //����
} eScene;

//�V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
class ISceneChanger {
public:
	virtual ~ISceneChanger() = 0;
	virtual void ChangeScene(eScene NextScene) = 0;//�w��V�[���ɕύX����
}; 
