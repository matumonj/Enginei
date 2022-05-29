#include"LastBossScene.h"
#include"Input.h"
#include"DirectXCommon.h"
#include"ClearScene.h"
#include"SceneManager.h"
#include"MobEnemy.h"
#include"ThrowEnemy.h"
#include"Line.h"
#include"Destroy.h"
#include"Fader.h"
#include"GamOver.h"
#include"StageSelect.h"
#include"Retry.h"
#include"LastBoss.h"
//コメントアウト


//シーンのコンストラクタ
LastBossScene::LastBossScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}

#pragma region スプライトの生成
//スプライト生成
void LastBossScene::SpriteCreate()
{
	// デバッグテキスト用テクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont2.png");
	//普通のテクスチャ(スプライトじゃないよ)
	Line::Initialize();
	GameUI::AllowUISet();

	Texture::LoadTexture(6, L"Resources/gomi.png");
	Texture::LoadTexture(1, L"Resources/background.png");
	Sprite::LoadTexture(1, L"Resources/haikei2.png");
	Sprite::LoadTexture(2, L"Resources/setumei.png");


	background = Sprite::Create(1, { 0.0f,0.0f });
	//setumei = Sprite::Create(2, { 0.0f,0.0f });
	// デバッグテキスト初期化
	//dxcomn = new DirectXCommon();
	//debugText = new DebugTxt();
	//debugText->Initialize(debugTextTexNumber);
}
#pragma endregion

#pragma region 
void LastBossScene::ModelCreate()
{
	playermodel = Model::CreateFromOBJ("player");
	player = Player::Create(playermodel);
	player->Initialize();
<<<<<<< HEAD
	tstmodel = Model::CreateFromOBJ("sea");
	//worldmodel = Model::CreateFromOBJ("skydome");
	//harimodel = Model::CreateFromOBJ("hari");
=======
	tstmodel = Model::CreateFromOBJ("casle");
	worldmodel = Model::CreateFromOBJ("skydome");
	harimodel = Model::CreateFromOBJ("hari");
>>>>>>> 2293fa0c16c4ff46c3456a0c8fd4274e37e3fb0e
	goalmodel = Model::CreateFromOBJ("goal");


	item = new Item();
	item->Initialize();
	//collision = new Collision();

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

	// ライト生成
	lightGroup = LightGroup::Create();
	// 3Dオブエクトにライトをセット
	Object3d::SetLightGroup(lightGroup);
	//パラメータの設定
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

#pragma region 各パラメータのセット
void LastBossScene::SetPrm()
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

			if (map[j][i] == 3) {
				goal->SetPosition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
				goal->SetRotation({ 0,120,0 });
				goal->SetScale({ tst_Scl });
			}
		}
	}

	background->SetPosition({ 0, 0 });
	background->SetSize({ WinApp::window_width,WinApp::window_height });
	background->setcolor({ 1,1,1,1 });

	object1->SetPosition({ Player_Pos });
	object1->SetRotation({ Player_Rot });
}
#pragma endregion

#pragma region オブジェクト+ライトの更新処理
void LastBossScene::objUpdate()
{
	{//ライトのパラメータを反映 	
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

#pragma region 初期化
void LastBossScene::Initialize(DirectXCommon* dxCommon)
{
	//

	GameUI::UISpriteSet();
	GameUI::TargetUISet();
	GameUI::PlayerUISet();
	bossenemy= std::make_unique<LastBoss>();
	bossenemy->Initialize();
	
	SpriteCreate();//
	ModelCreate();//

	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height/*input*/);
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);

	effects->Initialize(dxCommon, camera);
	attackeffects->Initialize(dxCommon, camera);


	//モデル名を指定してファイル読み込み
	fbxmodel = FbxLoader::GetInstance()->LoadModelFromFile("Knight");

	//デバイスをセット
	f_Object3d::SetDevice(dxCommon->GetDev());
	//カメラをセット
	f_Object3d::SetCamera(camera);
	//グラフィックパイプライン生成
	f_Object3d::CreateGraphicsPipeline();

	//FBXモデルの生成
	object1 = new f_Object3d();
	object1->Initialize(dxCommon, camera);
	object1->SetModel(fbxmodel);
	/*audio = new Audio();
	audio->Initialize();
	audio->LoopWave("Resources/loop100216.wav", vol);*/
	object1->PlayAnimation();
}
#pragma endregion

