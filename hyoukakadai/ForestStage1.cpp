#include "ForestStage1.h"
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
#include<thread>
#include"GamOver.h"
#include"StageSelect.h"
ForestStage1::ForestStage1(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}

#pragma region スプライトの生成
//スプライト生成
void ForestStage1::SpriteCreate()
{
	// デバッグテキスト用テクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont2.png");
	//普通のテクスチャ(スプライトじゃないよ)
	Line::Initialize();
	GameUI::AllowUISet();

	Texture::LoadTexture(6, L"Resources/gomi.png");
	Texture::LoadTexture(1, L"Resources/background.png");
	Sprite::LoadTexture(1, L"Resources/forest.png");

	mech = std::make_unique<Texture>();
	mech->Create(6, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });// = Texture::Create(6, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });

	zukki = std::make_unique<Texture>();
	zukki->Create(1, { 0,-20,50 }, { 1,1,1 }, { 1,1,1,1 });

	background = Sprite::Create(1, { 0.0f,0.0f });

	// デバッグテキスト初期化
	dxcomn = new DirectXCommon();
	debugText = new DebugTxt();
	debugText->Initialize(debugTextTexNumber);
}
#pragma endregion

#pragma region 
void ForestStage1::ModelCreate()
{
	playermodel = Model::CreateFromOBJ("player");
	player = Player::Create(playermodel);
	player->Initialize();
	tstmodel = Model::CreateFromOBJ("wood");
	harimodel = Model::CreateFromOBJ("hari");
	goalmodel = Model::CreateFromOBJ("goal");
	reefmodel = Model::CreateFromOBJ("reef");


	item = new Item();
	item->Initialize();
	collision = new Collision();

	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			tst[j][i] = std::make_unique<Object3d>();
			tst[j][i]->Initialize();// Object3d::Create();
			tst[j][i]->SetModel(tstmodel);

			reef[j][i] = std::make_unique<Object3d>();
			reef[j][i]->Initialize();// Object3d::Create();
			reef[j][i]->SetModel(reefmodel);
		}
	}

	goal = std::make_unique<Object3d>();
	goal->Initialize();
	goal->SetModel(goalmodel);

	block = std::make_unique<Object3d>();
	block->Initialize();// = Object3d::Create();
	block->SetModel(tstmodel);

	hari = std::make_unique<Object3d>();
	hari->Initialize();
	hari->SetModel(harimodel);

	
	// ライト生成
	lightGroup = LightGroup::Create();
	// 3Dオブエクトにライトをセット
	Object3d::SetLightGroup(lightGroup);
	//パラメータの設定
	lightGroup->SetDirLightActive(0, false);
	lightGroup->SetDirLightActive(1, false);
	lightGroup->SetDirLightActive(2, false);
	lightGroup->SetPointLightActive(0, true);

	effects = std::make_unique<Effects>();;

	attackeffects = std::make_unique<Effects>();;

	Player_Scl = player->GetScale();
}
#pragma endregion

#pragma region 各パラメータのセット
void ForestStage1::SetPrm()
{

	hari->SetPosition({ hari_Pos.x + 2.0f,hari_Pos.y,hari_Pos.z });

	player->SetPosition({ Player_Pos });
	player->SetScale({ Player_Scl });
	player->SetRotation({ Player_Rot });

	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			tst[j][i]->SetPosition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			tst[j][i]->SetRotation({ tst_Rot });
			tst[j][i]->SetScale({ tst_Scl });

			reef[j][i]->SetPosition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			reef[j][i]->SetRotation({ tst_Rot });
			reef[j][i]->SetScale({ tst_Scl });
			if (map[j][i] == 3) {
				goal->SetPosition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
				goal->SetRotation({ 0,120,0 });
				goal->SetScale({ tst_Scl });
			}

		}
	}

	block->SetPosition({ block_pos });
	block->SetScale({ block_Scl });

	background->SetPosition({ 0, 0 });
	background->SetSize({ WinApp::window_width,WinApp::window_height });
	background->setcolor({ 1,1,1,1 });

	object1->SetPosition({ Player_Pos });
	object1->SetRotation({ Player_Rot });
}
#pragma endregion

