#include "DesertField.h"
#include"Input.h"
#include"DirectXCommon.h"
#include"ClearScene.h"
#include"TitleScene.h"
#include"SceneManager.h"
#include"MobEnemy.h"
#include"BossEnemy.h"
#include"ThrowEnemy.h"
#include"Line.h"
#include"Destroy.h"
#include"Fader.h"
#include"BossScene1.h"
#include"FirstBossScene.h"
#include"GamOver.h"
//�R�����g�A�E�g


//�V�[���̃R���X�g���N�^
DesertField::DesertField(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}

#pragma region �X�v���C�g�̐���
//�X�v���C�g����
void DesertField::SpriteCreate()
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

	mech = std::make_unique<Texture>();
	mech->Create(6, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });// = Texture::Create(6, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });

	zukki = std::make_unique<Texture>();
	zukki->Create(1, { 0,-20,50 }, { 1,1,1 }, { 1,1,1,1 });

	background = Sprite::Create(1, { 0.0f,0.0f });
	setumei = Sprite::Create(2, { 0.0f,0.0f });
	// �f�o�b�O�e�L�X�g������
	dxcomn = new DirectXCommon();
	debugText = new DebugTxt();
	debugText->Initialize(debugTextTexNumber);
}
#pragma endregion

#pragma region 
void DesertField::ModelCreate()
{
	playermodel = Model::CreateFromOBJ("player");
	player = Player::Create(playermodel);
	player->Initialize();
	tstmodel = Model::CreateFromOBJ("block");
	worldmodel = Model::CreateFromOBJ("skydome");
	harimodel = Model::CreateFromOBJ("hari");
	goalmodel = Model::CreateFromOBJ("goalmo");


	item = new Item();
	item->Initialize();
	collision = new Collision();

	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			tst[j][i] = std::make_unique<Object3d>();
			tst[j][i]->Initialize();// Object3d::Create();
			tst[j][i]->SetModel(tstmodel);
		}
	}
	block = std::make_unique<Object3d>();
	block->Initialize();// = Object3d::Create();
	block->SetModel(tstmodel);

	sentan = std::make_unique<Object3d>();
	sentan->Initialize();// = Object3d::Create();
	sentan->SetModel(tstmodel);

	world = std::make_unique<Object3d>();
	world->Initialize();// = Object3d::Create();
	world->SetModel(worldmodel);

	hari = std::make_unique<Object3d>();
	hari->Initialize();
	hari->SetModel(harimodel);

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
	//pointLightPos[0] = 0.0f;
	//pointLightPos[1] = 1.0f;
	//pointLightPos[2] = 0.0f;
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
void DesertField::SetPrm()
{
	setumei->SetPosition({ 0, 400 });
	setumei->SetSize({ 500,300 });
	setumei->setcolor({ 1,1,1,1 });

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
	goal->SetPosition({ goal_pos.x,goal_pos.y,goal_pos.z });

	block->SetPosition({ block_pos });
	block->SetScale({ block_Scl });

	world->SetPosition({ 0,0,0 });
	world->SetScale({ 1,1,1 });

	sentan->SetPosition({ sentan_Pos });

	background->SetPosition({ 0, 0 });
	background->SetSize({ WinApp::window_width,WinApp::window_height });
	background->setcolor({ 1,1,1,1 });
}
#pragma endregion

#pragma region �I�u�W�F�N�g+���C�g�̍X�V����
void DesertField::objUpdate()
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

	world->Update({ 1,1,1,1 });
	block->Update({ 1,1,1,1 });
	hari->Update({ 1,1,1,1 });

	goal->Update({ 1,1,1,1 });

}
#pragma endregion

#pragma region ������
void DesertField::Initialize(DirectXCommon* dxCommon)
{
	//

	GameUI::UISpriteSet();
	GameUI::TargetUISet();
	GameUI::PlayerUISet();
	enemy[0] = std::make_unique<ThrowEnemy>();
	enemy[1] = std::make_unique<MobEnemy>();
	enemy[2] = std::make_unique<ThrowEnemy>();
	enemy[3] = std::make_unique<ThrowEnemy>();
	enemy[4] = std::make_unique<ThrowEnemy>();
	enemy[5] = std::make_unique<ThrowEnemy>();
	enemy[6] = std::make_unique<ThrowEnemy>();
	//enemy[0] = new MobEnemy();

	enemy[6]->Setposition({ 270,-18.2,0 });
	enemy[5]->Setposition({ 170,-18.2,0 });
	enemy[4]->Setposition({ 320,-14.2,0 });
	enemy[3]->Setposition({ 80,-4.2,0 });
	enemy[2]->Setposition({ 250,-4.2,0 });
	enemy[1]->Setposition({ 350, -18, 0 });
	enemy[0]->Setposition({ 50, -15, 0 });
	enemy[0]->Initialize();
	enemy[1]->Initialize();
	enemy[2]->Initialize();
	enemy[3]->Initialize();
	enemy[4]->Initialize();
	enemy[5]->Initialize();
	enemy[6]->Initialize();

	mapcol = new Collision();
	c_postEffect = Default;

	collision = new Collision();
	SpriteCreate();//
	ModelCreate();//

	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height/*input*/);
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);

	effects->Initialize(dxCommon, camera);
	attackeffects->Initialize(dxCommon, camera);


	//���f�������w�肵�ăt�@�C���ǂݍ���
	fbxmodel = FbxLoader::GetInstance()->LoadModelFromFile("player");

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
	postEffect = new PostEffect();
	postEffect->Initialize();

}
#pragma endregion

