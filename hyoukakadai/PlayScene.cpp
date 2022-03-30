#include "PlayScene.h"
#include"Input.h"
#include"DirectXCommon.h"
#include"TitleScene.h"
#include"SceneManager.h"
#include"MobEnemy.h"
#include"BossEnemy.h"

//�R�����g�A�E�g

//�V�[���̃R���X�g���N�^
PlayScene::PlayScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}

#pragma region �X�v���C�g�̐���
//�X�v���C�g����
void PlayScene::SpriteCreate()
{
	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont2.png");
	Sprite::LoadTexture(1, L"Resources/0057b6fa9ec85ae.jpg");
	Sprite::LoadTexture(2, L"Resources/tyuta_C.png");

	//���ʂ̃e�N�X�`��(�X�v���C�g����Ȃ���)
	Texture::LoadTexture(6, L"Resources/DQVDS_-_Mechanowyrm.png");
	Texture::LoadTexture(1, L"Resources/ball.png");
	mech = Texture::Create(6, { 0,-50,50 }, { 2,2,2 }, {1,1,1,1});
	zukki = Texture::Create(1, { 0,-20,50 }, { 2,2,2 }, { 1,1,1,1 });
	mech->CreateTexture();
	zukki->CreateTexture();

	background = Sprite::Create(1, { 0.0f,-200.0f });
	// �f�o�b�O�e�L�X�g������
	dxcomn = new DirectXCommon();
	debugText = new DebugTxt();
	debugText->Initialize(debugTextTexNumber);
}
#pragma endregion

#pragma region ���f���ƃG�t�F�N�g�ƃ��C�g�̃C���X�^���X����
void PlayScene::ModelCreate()
{
	//a
	playermodel = Model::CreateFromOBJ("chr_sword");
	itomodel = Model::CreateFromOBJ("ito");
	tstmodel = Model::CreateFromOBJ("block");


	

	ito = Object3d::Create();
	ito->SetModel(itomodel);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			tst[i][j] = Object3d::Create();
			tst[i][j]->SetModel(tstmodel);
		}
	}
	test = Object3d::Create();
	test->SetModel(tstmodel);

	sentan = Object3d::Create();
	sentan->SetModel(tstmodel);

	for (int i = 0; i < 10; i++) {
		player[i] = Object3d::Create();
		player[i]->SetModel(playermodel);
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
	//pointLightPos[0] = 0.0f;
	//pointLightPos[1] = 1.0f;
	//pointLightPos[2] = 0.0f;
	lightGroup->SetPointLightActive(0, false);
	lightGroup->SetPointLightActive(1, false);
	lightGroup->SetPointLightActive(2, false);
	lightGroup->SetSpotLightActive(0, true);


	effects = new Effects();

}
#pragma endregion

#pragma region �e�p�����[�^�̃Z�b�g
void PlayScene::SetPrm()
{
	//Scale,Position,Size
	//ito_Pos = Player_Pos;
	Player_Scl = { 1,1,1 };
	//ito_Scl = { 1,1,1 };
	for (int i = 0; i < 10; i++) {
		player[i]->SetPosition({ Player_Pos[i] });
		player[i]->SetScale({ Player_Scl });
	}
	ito->SetPosition({ ito_Pos });
	ito->SetScale({ ito_Scl });
	ito->SetRotation({ ito_Rot });
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			tst[j][i]->SetPosition({ tst_Pos.x+2*j,tst_Pos.y-2-2*i ,tst_Pos.z });
			tst[j][i]->SetRotation({ tst_Rot });
			tst[j][i]->SetScale({ tst_Scl });
		}
	}
	

	test->SetPosition({ tst_Pos.x - 2,tst_Pos.y,tst_Pos.z });
	sentan->SetPosition({ sentan_Pos });
	
}
#pragma endregion

#pragma region �I�u�W�F�N�g+���C�g�̍X�V����
void PlayScene::objUpdate()
{
	{//���C�g�̃p�����[�^�𔽉f 	
		lightGroup->SetSpotLightDir(0, XMVECTOR({ spotLightDir[0],spotLightDir[1],spotLightDir[2],0 }));
		lightGroup->SetSpotLightPos(0, XMFLOAT3(spotLightpos));
		lightGroup->SetSpotLightColor(0, XMFLOAT3(spotLightColor));
		lightGroup->SetSpotLightAtten(0, XMFLOAT3(spotLightAtten));
		lightGroup->SetSpotLightFactorAngle(0, XMFLOAT2(spotLightFactorAngle));
	}
	lightGroup->Update();
	for (int i = 0; i < 10; i++) {
		player[i]->Update({ 1,1,1,1 });
	}
	ito->Update({ 1,1,1,1 });
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			tst[j][i]->Update({ 1,1,1,1 });
		}
	}
	
	sentan->Update({ 1,1,1,1 });
	test->Update({ 1,1,1,1 });
}
#pragma endregion

