#pragma once

#include "BaseScene.h"

//�ݒ��ʃN���X
class types2 : public BaseScene {

public:
	types2(ISceneChanger* changer);
	void Initialize() override;    //�������������I�[�o�[���C�h�B
								   //void Finalize() override;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

};