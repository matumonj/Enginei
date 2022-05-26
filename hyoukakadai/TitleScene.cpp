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
/// ������
/// </summary>
void TitleScene::Initialize(DirectXCommon* dxCommon)
{
	titlesprite->LoadTexture(3, L"Resources/title.png");
	titlesprite = Sprite::Create(3, { 0.0f,0.0f });

	//���f�������w�肵�ăt�@�C���ǂݍ���
	playermodel = FbxLoader::GetInstance()->LoadModelFromFile("titleanim");

	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height/*input*/);

	//�f�o�C�X���Z�b�g
	f_Object3d::SetDevice(dxCommon->GetDev());
	//�J�������Z�b�g
	f_Object3d::SetCamera(camera);
	//�O���t�B�b�N�p�C�v���C������
	f_Object3d::CreateGraphicsPipeline();

	//FBX���f���̐���
	player = new f_Object3d();
	player->Initialize(dxCommon, camera);
	player ->SetModel(playermodel);
	
	player->SetRotation(Player_Rot);
	player->PlayAnimation();
}

/// <summary>
/// �X�V����
/// </summary>
void TitleScene::Update(DirectXCommon* dxCommon)
{
	player->SetPosition(Player_Pos);
	
	//ENTER�Ŏ��̃V�[����
	if (Input::GetInstance()->TriggerButtonA()) {//�����ꂽ��
		Fader::feedIn(1.0,0.05f);
		BaseScene* scene = new StageSelect(sceneManager_);//���̃V�[���̃C���X�^���X����
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
/// �X�v���C�g�`��
/// </summary>
/// <param name="cmdList"></param>
void TitleScene::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{


}

/// <summary>
/// �`��
/// </summary>
/// <param name="cmdList"></param>
void TitleScene::Draw(DirectXCommon* dxcomn)
{	

	//�|�X�g�G�t�F�N�g�̕`��
	dxcomn->BeginDraw();//�`��R�}���h�̏��ւ��
	Sprite::PreDraw(dxcomn->GetCmdList());
	titlesprite->Draw();
	//Fader::FeedSpriteDraw();
	dxcomn->ClearDepthBuffer(dxcomn->GetCmdList());
	Sprite::PostDraw(dxcomn->GetCmdList());
	SpriteDraw(dxcomn->GetCmdList());
	//FBX�̕`��
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