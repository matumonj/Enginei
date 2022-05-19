#include "BossScene2.h"
#include"Input.h"
#include"DirectXCommon.h"
#include"ClearScene.h"
#include"TitleScene.h"
#include"SceneManager.h"
#include"MobEnemy.h"
#include"BossEnemy.h"
#include"ThrowEnemy.h"
#include"Line.h"
#include"ForestBoss.h"
#include"Destroy.h"
#include"Fader.h"
#include"CollisionPrimitive.h"

//�V�[���̃R���X�g���N�^
BossScene2::BossScene2(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}

#pragma region �X�v���C�g�̐���
//�X�v���C�g����
void BossScene2::SpriteCreate()
{
	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont2.png");
	//���ʂ̃e�N�X�`��(�X�v���C�g����Ȃ���)
	Line::Initialize();
	GameUI::AllowUISet();

	Texture::LoadTexture(6, L"Resources/gomi.png");
	Texture::LoadTexture(1, L"Resources/background.png");
	Sprite::LoadTexture(1, L"Resources/haikei2.png");
	Sprite::LoadTexture(2, L"Resources/setumei.png");

}
#pragma endregion

#pragma region 
void BossScene2::ModelCreate()
{
	playermodel = Model::CreateFromOBJ("player");
	player = Player::Create(playermodel);
	player->Initialize();
	tstmodel = Model::CreateFromOBJ("block");
	goalmodel = Model::CreateFromOBJ("goalmo");

	item = new Item();
	item->Initialize();

	item2 = new Item();
	item2->Initialize();

	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			tst[j][i] = std::make_unique<Object3d>();
			tst[j][i]->Initialize();// Object3d::Create();
			tst[j][i]->SetModel(tstmodel);
		}
	}

	goal = std::make_unique<Object3d>();
	goal->Initialize();
	goal->SetModel(goalmodel);

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


	effects = std::make_unique<Effects>();

	//effects2 = std::make_unique<Effects>();;
	attackeffects = std::make_unique<Effects>();;

	//Player_Pos = player->GetPosition();
	Player_Rot = player->GetRotation();
	Player_Scl = player->GetScale();
	//Fader::SetFeedSprite();
}
#pragma endregion

#pragma region �e�p�����[�^�̃Z�b�g
void BossScene2::SetPrm()
{
	half_height = player->GetScale().y;
	half_Width = player->GetScale().x;

	player->SetPosition({ Player_Pos });
	player->SetScale({ Player_Scl });
	player->SetRotation({ Player_Rot });

	goal->SetPosition({ goal_pos.x,goal_pos.y,goal_pos.z });

}
#pragma endregion

#pragma region �I�u�W�F�N�g+���C�g�̍X�V����
void BossScene2::objUpdate()
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

	goal->Update({ 1,1,1,1 });

}
#pragma endregion