#pragma region �X�V����
void DesertField::Update(DirectXCommon* dxCommon)
{
	Old_Pos = Player_Pos;
	spotLightpos[0] = Player_Pos.x;
	spotLightpos[1] = Player_Pos.y + 10;
	spotLightpos[2] = 0;

	LONG u_r = 32768;
	LONG a = 30000;

	object1->Setpos({ Player_Pos.x+4.0f,Player_Pos.y,Player_Pos.z });


	//��
	player->PlayerMoves(Player_Pos, moveSpeed);

	
	///////// �R���g���[���[ //////////
	// �X�e�B�b�N�̕�������
	// �������͈�




	

	//FBX���f���̍X�V
	object1->Updata(TRUE);
	if (Input::GetInstance()->Pushkey(DIK_RIGHT)) {
		Player_Pos.x += moveSpeed;
	}
	if (Input::GetInstance()->Pushkey(DIK_LEFT)) {
		Player_Pos.x -= moveSpeed;
	}

	if (Input::GetInstance()->GetCMove().lY < u_r - a)
	{

		jumpFlag = true;
		// ���ɌX����
		//Player_Pos.x -= moveSpeed;

	}


	if (jumpFlag == true) {
		Player_Pos.y += 0.12f;
		time += 0.02f;
	}


	///�������ɓ��͏���������
	////�����蔻��

	float disl;

	//���͏�������ɓ����蔻���`��
	//aaaaaaa

	if (OnFlag == true) {
		if (Ontime >= 0) {
			Ontime--;
		}
		else if (Ontime <= 0) {
			OnFlag = false;
		}
	}

	if (OnFlag == false) {
		Ontime++;
		if (Ontime >= 300) {
			OnFlag = true;
		}
	}

	for (int i = 0; i < MAX_X; i++) {
		for (int j = 0; j < MAX_Y; j++) {
			if (map[j][i] == 1 || (map[j][i] == 2 && OnFlag == true)) {
				mapx[j][i] = tst[j][i]->GetPosition().x;
				mapy[j][i] = tst[j][i]->GetPosition().y;
				height = tst[j][i]->GetScale().y;
				width = tst[j][i]->GetScale().x;
				if ((Line::GetInstance()->getpos().x + 1.0f > mapx[j][i] - (width) && Line::GetInstance()->getpos().x - 1.0f < mapx[j][i] + (width)) && Line::GetInstance()->getpos().y + 1.0f > mapy[j][i] - height && Line::GetInstance()->getpos().y - 1.0f < mapy[j][i] + height) {
					if ( Line::GetInstance()->Gettriggerflag() == true) {
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
						jumpFlag = false;
						break;
					}
					else if (Old_Pos.y <mapy[j][i] && Player_Pos.y + Player_Scl.y>mapy[j][i] - height) {
						Player_Pos.y = mapy[j][i] - (Player_Scl.y + height);
						break;
					}

				}
				else {
					moveSpeed = 0.2f;
					grav = 0.03;
				}

				//�v���C���[�̍���
				if ((Player_Pos.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Player_Pos.y + Player_Scl.y)) {
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
				}
				else {
					moveSpeed = 0.2f;
				}
			}
		}
	}

	if (Player_Pos.x <= goal_pos.x + goal->GetScale().x && Player_Pos.x >= goal_pos.x - goal->GetScale().x && Player_Pos.y <= goal_pos.y + goal->GetScale().y && Player_Pos.y >= goal_pos.y - goal->GetScale().y) {
		BaseScene* scene = new FirstBossScene(sceneManager_);//���̃V�[���̃C���X�^���X����
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

	time += 0.04f;
	Player_Pos.y -= grav * time * time;


	//���_���W�̍X�V
	mech->CreateLineTexture(linex, linex2, liney, liney2);

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

	//needlepos = Line::GetInstance()->getpos();

	Line::Update(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player, Player_Pos, colf, moveSpeed);

	Line::CollisionEnemy(enemy->get());
	//weffect->Update(dxcomn,camera,player[0]->GetPosition(),Line::GetInstance()->Getboundflag());
	//FBX�̃A�j���[�V�����Đ�
	if (Input::GetInstance()->Pushkey(DIK_0)) {
		object1->PlayAnimation();
	}



	//}
	//�J�����֌W�̏���
	camera->SetTarget({ 0,1,0 });//�����_
	camera->SetDistance(distance);//
	camera->SetEye({ Player_Pos.x,Player_Pos.y,Player_Pos.z - 27.0f });
	camera->SetTarget({ Player_Pos.x,Player_Pos.y ,Player_Pos.z });

	camera->Update();

	player->SetPosition(Player_Pos);
	player->SetRotation(Player_Rot);

	player->SetScale(Player_Scl);


	player->Attack(Player_Pos);
	//for (int i = 0; i < 2; i++) {
	player->CollisionAttack(enemy, Player_Pos);

	SetPrm();//�p�����[�^�̃Z�b�g

	objUpdate();//�I�u�W�F�N�g�̍X�V����

	effects->Update(dxCommon, camera, enemy, player);

	//enemy��nullptr�������Ƃ��͓G�����񂾂�
	for (int i = 0; i < 10; i++) {
		if (enemy[i] != nullptr) {
			//�v���C���[�̌��m
			//enemy[0]->Motion(player);
			enemy[i]->ColMap(map, tst, mapx,mapy,MAX_X, MAX_Y);
			enemy[i]->Attack(player);
			enemy[i]->Update(Player_Pos);

			enemy[i]->EnemySearchPlayer(player);
			enemy[i]->SearchAction(camera->GetViewMatrix(), camera->GetProjectionMatrix(), Player_Pos);

			//�����G�����񂾂�j��
			if (enemy[i]->GetState_DEAD() == true) {
				Destroy_unique(enemy[i]);

			}
		}
	}
	item->HealEfficasy(player);
	item->Update(enemy);
	//Fader::FeedSpriteUpdate();
	GameUI::AllowUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player->GetPosition(),
		Line::GetInstance()->GetlineAngle(), Line::GetInstance()->Gettriggerflag());
	GameUI::TargetUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), Line::GetInstance()->Getelf());
	GameUI::PlayerUIUpdate(player);
	//�V�[���`�F���W
	if (Input::GetInstance()->TriggerKey(DIK_R) || (Player_Pos.y <= -50)) {//�����ꂽ��
		BaseScene* scene = new GamOver(sceneManager_);//���̃V�[���̃C���X�^���X����
		sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
		//delete scene;
	}
}
#pragma endregion 

