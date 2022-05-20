
#include "FirstBossScene.h"
#include"Input.h"
#include"DirectXCommon.h"
#include"ClearScene.h"
#include"TitleScene.h"
#include"SceneManager.h"
#include"MobEnemy.h"
#include"FirstBoss.h"
#include"ThrowEnemy.h"
#include"Line.h"
#include"Destroy.h"
#include"Fader.h"
#include"CollisionPrimitive.h"
#include"StageSelect.h"
//�R�����g�A�E�g


//�V�[���̃R���X�g���N�^
FirstBossScene::FirstBossScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}

#pragma region �X�v���C�g�̐���
//�X�v���C�g����
void FirstBossScene::SpriteCreate()
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
void FirstBossScene::ModelCreate()
{
	playermodel = Model::CreateFromOBJ("player");
	player = Player::Create(playermodel);
	player->Initialize();
	tstmodel = Model::CreateFromOBJ("box1");
	goalmodel = Model::CreateFromOBJ("goalmo");

	item = new Item();
	item->Initialize();

	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			tst[j][i] = std::make_unique<Object3d>();
			tst[j][i]->Initialize();// Object3d::Create();
			tst[j][i]->SetModel(tstmodel);
		}
	}

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


	effects = std::make_unique<Effects>();;

	attackeffects = std::make_unique<Effects>();;

	//Player_Pos = player->GetPosition();
	Player_Rot = player->GetRotation();
	Player_Scl = player->GetScale();
	//Fader::SetFeedSprite();
}
#pragma endregion

#pragma region �e�p�����[�^�̃Z�b�g
void FirstBossScene::SetPrm()
{
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
void FirstBossScene::objUpdate()
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

}
#pragma endregion

#pragma region ������
void FirstBossScene::Initialize(DirectXCommon* dxCommon)
{
	//

	GameUI::UISpriteSet();
	GameUI::TargetUISet();
	GameUI::PlayerUISet();
	bossenemy = std::make_unique<FirstBoss>();

	//bossenemy->Setposition({ 20, -4, 0 });

	bossenemy->Initialize();

	SpriteCreate();//
	ModelCreate();//

	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height/*input*/);
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);

	effects->Initialize(dxCommon, camera);
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
	object1->Initialize(dxCommon, camera);
	object1->SetModel(fbxmodel);
	/*audio = new Audio();
	audi]o->Initialize();
	audio->LoopWave("Resources/loop100216.wav", vol);*/
	//camerapositionx = 46.94f;
	camerapositiony = -4.5f;
	camerapositionz = -12.15f;
	bossenemy->Setposition({ 57,-4,0 });
}
#pragma endregion

#pragma region �X�V����
void FirstBossScene::Update(DirectXCommon* dxCommon)
{
	//camerapositionx = Player_Pos.x;
	Old_Pos = Player_Pos;
	spotLightpos[0] = Player_Pos.x;
	spotLightpos[1] = Player_Pos.y + 1000;
	spotLightpos[2] = 0;

	LONG u_r = 32768;
	LONG a = 30000;

	//��
	player->PlayerMoves(Player_Pos, moveSpeed, jumpFlag, grav, time);
	///////// �R���g���[���[ //////////
	// �X�e�B�b�N�̕�������
	// �������͈�

	//��
	//���������𒲂ׂ���@
		if (Input::GetInstance()->GetCMove().lX < u_r - a)
		{
			// ���ɌX����
			Player_Pos.x -= moveSpeed;

		} else if (Input::GetInstance()->GetCMove().lX > u_r + a)
		{
			// �E�ɌX����
			Player_Pos.x += moveSpeed;
		}

		//FBX���f���̍X�V
		object1->Updata({ 1,1,1,1 }, dxCommon, camera, TRUE);
		if (Input::GetInstance()->Pushkey(DIK_RIGHT)) {
			Player_Pos.x += moveSpeed;
		}
		if (Input::GetInstance()->Pushkey(DIK_LEFT)) {
			Player_Pos.x -= moveSpeed;
		}


	///�������ɓ��͏���������
	////�����蔻��

	//���͏�������ɓ����蔻���`��

	GameUI::BossUIUpdate(bossenemy.get());
	Collision::CollisionMap(map, tst, mapx, mapy, MAX_X, MAX_Y, grav, time, moveSpeed, jumpFlag, Player_Pos, Player_Scl, Old_Pos, 1);

	//Collision::CollisionMap(map, tst, mapx, mapy, 200, 20, grav, time, moveSpeed, jumpFlag, Player_Pos, Old_Pos,1);

	if (Line::GetInstance()->Getboundflag() == true) {
		grav = 0;
		time = 0;
	}

#pragma region ���̏���

	if (Line::GetInstance()->Getboundflag() == false || Line::GetInstance()->Gettriggerflag() == false) {
		//grav = 0.0f;
	} else {
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

	Line::CollisionEnemy(bossenemy.get());
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
	//camera->SetTarget({ 0,1,0 });//�����_
	//camera->SetDistance(distance);//
	//XMFLOAT3 camerapos={
	FirstBoss::GetInstance()->appearance(camerapositionx);
	camera->SetEye({ camerapositionx,camerapositiony,camerapositionz - 20 });
	camera->SetTarget({ camerapositionx,camerapositiony - 2 ,camerapositionz });

	camera->Update();

	effects->BossAttackEffect(dxCommon, camera, FirstBoss::GetInstance()->GetAltStay(), atb, bpos);
	player->SetPosition(Player_Pos);
	player->SetRotation(Player_Rot);
	player->SetScale(Player_Scl);
	player->CollisionAttack1(bossenemy.get(), Player_Pos);

	player->Attack(Player_Pos);

	SetPrm();//�p�����[�^�̃Z�b�g

	objUpdate();//�I�u�W�F�N�g�̍X�V����

	effects->Update(dxCommon, camera, &bossenemy, player);

	//bossenemy��nullptr�������Ƃ��͓G�����񂾂�
	if (bossenemy != nullptr) {
		//�v���C���[�̌��m

		bossenemy->Motion(player);
		bossenemy->Attack(player);
		bossenemy->Update(Player_Pos);
		bossenemy->ColMap(map, tst, mapx, mapy, 200, 20);
		bossenemy->EnemySearchPlayer(player);
		//�����G�����񂾂�j��
		if (bossenemy->GetState_DEAD() == true) {
			Destroy_unique(bossenemy);
		}
	}

	//BossPos = bossenemy->GetPosition();

//bossenemy[3]->Update(Player_Pos);
	
	item->HealEfficasy(player);
	item->Update(&bossenemy);
	//Fader::FeedSpriteUpdate();

	GameUI::AllowUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player->GetPosition(),
		Line::GetInstance()->GetlineAngle(), Line::GetInstance()->Gettriggerflag());
	GameUI::TargetUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), Line::GetInstance()->Getelf());
	GameUI::PlayerUIUpdate(player);
	//�V�[���`�F���W
	if (Input::GetInstance()->TriggerKey(DIK_R) || (Player_Pos.y <= -50)) {//�����ꂽ��
		BaseScene* scene = new StageSelect(sceneManager_);//���̃V�[���̃C���X�^���X����
		sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
		//delete scene;
	}
}
#pragma endregion 

