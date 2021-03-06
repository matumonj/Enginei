#include "GamOver.h"
#include"Input.h"
#include"PlayScene.h"
#include"DesertField.h"
#include"Tutorial.h"
#include"TitleScene.h"
#include"SceneManager.h"
#include"imgui.h"
#include"Helper.h"
#include"BossScene3.h"
#include"Retry.h"
#include"ForestStage1.h"
#include"ForestStage2.h"
#include"SeaScene1.h"
#include"BossScene2.h"
#include"Fader.h"
#include"LastBossScene.h"
#include"LastStage.h"
GamOver::GamOver(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{
}


/// <summary>
/// 初期化
/// </summary>
void GamOver::Initialize(DirectXCommon* dxCommon)
{
	titlesprite->LoadTexture(3, L"Resources/gameover.png");
	titlesprite = Sprite::Create(3, { 0.0f,0.0f });
	Fader::SetFeedSprite();
}

/// <summary>
/// 更新処理
/// </summary>
void GamOver::Update(DirectXCommon* dxCommon)
{
	if (Input::GetInstance()->TriggerButtonA()) {//押されたら
		faderflag = true;
		loadf=true;
	}
	if (faderflag) {
		Fader::feedIn(1.0f, 0.1f);
	}

	if (Fader::GetInstance()->GetAlpha() >= 1.0f) {
		if (Retry::getStage() == Sea_1_1) {
			BaseScene* scene = new SeaScene1(sceneManager_);//次のシーンのインスタンス生成
			sceneManager_->SetnextScene(scene);//シーンのセット
		}
		if (Retry::getStage() == Sea_1_2) {
			BaseScene* scene = new BossScene3(sceneManager_);//次のシーンのインスタンス生成
			sceneManager_->SetnextScene(scene);//シーンのセット
		}
		if (Retry::getStage() == Sea_1_3) {
			BaseScene* scene = new BossScene3(sceneManager_);//次のシーンのインスタンス生成
			sceneManager_->SetnextScene(scene);//シーンのセット
		}
		if (Retry::getStage() == Jungle_1_1) {
			BaseScene* scene = new ForestStage1(sceneManager_);//次のシーンのインスタンス生成
			sceneManager_->SetnextScene(scene);//シーンのセット
		}
		if (Retry::getStage() == Jungle_1_2) {
			BaseScene* scene = new ForestStage2(sceneManager_);//次のシーンのインスタンス生成
			sceneManager_->SetnextScene(scene);//シーンのセット
		}
		if (Retry::getStage() == Jungle_1_3) {
			BaseScene* scene = new BossScene2(sceneManager_);//次のシーンのインスタンス生成
			sceneManager_->SetnextScene(scene);//シーンのセット

		}
		if (Retry::getStage() == Cas_1_1) {
			BaseScene* scene = new LastStage(sceneManager_);//次のシーンのインスタンス生成
			sceneManager_->SetnextScene(scene);//シーンのセット
		}
		if (Retry::getStage() == Cas_1_2) {
			BaseScene* scene = new LastBossScene(sceneManager_);//次のシーンのインスタンス生成
			sceneManager_->SetnextScene(scene);//シーンのセット

		}
	}
	//ENTERで次のシーンへ
	if (Input::GetInstance()->TriggerButtonB()) {//押されたら
		BaseScene* scene = new StageSelect(sceneManager_);//次のシーンのインスタンス生成
		sceneManager_->SetnextScene(scene);//シーンのセット
	}
	//if (Input::GetInstance()->TriggerKey(DIK_F))
	//{
	//	feedflag = true;
	//}
	//if (Input::GetInstance()->TriggerKey(DIK_I))
	//{
	//	feedinflag = true;
	//}
	//if (Input::GetInstance()->TriggerKey(DIK_T))
	//{
	//	feedd = true;
	//}

	//if (feedinflag) {
	//	Helper::feedIn(alpha,1);
	//	if (alpha >= 1.0f) {
	//		feedinflag = false;
	//	}
	//}
	//if (feedflag) {
	//	Helper::feedInOut_f(alpha,1,0,feedd);
	//	if (alpha <=0.0f) {
	//		feedflag = false;
	//	}
	//}
	//
	//Helper::Update(alpha);
	alpha = min(alpha, 1.1f);
	alpha = max(alpha, 0.0f);
	Fader::FeedSpriteUpdate();
	titlesprite->setcolor({ 1,1,1,alpha });
	//titlesprite->SpriteUpdate();
	GameUI::NowLoadUpdate(loadf);

	titlesprite->SetSize({ WinApp::window_width,WinApp::window_height });
}

/// <summary>
/// スプライト描画
/// </summary>
/// <param name="cmdList"></param>
void GamOver::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{
	Sprite::PreDraw(cmdList);
	titlesprite->Draw();
	Fader::FeedSpriteDraw();
	Sprite::PostDraw(cmdList);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="cmdList"></param>
void GamOver::Draw(DirectXCommon* dxcomn)
{
	//ポストエフェクトの描画
	dxcomn->BeginDraw();//描画コマンドの上らへんに
	SpriteDraw(dxcomn->GetCmdList());
	GameUI::NowLoadDraw(dxcomn);
	/*ImGui::Begin("Obj1");
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(500, 300));
	if (ImGui::TreeNode("cameraposition")) {
		ImGui::SliderFloat("cy", &alpha, 200, -200);
		ImGui::TreePop();
	}
	ImGui::End();*/
	dxcomn->EndDraw();

}
void GamOver::Finalize()
{
	//delete postEffect;
	delete titlesprite;
}

