#include "SeaScene1.h"
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
#include"StageSelect.h"
#include"GamOver.h"
#include"Retry.h"
//コメントアウト


//シーンのコンストラクタ
SeaScene1::SeaScene1(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}

#pragma region スプライトの生成
//スプライト生成
void SeaScene1::SpriteCreate()
{
	// デバッグテキスト用テクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont2.png");
	//普通のテクスチャ(スプライトじゃないよ)
	Line::Initialize();
	GameUI::AllowUISet();

	Texture::LoadTexture(6, L"Resources/gomi.png");
	Texture::LoadTexture(1, L"Resources/background.png");
	Sprite::LoadTexture(1, L"Resources/hamabe.png");
	Sprite::LoadTexture(2, L"Resources/setumei.png");

	mech = std::make_unique<Texture>();
	mech->Create(6, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });// = Texture::Create(6, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });

	zukki = std::make_unique<Texture>();
	zukki->Create(1, { 0,-20,50 }, { 1,1,1 }, { 1,1,1,1 });

	background = Sprite::Create(1, { 0.0f,0.0f });
	setumei = Sprite::Create(2, { 0.0f,0.0f });
	// デバッグテキスト初期化
	dxcomn = new DirectXCommon();
	debugText = new DebugTxt();
	debugText->Initialize(debugTextTexNumber);
}
#pragma endregion

#pragma region 
void SeaScene1::ModelCreate()
{
	playermodel = Model::CreateFromOBJ("player");
	player = Player::Create(playermodel);
	player->Initialize();
	tstmodel = Model::CreateFromOBJ("sand");
	worldmodel = Model::CreateFromOBJ("skydome");
	harimodel = Model::CreateFromOBJ("hari");
	goalmodel = Model::CreateFromOBJ("goal");
	seamodel = Model::CreateFromOBJ("sea");

	item = new Item();
	item->Initialize();
	item1 = new Item();
	item1->Initialize();
	collision = new Collision();

	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			tst[j][i] = std::make_unique<Object3d>();
			tst[j][i]->Initialize();// Object3d::Create();
			tst[j][i]->SetModel(tstmodel);

			seablock[j][i] = std::make_unique<Object3d>();
			seablock[j][i]->Initialize();
			seablock[j][i]->SetModel(seamodel);
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
void SeaScene1::SetPrm()
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

			seablock[j][i]->SetPosition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			seablock[j][i]->SetRotation({ tst_Rot });
			seablock[j][i]->SetScale({ tst_Scl });

			if (map[j][i] == 3) {
				goal->SetPosition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
				goal->SetRotation({ 0,120,0 });
				goal->SetScale({ tst_Scl });
			}
		}
	}


	block->SetPosition({ block_pos });
	block->SetScale({ block_Scl });

	world->SetPosition({ 0,0,0 });
	world->SetScale({ 1,1,1 });

	sentan->SetPosition({ sentan_Pos });

	background->SetPosition({ 0, 0 });
	background->SetSize({ WinApp::window_width,WinApp::window_height });
	background->setcolor({ 1,1,1,1 });

	object1->SetPosition({ Player_Pos });
	object1->SetRotation({ Player_Rot });
}
#pragma endregion

#pragma region オブジェクト+ライトの更新処理
void SeaScene1::objUpdate()
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
			seablock[j][i]->Update({ 1,1,1,1 });
		}
	}

	world->Update({ 1,1,1,1 });
	block->Update({ 1,1,1,1 });
	hari->Update({ 1,1,1,1 });

	goal->Update({ 1,1,1,1 });

}
#pragma endregion