#pragma region ������
void PlayScene::Initialize(DirectXCommon* dxCommon)
{
	//
	c_postEffect = Default;

	collision = new Collision();
	SpriteCreate();//
	ModelCreate();//

	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height/*input*/);
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);


	effects->Initialize(dxCommon, camera);
	spotLightpos[0] = 10;
	spotLightpos[2] = 0;

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
	postEffect = new PostEffect();
	postEffect->Initialize();

	
	
}
#pragma endregion

#pragma region �X�V����
void PlayScene::Update(DirectXCommon* dxCommon)
{
	Input::MouseMove mouseMove = Input::GetInstance()->GetMouseMove();
	//�}�E�X�̓��͏�Ԏ擾
	if (Input::GetInstance()->PushMouseLeft()) {
		dy = (float)mouseMove.lX;
		dx = (float)mouseMove.lY;
		dz = (float)mouseMove.lZ;
		//Player_Rot.y -= -dy * 0.2;
		//Player_Rot.z -= dx * 0.2;
	}
	effects->Update(dxCommon, camera);
	//�����蔻��
//	if (collision->CheckSphere2Sphere() == TRUE) {
		//debugText->Print("Hit", 950, 20, 3.0f);
	//}

	ito_PS.x = ito_Pos.x + (ito_Scl.x/4);
	sentan_Pos = ito_PS;
	sentan_Rot = ito_Rot;

	

	if (Input::GetInstance()->Pushkey(DIK_RIGHT)) {
		Player_Pos[0].x += 0.5f; 
		//ito_Pos.x += 1;
	}
	if (Input::GetInstance()->Pushkey(DIK_LEFT)) {
		Player_Pos[0].x -= 0.5f;
		//ito_Pos.x -= 1;
	}
	

	if (Input::GetInstance()->Pushkey(DIK_1)) {
		ito_Rot.z++;
		ito_Scl.x = 4;
		//ito_rad = ito_Rot.y * 3.14 / 180;
	}
	

	if (Input::GetInstance()->Pushkey(DIK_2)) {
		tst_Pos.x++;
	}
	if (Input::GetInstance()->Pushkey(DIK_3)) {
		tst_Rot.y++;
	}
	if (Input::GetInstance()->Pushkey(DIK_4)) {
		tst_Rot.z++;
	}


	if (Input::GetInstance()->Pushkey(DIK_SPACE)) {
		Line = 1;
		//ito_Scl.y+=1;
	}

	if (Line == 1) {
		Limit-=0.1f;
		vec_x = speed;
		if (vec_x != 0.0f ) {
			length = sqrtf(vec_x * vec_x );
			normal_x = vec_x / length;
			normal_x *= speed;
			if (Limit <= 0) {
				normal_x = -normal_x;
				speed = -1;
				if (ito_Scl.x == old_Scl.x) {
					Line = 0;
					Limit = 4;
				}
			}
			ito_Scl.x += normal_x;
		}
	}
	

	if (Line == 0) {
		ito_Scl = old_Scl;
		ito_Pos = Player_Pos[0];
		Limitsave = Limit;
		zanzouSpeed = 0;
	}

	

	//if (Line == 1 && Limit > 0) {
	//	ito_rad = ito_PS.x / cosf(ito_Rot.z);
	//	if ( ito_PS.x > tst_Pos.x + (tst_Scl.x / 2)   /*ito_rad >= tst_Pos.x + (tst_Scl.x / 2)*/) {
	//		ito_speed.x = 0;
	//		Limit = Limitsave;
	//		Player_Pos[0].x++;
	//		zanzouSpeed = 0.5f;
	//	}
	//}

	for (int i = 9; i > 0; i--) {
		Player_Pos[i].x = Player_Pos[i - 1].x + zanzouSpeed;
	}
	
	//FBX�̃A�j���[�V�����Đ�
	if (Input::GetInstance()->Pushkey(DIK_0)) {
		object1->PlayAnimation();
	}
	//FBX���f���̍X�V
	object1->Updata(TRUE);
	
	mech->SetPosition(texpo);
	mech->Update(camera->GetViewMatrix(), camera->GetViewProjectionMatrix());
	zukki->Update(camera->GetViewMatrix(), camera->GetViewProjectionMatrix());

	//�J�����֌W�̏���
	camera->SetTarget({ 0,1,0 });//�����_
	camera->SetDistance(distance);//
	camera->SetEye({ Player_Pos[0].x,Player_Pos[0].y + 5,Player_Pos[0].z - 25 });
	camera->SetTarget({ Player_Pos[0].x,Player_Pos[0].y + 5,Player_Pos[0].z });
	camera->Update();

	SetPrm();//�p�����[�^�̃Z�b�g
	
	objUpdate();//�I�u�W�F�N�g�̍X�V����

	//�V�[���`�F���W
	if (Input::GetInstance()->TriggerKey(DIK_R)) {//�����ꂽ��
	BaseScene* scene = new TitleScene(sceneManager_);//���̃V�[���̃C���X�^���X����
	sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
	}
}
#pragma endregion 