#pragma region ������
void BossScene2::Initialize(DirectXCommon* dxCommon)
{
	//

	GameUI::UISpriteSet();
	GameUI::TargetUISet();
	GameUI::PlayerUISet();

	mapcol = new Collision();

	collision = new Collision();
	SpriteCreate();//
	ModelCreate();//

	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height/*input*/);
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);

	effects->Initialize(dxCommon, camera);
	//effects2->Initialize(dxCommon, camera);

	attackeffects->Initialize(dxCommon, camera);

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
	//camerapositionx = 46.94f;
	camerapositiony = -4.5f;
	camerapositionz = -40.51;
	bossenemy = std::make_unique<ForestBoss>();
	enemycolony1[0] = std::make_unique<MobEnemy>();
	enemycolony1[1] = std::make_unique<MobEnemy>();
	enemycolony1[2] = std::make_unique<MobEnemy>();
	enemycolony1[3] = std::make_unique<MobEnemy>();
	enemycolony1[4] = std::make_unique<MobEnemy>();
	enemycolony1[5] = std::make_unique<MobEnemy>();
	enemycolony1[6] = std::make_unique<MobEnemy>();
	enemycolony1[7] = std::make_unique<MobEnemy>();
	enemycolony1[8] = std::make_unique<MobEnemy>();
	enemycolony1[9] = std::make_unique<MobEnemy>();

	//bossenemy->Setposition({ 20, -4, 0 });
	enemycolony2[0] = std::make_unique<MobEnemy>();
	enemycolony2[1] = std::make_unique<MobEnemy>();
	enemycolony2[2] = std::make_unique<MobEnemy>();
	enemycolony2[3] = std::make_unique<MobEnemy>();
	enemycolony2[4] = std::make_unique<MobEnemy>();
	enemycolony2[5] = std::make_unique<MobEnemy>();
	enemycolony2[6] = std::make_unique<MobEnemy>();
	enemycolony2[7] = std::make_unique<MobEnemy>();
	enemycolony2[8] = std::make_unique<MobEnemy>();
	enemycolony2[9] = std::make_unique<MobEnemy>();

	for (int i = 0; i < 10; i++) {
		//enemycolony2[i] = nullptr;
		enemycolony1[i]->Initialize();
		enemycolony2[i]->Initialize();
		enemycolony2[i]->Setposition({ 1222,1,1 });
	}

	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			tst[j][i]->SetPosition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			tst[j][i]->SetRotation({ tst_Rot });
			tst[j][i]->SetScale({ tst_Scl });
		}
	}
	bossenemy->Initialize();

	bossenemy->Setposition({ 40,-4,0 });
	if (startSet == false) {
		
		for (int i = 0; i < 130; i++) {
			for (int j = 0; j < 20; j++) {
				if (map[i][j] == 10) {
					enemycolony1[0]->Setposition(tst[i][j]->GetPosition());

					//	break;
				} else if (map[i][j] == 11) {
					enemycolony1[1]->Setposition(tst[i][j]->GetPosition());
					//break;
				} else if (map[i][j] == 12) {
					enemycolony1[2]->Setposition(tst[i][j]->GetPosition());
					//	break;
				} else if (map[i][j] == 13) {
					enemycolony1[3]->Setposition(tst[i][j]->GetPosition());
					//	break;
				} else if (map[i][j] == 14) {
					enemycolony1[4]->Setposition(tst[i][j]->GetPosition());
					//break;
				} else if (map[i][j] == 15) {
					enemycolony1[5]->Setposition(tst[i][j]->GetPosition());
					//break;
				} else if (map[i][j] == 16) {
					enemycolony1[6]->Setposition(tst[i][j]->GetPosition());
					//	break;
				} else if (map[i][j] == 17) {
					enemycolony1[7]->Setposition(tst[i][j]->GetPosition());
					//	break;
				} else if (map[i][j] == 18) {
					enemycolony1[8]->Setposition(tst[i][j]->GetPosition());
					//break;
					//enemycolony1[8]->Setposition(tst[i][j]->GetPosition());
				} else if (map[i][j] == 19) {
					enemycolony1[9]->Setposition(tst[i][j]->GetPosition());
					xx = tst[i][j]->GetPosition().x;
					//break;
					//break;
				}
			}
		}
	}
	//168,48
Player_Pos={ 20,38,0 };
}
#pragma endregion

