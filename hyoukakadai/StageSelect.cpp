#include "StageSelect.h"
#include"PlayScene.h"
#include"Tutorial.h"
#include"TitleScene.h"
#include"DesertField.h"
#include"SceneManager.h"
#include"Destroy.h"
#include"ForestStage1.h"
#include"ForestStage2.h"
#include"FirstBossScene.h"
#include"BossScene2.h"
#include"mHelper.h"
#include"imgui.h"
#include"Fader.h"

//�R�����g�A�E�g
#define PI 360.0f

//�V�[���̃R���X�g���N�^
StageSelect::StageSelect(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}

#pragma region �X�v���C�g�̐���
//�X�v���C�g����
void StageSelect::SpriteCreate()
{
	GameUI::NowLoadSet();
	//����
	Sprite::LoadTexture(100, L"Resources/Stage1-1.png");
	Sprite::LoadTexture(101, L"Resources/Stage1-1.png");
	Sprite::LoadTexture(102, L"Resources/Stage1-1.png");
	Sprite::LoadTexture(103, L"Resources/Stage1-1.png");
	Sprite::LoadTexture(104, L"Resources/Stage1-1.png");
	Sprite::LoadTexture(105, L"Resources/Stage1-1.png");
	Sprite::LoadTexture(106, L"Resources/targetSprite.png");

	StageSprite[0] = Sprite::Create(100, { 200,0 });
	StageSprite[1] = Sprite::Create(101, { 200,0 });
	StageSprite[2] = Sprite::Create(102, { 200,0 });
	StageSprite[3] = Sprite::Create(103, { 200,0 });
	StageSprite[4] = Sprite::Create(104, { 200,0 });
	StageSprite[5] = Sprite::Create(105, { 200,0 });
	TargetSprite= Sprite::Create(106, { 200,0 });
	
	SpritePosition[0] = { 480,480 };
	SpritePosition[1] = { 960,480 };
	SpritePosition[2] = { 1440,480 };
	SpriteScale[0] = { 0,0 };
	SpriteScale[1] = { 0,0 };
	SpriteScale[2] = { 0,0 };
}
#pragma endregion

#pragma region 
void StageSelect::ModelCreate()
{
	SelectStageModel = Model::CreateFromOBJ("stageselect");
	SelectStageObj = Object3d::Create();
	SelectStageObj->SetModel(SelectStageModel);
	DomeModel = Model::CreateFromOBJ("skydome");
	Skydome = Object3d::Create();
	Skydome->SetModel(DomeModel);
	SelectStageObj->Initialize();
	Skydome->Initialize();
	Skydome->SetPosition({ 0,0,0 });
	SelectStageObj->SetPosition({ 0,0,0 });
	SelectStageObj->SetScale({ 8,8,8 });
	obj_Rot = { 0,0,0 };
	for (int i = 0; i < 6; i++) {
		StageSprite[i]->SetAnchorPoint({ 0.5,0.5 });
		StageSprite[i]->SetPosition({ -300,-300 });
	}
	TargetSprite->SetAnchorPoint({ 0.5,0.5 });
	TargetSprite->SetPosition({ -300,-300 });
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

	Fader::SetFeedSprite();
}
#pragma endregion

#pragma region ������
void StageSelect::Initialize(DirectXCommon* dxCommon)
{
	nextScene = false;
	SpriteCreate();//
	ModelCreate();//

	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height/*input*/);
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);
	for (int i = 0; i < 3; i++) {
		TargetSpritePos[i] = SpritePosition[i];
	}
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
	Rot_y+=0.3f;
	Skydome->SetRotation({ 0,Rot_y,0 });
	Skydome->SetScale({ 0.5,0.5,0.5});
	Skydome->Update({ 1,1,1,1 });
	SelectMove();
	Select();
	SpriteUpdate();
	Fader::FeedSpriteUpdate();
	GameUI::NowLoadUpdate(Loadf);
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

	Skydome->PreDraw();
	Skydome->Draw();
	Skydome->PostDraw();
}
#pragma endregion
//���ɓ���
#pragma region
void StageSelect::Draw(DirectXCommon* dxcomn)
{

	dxcomn->BeginDraw();
	MyGameDraw(dxcomn);
	Sprite::PreDraw(dxcomn->GetCmdList());
	TargetSprite->Draw();
	Fader::FeedSpriteDraw();
	for (int i = 0; i < 6; i++) {
		StageSprite[i]->Draw();
	}
	Sprite::PostDraw(dxcomn->GetCmdList());

	GameUI::NowLoadDraw(dxcomn);
	ImGuiDraw();
	dxcomn->EndDraw();
}
#pragma endregion

