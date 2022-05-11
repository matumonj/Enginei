#include "StageSelect.h"
#include"PlayScene.h"
#include"Tutorial.h"
#include"TitleScene.h"
#include"DesertField.h"
#include"SceneManager.h"
#include"Destroy.h"
#include"mHelper.h"
#include"Fader.h"
//�R�����g�A�E�g
#define PI 360.0

//�V�[���̃R���X�g���N�^
StageSelect::StageSelect(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}

#pragma region �X�v���C�g�̐���
//�X�v���C�g����
void StageSelect::SpriteCreate()
{

}
#pragma endregion

#pragma region 
void StageSelect::ModelCreate()
{
	SelectStageModel = Model::CreateFromOBJ("selectfield");
	SelectStageObj = Object3d::Create();
	SelectStageObj->SetModel(SelectStageModel);
	SelectStageObj->Initialize();
	SelectStageObj->SetPosition({ 0,0,0 });
	SelectStageObj->SetScale({ 8,8,8 });
	obj_Rot = { 0,0,0 };

	// ���C�g����
	lightGroup = LightGroup::Create();
	// 3D�I�u�G�N�g�Ƀ��C�g���Z�b�g
	Object3d::SetLightGroup(lightGroup);
	//�p�����[�^�̐ݒ�
	lightGroup->SetDirLightActive(0, false);
	lightGroup->SetDirLightActive(1, false);
	lightGroup->SetDirLightActive(2, false);
	lightGroup->SetPointLightActive(0, true);
	lightGroup->SetPointLightActive(0, false);
	lightGroup->SetPointLightActive(1, false);
	lightGroup->SetPointLightActive(2, false);
	lightGroup->SetSpotLightActive(0, true);

}
#pragma endregion

#pragma region ������
void StageSelect::Initialize(DirectXCommon* dxCommon)
{

	SpriteCreate();//
	ModelCreate();//

	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height/*input*/);
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);

}
#pragma endregion

#pragma region �X�V����
void StageSelect::Update(DirectXCommon* dxCommon)
{

	LONG u_r = 32768;
	LONG a = 30000;

	//�J�����֌W�̏���
	camera->SetEye({ SelectStageObj->GetPosition().x,SelectStageObj->GetPosition().y + 8,SelectStageObj->GetPosition().z - 30 });
	camera->SetTarget(SelectStageObj->GetPosition());

	camera->Update();

	{//���C�g�̃p�����[�^�𔽉f 	

		lightGroup->SetSpotLightDir(0, XMVECTOR({ spotLightDir[0],spotLightDir[1],spotLightDir[2],0 }));
		lightGroup->SetSpotLightPos(0, XMFLOAT3(spotLightpos));

		lightGroup->SetSpotLightColor(0, XMFLOAT3(spotLightColor));
		lightGroup->SetSpotLightAtten(0, XMFLOAT3(spotLightAtten));
		lightGroup->SetSpotLightFactorAngle(0, XMFLOAT2(spotLightFactorAngle));
	}
	lightGroup->Update();
	SelectStageObj->SetRotation(obj_Rot);
	SelectStageObj->Update({ 1,1,1,1 });
	SelectMove();
	Select();
	//�V�[���`�F���W
//	if (Input::GetInstance()->TriggerKey(DIK_R) || (Player_Pos.y <= -50)) {//�����ꂽ��
	//	BaseScene* scene = new DesertField(sceneManager_);//���̃V�[���̃C���X�^���X����
		//sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
		//delete scene;
	//}
}
#pragma endregion 

//s�v���C�ƈȊO�̕`��
void StageSelect::MyGameDraw(DirectXCommon* dxcomn)
{

	Sprite::PreDraw(dxcomn->GetCmdList());
	//background->Draw();
	//setumei->Draw();
	dxcomn->ClearDepthBuffer(dxcomn->GetCmdList());
	Sprite::PostDraw(dxcomn->GetCmdList());

	SelectStageObj->PreDraw();
	SelectStageObj->Draw();
	SelectStageObj->PostDraw();
}
#pragma endregion
//���ɓ���
#pragma region
void StageSelect::Draw(DirectXCommon* dxcomn)
{

	dxcomn->BeginDraw();
	MyGameDraw(dxcomn);
	ImGuiDraw();
	dxcomn->EndDraw();
}
#pragma endregion

void StageSelect::ImGuiDraw()
{
	ImGui::Begin("Obj1");
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(500, 300));
	if (ImGui::TreeNode("light_position")) {
		if (ImGui::Button("spotlight ON")) {
			lightGroup->SetSpotLightActive(0, true);
		}
		if (ImGui::Button("spotlight OFF")) {
			lightGroup->SetSpotLightActive(0, false);
		}
		float x = spotLightpos[1];
		ImGui::SliderFloat("x", &obj_Rot.y, -300, 300);
		ImGui::SliderFloat("y", &spotLightpos[1], -300, 300);
		ImGui::SliderFloat("z", &spotLightpos[2], -300, 300);
		ImGui::ColorPicker3("light_color", spotLightColor);
		ImGui::TreePop();
	}

	ImGui::End();

}
#pragma region �������
void StageSelect::Finalize()
{
	//delete sceneManager_;

	//delete efk,efk1;

}
#pragma endregion

void StageSelect::Select()
{
	NowSelectStage = selectStage[SelectNum];

	if (Selectflag != true&& Input::GetInstance()->TriggerButtonA()) {
		switch (NowSelectStage)
		{
		case TutorialStage:
			if (Input::GetInstance()->TriggerButtonA()) {//�����ꂽ��
				BaseScene* scene = new Tutorial(sceneManager_);//���̃V�[���̃C���X�^���X����
				sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
			}
			break;
		case Stage1_1:
			if (Input::GetInstance()->TriggerButtonA()) {//�����ꂽ��
				BaseScene* scene = new PlayScene(sceneManager_);//���̃V�[���̃C���X�^���X����
				sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
			}
			break;
		case Stage1_2:
			if (Input::GetInstance()->TriggerButtonA()) {//�����ꂽ��
				BaseScene* scene = new TitleScene(sceneManager_);//���̃V�[���̃C���X�^���X����
				sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
			}
			break;
		case Stage2_1:
			break;
		case Stage2_2:
			break;
		default:
			break;
		}
	}
}

void StageSelect::SelectMove()
{
	if (Selectflag) {
		time += 0.02f;
		obj_Rot.y = Easing::EaseOut(time, RotNow, Rotnext);
		if (obj_Rot.y >= Rotnext - 1) {
			Selectflag = false;
		}
	} else {
		time = 0.0f;
		RotNow = obj_Rot.y;
		Rotnext = obj_Rot.y + (PI/StageTotalAmount);
		if (Input::GetInstance()->TriggerButtonRB())
		{
			Selectflag = true;
			SelectNum++;
		}
	}
}