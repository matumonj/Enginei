#include "Tutorial.h"
#include"Input.h"
#include"DirectXCommon.h"
#include"PlayScene.h"
#include"SceneManager.h"
#include"MobEnemy.h"
#include"BossEnemy.h"
#include"ThrowEnemy.h"
#include"Line.h"
#include"Destroy.h"
#include"Fader.h"
//�R�����g�A�E�g
//�V�[���̃R���X�g���N�^
Tutorial::Tutorial(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}

#pragma region �X�v���C�g�̐���
//�X�v���C�g����
void Tutorial::SpriteCreate()
{
	//���ʂ̃e�N�X�`��(�X�v���C�g����Ȃ���)
	Line::Initialize();
	GameUI::AllowUISet();
	Texture::LoadTexture(6, L"Resources/gomi.png");
}
#pragma endregion

#pragma region 
void Tutorial::ModelCreate()
{
	//feed = new Fader();
	playermodel = Model::CreateFromOBJ("player");
	player = Player::Create(playermodel);
	player->Initialize();
	tstmodel = Model::CreateFromOBJ("tutorialblock");
	harimodel = Model::CreateFromOBJ("hari");

	collision = new Collision();

	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			tst[j][i] = Object3d::Create();
			tst[j][i]->Initialize();// Object3d::Create();
			tst[j][i]->SetModel(tstmodel);
		}
	}
	hari = Object3d::Create();
	hari->Initialize();
	hari->SetModel(harimodel);

	// ���C�g����
	lightGroup = LightGroup::Create();
	// 3D�I�u�G�N�g�Ƀ��C�g���Z�b�g
	Object3d::SetLightGroup(lightGroup);
	
	lightGroup->SetSpotLightActive(0, true);

	Player_Rot = player->GetRotation();
	Player_Scl = player->GetScale();
}
#pragma endregion

#pragma region �e�p�����[�^�̃Z�b�g
void Tutorial::SetPrm()
{

	hari->SetPosition({ hari_Pos.x + 2.0f,hari_Pos.y,hari_Pos.z });

	half_height = player->GetScale().y;
	half_Width = player->GetScale().x;

	player->SetPosition({ Player_Pos });
	player->SetScale({ Player_Scl });
	player->SetRotation({ Player_Rot });

	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			tst[j][i]->SetPosition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			tst[j][i]->SetRotation({ tst_Rot });
			tst[j][i]->SetScale({ tst_Scl });
		}
	}

}
#pragma endregion

#pragma region �I�u�W�F�N�g+���C�g�̍X�V����
void Tutorial::objUpdate()
{
	{//���C�g�̃p�����[�^�𔽉f 	
		lightGroup->SetSpotLightDir(0, XMVECTOR({ spotLightDir[0],spotLightDir[1],spotLightDir[2],0 }));
		lightGroup->SetSpotLightPos(0, XMFLOAT3(spotLightpos));
		lightGroup->SetSpotLightColor(0, XMFLOAT3(spotLightColor));
		lightGroup->SetSpotLightAtten(0, XMFLOAT3(spotLightAtten));
		lightGroup->SetSpotLightFactorAngle(0, XMFLOAT2(spotLightFactorAngle));
	}
	lightGroup->Update();

	player->Update({ 1,1,1,1 });

	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			tst[j][i]->Update({ 1,1,1,1 });
		}
	}
	hari->Update({ 1,1,1,1 });
}
#pragma endregion

#pragma region ������
void Tutorial::Initialize(DirectXCommon* dxCommon)
{
	//

	GameUI::UISpriteSet();
	GameUI::TargetUISet();
	GameUI::PlayerUISet();

	//enemy[0] = new MobEnemy();
	enemy = new MobEnemy();
	enemy->Setposition({ 20, -10, 0 });
	enemy->Initialize();

	mapcol = new Collision();

	collision = new Collision();
	SpriteCreate();//
	ModelCreate();//

	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height/*input*/);
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);

	//���f�������w�肵�ăt�@�C���ǂݍ���
	fbxmodel = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");

	//�f�o�C�X���Z�b�g
	f_Object3d::SetDevice(dxCommon->GetDev());
	//�J�������Z�b�g
	f_Object3d::SetCamera(camera);
	//�O���t�B�b�N�p�C�v���C������
	f_Object3d::CreateGraphicsPipeline();

	//FBX���f���̐���
	object1 = new f_Object3d();
	object1->Initialize();
	object1->SetModel(fbxmodel);
	/*audio = new Audio();
	audio->Initialize();
	audio->LoopWave("Resources/loop100216.wav", vol);*/

}
#pragma endregion