//�X�v���C�g�̕`��
#pragma region ���f���̕`��
void FirstBossScene::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{
	player->PreDraw();
	player->Draw();
	player->PostDraw();

	if (bossenemy != nullptr) {
		bossenemy->Draw(dxcomn);
	}

	item->Draw();
	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			if (map[j][i] == 1 || map[j][i] == 2) {
				tst[j][i]->PreDraw();
				tst[j][i]->Draw();
				tst[j][i]->PostDraw();
			}
		}
	}

}
//s�v���C�ƈȊO�̕`��
void FirstBossScene::MyGameDraw(DirectXCommon* dxcomn)
{
	Sprite::PreDraw(dxcomn->GetCmdList());

	dxcomn->ClearDepthBuffer(dxcomn->GetCmdList());
	Sprite::PostDraw(dxcomn->GetCmdList());

	//�X�v���C�g�̕`��
	SpriteDraw(dxcomn->GetCmdList());

	//���ʂ̃e�N�X�`���̕`��
	Line::Draw(dxcomn);

	GameUI::AllDraw(dxcomn);

	attackeffects->Draw(dxcomn);
	effects->Draw(dxcomn);
	//FBX�̕`��
	object1->Draw(dxcomn->GetCmdList());
}
#pragma endregion
//���ɓ���
#pragma region
void FirstBossScene::Draw(DirectXCommon* dxcomn)
{
	dxcomn->BeginDraw();
	MyGameDraw(dxcomn);
	effects->ImGuiDraw();
	//ImGuiDraw();//imgui�͍Ō�̕�����Ƃ�
	dxcomn->EndDraw();
}
#pragma endregion

void FirstBossScene::ImGuiDraw()
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
		float x = player->GetPosition().x;
		ImGui::SliderFloat("positionX", &x, -200, 200);
		ImGui::SliderFloat("positionY", &camerapositiony, -200, 200);
		ImGui::SliderFloat("positionz", &camerapositionz, -200, 200);
		camera->SetEye({ camerapositionx,camerapositiony,camerapositionz-20 });
		camera->SetTarget({ camerapositionx,camerapositiony - 2 ,camerapositionz});
		//ImGui::SliderInt("positionZ", &elf, -200, 200);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("enemy_position")) {

		ImGui::TreePop();
	}
	float linex = Line::GetInstance()->getpos().x;
	float liney = Line::GetInstance()->getpos().y;
	float rr = player->GetPosition().x;
	if (ImGui::TreeNode("Player_position")) {
		ImGui::SliderFloat("positionX", &linex, -200, 200);
		ImGui::SliderFloat("positionY", &liney, -200, 200);
		ImGui::SliderFloat("positionZ", &Player_Pos.z, -200, 200);
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
void FirstBossScene::Finalize()
{
	//delete sceneManager_;

	attackeffects.reset();
	effects.reset();
	bossenemy.reset();
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 200; j++) {
			tst[i][j].reset();
		}
	}
	delete player, playermodel;
	delete tstmodel;
	delete goalmodel, tstmodel;
	delete item;
	GameUI::Finalize();
	Line::Finalize();

}
#pragma endregion