#pragma region 初期化
void SeaScene1::Initialize(DirectXCommon* dxCommon)
{
	//

	GameUI::UISpriteSet();
	GameUI::TargetUISet();
	GameUI::PlayerUISet();
	enemy[0] = std::make_unique<MobEnemy>();
	enemy[1] = std::make_unique<MobEnemy>();
	enemy[2] = std::make_unique<ThrowEnemy>();
	enemy[3] = std::make_unique<ThrowEnemy>();
	enemy[4] = std::make_unique<ThrowEnemy>();
	enemy[5] = std::make_unique<ThrowEnemy>();
	enemy[6] = std::make_unique<ThrowEnemy>();
	enemy[7] = std::make_unique<ThrowEnemy>();
	enemy[8] = std::make_unique<ThrowEnemy>();
	enemy[9] = std::make_unique<ThrowEnemy>();

	enemy1[0] = std::make_unique<MobEnemy>();
	enemy1[1] = std::make_unique<MobEnemy>();
	enemy1[2] = std::make_unique<ThrowEnemy>();
	enemy1[3] = std::make_unique<ThrowEnemy>();
	enemy1[4] = std::make_unique<ThrowEnemy>();
	enemy1[5] = std::make_unique<ThrowEnemy>();
	enemy1[6] = std::make_unique<ThrowEnemy>();
	enemy1[7] = std::make_unique<ThrowEnemy>();
	enemy1[8] = std::make_unique<ThrowEnemy>();
	enemy1[9] = std::make_unique<ThrowEnemy>();

	for (int i = 0; i < 10; i++) {
		enemy[i]->Initialize();
		enemy1[i]->Initialize();
	}

	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			if (map[j][i] == 4) {
				enemy[0]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}
			else if (map[j][i] == 5) {
				enemy[1]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}
			else if (map[j][i] == 6) {
				enemy[2]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}
			else if (map[j][i] == 7) {
				enemy[3]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}
			else if (map[j][i] == 8) {
				enemy[4]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}
			else if (map[j][i] == 9) {
				enemy[5]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}
			else if (map[j][i] == 10) {
				enemy[6]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}
			else if (map[j][i] == 11) {
				enemy[7]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}
			else if (map[j][i] == 12) {
				enemy[8]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}
			else if (map[j][i] == 13) {
				enemy[9]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}
		/*	else if (map[j][i] == 14) {
				enemy1[0]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}*/
			/*if (map[j][i] == 15) {
				enemy1[1]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}*/
			/*else if (map[j][i] == 16) {
				enemy1[2]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}
			else if (map[j][i] == 17) {
				enemy1[3]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}
			else if (map[j][i] == 18) {
				enemy1[4]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}
			else if (map[j][i] == 19) {
				enemy1[5]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}
			else if (map[j][i] == 20) {
				enemy1[6]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}
			else if (map[j][i] == 21) {
				enemy1[7]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}
			else if (map[j][i] == 22) {
				enemy1[8]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}
			else if (map[j][i] == 23) {
				enemy1[9]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}*/
		}
	}

	mapcol = new Collision();
	c_postEffect = Default;

	collision = new Collision();
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
	postEffect = new PostEffect();
	postEffect->Initialize();

	object1->PlayAnimation();
}
#pragma endregion

#pragma region 更新処理
void SeaScene1::Update(DirectXCommon* dxCommon)
{
	if (Collision::GetInstance()->Gethit() == true) {
		loadf = false;
		Fader::feedOut(0.0f, 0.1f);
		if (Fader::GetInstance()->GetAlpha() <= 0.0f) {
			//::GetInstance()->SetHit(false);
		}
	}
	else {
		loadf = true;
	}
	GameUI::NowLoadUpdate(loadf);
	Old_Pos = Player_Pos;
	spotLightpos[0] = Player_Pos.x;
	spotLightpos[1] = Player_Pos.y + 10;
	spotLightpos[2] = 0;


	//FBXモデルの更新
	object1->Updata({ 1,1,1,1 }, dxCommon, camera, TRUE);

	if (Line::GetInstance()->Gettriggerflag() != true || Line::GetInstance()->Getboundflag() == true) {
		player->PlayerMoves(Player_Pos, moveSpeed, jumpFlag, grav, time, Player_Rot);

	}
	Collision::CollisionMap(map, tst, mapx, mapy, MAX_X, MAX_Y, grav, time, moveSpeed, jumpFlag, Player_Pos, Player_Scl, Old_Pos, 1);
	Collision::CollisionMap(map, tst, mapx, mapy, MAX_X, MAX_Y, grav, time, moveSpeed, jumpFlag, Player_Pos, Player_Scl, Old_Pos, 2);

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
				BaseScene* scene = new  ClearScene(sceneManager_);//次のシーンのインスタンス生成
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
	}
	else {
		grav = 0.03f;
	}

	time += 0.04f;
	Player_Pos.y -= grav * time * time;

	//頂点座標の更新
	mech->CreateLineTexture(linex, linex2, liney, liney2);

	hari_Pos.x = Line::GetInstance()->getpos().x;
	hari_Pos.y = Line::GetInstance()->getpos().y;

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

	Line::CollisionEnemys(enemy);
	Line::CollisionEnemys2group(enemy1);

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
	}
	else {
		camera->SetTarget({ 0,1,0 });//注視点
		camera->SetDistance(distance);//
		camera->SetEye({ Player_Pos.x,Player_Pos.y,Player_Pos.z - 27.0f });
		camera->SetTarget({ Player_Pos.x,Player_Pos.y,Player_Pos.z });
	}

	camera->Update();

	player->Attack(Player_Pos);
	//for (int i = 0; i < 2; i++) {
	player->CollisionAttack(enemy, Player_Pos);
	player->CollisionAttack(enemy1, Player_Pos);
	SetPrm();//パラメータのセット

	objUpdate();//オブジェクトの更新処理

	effects->Update(dxCommon, camera, enemy, player);
	effects->Update(dxCommon, camera, enemy1, player);
	//enemyにnullptr代入するときは敵が死んだら
	for (int i = 0; i < 10; i++) {
		if (enemy[i] != nullptr) {
			//プレイヤーの検知
			enemy[i]->Motion(player);
			enemy[i]->ColMap(map, tst, mapx, mapy, MAX_X, MAX_Y);
			enemy[i]->ColMap(map, seablock, mapx, mapy, MAX_X, MAX_Y);
			enemy[i]->Update(Player_Pos);

			enemy[i]->EnemySearchPlayer(player);
			//もし敵が死んだら破棄
			if (enemy[i]->GetState_DEAD() == true) {
				Destroy_unique(enemy[i]);

			}
		}

		if (enemy1[i] != nullptr) {
			//プレイヤーの検知
			enemy1[i]->Motion(player);
			enemy1[i]->ColMap(map, tst, mapx, mapy, MAX_X, MAX_Y);
			enemy1[i]->Attack(player);
			enemy1[i]->Update(Player_Pos);

			enemy1[i]->EnemySearchPlayer(player);
			enemy1[i]->SearchAction(camera->GetViewMatrix(), camera->GetProjectionMatrix(), Player_Pos);

			//もし敵が死んだら破棄
			if (enemy1[i]->GetState_DEAD() == true) {
				Destroy_unique(enemy1[i]);
			}
		}
	}
	item->HealEfficasy(player);
	item->Update(enemy);
	item1->Update(enemy1);
	//Fader::FeedSpriteUpdate();
	GameUI::AllowUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player->GetPosition(),
		Line::GetInstance()->GetlineAngle(), Line::GetInstance()->Gettriggerflag());
	GameUI::TargetUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), Line::GetInstance()->Getelf());
	GameUI::PlayerUIUpdate(player);
	//シーンチェンジ
	if (player->getHp() <= 0 || (Player_Pos.y <= -50)) {
		Retry::SetStage(Sea_1_1);
		BaseScene* scene = new GamOver(sceneManager_);//次のシーンのインスタンス生成
		sceneManager_->SetnextScene(scene);//シーンのセット
		//delete scene;
	}
}
#pragma endregion 