#pragma region �X�V����
void Tutorial::Update(DirectXCommon* dxCommon)
{
	Old_Pos = Player_Pos;
	spotLightpos[0] = Player_Pos.x;
	spotLightpos[1] = Player_Pos.y + 10;
	spotLightpos[2] = 0;



	//FBX���f���̍X�V
	object1->Updata(TRUE);
	if (Input::GetInstance()->Pushkey(DIK_RIGHT)) {
		Player_Pos.x += moveSpeed;
	}
	if (Input::GetInstance()->Pushkey(DIK_LEFT)) {
		Player_Pos.x -= moveSpeed;

	}

	float disl;
	//���͏�������ɓ����蔻���`��
	for (int i = 0; i < MAX_X; i++) {
		for (int j = 0; j < MAX_Y; j++) {
			if (map[j][i] == 1) {
				mapx[j][i] = tst[j][i]->GetPosition().x;
				mapy[j][i] = tst[j][i]->GetPosition().y;
				height =2.5;
				width = 1;
				if ((Line::GetInstance()->getpos().x + 1.0f > mapx[j][i] - (width) && Line::GetInstance()->getpos().x - 1.0f < mapx[j][i] + (width)) && Line::GetInstance()->getpos().y + 1.0f > mapy[j][i] && Line::GetInstance()->getpos().y - 1.0f < mapy[j][i] + height) {
					if (Line::GetInstance()->Getreturnflag() != true && Line::GetInstance()->Gettriggerflag() == true) {
						Line::GetInstance()->Setmapcol(true);
						Line::GetInstance()->Setelf(true);
					}
				}

				if ((Player_Pos.x + Player_Scl.x > mapx[j][i] - (width - moveSpeed) && Player_Pos.x - Player_Scl.x < mapx[j][i] + (width - moveSpeed))) {
					if (Old_Pos.y > mapy[j][i] && Player_Pos.y - Player_Scl.y < mapy[j][i] + height) {
						Player_Pos.y = height + mapy[j][i] + Player_Scl.y;
						//moveSpeed = 0;
						grav = 0.0f;
						time = 0;
						break;
					} else if (Old_Pos.y <mapy[j][i] && Player_Pos.y + Player_Scl.y>mapy[j][i]) {
						Player_Pos.y = mapy[j][i] - (Player_Scl.y + height);
						break;
					}

				} else {
					moveSpeed = 0.2f;
					grav = 0.03;
				}

				//�v���C���[�̍���
				if ((Player_Pos.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i]  < Player_Pos.y + Player_Scl.y)) {
					if (Player_Pos.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {
						Player_Pos.y = Player_Pos.y + 0.001f;
						Player_Pos.x = width + mapx[j][i] + Player_Scl.x;
						//grav = 0.0f;
						//time = 0;
						break;
					}
					//�v���C���[�̉E��
					else if (Player_Pos.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {
						Player_Pos.x = mapx[j][i] - (Player_Scl.x + width);
						//grav = 0.0f;
						//time = 0;
						//moveSpeed = 0;
						break;
					}
				} else {
					moveSpeed = 0.2f;
				}
			}
		}
	}


#pragma region ���̏���


	if (Line::GetInstance()->Getboundflag() == false || Line::GetInstance()->Gettriggerflag() == false) {
		//grav = 0.0f;
	} else {
		grav = 0.03f;
	}

	time += 0.04f;
	Player_Pos.y -= grav * time * time;
	//�d�͂̉e���ŏ��������
	hari_Pos.x = Line::GetInstance()->getpos().x;
	hari_Pos.y = Line::GetInstance()->getpos().y;

#pragma endregion
	//�ő�l������Ƃ��Ɏg���t���O�͂������ŊǗ�
	colf = Line::GetInstance()->GetColf();

	GameUI::UIUpdate(
		Line::GetInstance()->GetLength(),//
		Line::GetInstance()->Gettriggerflag(),//
		colf,//
		Line::GetInstance()->Getolddistance());//

	Line::GetInstance()->SetColf(colf);
	Line::Update(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player, Player_Pos, colf, moveSpeed);
	Line::CollisionEnemy(enemy);
	//FBX�̃A�j���[�V�����Đ�
	if (Input::GetInstance()->Pushkey(DIK_0)) {
		object1->PlayAnimation();
	}

	//�J�����֌W�̏���
	camera->SetTarget({ 0,1,0 });//�����_
	camera->SetEye({Player_Pos.x,-6,Player_Pos.z - 23 });
	camera->SetTarget({Player_Pos.x,-6 ,Player_Pos.z });
	camera->Update();

	player->SetPosition(Player_Pos);
	player->SetRotation(Player_Rot);
	player->SetScale(Player_Scl);

	player->Attack(Player_Pos);
	player->CollisionAttack(enemy, Player_Pos);

	SetPrm();//�p�����[�^�̃Z�b�g

	objUpdate();//�I�u�W�F�N�g�̍X�V����

	//enemy��nullptr�������Ƃ��͓G�����񂾂�
	for (int i = 0; i < 4; i++) {
		if (enemy != nullptr) {
			//�v���C���[�̌��m
			enemy->Attack(player);
			enemy->ColMap(map, mapx, mapy, MAX_X, MAX_Y);
			enemy->Update(Player_Pos);

			enemy->EnemySearchPlayer(player);
			//�����G�����񂾂�j��
			if (enemy->GetState_DEAD() == true) {
				Destroy(enemy);
			}
		}
	}

	GameUI::AllowUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player->GetPosition(),
		Line::GetInstance()->GetlineAngle(), Line::GetInstance()->Gettriggerflag());
	GameUI::TargetUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), Line::GetInstance()->Getelf());
	GameUI::PlayerUIUpdate(player);
	//�V�[���`�F���W
	if (Input::GetInstance()->TriggerKey(DIK_R)) {//�����ꂽ��
		BaseScene* scene = new PlayScene(sceneManager_);//���̃V�[���̃C���X�^���X����
		sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
		//delete scene;
	}
}
#pragma endregion 

