#include "DxLib.h"
#include "SceneMgr.h"

#define SCREEN_SIZE_X			(1920)
#define SCREEN_SIZE_Y			(1080)

int Handle;
int w = 1920, h = 1080;
int card[55];
bool kakumei=0;
int UseCard2[15] = { 0 };

void init()
{
	ChangeWindowMode(1);
	SetWindowSizeChangeEnableFlag(TRUE);
	SetGraphMode(1920, 1080, 32);
	SetWindowStyleMode(4);
	SetWindowPosition(0, 0);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	SetGraphMode(w, h, 16);
	SetMainWindowText("��x��");                       //�E�C���h�E�̃^�C�g����ύX����
	SetWindowSizeChangeEnableFlag(TRUE);			   //�E�C���h�E���[�h�̎��ɃE�C���h�E�̃T�C�Y�����R�ɕύX�o����悤�ɂ��邩�ǂ�����ݒ肷��
	SetWindowSizeExtendRate(1);                        //�E�C���h�E���[�h�̎��̃E�C���h�E�̑傫���ƕ`���ʂ̑傫���̔䗦��ݒ肷��
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
	init(); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
	SetBackgroundColor(50, 50, 255);
	Handle = LoadDivGraph("card.jpg", 55, 13, 5, 200, 300, card);     //147,220
	SceneMgr sceneMgr;
	sceneMgr.Initialize();
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		SetFontSize(64);
		Keyboard_Update();    //�L�[�{�[�h�̍X�V
		sceneMgr.Update();  //�X�V
		sceneMgr.Draw();    //�`��
	}
	sceneMgr.Finalize();

	DxLib_End(); // DX���C�u�����I������
	return 0;
}