//スプライトの描画
#pragma region モデルの描画
void SeaScene1::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{


	player->PreDraw();
	//player->Draw();
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
			if (map[j][i] == 1 ) {
				tst[j][i]->PreDraw();
				tst[j][i]->Draw();
				tst[j][i]->PostDraw();
			}

			if (map[j][i] == 2) {
				seablock[j][i]->PreDraw();
				seablock[j][i]->Draw();
				seablock[j][i]->PostDraw();
			}

			if (map[j][i] == 3) {
				goal->PreDraw();
				goal->Draw();
				goal->PostDraw();
			}
		}
	}


	

	/*hari->PreDraw();
	hari->Draw();
	hari->PostDraw();*/

}
//sプライと以外の描画
void SeaScene1::MyGameDraw(DirectXCommon* dxcomn)
{

	Sprite::PreDraw(dxcomn->GetCmdList());
	background->Draw();
	//setumei->Draw();
	dxcomn->ClearDepthBuffer(dxcomn->GetCmdList());
	Sprite::PostDraw(dxcomn->GetCmdList());


	//スプライトの描画
	SpriteDraw(dxcomn->GetCmdList());

	for (int i = 0; i < 10; i++) {
		if (enemy[i] != nullptr) {
			enemy[i]->Draw(dxcomn);
			enemy[i]->SearchActionDraw(dxcomn);
		}
		if (enemy1[i] != nullptr) {
			enemy1[i]->Draw(dxcomn);
			enemy1[i]->SearchActionDraw(dxcomn);
		}
	}
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
void SeaScene1::Draw(DirectXCommon* dxcomn)
{
	//ポストエフェクトの場合わけ(Bでぼかし Dがデフォルト)
	switch (c_postEffect)
	{
	case Blur://ぼかし　描画準違うだけ
		postEffect->PreDrawScene(dxcomn->GetCmdList());
		MyGameDraw(dxcomn);
		postEffect->PostDrawScene(dxcomn->GetCmdList());

		dxcomn->BeginDraw();
		postEffect->Draw(dxcomn->GetCmdList());
		ImGuiDraw();//imguiは最後の方入れとく
		dxcomn->EndDraw();
		break;

	case Default://普通のやつ特に何もかかっていない
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

void SeaScene1::ImGuiDraw()
{
	//ImGui::Begin("Obj1");
	//ImGui::SetWindowPos(ImVec2(0, 0));
	//ImGui::SetWindowSize(ImVec2(500, 300));
	//if (ImGui::TreeNode("light_position")) {
	//	//ImGui::SliderFloat("positionX", &needlepos.x, -200, 200);
	//	///ImGui::SliderFloat("positionY", &needlepos.y, -200, 200);
	//	///ImGui::SliderFloat("positionZ", &needlepos.z, -200, 200);
	//	if (ImGui::Button("spotlight ON")) {
	//		lightGroup->SetSpotLightActive(0, true);
	//	}
	//	if (ImGui::Button("spotlight OFF")) {
	//		lightGroup->SetSpotLightActive(0, false);
	//	}
	//	ImGui::ColorPicker3("light_color", spotLightColor);
	//	ImGui::TreePop();
	//}

	//if (ImGui::TreeNode("Effect_position")) {
	//	//ImGui::SliderInt("positionX", &L_Cflag, -200, 200);
	//	//ImGui::SliderFloat("positionY", &debuga, -200, 200);
	//	//ImGui::SliderInt("positionZ", &elf, -200, 200);
	//	ImGui::TreePop();
	//}
	//if (ImGui::TreeNode("enemy_position")) {
	//	float rf = enemy[0]->GetPosition().x;
	//	float rf2 = enemy[0]->GetPosition().y;
	//	float rrr = player->getdis();
	//	//float rf3 = enemy->GetPosition().z;
	//	ImGui::SliderInt("positionX", &co, -100, 100);
	//	ImGui::SliderFloat("positionY", &rf2, -100, 100);
	//	ImGui::SliderFloat("positionZ", &rrr, -100, 100);
	//	ImGui::SliderInt("positionX", &co, -200, 200);
	//	ImGui::SliderFloat("positionY", &rf2, -200, 200);
	//	ImGui::SliderFloat("positionZ", &rrr, -200, 200);
	//	ImGui::TreePop();
	//}
	//float linex = Line::GetInstance()->getpos().x;
	//float liney = Line::GetInstance()->getpos().y;
	//float rr = player->GetPosition().x;
	//if (ImGui::TreeNode("Player_position")) {
	//	ImGui::SliderFloat("positionX", &linex, -200, 200);
	//	ImGui::SliderFloat("positionY", &liney, -200, 200);
	//	ImGui::SliderFloat("positionZ", &Player_Pos.z, -200, 200);
	//	ImGui::SliderFloat("grav", &grav, -200, 200);
	//	ImGui::SliderFloat("time", &time, -200, 200);
	//	ImGui::TreePop();
	//}
	//float sx = player->GetArea_S().x;
	//float sy = player->GetArea_S().y;

	//float ex = player->GetArea_e().x;
	//float ey = player->GetArea_e().y;

	//if (ImGui::TreeNode("half")) {
	//	ImGui::SliderFloat("sx", &sx, -200, 200);
	//	ImGui::SliderFloat("sy", &sy, -200, 200);
	//	ImGui::SliderFloat("ex", &ex, -200, 200);
	//	ImGui::SliderFloat("ey", &ey, -200, 200);
	//	ImGui::TreePop();
	//}
	//if (ImGui::TreeNode("Old")) {
	//	ImGui::SliderFloat("Old_PosX", &Old_Pos.x, -200, 200);
	//	ImGui::SliderFloat("old_PosY", &Old_Pos.y, -200, 200);
	//	ImGui::TreePop();
	//}


	///*if (ImGui::TreeNode("1")) {
	//	ImGui::SliderFloat("+_width", &half_Width, -200, 200);
	//	ImGui::SliderFloat("+_height", &half_height, -200, 200);
	//	ImGui::SliderFloat("-_width", &half_Width, -200, 200);
	//	ImGui::SliderFloat("-_height", &half_height, -200, 200);
	//	ImGui::SliderFloat("map_1_width", &width, -200, 200);
	//	ImGui::SliderFloat("map_1_height", &height, -200, 200);
	//	ImGui::TreePop();
	//}*/


	//ImGui::End();

	//ImGui::Begin("postEffect");
	//if (ImGui::RadioButton("Blur", &c_postEffect)) {
	//	c_postEffect = Blur;
	//}
	//if (ImGui::RadioButton("Default", &c_postEffect)) {
	//	c_postEffect = Default;
	//}

	//ImGui::End();

}
#pragma region 解放部分
void SeaScene1::Finalize()
{
	//delete sceneManager_;

	//delete efk,efk1;

}
#pragma endregion