//�X�v���C�g�̕`��
#pragma region ���f���̕`��
void DesertField::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{


	player->PreDraw();
	player->Draw();
	player->PostDraw();


	world->PreDraw();
	//world->Draw();
	world->PostDraw();
	
	block->PreDraw();
	block->Draw();
	block->PostDraw();

	item->Draw();
	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			if (map[j][i] == 1 || (map[j][i] == 2 && OnFlag == true)) {
				tst[j][i]->PreDraw();
				tst[j][i]->Draw();
				tst[j][i]->PostDraw();
			}
		}
	}


	goal->PreDraw();
	goal->Draw();
	goal->PostDraw();

	/*hari->PreDraw();
	hari->Draw();
	hari->PostDraw();*/

}
//s�v���C�ƈȊO�̕`��
void DesertField::MyGameDraw(DirectXCommon* dxcomn)
{

	Sprite::PreDraw(dxcomn->GetCmdList());
	background->Draw();
	//setumei->Draw();
	dxcomn->ClearDepthBuffer(dxcomn->GetCmdList());
	Sprite::PostDraw(dxcomn->GetCmdList());


	//�X�v���C�g�̕`��
	SpriteDraw(dxcomn->GetCmdList());

	for (int i = 0; i < 10; i++) {
		if (enemy[i] != nullptr) {
			enemy[i]->Draw(dxcomn);
			enemy[i]->SearchActionDraw(dxcomn);
		}
	}
	//���ʂ̃e�N�X�`���̕`��
	Line::Draw(dxcomn);

	//weffect->Draw(dxcomn);
	GameUI::AllowUIDraw(dxcomn);
	GameUI::TargetUIDraw(dxcomn);
	GameUI::UIDraw(dxcomn);
	GameUI::PlayerUIDraw(dxcomn);

	attackeffects->Draw(dxcomn);
	effects->Draw(dxcomn);
	//FBX�̕`��
	object1->Draw(dxcomn->GetCmdList());

}
#pragma endregion
//���ɓ���
#pragma region
void DesertField::Draw(DirectXCommon* dxcomn)
{
	//�|�X�g�G�t�F�N�g�̏ꍇ�킯(B�łڂ��� D���f�t�H���g)
	switch (c_postEffect)
	{
	case Blur://�ڂ����@�`�揀�Ⴄ����
		postEffect->PreDrawScene(dxcomn->GetCmdList());
		MyGameDraw(dxcomn);
		postEffect->PostDrawScene(dxcomn->GetCmdList());

		dxcomn->BeginDraw();
		postEffect->Draw(dxcomn->GetCmdList());
		ImGuiDraw();//imgui�͍Ō�̕�����Ƃ�
		dxcomn->EndDraw();
		break;

	case Default://���ʂ̂���ɉ����������Ă��Ȃ�
		postEffect->PreDrawScene(dxcomn->GetCmdList());
		postEffect->Draw(dxcomn->GetCmdList());
		postEffect->PostDrawScene(dxcomn->GetCmdList());

		dxcomn->BeginDraw();
		MyGameDraw(dxcomn);
		ImGuiDraw();
		dxcomn->EndDraw();
		break;
	}
}
#pragma endregion

