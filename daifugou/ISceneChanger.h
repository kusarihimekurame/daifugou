#pragma once

typedef enum {
	eScene_Menu,    //メニュー画面
	eScene_Game,    //ゲーム画面
	eScene_types,  
	eScene_cards,
	eScene_Decision,
	eScene_Turn,
	eScene_types2,
	eScene_cards2,
	eScene_Decision2,
	eScene_End,

	eScene_None,    //無し
} eScene;

//シーンを変更するためのインターフェイスクラス
class ISceneChanger {
public:
	virtual ~ISceneChanger() = 0;
	virtual void ChangeScene(eScene NextScene) = 0;//指定シーンに変更する
}; 