#pragma region オブジェクト+ライトの更新処理
void ForestStage1::objUpdate()
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
			reef[j][i]->Update({ 1,1,1,1 });
		}
	}

	goal->Update({ 1,1,1,1 });
	block->Update({ 1,1,1,1 });
	hari->Update({ 1,1,1,1 });
}
#pragma endregion

#pragma region 初期化
void ForestStage1::Initialize(DirectXCommon* dxCommon)
{
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

	for (int i = 0; i < 10; i++) {
		enemy[i]->Initialize();
	}
	
	



	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			if (map[i][j] == 4) {
				enemy[0]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });

				//	break;
			}
			else if (map[i][j] == 5) {
				enemy[1]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
				//break;
			}
			else if (map[i][j] == 6) {
				enemy[2]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
				//	break;
			}
			else if (map[i][j] == 7) {
				enemy[3]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			}
			else if (map[i][j] == 8) {
				enemy[4]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });

				//break;
			}
			else if (map[i][j] == 9) {
				enemy[5]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });

				//break;
			}
			else if (map[i][j] == 10) {
				enemy[6]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });

				//	break;
			}
			else if (map[i][j] == 11) {
				enemy[7]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });

				//	break;
			}
			else if (map[i][j] == 12) {
				enemy[8]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });

				//break;
				//enemy[8]->Setposition(tst[i][j]->GetPosition());
			}
			else if (map[i][j] == 13) {
				enemy[9]->Setposition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });

				//break;
				//break;
			}
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
	//Audioの生成
	/*audio = new Audio();
	audio->Initialize();
	audio->LoopWave("Resources/loop100216.wav", vol);*/
	postEffect = new PostEffect();
	postEffect->Initialize();

	object1->PlayAnimation();
}
#pragma endregion

void ForestStage1::ThInitialize()
{

}
#pragma region 更新処理
void ForestStage1::Update(DirectXCommon* dxCommon)
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

	if (Line::GetInstance()->Gettriggerflag() != true||Line::GetInstance()->Getboundflag() == true) {
		player->PlayerMoves(Player_Pos, moveSpeed,jumpFlag,grav,time,Player_Rot);
		
	}
	if(Input::GetInstance()->Pushkey(DIK_0)){
	
	}
	//FBXモデルの更新
	object1->Updata({ 1,1,1,1 }, dxCommon, camera, TRUE);
		

	Collision::CollisionMap(map, tst, mapx, mapy, MAX_X, MAX_Y, grav, time, moveSpeed, jumpFlag, Player_Pos, Player_Scl, Old_Pos, 1);
	Collision::CollisionMap(map, reef, mapx, mapy, MAX_X, MAX_Y, grav, time, moveSpeed, jumpFlag, Player_Pos, Player_Scl, Old_Pos, 2);
	
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

	//needlepos = Line::GetInstance()->getpos();

	Line::Update(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player, Player_Pos, colf, moveSpeed);

	Line::CollisionEnemy(enemy->get());
	//weffect->Update(dxcomn,camera,player[0]->GetPosition(),Line::GetInstance()->Getboundflag());
	//FBXのアニメーション再生
	//if (Input::GetInstance()->Pushkey(DIK_0)) {
		
	//}

	if (Player_Pos.y >= -11) {
		cameramove-=0.1f;
		if (cameramove <= 6) {
			cameramove = 6;
		}
	}
	else {
		cameramove+=0.1f;
		if (cameramove >= 9) {
			cameramove = 9;
		}
	}


	//}
	//カメラ関係の処理
	if (Player_Pos.x <=  27.0f) {
		camera->SetTarget({ 0,1,0 });//注視点
		camera->SetDistance(distance);//
		camera->SetEye({ 27.0f,Player_Pos.y+cameramove,Player_Pos.z - 27.0f });
		camera->SetTarget({ 27.0f,Player_Pos.y+cameramove,Player_Pos.z });
	}

	else if (Player_Pos.x >= 368.0f) {
		camera->SetTarget({ 0,1,0 });//注視点
		camera->SetDistance(distance);//
		camera->SetEye({ 368.0f,Player_Pos.y+cameramove,Player_Pos.z - 27.0f });
		camera->SetTarget({ 368.0f,Player_Pos.y+cameramove ,Player_Pos.z });
	}
	else {
		camera->SetTarget({ 0,1,0 });//注視点
		camera->SetDistance(distance);//
		camera->SetEye({ Player_Pos.x,Player_Pos.y+cameramove,Player_Pos.z - 27.0f });
		camera->SetTarget({ Player_Pos.x,Player_Pos.y+cameramove,Player_Pos.z });
	}



	camera->Update();

	


	player->Attack(Player_Pos);
	//for (int i = 0; i < 2; i++) {
	player->CollisionAttack(enemy, Player_Pos);

	SetPrm();//パラメータのセット

	objUpdate();//オブジェクトの更新処理

	effects->Update(dxCommon, camera, enemy, player);

	//enemyにnullptr代入するときは敵が死んだら
	for (int i = 0; i < 10; i++) {
		if (enemy[i] != nullptr) {
			//プレイヤーの検知
			enemy[i]->Attack(player);
			enemy[i]->ColMap(map, tst, mapx, mapy, MAX_X, MAX_Y);
			enemy[i]->ColMap(map, reef, mapx, mapy, MAX_X, MAX_Y);
			enemy[i]->Update(Player_Pos);

			enemy[i]->EnemySearchPlayer(player);
			//もし敵が死んだら破棄
			if (enemy[i]->GetState_DEAD() == true) {
				Destroy_unique(enemy[i]);

			}
		}
	}
	item->HealEfficasy(player);
	item->Update(enemy);
	Fader::FeedSpriteUpdate();
	GameUI::AllowUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player->GetPosition(),
		Line::GetInstance()->GetlineAngle(), Line::GetInstance()->Gettriggerflag());
	GameUI::TargetUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), Line::GetInstance()->Getelf());
	GameUI::PlayerUIUpdate(player);
	//シーンチェンジ
	if (Input::GetInstance()->TriggerKey(DIK_R) || (Player_Pos.y <= -50)) {//押されたら
		BaseScene* scene = new GamOver(sceneManager_);//次のシーンのインスタンス生成
		sceneManager_->SetnextScene(scene);//シーンのセット
		//delete scene;
	}
}
#pragma endregion 