void DesertField::ImGuiDraw()
{
	ImGui::Begin("Obj1");
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(500, 300));
	if (ImGui::TreeNode("light_position")) {
		//ImGui::SliderFloat("positionX", &needlepos.x, -200, 200);
		///ImGui::SliderFloat("positionY", &needlepos.y, -200, 200);
		///ImGui::SliderFloat("positionZ", &needlepos.z, -200, 200);
		if (ImGui::Button("spotlight ON")) {
			lightGroup->SetSpotLightActive(0, true);
		}
		if (ImGui::Button("spotlight OFF")) {
			lightGroup->SetSpotLightActive(0, false);
		}
		ImGui::ColorPicker3("light_color", spotLightColor);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Effect_position")) {
		//ImGui::SliderInt("positionX", &L_Cflag, -200, 200);
		//ImGui::SliderFloat("positionY", &debuga, -200, 200);
		//ImGui::SliderInt("positionZ", &elf, -200, 200);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("enemy_position")) {
		float rf = enemy[0]->GetPosition().x;
		float rf2 = enemy[0]->GetPosition().y;
		float rrr = player->getdis();
		//float rf3 = enemy->GetPosition().z;
		ImGui::SliderInt("positionX", &co, -100, 100);
		ImGui::SliderFloat("positionY", &rf2, -100, 100);
		ImGui::SliderFloat("positionZ", &rrr, -100, 100);
		ImGui::SliderInt("positionX", &co, -200, 200);
		ImGui::SliderFloat("positionY", &rf2, -200, 200);
		ImGui::SliderFloat("positionZ", &rrr, -200, 200);
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
	float sx = player->GetArea_S().x;
	float sy = player->GetArea_S().y;

	float ex = player->GetArea_e().x;
	float ey = player->GetArea_e().y;

	if (ImGui::TreeNode("half")) {
		ImGui::SliderFloat("sx", &sx, -200, 200);
		ImGui::SliderFloat("sy", &sy, -200, 200);
		ImGui::SliderFloat("ex", &ex, -200, 200);
		ImGui::SliderFloat("ey", &ey, -200, 200);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Old")) {
		ImGui::SliderFloat("Old_PosX", &Old_Pos.x, -200, 200);
		ImGui::SliderFloat("old_PosY", &Old_Pos.y, -200, 200);
		ImGui::TreePop();
	}


	/*if (ImGui::TreeNode("1")) {
		ImGui::SliderFloat("+_width", &half_Width, -200, 200);
		ImGui::SliderFloat("+_height", &half_height, -200, 200);
		ImGui::SliderFloat("-_width", &half_Width, -200, 200);
		ImGui::SliderFloat("-_height", &half_height, -200, 200);
		ImGui::SliderFloat("map_1_width", &width, -200, 200);
		ImGui::SliderFloat("map_1_height", &height, -200, 200);
		ImGui::TreePop();
	}*/


	ImGui::End();

	ImGui::Begin("postEffect");
	if (ImGui::RadioButton("Blur", &c_postEffect)) {
		c_postEffect = Blur;
	}
	if (ImGui::RadioButton("Default", &c_postEffect)) {
		c_postEffect = Default;
	}

	ImGui::End();

}
#pragma region �������
void DesertField::Finalize()
{
	//delete sceneManager_;

	//delete efk,efk1;

}
#pragma endregion