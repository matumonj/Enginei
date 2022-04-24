#include "TitleScene.h"
#include"Input.h"
#include"PlayScene.h"
#include"Tutorial.h"
#include"SceneManager.h"
#include"imgui.h"
#include"Helper.h"
TitleScene::TitleScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}
/// <summary>
/// ������
/// </summary>
void TitleScene::Initialize(DirectXCommon* dxCommon)
{
	Sprite::LoadTexture(3, L"Resources/background.png");
	titlesprite = Sprite::Create(3, { 0.0f,0.0f });
}

/// <summary>
/// �X�V����
/// </summary>
void TitleScene::Update(DirectXCommon* dxCommon)
{
	//ENTER�Ŏ��̃V�[����
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {//�����ꂽ��
		BaseScene* scene = new Tutorial(sceneManager_);//���̃V�[���̃C���X�^���X����
		sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
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

	titlesprite->setcolor({ 1,1,1,alpha });
	//titlesprite->SpriteUpdate()
	titlesprite->SetSize({ WinApp::window_width,WinApp::window_height });
}

/// <summary>
/// �X�v���C�g�`��
/// </summary>
/// <param name="cmdList"></param>
void TitleScene::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{
	Sprite::PreDraw(cmdList);
	titlesprite->Draw();
	Sprite::PostDraw(cmdList);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="cmdList"></param>
void TitleScene::Draw(DirectXCommon* dxcomn)
{	
	//�|�X�g�G�t�F�N�g�̕`��
	dxcomn->BeginDraw();//�`��R�}���h�̏��ւ��
	SpriteDraw(dxcomn->GetCmdList());

	ImGui::Begin("Obj1");
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(500, 300));
	if (ImGui::TreeNode("cameraposition")) {
		ImGui::SliderFloat("cy", &alpha, 100, -100);
		ImGui::TreePop();
	}
	ImGui::End();
	dxcomn->EndDraw();

}
void TitleScene::Finalize()
{
	//delete postEffect;
	delete titlesprite;
}