//スプライトの描画
#pragma region モデルの描画
void ForestStage1::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{

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
				reef[j][i]->PreDraw();
				reef[j][i]->Draw();
				reef[j][i]->PostDraw();
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
void ForestStage1::MyGameDraw(DirectXCommon* dxcomn)
{

	for (int i = 0; i < 10; i++) {
		if (enemy[i] != nullptr) {
			enemy[i]->Draw(dxcomn);
			enemy[i]->SearchActionDraw(dxcomn);
		}
		if (enemy[i] != nullptr) {
			enemy[i]->Draw(dxcomn);
		}
	}

	Sprite::PreDraw(dxcomn->GetCmdList());
	background->Draw();
	//setumei->Draw();
	dxcomn->ClearDepthBuffer(dxcomn->GetCmdList());
	//Fader::FeedSpriteDraw();
	Sprite::PostDraw(dxcomn->GetCmdList());

	//スプライトの描画
	SpriteDraw(dxcomn->GetCmdList());


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

	Sprite::PreDraw(dxcomn->GetCmdList());
	Fader::FeedSpriteDraw();
	Sprite::PostDraw(dxcomn->GetCmdList());

	GameUI::NowLoadDraw(dxcomn);
}
#pragma endregion
//↓に入る
#pragma region
void ForestStage1::Draw(DirectXCommon* dxcomn)
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

void ForestStage1::ImGuiDraw()
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
		ImGui::SliderFloat("positionY", &Player_Pos.y, -100, 100);
		ImGui::SliderFloat("positionZ", &rrr, -100, 100);
		ImGui::SliderInt("positionX", &co, -200, 200);
		ImGui::SliderFloat("positionY", &rf2, -200, 200);
		ImGui::SliderFloat("positionZ", &rrr, -200, 200);
		ImGui::TreePop();
	}


	ImGui::End();

}
#pragma region 解放部分
void ForestStage1::Finalize()
{
	//delete sceneManager_;

	//delete efk,efk1;

}
