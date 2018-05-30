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
	mNextScene(eScene_None) //次のシーン管理変数
{
	mScene = (BaseScene*) new Menu(this);
}

//初期化
void SceneMgr::Initialize() {
	mScene->Initialize();
}

//終了処理
void SceneMgr::Finalize() {
	mScene->Finalize();
}

//更新
void SceneMgr::Update() {
	if (mNextScene != eScene_None) {    //次のシーンがセットされていたら
		mScene->Finalize();//現在のシーンの終了処理を実行
		delete mScene;
		switch (mNextScene) {       //シーンによって処理を分岐
		case eScene_Menu:        //次の画面がメニューなら
			mScene = (BaseScene*) new Menu(this);   //メニュー画面のインスタンスを生成する
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
		mNextScene = eScene_None;    //次のシーン情報をクリア

		mScene->Initialize();    //シーンを初期化
	}

	mScene->Update(); //シーンの更新
}

//描画
void SceneMgr::Draw() {
	mScene->Draw(); //シーンの描画
}

// 引数 nextScene にシーンを変更する
void SceneMgr::ChangeScene(eScene NextScene) {
	mNextScene = NextScene;    //次のシーンをセットする
}