void StageSelect::ImGuiDraw()
{
	/*ImGui::Begin("Obj1");
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
		ImGui::SliderInt("z", &SelectNum, -300, 300);
		ImGui::ColorPicker3("light_color", spotLightColor);
		ImGui::TreePop();
	}

	ImGui::End();*/

}
#pragma region �������
void StageSelect::Finalize()
{
	//delete sceneManager_;
	delete camera;
	delete SelectStageModel, SelectStageObj;
	for (int i = 0; i < 6; i++) {
		delete StageSprite[i];
	}
	delete TargetSprite;
	//delete efk,efk1;

}
#pragma endregion

void StageSelect::Select()
{
	NowSelectStage = selectStage[SelectNum];
		if (Selectflag_right != true && Selectflag_left != true && stageSpriteScene == None) {
			switch (NowSelectStage)
			{
			case TutorialStage:
				if (Input::GetInstance()->TriggerButtonA()) {//�����ꂽ��
					nextScene = true;
				}
				if (nextScene) {
					stageSpriteScene = Jungle;
					
				}
				break;
			case Stage1_1:
				if (Input::GetInstance()->TriggerButtonA()) {//�����ꂽ��
					nextScene = true;
				}
				if (nextScene) {
					stageSpriteScene = Sea;
					
				}
				break;
			case Stage1_2:
				if (Input::GetInstance()->TriggerButtonA()) {//�����ꂽ��
					BaseScene* scene = new TitleScene(sceneManager_);//���̃V�[���̃C���X�^���X����
					sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
				}
				break;
			case Stage2_1:
				if (Input::GetInstance()->TriggerButtonA()) {//�����ꂽ��
					BaseScene* scene = new FirstBossScene(sceneManager_);//���̃V�[���̃C���X�^���X����
					sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
				}
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
	if (stageSpriteScene == None) {
		if (!Selectflag_left) {
			if (Selectflag_right) {
				time += 0.02f;
				obj_Rot.y = Easing::EaseOut(time, RotNow, Rotnext);
				if (obj_Rot.y >= Rotnext - 1) {
					Selectflag_right = false;
				}
			} else {
				time = 0.0f;
				RotNow = obj_Rot.y;
				Rotnext = obj_Rot.y + (PI / StageTotalAmount);
				if (Input::GetInstance()->TriggerButtonRB())
				{
					Selectflag_right = true;
					SelectNum++;
				}
			}
		}
	//
		if (!Selectflag_right) {
			if (Selectflag_left) {
				time += 0.02f;
				obj_Rot.y = Easing::EaseOut(time, RotNow, Rotnext);
				if (obj_Rot.y <= Rotnext + 1) {
					Selectflag_left = false;
				}
			} else {
				time = 0.0f;
				RotNow = obj_Rot.y;
				Rotnext = obj_Rot.y - (PI / StageTotalAmount);
				if (Input::GetInstance()->TriggerButtonLB())
				{
					Selectflag_left = true;
					SelectNum--;
				}
			}
		}
	}
	const int MinStage = -1;
	const int MaxStage = 5;
	obj_Rot.y = max(obj_Rot.y, 0);
	obj_Rot.y = min(obj_Rot.y, 360);
	SelectNum = max(SelectNum, 0);
	SelectNum = min(SelectNum, 4);
}

void StageSelect::SpriteUpdate()
{
		switch (stageSpriteScene)
		{
		case Jungle:
			nextScene = false;
			Fader::feedIn(0.5f, 1);
			stime += 0.01f;
			for (int i = 0; i < 3; i++) {
				SpriteScale[i].x = Easing::EaseOut(stime, SpriteScale[i].x, 300);
				SpriteScale[i].y = Easing::EaseOut(stime, SpriteScale[i].y, 300);

				StageSprite[i]->SetPosition(SpritePosition[i]);
				StageSprite[i]->SetSize(SpriteScale[i]);
			}
			if (Input::GetInstance()->TriggerButtonB()) {
				stime = 0;
				stageSpriteScene =Stay;
			}
			SelectStageofStage();
			//
			if (SpriteScale[0].x>=300&&Input::GetInstance()->TriggerButtonA()) {//�����ꂽ��
				if (TargetNum == 0) {
					Loadf = true;
				J_stagechanges[0] = true;
				}
				else if (TargetNum == 1) {
					Loadf = true;
					J_stagechanges[1] = true;
				}
				else if (TargetNum == 2) {
					Loadf = true;
					J_stagechanges[2] = true;
				}
			}
			if (J_stagechanges[0]== true) {
				Fader::feedIn(1.0f, 0.1f);
				if (Fader::GetInstance()->GetAlpha() >= 0.99) {
					BaseScene* scene = new ForestStage1(sceneManager_);//���̃V�[���̃C���X�^���X����
					sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
				}
			}
			else if (J_stagechanges[1] == true) {
				Fader::feedIn(1.0f, 0.1f);
				if (Fader::GetInstance()->GetAlpha() >= 0.99) {
					BaseScene* scene = new ForestStage2(sceneManager_);//���̃V�[���̃C���X�^���X����
					sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
				}
			}
			else if (J_stagechanges[2] == true) {
				Fader::feedIn(1.0f, 0.1f);
				if (Fader::GetInstance()->GetAlpha() >= 0.99) {
					BaseScene* scene = new BossScene2(sceneManager_);//���̃V�[���̃C���X�^���X����
					sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
				}
			}
			break;
		case Sea:
			nextScene = false;
			Fader::feedIn(0.5f, 1);
			stime += 0.01f;
			for (int i = 0; i < 3; i++) {
				SpriteScale[i].x = Easing::EaseOut(stime, SpriteScale[i].x, 300);
				SpriteScale[i].y = Easing::EaseOut(stime, SpriteScale[i].y, 300);
				for (int j = 3; j < 6; j++) {
					

					StageSprite[3]->SetPosition(SpritePosition[0]);
					StageSprite[4]->SetPosition(SpritePosition[1]);
					StageSprite[5]->SetPosition(SpritePosition[2]);//StageSprite[j]->SetPosition(SpritePosition[i]);
					StageSprite[j]->SetSize(SpriteScale[i]);
				}
			}
			if (Input::GetInstance()->TriggerButtonB()) {
				stime = 0;
				stageSpriteScene = Stay;
			}
			SelectStageofStage();
			break;
		case Stay:
			Fader::feedOut(0.0f, 0.1f);
			if (Fader::GetInstance()->GetAlpha() <= 0.0f) {
				stageSpriteScene = None;
			}
			stime += 0.01f;
			for (int i = 0; i < 3; i++) {
				if (SpriteScale[i].x >= 0) {
					SpriteScale[i].x = Easing::EaseOut(stime, SpriteScale[i].x, 0);
				}
				if (SpriteScale[i].y >= 0) {
					SpriteScale[i].y = Easing::EaseOut(stime, SpriteScale[i].y, 0);
				}
			}
			for (int i = 0; i < 3; i++) {
				StageSprite[i]->SetPosition(SpritePosition[i]);
					StageSprite[i]->SetSize(SpriteScale[i]);
			}
			for (int i = 3; i < 6; i++) {
				for (int j = 0; j < 3; j++) {
					StageSprite[i]->SetPosition(SpritePosition[j]);
					StageSprite[i]->SetSize(SpriteScale[j]);
				}
			}
			TargetSprite->SetSize({ 0,0 });

			break;
		case None:
			stime = 0;
			break;
		default:
			
			break;
		}

	}


void StageSelect::SelectStageofStage()
{
	if (Input::GetInstance()->TriggerButtonRB()) {//�����ꂽ��
		TargetNum++;
	}
	else if (Input::GetInstance()->TriggerButtonLB()) {
		TargetNum--;
	}
	TargetNum = max(TargetNum, 0);
	TargetNum = min(TargetNum, 3);
	TargetSprite->SetPosition(TargetSpritePos[TargetNum]);
	TargetSprite->SetSize({ 300,300 });
}