#pragma region �X�V����
void BossScene2::Update(DirectXCommon* dxCommon)
{

	camerapositionx = Player_Pos.x;
	Old_Pos = Player_Pos;
	spotLightpos[0] = Player_Pos.x;
	spotLightpos[1] = Player_Pos.y + 10;
	spotLightpos[2] = 0;

	LONG u_r = 32768;
	LONG a = 30000;

	//��
	player->PlayerMoves(Player_Pos, moveSpeed, jumpFlag, grav, time);
	///////// �R���g���[���[ //////////
	// �X�e�B�b�N�̕�������
	// �������͈�



	//player->PlayerMoves(Player_Pos, moveSpeed);

	//FBX���f���̍X�V
	object1->Updata(TRUE);
	if (Input::GetInstance()->Pushkey(DIK_RIGHT)) {
		Player_Pos.x += moveSpeed;
	}
	if (Input::GetInstance()->Pushkey(DIK_LEFT)) {
		Player_Pos.x -= moveSpeed;
	}

	if (jumpFlag == true) {
		Player_Pos.y += 0.1f;
		time += 0.02f;
	}

	///�������ɓ��͏���������
	////�����蔻��

	//���͏�������ɓ����蔻���`��

	GameUI::BossUIUpdate(bossenemy.get());

	float disl;
	//����͈ڂ�


	Collision::ColMapb1(map, tst, mapx, mapy, 20, 130, grav, time, moveSpeed, jumpFlag, Player_Pos, Old_Pos);

	//����ʂ�Ƃ���ڂ��̑����߂�ǂ����琘���u��
	
	if (Player_Pos.x <= goal_pos.x + goal->GetScale().x && Player_Pos.x >= goal_pos.x - goal->GetScale().x && Player_Pos.y <= goal_pos.y + goal->GetScale().y && Player_Pos.y >= goal_pos.y - goal->GetScale().y) {
		BaseScene* scene = new ClearScene(sceneManager_);//���̃V�[���̃C���X�^���X����
		sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
	}

	if (Line::GetInstance()->Getboundflag() == true) {
		grav = 0;
		time = 0;
	}

#pragma region ���̏���

	if (Line::GetInstance()->Getboundflag() == false || Line::GetInstance()->Gettriggerflag() == false) {
		//grav = 0.0f;
	}
	else {
		grav = 0.03f;
	}

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
	Line::GetInstance()->CollisionEnemys(enemycolony1);
	Line::GetInstance()->CollisionEnemys2group(enemycolony2);
	//Line::CollisionEnemys2group(enemycolony1, enemycolony2);
	//Line::CollisionEnemy(bossenemy.get());
	//weffect->Update(dxcomn,camera,player[0]->GetPosition(),Line::GetInstance()->Getboundflag());
	//FBX�̃A�j���[�V�����Đ�
	if (Input::GetInstance()->Pushkey(DIK_0)) {
		object1->PlayAnimation();
	}
	XMFLOAT3 bpos;
	if (bossenemy != nullptr) {
		bpos = bossenemy->GetPosition();
	}
	//�J�����֌W�̏���
	ForestBoss::GetInstance()->appearance(camerapositiony,Player_Pos.y);
	camera->SetTarget({ 0,1,0 });//�����_
	camera->SetDistance(distance);//
	camera->SetEye({ Player_Pos.x,camerapositiony,Player_Pos.z - 27.0f });
	camera->SetTarget({ Player_Pos.x,camerapositiony-2 ,Player_Pos.z });

	camera->Update();

	effects->BossAttackEffect(dxCommon, camera, BossEnemy::GetInstance()->GetAltStay(), atb, bpos);
	player->SetPosition(Player_Pos);
	player->SetRotation(Player_Rot);
	player->SetScale(Player_Scl);
	player->CollisionAttack1(bossenemy.get(), Player_Pos);
	player->CollisionAttack(enemycolony1, Player_Pos);
	player->CollisionAttack(enemycolony2, Player_Pos);
	player->Attack(Player_Pos);

	SetPrm();//�p�����[�^�̃Z�b�g

	objUpdate();//�I�u�W�F�N�g�̍X�V����
	effects->Update(dxCommon, camera, enemycolony1, player);
	effects->Update2(dxCommon, camera, enemycolony2, player);
	//effects2->Update(dxCommon, camera, enemycolony2, player);

	//effects->Update(dxCommon, camera, &bossenemy, player);

	//bossenemy��nullptr�������Ƃ��͓G�����񂾂�
	if (bossenemy != nullptr) {
		//�v���C���[�̌��m

		bossenemy->Motion(player);
		bossenemy->Attack(player);
		bossenemy->Update(Player_Pos);
		ForestBoss::GetInstance()->SkewersAttack(map, tst);

		bossenemy->EnemySearchPlayer(player);
		//�����G�����񂾂�j��
		if (bossenemy->GetState_DEAD() == true) {
			Destroy_unique(bossenemy);
		}
	}
	float len[10];
	for (int i = 0; i < 10; i++) {
		//Collision::GetLen(enemycolony1[i]->GetPosition(),Player_Pos)
			if (enemycolony1[i] != nullptr) {
				//if (Collision::GetLen(enemycolony1[i]->GetPosition(), Player_Pos) < 30) {

				enemycolony1[i]->Motion(player);
				enemycolony1[i]->ColMap1(map, tst, mapx, mapy, 20, 130);
				enemycolony1[i]->Attack(player);
				enemycolony1[i]->Update(Player_Pos);
				enemycolony1[i]->EnemySearchPlayer(player);
				//�����G�����񂾂�j��
				if (enemycolony1[i]->GetState_DEAD() == true) {
					Destroy_unique(enemycolony1[i]);
				///}
			}
		}
		if (enemycolony2[i] != nullptr) {
			//if (Collision::GetLen(enemycolony2[i]->GetPosition(), Player_Pos) < 30) {
				enemycolony2[i]->Motion(player);
				enemycolony2[i]->ColMap1(map, tst, mapx, mapy, 20, 130);
				enemycolony2[i]->Attack(player);
				enemycolony2[i]->Update(Player_Pos);
				enemycolony2[i]->EnemySearchPlayer(player);
				//�����G�����񂾂�j��
				if (enemycolony2[i]->GetState_DEAD() == true) {
					Destroy_unique(enemycolony2[i]);
				}
			}
		}
	//BossPos = bossenemy->GetPosition();

//bossenemy[3]->Update(Player_Pos);
	atb = BossEnemy::GetInstance()->GetaltAttack();

	item->HealEfficasy(player);
	item2->HealEfficasy(player);

	effects->HealEffect(item->ColItem(), item2->ColItem());
	//effects->HealEffect2(item2->ColItem());
	//item->Update(&bossenemy);
	item->Update(enemycolony1);
	item2->Update(enemycolony2);
	Fader::FeedSpriteUpdate();

	GameUI::AllowUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player->GetPosition(),
		Line::GetInstance()->GetlineAngle(), Line::GetInstance()->Gettriggerflag());
	GameUI::TargetUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), Line::GetInstance()->Getelf());
	GameUI::PlayerUIUpdate(player);
	//�V�[���`�F���W
	if (Input::GetInstance()->TriggerKey(DIK_R) || (Player_Pos.y <= -50)) {//�����ꂽ��
		BaseScene* scene = new ClearScene(sceneManager_);//���̃V�[���̃C���X�^���X����
		sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
		//delete scene;
	}
}
#pragma endregion 

