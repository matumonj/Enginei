#include "TitleScene.h"
#include"Input.h"
#include"PlayScene.h"
#include"Tutorial.h"
#include"SceneManager.h"


TitleScene::TitleScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}
/// <summary>
/// 初期化
/// </summary>
void TitleScene::Initialize(DirectXCommon* dxCommon)
{
	Sprite::LoadTexture(3, L"Resources/background.png");
	titlesprite = Sprite::Create(3, { 0.0f,0.0f });
}

/// <summary>
/// 更新処理
/// </summary>
void TitleScene::Update(DirectXCommon* dxCommon)
{
	//ENTERで次のシーンへ
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {//押されたら
		BaseScene* scene = new Tutorial(sceneManager_);//次のシーンのインスタンス生成
		sceneManager_->SetnextScene(scene);//シーンのセット
	}
	if (Input::GetInstance()->TriggerKey(DIK_F))
	{
		feedflag = true;
	}
	if (feedflag) {
		Helper::feedOut(alpha);
		if (Helper::GetFeedState_End() == true) {
			feedflag = false;
		}
	}
	Helper::Update(alpha);
	titlesprite->setcolor({ 1,1,1,alpha });
	//titlesprite->SpriteUpdate()
	titlesprite->SetSize({ WinApp::window_width,WinApp::window_height });
}

/// <summary>
/// スプライト描画
/// </summary>
/// <param name="cmdList"></param>
void TitleScene::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{
	Sprite::PreDraw(cmdList);
	titlesprite->Draw();
	Sprite::PostDraw(cmdList);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="cmdList"></param>
void TitleScene::Draw(DirectXCommon* dxcomn)
{	
	//ポストエフェクトの描画
	dxcomn->BeginDraw();//描画コマンドの上らへんに
	SpriteDraw(dxcomn->GetCmdList());
	dxcomn->EndDraw();

}
void TitleScene::Finalize()
{
	//delete postEffect;
	delete titlesprite;
}