//�X�v���C�g�̕`��
#pragma region ���f���̕`��
void Tutorial::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{
	player->PreDraw();
	player->Draw();
	player->PostDraw();

	if (enemy != nullptr) {
		enemy->Draw();
	}

	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			if (map[j][i] == 1) {
				tst[j][i]->PreDraw();
				tst[j][i]->Draw();
				tst[j][i]->PostDraw();
			}
		}
	}

}
//s�v���C�ƈȊO�̕`��
void Tutorial::MyGameDraw(DirectXCommon* dxcomn)
{

	//�X�v���C�g�̕`��
	SpriteDraw(dxcomn->GetCmdList());

	//���ʂ̃e�N�X�`���̕`��
	Line::Draw(dxcomn);

	//weffect->Draw(dxcomn);
	GameUI::AllowUIDraw(dxcomn);
	GameUI::TargetUIDraw(dxcomn);
	GameUI::UIDraw(dxcomn);
	GameUI::PlayerUIDraw(dxcomn);
	//FBX�̕`��
	object1->Draw(dxcomn->GetCmdList());
}
#pragma endregion
//���ɓ���
#pragma region
void Tutorial::Draw(DirectXCommon* dxcomn)
{
	dxcomn->BeginDraw();
	MyGameDraw(dxcomn);
	ImGuiDraw();
	dxcomn->EndDraw();
}
#pragma endregion

void Tutorial::ImGuiDraw()
{
	ImGui::Begin("Obj1");
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(500, 300));
	if (ImGui::TreeNode("cameraposition")) {
		float cx = camera->GetEye().x;
		float cy = camera->GetEye().y;
		ImGui::SliderFloat("cx", &cx, 100, -100);
		ImGui::SliderFloat("cy", &cy, 100, -100);
		ImGui::TreePop();
	}
	ImGui::End();
}
#pragma region �������
void Tutorial::Finalize()
{
	//delete sceneManager_;

	//delete efk,efk1;

}
#pragma endregion