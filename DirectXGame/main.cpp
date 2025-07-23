#include <Windows.h>
#include <KamataEngine.h>

#include "GameScene.h"

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	// KamataEngineの初期化
	KamataEngine::Initialize(L"LE3C_14_タカキ_ケンゴ");

	// DirectXCommonのインスタンス生成
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// GameSceneのインスタンス取得、初期化
	GameScene* gameScene = new GameScene();
	gameScene->Initialize();

	while (true) {
		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		//=============
		// 更新処理
		//=============

		// GameScene更新
		gameScene->Update();

		//=============
		/// 描画処理 
		//=============

		// 描画処理開始
		dxCommon->PreDraw();

		// GameScene描画
		gameScene->Draw();

		// 描画処理終了
		dxCommon->PostDraw();
	}

	// ゲームシーンの解放
	delete gameScene;
	gameScene = nullptr;

	// KamataEngineの終了
	KamataEngine::Finalize();

	return 0;
}
