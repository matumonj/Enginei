#include "TitleScene.h"
#include"Input.h"
#include"PlayScene.h"
#include"StageSelect.h"
#include"DesertField.h"
#include"Tutorial.h"
#include"SceneManager.h"
#include"imgui.h"
#include"Helper.h"
#include"Fader.h"
TitleScene::TitleScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}
/// <summary>
/// 初期化
/// </summary>
void TitleScene::Initialize(DirectXCommon* dxCommon)
{
	titlesprite->LoadTexture(3, L"Resources/title.png");
	titlesprite = Sprite::Create(3, { 0.0f,0.0f });

	//モデル名を指定してファイル読み込み
	playermodel = FbxLoader::GetInstance()->LoadModelFromFile("titleanim");

	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height/*input*/);

	//デバイスをセット
	f_Object3d::SetDevice(dxCommon->GetDev());
	//カメラをセット
	f_Object3d::SetCamera(camera);
	//グラフィックパイプライン生成
	f_Object3d::CreateGraphicsPipeline();

	//FBXモデルの生成
	player = new f_Object3d();
	player->Initialize(dxCommon, camera);
	player ->SetModel(playermodel);
	
	player->SetRotation(Player_Rot);
	player->PlayAnimation();
}

/// <summary>
/// 更新処理
/// </summary>
void TitleScene::Update(DirectXCommon* dxCommon)
{
	player->SetPosition(Player_Pos);
	
	//ENTERで次のシーンへ
	if (Input::GetInstance()->TriggerButtonA()) {//押されたら
		Fader::feedIn(1.0,0.05f);
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

	player->Updata({ 1,1,1,1 }, dxCommon, camera, TRUE);
	alpha = min(alpha, 1.1f);
	alpha = max(alpha, 0.0f);
	//Fader::FeedSpriteUpdate();
	titlesprite->setcolor({ 1,1,1,alpha });
	//titlesprite->SpriteUpdate()
	titlesprite->SetSize({ WinApp::window_width,WinApp::window_height });

	camera->SetDistance(distance);//
	camera->SetEye({ Player_Pos.x,Player_Pos.y+5,Player_Pos.z-10});
	camera->SetTarget({ Player_Pos.x,Player_Pos.y+5 ,Player_Pos.z });

	camera->Update();



}

/// <summary>
/// スプライト描画
/// </summary>
/// <param name="cmdList"></param>
void TitleScene::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{


}

/// <summary>
/// 描画
/// </summary>
/// <param name="cmdList"></param>
void TitleScene::Draw(DirectXCommon* dxcomn)
{	

	//ポストエフェクトの描画
	dxcomn->BeginDraw();//描画コマンドの上らへんに
	Sprite::PreDraw(dxcomn->GetCmdList());
	titlesprite->Draw();
	//Fader::FeedSpriteDraw();
	dxcomn->ClearDepthBuffer(dxcomn->GetCmdList());
	Sprite::PostDraw(dxcomn->GetCmdList());
	SpriteDraw(dxcomn->GetCmdList());
	//FBXの描画
	player->Draw(dxcomn->GetCmdList());
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
void TitleScene::Finalize()
{
	//delete postEffect;
	delete titlesprite;
}