#pragma region 更新処理
void LastBossScene::Update(DirectXCommon* dxCommon)
{
	if (Collision::GetInstance()->Gethit() == true) {
		loadf = false;
		Fader::feedOut(0.0f, 0.1f);
		if (Fader::GetInstance()->GetAlpha() <= 0.0f) {
			//::GetInstance()->SetHit(false);
		}
	} else {
		loadf = true;
	}
	GameUI::NowLoadUpdate(loadf);
	Old_Pos = Player_Pos;
	spotLightpos[0] = Player_Pos.x;
	spotLightpos[1] = Player_Pos.y + 10;
	spotLightpos[2] = 0;

	if (Line::GetInstance()->Gettriggerflag() != true || Line::GetInstance()->Getboundflag() == true) {
		player->PlayerMoves(Player_Pos, moveSpeed, jumpFlag, grav, time, Player_Rot);

	}

	//FBXモデルの更新
	object1->Updata({ 1,1,1,1 }, dxCommon, camera, TRUE);


	Collision::CollisionMap(map, tst, mapx, mapy, MAX_X, MAX_Y, grav, time, moveSpeed, jumpFlag, Player_Pos, Player_Scl, Old_Pos, 1);

	if (Collision::GoalCollision(map, tst, mapx, mapy, MAX_X, MAX_Y, grav, time, moveSpeed, jumpFlag, Player_Pos, Player_Scl, Old_Pos, 3) == true)
	{
		goalflag = true;
		jumpFlag = false;
		moveSpeed = 0;
		goaltime += 0.01f;
		goalSpeed = 0.01f;
		Player_Pos.x += goalSpeed;
		if (goaltime >= 1) {
			goaltime = 1;
			Player_Pos.z += 0.01f;
			Player_Rot.y--;
			if (Player_Rot.y <= 0) {
				Player_Rot.y = 0;
			}
			if (Player_Pos.z >= 1) {
				BaseScene* scene = new  StageSelect(sceneManager_);//次のシーンのインスタンス生成
				sceneManager_->SetnextScene(scene);//シーンのセット
			}
		}
	}


	if (Line::GetInstance()->Getboundflag() == true) {
		grav = 0;
		time = 0;
	}

#pragma region 線の処理


	if (Line::GetInstance()->Getboundflag() == false || Line::GetInstance()->Gettriggerflag() == false) {
		//grav = 0.0f;
	} else {
		grav = 0.03f;
	}

	time += 0.04f;
	Player_Pos.y -= grav * time * time;

#pragma endregion
	//最大値が減るときに使うフラグはこっちで管理
	colf = Line::GetInstance()->GetColf();

	GameUI::UIUpdate(
		Line::GetInstance()->GetLength(),//
		Line::GetInstance()->Gettriggerflag(),//
		colf,//
		Line::GetInstance()->Getolddistance());//

	Line::GetInstance()->SetColf(colf);
	Line::Update(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player, Player_Pos, colf, moveSpeed);

	Line::CollisionEnemys(&bossenemy);


	//カメラ関係の処理
	if (Player_Pos.x <= 27.0f) {
		camera->SetTarget({ 0,1,0 });//注視点
		camera->SetDistance(distance);//
		camera->SetEye({ 27.0f,Player_Pos.y,Player_Pos.z - 27.0f });
		camera->SetTarget({ 27.0f,Player_Pos.y,Player_Pos.z });
	}

	else if (Player_Pos.x >= 368.0f) {
		camera->SetTarget({ 0,1,0 });//注視点
		camera->SetDistance(distance);//
		camera->SetEye({ 368.0f,Player_Pos.y,Player_Pos.z - 27.0f });
		camera->SetTarget({ 368.0f,Player_Pos.y ,Player_Pos.z });
	} else {
		camera->SetTarget({ 0,1,0 });//注視点
		camera->SetDistance(distance);//
		camera->SetEye({ Player_Pos.x,Player_Pos.y,Player_Pos.z - 27.0f });
		camera->SetTarget({ Player_Pos.x,Player_Pos.y,Player_Pos.z });
	}

	camera->Update();

	player->Attack(Player_Pos);
	//for (int i = 0; i < 2; i++) {
	player->CollisionAttack(&bossenemy, Player_Pos);
	SetPrm();//パラメータのセット

	objUpdate();//オブジェクトの更新処理

	effects->Update(dxCommon, camera, &bossenemy, player);
	//enemyにnullptr代入するときは敵が死んだら
	//for (int i = 0; i < 10; i++) {
		if (bossenemy != nullptr) {
			//プレイヤーの検知
			bossenemy->Motion(player);
			bossenemy->ColMap(map, tst, mapx, mapy, MAX_X, MAX_Y);
			bossenemy->Attack(player);
			bossenemy->Update(Player_Pos);

			bossenemy->EnemySearchPlayer(player);
			bossenemy->SearchAction(camera->GetViewMatrix(), camera->GetProjectionMatrix(), Player_Pos);

			//もし敵が死んだら破棄
			if (bossenemy->GetState_DEAD() == true) {
				Destroy_unique(bossenemy);

			}
		//	LastBoss::GetInstance()->ZAttackTex(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player);

		}

		effects->BossAttackEffect(dxCommon, camera, j, LastBoss::GetInstance()->GetAtc(), LastBoss::GetInstance()->Gettexpos());

	item->HealEfficasy(player);
	item->Update(&bossenemy);

	Fader::FeedSpriteUpdate();
	GameUI::AllowUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player->GetPosition(),
		Line::GetInstance()->GetlineAngle(), Line::GetInstance()->Gettriggerflag());
	GameUI::TargetUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), Line::GetInstance()->Getelf());
	GameUI::PlayerUIUpdate(player);
	//シーンチェンジ
	if (Input::GetInstance()->TriggerKey(DIK_R) || (Player_Pos.y <= -50)) {//押されたら
		Retry::SetStage(Jungle_1_1);
		BaseScene* scene = new GamOver(sceneManager_);//次のシーンのインスタンス生成
		sceneManager_->SetnextScene(scene);//シーンのセット
		//delete scene;
	}
}
#pragma endregion 

