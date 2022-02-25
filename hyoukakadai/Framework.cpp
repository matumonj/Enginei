#include "Framework.h"

void Framework::Run()
{
	Initialize(dxcomn);

	while (true) {
		//ウィンドウメッセージ処理
		Update(dxcomn);
		Draw(dxcomn);
	}
}
/// <summary>
/// 初期化
/// </summary>
void Framework::Initialize(DirectXCommon* dxCommon)
{
	//共通部分のインスタンス生成と初期化
	winapp = new WinApp();
	winapp->Createwindow();
	dxcomn = new DirectXCommon();
	dxcomn->Initialize(winapp);
	input = Input::GetInstance();
	input->Initialize(winapp);
	audio = new Audio();
	
	// ライト静的初期化
	Object3d::StaticInitialize(dxcomn->GetDev(),dxcomn->GetCmdList(), WinApp::window_width, WinApp::window_height);
	//MyGame* MyGame = new MyGame();
	sceneManger = new SceneManager();
}

/// <summary>
/// 更新
/// </summary>
void Framework::Update(DirectXCommon* dxCommon)
{
	if (winapp->Processmassage()) {
		winRequest = true;
		return;
	}
	input->update();
	sceneManger->Update(dxCommon);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="cmdList"></param>
void Framework::Draw(DirectXCommon* dxcomn)
{
	sceneManger->Draw(dxcomn);
}

void Framework::Finalize()
{
	FbxLoader::GetInstance()->Finalize();
	delete sceneManger;
	delete audio;
	delete dxcomn;
	delete input;
	delete winapp;
}