//�X�v���C�g�̕`��
#pragma region ���f���̕`��
void BossScene2::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{
	player->PreDraw();
	player->Draw();
	player->PostDraw();

	item->Draw();
	item2->Draw();
	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			if (map[j][i] == 1 || map[j][i] == 2) {
				tst[j][i]->PreDraw();
				tst[j][i]->Draw();
				tst[j][i]->PostDraw();
			}
		}
	}

	goal->PreDraw();
	goal->Draw();
	goal->PostDraw();

}
//s�v���C�ƈȊO�̕`��
void BossScene2::MyGameDraw(DirectXCommon* dxcomn)
{
	Sprite::PreDraw(dxcomn->GetCmdList());

	dxcomn->ClearDepthBuffer(dxcomn->GetCmdList());
	Sprite::PostDraw(dxcomn->GetCmdList());

	//�X�v���C�g�̕`��
	SpriteDraw(dxcomn->GetCmdList());

	if (bossenemy != nullptr) {
		bossenemy->Draw(dxcomn);
	}
	for (int i = 0; i < 10; i++) {
		//if (Collision::GetLen(enemycolony1[i]->GetPosition(), Player_Pos) < 30) {
		if (enemycolony1[i] != nullptr) {
			enemycolony1[i]->Draw(dxcomn);
		}
		//}
		//if (Collision::GetLen(enemycolony2[i]->GetPosition(), Player_Pos) < 30) {
		if (enemycolony2[i] != nullptr) {
			enemycolony2[i]->Draw(dxcomn);
		}
		//}
	}
	//���ʂ̃e�N�X�`���̕`��
	Line::Draw(dxcomn);

	GameUI::AllDraw(dxcomn);

	attackeffects->Draw(dxcomn);
	effects->Draw(dxcomn);
	//effects2->Draw(dxcomn);
	//FBX�̕`��
	object1->Draw(dxcomn->GetCmdList());
}
#pragma endregion
//���ɓ���
#pragma region
void BossScene2::Draw(DirectXCommon* dxcomn)
{
	dxcomn->BeginDraw();
	MyGameDraw(dxcomn);
	effects->ImGuiDraw();
	ImGuiDraw();//imgui�͍Ō�̕�����Ƃ�
	dxcomn->EndDraw();
}
#pragma endregion

void BossScene2::ImGuiDraw()
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
		ImGui::ColorPicker3("light_color", spotLightColor);
		ImGui::TreePop();
	}
	//int x= bossenemy->GetHP();
	if (ImGui::TreeNode("Effect_position")) {
		//ImGui::SliderInt("positionX", &x, -200, 200);
		ImGui::SliderFloat("positionY", &camerapositiony, -200, 200);
		ImGui::SliderFloat("positionz", &camerapositionz, -200, 200);
		//ImGui::SliderInt("positionZ", &elf, -200, 200);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("enemy_position")) {

		ImGui::TreePop();
	}
	float linex = Line::GetInstance()->getpos().x;
	float liney = Line::GetInstance()->getpos().y;
	float rr = enemycolony1[9]->GetPosition().y;
	if (ImGui::TreeNode("Player_position")) {
		//ImGui::SliderFloat("positionX", &Player_Pos.x, -200, 200);
		ImGui::SliderFloat("positionY", &Player_Pos.y, -200, 200);
		//ImGui::SliderFloat("positionZ", &Player_Pos.z, -200, 200);
		ImGui::SliderFloat("grav", &grav, -200, 200);
		ImGui::SliderFloat("time", &time, -200, 200);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Old")) {
		ImGui::SliderFloat("Old_PosX", &Old_Pos.x, -200, 200);
		ImGui::SliderFloat("old_PosY", &Old_Pos.y, -200, 200);
		ImGui::TreePop();
	}

	ImGui::End();

}
#pragma region �������
void BossScene2::Finalize()
{
	//delete sceneManager_;

	attackeffects.reset();
	effects.reset();
	bossenemy.reset();
	for (int i = 0; i < 20; i++) {
		enemycolony1->reset();
		enemycolony2->reset();
	}

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 200; j++) {
			tst[i][j].reset();
		}
	}
	bossenemy.reset();
	goal.reset();
	delete player, playermodel;
	delete tstmodel;
	delete goalmodel, tstmodel;
	delete item;
	GameUI::Finalize();
	Line::Finalize();

}
#pragma endregion