//スプライトの描画
#pragma region モデルの描画
void LastBossScene::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{


	player->PreDraw();
	//player->Draw();
	player->PostDraw();


	item->Draw();
	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			if (map[j][i] == 1) {
				tst[j][i]->PreDraw();
				tst[j][i]->Draw();
				tst[j][i]->PostDraw();
			}

			if (map[j][i] == 3) {
				goal->PreDraw();
				goal->Draw();
				goal->PostDraw();
			}
		}
	}




}
//sプライと以外の描画
void LastBossScene::MyGameDraw(DirectXCommon* dxcomn)
{

	Sprite::PreDraw(dxcomn->GetCmdList());
	background->Draw();
	//setumei->Draw();
	dxcomn->ClearDepthBuffer(dxcomn->GetCmdList());
	Sprite::PostDraw(dxcomn->GetCmdList());


	//スプライトの描画
	SpriteDraw(dxcomn->GetCmdList());
	if (bossenemy != nullptr) {
			bossenemy->Draw(dxcomn);
			bossenemy->SearchActionDraw(dxcomn);
		}
	LastBoss::GetInstance()->Drawtex(dxcomn);
	//普通のテクスチャの描画
	Line::Draw(dxcomn);

	//weffect->Draw(dxcomn);
	GameUI::AllowUIDraw(dxcomn);
	GameUI::TargetUIDraw(dxcomn);
	GameUI::UIDraw(dxcomn);
	GameUI::PlayerUIDraw(dxcomn);

	attackeffects->Draw(dxcomn);
	effects->Draw(dxcomn);
	//FBXの描画
	object1->Draw(dxcomn->GetCmdList());

}
#pragma endregion
//↓に入る
#pragma region
void LastBossScene::Draw(DirectXCommon* dxcomn)
{

		dxcomn->BeginDraw();
		MyGameDraw(dxcomn);
		ImGuiDraw();
		dxcomn->EndDraw();
}
#pragma endregion

void LastBossScene::ImGuiDraw()
{
	ImGui::Begin("Obj1");
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(500, 300));
	if (ImGui::TreeNode("Old")) {
		float cx = LastBoss::GetInstance()->Gettexpos().x;
		float cy = LastBoss::GetInstance()->Gettexpos().y;

		ImGui::SliderFloat("Old_PosX", &cx, -200, 200);
		ImGui::SliderFloat("old_PosY", &cy, -200, 200);
		ImGui::TreePop();
	}

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

	
	ImGui::End();

}
#pragma region 解放部分
void LastBossScene::Finalize()
{
	//delete sceneManager_;
	delete dxcomn;
	delete background;

		bossenemy.reset();
	//Enemy* enemy[2];
	effects.reset();
	attackeffects.reset();
	
	delete player;
	//std::unique_ptr<Object3d>player[10];
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 200; j++) {
			tst[i][j].reset();
		}
	}


	goal.reset();

	Line::Finalize();
	GameUI::Finalize();
	delete object1;
	delete fbxmodel;
	delete playermodel;
	delete tstmodel;
	delete goalmodel;
	delete camera;
	delete item;
	//delete efk,efk1;

}
#pragma endregion