//#include "Scene2.h"
//#include "PlayScene.h"
//#include"Input.h"
//#include"DirectXCommon.h"
//#include"ClearScene.h"
//#include"TitleScene.h"
//#include"SceneManager.h"
//#include"MobEnemy.h"
//#include"BossEnemy.h"
//#include"ThrowEnemy.h"
//#include"Line.h"
//#include"Destroy.h"
//#include"Fader.h"
////�R�����g�A�E�g
//
//
////�V�[���̃R���X�g���N�^
//PlayScene::PlayScene(SceneManager* sceneManager)
//	:BaseScene(sceneManager)
//{
//
//}
//
//#pragma region �X�v���C�g�̐���
////�X�v���C�g����
//void PlayScene::SpriteCreate()
//{
//	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
//	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont2.png");
//	//���ʂ̃e�N�X�`��(�X�v���C�g����Ȃ���)
//	Line::Initialize();
//	GameUI::AllowUISet();
//
//	Texture::LoadTexture(6, L"Resources/gomi.png");
//	Texture::LoadTexture(1, L"Resources/background.png");
//	Sprite::LoadTexture(1, L"Resources/haikei2.png");
//	Sprite::LoadTexture(2, L"Resources/setumei.png");
//
//	background = Sprite::Create(1, { 0.0f,0.0f });
//	setumei = Sprite::Create(2, { 0.0f,0.0f });
//	// �f�o�b�O�e�L�X�g������
//	dxcomn = new DirectXCommon();
//	debugText = new DebugTxt();
//	debugText->Initialize(debugTextTexNumber);
//}
//#pragma endregion
//
//#pragma region 
//void PlayScene::ModelCreate()
//{
//	playermodel = Model::CreateFromOBJ("player");
//	player = Player::Create(playermodel);
//	player->Initialize();
//	tstmodel = Model::CreateFromOBJ("box1");
//	goalmodel = Model::CreateFromOBJ("goalmo");
//
//	item = new Item();
//	item->Initialize();
//
//	for (int j = 0; j < MAX_Y; j++) {
//		for (int i = 0; i < MAX_X; i++) {
//			tst[j][i] = std::make_unique<Object3d>();
//			tst[j][i]->Initialize();// Object3d::Create();
//			tst[j][i]->SetModel(tstmodel);
//		}
//	}
//
//	goal = std::make_unique<Object3d>();
//	goal->Initialize();
//	goal->SetModel(goalmodel);
//
//	// ���C�g����
//	lightGroup = LightGroup::Create();
//	// 3D�I�u�G�N�g�Ƀ��C�g���Z�b�g
//	Object3d::SetLightGroup(lightGroup);
//	//�p�����[�^�̐ݒ�
//	lightGroup->SetDirLightActive(0, false);
//	lightGroup->SetDirLightActive(1, false);
//	lightGroup->SetDirLightActive(2, false);
//	lightGroup->SetPointLightActive(0, true);
//	lightGroup->SetPointLightActive(0, false);
//	lightGroup->SetPointLightActive(1, false);
//	lightGroup->SetPointLightActive(2, false);
//	lightGroup->SetSpotLightActive(0, true);
//
//
//	effects = std::make_unique<Effects>();;
//
//	attackeffects = std::make_unique<Effects>();;
//
//	//Player_Pos = player->GetPosition();
//	Player_Rot = player->GetRotation();
//	Player_Scl = player->GetScale();
//	//Fader::SetFeedSprite();
//}
//#pragma endregion
//
//#pragma region �e�p�����[�^�̃Z�b�g
//void PlayScene::SetPrm()
//{
//	half_height = player->GetScale().y;
//	half_Width = player->GetScale().x;
//
//	player->SetPosition({ Player_Pos });
//	player->SetScale({ Player_Scl });
//	player->SetRotation({ Player_Rot });
//
//	for (int j = 0; j < MAX_Y; j++) {
//		for (int i = 0; i < MAX_X; i++) {
//			tst[j][i]->SetPosition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
//			tst[j][i]->SetRotation({ tst_Rot });
//			tst[j][i]->SetScale({ tst_Scl });
//		}
//	}
//	goal->SetPosition({ goal_pos.x,goal_pos.y,goal_pos.z });
//
//	background->SetPosition({ 0, 0 });
//	background->SetSize({ WinApp::window_width,WinApp::window_height });
//	background->setcolor({ 1,1,1,1 });
//}
//#pragma endregion
//
//#pragma region �I�u�W�F�N�g+���C�g�̍X�V����
//void PlayScene::objUpdate()
//{
//	{//���C�g�̃p�����[�^�𔽉f 	
//		lightGroup->SetSpotLightDir(0, XMVECTOR({ spotLightDir[0],spotLightDir[1],spotLightDir[2],0 }));
//		lightGroup->SetSpotLightPos(0, XMFLOAT3(spotLightpos));
//		lightGroup->SetSpotLightColor(0, XMFLOAT3(spotLightColor));
//		lightGroup->SetSpotLightAtten(0, XMFLOAT3(spotLightAtten));
//		lightGroup->SetSpotLightFactorAngle(0, XMFLOAT2(spotLightFactorAngle));
//	}
//	lightGroup->Update();
//
//	player->Update({ 1,1,1,1 });
//
//	for (int j = 0; j < MAX_Y; j++) {
//		for (int i = 0; i < MAX_X; i++) {
//			tst[j][i]->Update({ 1,1,1,1 });
//		}
//	}
//
//	goal->Update({ 1,1,1,1 });
//
//}
//#pragma endregion
//
//#pragma region ������
//void PlayScene::Initialize(DirectXCommon* dxCommon)
//{
//	//
//
//	GameUI::UISpriteSet();
//	GameUI::TargetUISet();
//	GameUI::PlayerUISet();
//	enemy[0] = std::make_unique<MobEnemy>();
//	enemy[1] = std::make_unique<MobEnemy>();
//	enemy[2] = std::make_unique<ThrowEnemy>();
//	enemy[3] = std::make_unique<ThrowEnemy>();
//	enemy[4] = std::make_unique<ThrowEnemy>();
//	enemy[5] = std::make_unique<ThrowEnemy>();
//	enemy[6] = std::make_unique<ThrowEnemy>();
//	enemy[7] = std::make_unique<ThrowEnemy>();
//	enemy[8] = std::make_unique<ThrowEnemy>();
//	enemy[9] = std::make_unique<ThrowEnemy>();
//	//enemy[6] = std::make_unique<ThrowEnemy>();
//	//enemy[0] = new MobEnemy();
//
//	enemy[6]->Setposition({ 270,-18.2,0 });
//	enemy[5]->Setposition({ 170,-18.2,0 });
//	enemy[4]->Setposition({ 320,-14.2,0 });
//	enemy[3]->Setposition({ 80,-4.2,0 });
//	enemy[2]->Setposition({ 250,-4.2,0 });
//	enemy[1]->Setposition({ 350, -18, 0 });
//	enemy[0]->Setposition({ 200, -7, 0 });
//	for (int i = 0; i < emax; i++) {
//		enemy[i]->Initialize();
//	}
//	mapcol = new Collision();
//	c_postEffect = Default;
//
//	collision = new Collision();
//	SpriteCreate();//
//	ModelCreate();//
//
//	// �J��������
//	camera = new DebugCamera(WinApp::window_width, WinApp::window_height/*input*/);
//	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
//	Object3d::SetCamera(camera);
//
//	effects->Initialize(dxCommon, camera);
//	attackeffects->Initialize(dxCommon, camera);
//
//
//	//���f�������w�肵�ăt�@�C���ǂݍ���
//	fbxmodel = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
//
//	//�f�o�C�X���Z�b�g
//	f_Object3d::SetDevice(dxCommon->GetDev());
//	//�J�������Z�b�g
//	f_Object3d::SetCamera(camera);
//	//�O���t�B�b�N�p�C�v���C������
//	f_Object3d::CreateGraphicsPipeline();
//
//	//FBX���f���̐���
//	object1 = new f_Object3d();
//	object1->Initialize();
//	object1->SetModel(fbxmodel);
//	/*audio = new Audio();
//	audio->Initialize();
//	audio->LoopWave("Resources/loop100216.wav", vol);*/
//	postEffect = new PostEffect();
//	postEffect->Initialize();
//
//}
//#pragma endregion
//
//#pragma region �X�V����
//void PlayScene::Update(DirectXCommon* dxCommon)
//{
//	Old_Pos = Player_Pos;
//	spotLightpos[0] = Player_Pos.x;
//	spotLightpos[1] = Player_Pos.y + 10;
//	spotLightpos[2] = 0;
//
//	LONG u_r = 32768;
//	LONG a = 30000;
//
//	//��
//	player->PlayerMoves(Player_Pos, moveSpeed);
//
//	///////// �R���g���[���[ //////////
//	// �X�e�B�b�N�̕�������
//	// �������͈�
//
//	//��
//	// ���������𒲂ׂ���@
//	//if (Input::GetInstance()->GetCMove().lX < u_r - a)
//	//{
//	//	// ���ɌX����
//	//	Player_Pos.x -= moveSpeed;
//
//	//}
//	//else if (Input::GetInstance()->GetCMove().lX > u_r + a)
//	//{
//	//	// �E�ɌX����
//	//	Player_Pos.x += moveSpeed;
//	//}
//
//
//	player->PlayerMoves(Player_Pos, moveSpeed);
//
//	//FBX���f���̍X�V
//	object1->Updata(TRUE);
//	if (Input::GetInstance()->Pushkey(DIK_RIGHT)) {
//		Player_Pos.x += moveSpeed;
//	}
//	if (Input::GetInstance()->Pushkey(DIK_LEFT)) {
//		Player_Pos.x -= moveSpeed;
//	}
//
//	if (jumpFlag == true) {
//		Player_Pos.y += 0.1f;
//		time += 0.02f;
//	}
//
//	///�������ɓ��͏���������
//	////�����蔻��
//
//	float disl;
//	for (int i = 0; i < MAX_X; i++) {
//		for (int j = 0; j < MAX_Y; j++) {
//			if (map[j][i] == 1 || map[j][i] == 2) {
//				if ((Line::GetInstance()->getpos().x + 1.0f > mapx[j][i] - (width) && Line::GetInstance()->getpos().x - 1.0f < mapx[j][i] + (width)) && Line::GetInstance()->getpos().y + 1.0f > mapy[j][i] - height && Line::GetInstance()->getpos().y - 1.0f < mapy[j][i] + height) {
//					if (Line::GetInstance()->Getreturnflag() != true && Line::GetInstance()->Gettriggerflag() == true) {
//						Line::GetInstance()->Setmapcol(true);
//						Line::GetInstance()->Setelf(true);
//					}
//				}
//			}
//		}
//	}
//	//���͏�������ɓ����蔻���`��
//	Collision::ColMap1(map, tst, mapx, mapy, 200, 20, grav, time, moveSpeed, jumpFlag, Player_Pos, Old_Pos);
//
//	if (Player_Pos.x <= goal_pos.x + goal->GetScale().x && Player_Pos.x >= goal_pos.x - goal->GetScale().x && Player_Pos.y <= goal_pos.y + goal->GetScale().y && Player_Pos.y >= goal_pos.y - goal->GetScale().y) {
//		BaseScene* scene = new ClearScene(sceneManager_);//���̃V�[���̃C���X�^���X����
//		sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
//	}
//
//	if (Line::GetInstance()->Getboundflag() == true) {
//		grav = 0;
//		time = 0;
//	}
//
//#pragma region ���̏���
//
//	if (Line::GetInstance()->Getboundflag() == false || Line::GetInstance()->Gettriggerflag() == false) {
//		//grav = 0.0f;
//	} else {
//		grav = 0.03f;
//	}
//
//	time += 0.04f;
//	Player_Pos.y -= grav * time * time;
//
//#pragma endregion
//	//�ő�l������Ƃ��Ɏg���t���O�͂������ŊǗ�
//	colf = Line::GetInstance()->GetColf();
//
//	GameUI::UIUpdate(
//		Line::GetInstance()->GetLength(),//
//		Line::GetInstance()->Gettriggerflag(),//
//		colf,//
//		Line::GetInstance()->Getolddistance());//
//
//	Line::GetInstance()->SetColf(colf);
//
//	//needlepos = Line::GetInstance()->getpos();
//
//	Line::Update(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player, Player_Pos, colf, moveSpeed);
//
//	Line::CollisionEnemy(enemy);
//	//weffect->Update(dxcomn,camera,player[0]->GetPosition(),Line::GetInstance()->Getboundflag());
//	//FBX�̃A�j���[�V�����Đ�
//	if (Input::GetInstance()->Pushkey(DIK_0)) {
//		object1->PlayAnimation();
//	}
//
//	//�J�����֌W�̏���
//	camera->SetTarget({ 0,1,0 });//�����_
//	camera->SetDistance(distance);//
//	camera->SetEye({ Player_Pos.x,Player_Pos.y,Player_Pos.z - 27.0f });
//	camera->SetTarget({ Player_Pos.x,Player_Pos.y ,Player_Pos.z });
//
//	camera->Update();
//
//	player->SetPosition(Player_Pos);
//	player->SetRotation(Player_Rot);
//
//	player->SetScale(Player_Scl);
//
//
//	player->Attack(Player_Pos);
//	player->CollisionAttack(enemy, Player_Pos);
//
//	SetPrm();//�p�����[�^�̃Z�b�g
//
//	objUpdate();//�I�u�W�F�N�g�̍X�V����
//
//	effects->Update(dxCommon, camera, enemy, player);
//
//	//enemy��nullptr�������Ƃ��͓G�����񂾂�
//	for (int i = 0; i < 10; i++) {
//		if (enemy[i] != nullptr) {
//			//�v���C���[�̌��m
//			enemy[i]->Attack(player);
//			enemy[i]->ColMap(map, mapx, mapy, MAX_X, MAX_Y);
//			enemy[i]->Update(Player_Pos);
//
//			enemy[i]->EnemySearchPlayer(player);
//			//�����G�����񂾂�j��
//			if (enemy[i]->GetState_DEAD() == true) {
//				Destroy_unique(enemy[i]);
//
//			}
//		}
//	}
//	item->HealEfficasy(player);
//	item->Update(enemy);
//	//Fader::FeedSpriteUpdate();
//	GameUI::AllowUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player->GetPosition(),
//		Line::GetInstance()->GetlineAngle(), Line::GetInstance()->Gettriggerflag());
//	GameUI::TargetUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), Line::GetInstance()->Getelf());
//	GameUI::PlayerUIUpdate(player);
//	//�V�[���`�F���W
//	if (Input::GetInstance()->TriggerKey(DIK_R) || (Player_Pos.y <= -50)) {//�����ꂽ��
//		BaseScene* scene = new ClearScene(sceneManager_);//���̃V�[���̃C���X�^���X����
//		sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
//		//delete scene;
//	}
//}
//#pragma endregion 
//
////�X�v���C�g�̕`��
//#pragma region ���f���̕`��
//void PlayScene::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
//{
//	player->PreDraw();
//	player->Draw();
//	player->PostDraw();
//
//	for (int i = 0; i < 10; i++) {
//		if (enemy[i] != nullptr) {
//			enemy[i]->Draw();
//		}
//	}
//
//	item->Draw();
//	for (int j = 0; j < MAX_Y; j++) {
//		for (int i = 0; i < MAX_X; i++) {
//			if (map[j][i] == 1 || map[j][i] == 2) {
//				tst[j][i]->PreDraw();
//				tst[j][i]->Draw();
//				tst[j][i]->PostDraw();
//			}
//		}
//	}
//
//	goal->PreDraw();
//	goal->Draw();
//	goal->PostDraw();
//
//}
////s�v���C�ƈȊO�̕`��
//void PlayScene::MyGameDraw(DirectXCommon* dxcomn)
//{
//
//	Sprite::PreDraw(dxcomn->GetCmdList());
//	background->Draw();
//	//setumei->Draw();
//	dxcomn->ClearDepthBuffer(dxcomn->GetCmdList());
//	Sprite::PostDraw(dxcomn->GetCmdList());
//
//
//	//�X�v���C�g�̕`��
//	SpriteDraw(dxcomn->GetCmdList());
//
//
//	//���ʂ̃e�N�X�`���̕`��
//	Line::Draw(dxcomn);
//
//	//weffect->Draw(dxcomn);
//	GameUI::AllowUIDraw(dxcomn);
//	GameUI::TargetUIDraw(dxcomn);
//	GameUI::UIDraw(dxcomn);
//	GameUI::PlayerUIDraw(dxcomn);
//
//	attackeffects->Draw(dxcomn);
//	effects->Draw(dxcomn);
//	//FBX�̕`��
//	object1->Draw(dxcomn->GetCmdList());
//
//}
//#pragma endregion
////���ɓ���
//#pragma region
//void PlayScene::Draw(DirectXCommon* dxcomn)
//{
//	//�|�X�g�G�t�F�N�g�̏ꍇ�킯(B�łڂ��� D���f�t�H���g)
//	switch (c_postEffect)
//	{
//	case Blur://�ڂ����@�`�揀�Ⴄ����
//		postEffect->PreDrawScene(dxcomn->GetCmdList());
//		MyGameDraw(dxcomn);
//		postEffect->PostDrawScene(dxcomn->GetCmdList());
//
//		dxcomn->BeginDraw();
//		postEffect->Draw(dxcomn->GetCmdList());
//		ImGuiDraw();//imgui�͍Ō�̕�����Ƃ�
//		dxcomn->EndDraw();
//		break;
//
//	case Default://���ʂ̂���ɉ����������Ă��Ȃ�
//		postEffect->PreDrawScene(dxcomn->GetCmdList());
//		postEffect->Draw(dxcomn->GetCmdList());
//		postEffect->PostDrawScene(dxcomn->GetCmdList());
//
//		dxcomn->BeginDraw();
//		MyGameDraw(dxcomn);
//		ImGuiDraw();
//		dxcomn->EndDraw();
//		break;
//	}
//}
//#pragma endregion
//
//void PlayScene::ImGuiDraw()
//{
//	ImGui::Begin("Obj1");
//	ImGui::SetWindowPos(ImVec2(0, 0));
//	ImGui::SetWindowSize(ImVec2(500, 300));
//	if (ImGui::TreeNode("light_position")) {
//		if (ImGui::Button("spotlight ON")) {
//			lightGroup->SetSpotLightActive(0, true);
//		}
//		if (ImGui::Button("spotlight OFF")) {
//			lightGroup->SetSpotLightActive(0, false);
//		}
//		ImGui::ColorPicker3("light_color", spotLightColor);
//		ImGui::TreePop();
//	}
//
//	if (ImGui::TreeNode("Effect_position")) {
//		//ImGui::SliderInt("positionX", &L_Cflag, -200, 200);
//		//ImGui::SliderFloat("positionY", &debuga, -200, 200);
//		//ImGui::SliderInt("positionZ", &elf, -200, 200);
//		ImGui::TreePop();
//	}
//	if (ImGui::TreeNode("enemy_position")) {
//
//		ImGui::TreePop();
//	}
//	float linex = Line::GetInstance()->getpos().x;
//	float liney = Line::GetInstance()->getpos().y;
//	float rr = player->GetPosition().x;
//	if (ImGui::TreeNode("Player_position")) {
//		ImGui::SliderFloat("positionX", &linex, -200, 200);
//		ImGui::SliderFloat("positionY", &liney, -200, 200);
//		ImGui::SliderFloat("positionZ", &Player_Pos.z, -200, 200);
//		ImGui::SliderFloat("grav", &grav, -200, 200);
//		ImGui::SliderFloat("time", &time, -200, 200);
//		ImGui::TreePop();
//	}
//
//	if (ImGui::TreeNode("Old")) {
//		ImGui::SliderFloat("Old_PosX", &Old_Pos.x, -200, 200);
//		ImGui::SliderFloat("old_PosY", &Old_Pos.y, -200, 200);
//		ImGui::TreePop();
//	}
//
//	ImGui::End();
//
//	ImGui::Begin("postEffect");
//	if (ImGui::RadioButton("Blur", &c_postEffect)) {
//		c_postEffect = Blur;
//	}
//	if (ImGui::RadioButton("Default", &c_postEffect)) {
//		c_postEffect = Default;
//	}
//
//	ImGui::End();
//
//}
//#pragma region �������
//void PlayScene::Finalize()
//{
//	//delete sceneManager_;
//
//	//delete efk,efk1;
//
//}
//#pragma endregion