//�X�v���C�g�̕`��
#pragma region ���f���̕`��
void PlayScene::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{
	for (int i = 0; i < 10; i++) {
		player[i]->PreDraw();
		player[i]->Draw();
		player[i]->PostDraw();
	}
	

	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			if (map[j][i] == 1) {
				tst[i][j]->PreDraw();
				tst[i][j]->Draw();
				tst[i][j]->PostDraw();
			}
		}
	}

	ito->PreDraw();
	ito->Draw();
	ito->PostDraw();

	

	//test->PreDraw();
	//test->Draw();
	//test->PostDraw();

	/*sentan->PreDraw();
	sentan->Draw();
	sentan->PostDraw();*/
	
	/*if (radY <= tst_Pos.y ) {
		debugText->Print("Hit", 0, 0, 10);
	}*/


	Sprite::PreDraw(cmdList);
	//// �w�i�X�v���C�g�`��
	debugText->DrawAll(DirectXCommon::GetInstance()->GetCmdList());
	//// �X�v���C�g�`��㏈��
	Sprite::PostDraw(cmdList);
}
//s�v���C�ƈȊO�̕`��
void PlayScene::MyGameDraw(DirectXCommon* dxcomn)
{
	//�X�v���C�g�̕`��
	SpriteDraw(dxcomn->GetCmdList());
	
	//���ʂ̃e�N�X�`���̕`��
	Texture::PreDraw(dxcomn->GetCmdList());
	//zukki->Draw();//�Y�b�L�[�j���̉摜
	//mech->Draw();//���J�o�[���̉摜
	Texture::PostDraw();
	
	effects->Draw(dxcomn);
	//FBX�̕`��
	object1->Draw(dxcomn->GetCmdList());
}
#pragma endregion
//���ɓ���
#pragma region �`��(imgui�ƃX�v���C�g�ƃ��f���܂Ƃ߂�����)
void PlayScene::Draw(DirectXCommon* dxcomn)
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

void PlayScene::ImGuiDraw()
{
	ImGui::Begin("Obj1");
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(500, 300));
	if (ImGui::TreeNode("light_position")) {
		ImGui::SliderFloat("positionX", &spotLightpos[0], -100, 100);
		ImGui::SliderFloat("positionY", &spotLightpos[1], -100, 100);
		ImGui::SliderFloat("positionZ", &spotLightpos[2], -100, 100);
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
		ImGui::SliderFloat("positionX", &efkposition.x, -100, 100);
		ImGui::SliderFloat("positionY", &efkposition.y, -100, 100);
		ImGui::SliderFloat("positionZ", &efkposition.z, -100, 100);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Texture_position")) {
		ImGui::SliderFloat("positionX", &texpo.x, -100, 100);
		ImGui::SliderFloat("positionY", &texpo.y, -100, 100);
		ImGui::SliderFloat("positionZ", &texpo.z, -100, 100);
		ImGui::TreePop();
	}


	ImGui::End();

	ImGui::Begin("postEffect");
	if(ImGui::RadioButton("Blur", &c_postEffect)) {
		c_postEffect = Blur;
	}
	if (ImGui::RadioButton("Default", &c_postEffect)) {
		c_postEffect = Default;
	}

	ImGui::End();

}
#pragma region �������
void PlayScene::Finalize()
{	
	//delete efk,efk1;
	delete mech, zukki;
	delete player;
	delete debugText;
	delete collision;
	delete lightGroup;
	delete camera;
	delete background;
}
#pragma endregion