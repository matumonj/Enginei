#include "ClearScene.h"
#include"Input.h"
#include"PlayScene.h"
#include"Tutorial.h"
#include"SceneManager.h"
#include"imgui.h"
#include"Helper.h"

ClearScene::ClearScene(SceneManager* sceneManager):BaseScene(sceneManager)
{
}

void ClearScene::Initialize(DirectXCommon* dxCommon)
{
	clearsprite->LoadTexture(3, L"Resources/background.png");
	clearsprite = Sprite::Create(3, { 0.0f,0.0f });
}

void ClearScene::Update(DirectXCommon* dxCommon)
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

	clearsprite->setcolor({ 1,1,1,alpha });
	//titlesprite->SpriteUpdate()
	clearsprite->SetSize({ WinApp::window_width,WinApp::window_height });
}

void ClearScene::Draw(DirectXCommon* dxcomn)
{
	//�|�X�g�G�t�F�N�g�̕`��
	dxcomn->BeginDraw();//�`��R�}���h�̏��ւ��
	SpriteDraw(dxcomn->GetCmdList());

	dxcomn->EndDraw();

}

void ClearScene::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{
	Sprite::PreDraw(cmdList);
	clearsprite->Draw();
	Sprite::PostDraw(cmdList);
}

void ClearScene::Finalize()
{
	delete clearsprite;
}
