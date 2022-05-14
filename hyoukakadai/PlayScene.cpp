#include "PlayScene.h"
#include"Input.h"
#include"DirectXCommon.h"
#include"ClearScene.h"
#include"TitleScene.h"
#include"DesertField.h"
#include"SceneManager.h"
#include"MobEnemy.h"
#include"BossEnemy.h"
#include"ThrowEnemy.h"
#include"Line.h"
#include"Destroy.h"
#include"Fader.h"
//コメントアウト


//シーンのコンストラクタ
PlayScene::PlayScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}

#pragma region スプライトの生成
//スプライト生成
void PlayScene::SpriteCreate()
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
	setumei = Sprite::Create(2, { 0.0f,0.0f });
	// デバッグテキスト初期化
	dxcomn = new DirectXCommon();
	debugText = new DebugTxt();
	debugText->Initialize(debugTextTexNumber);
}
#pragma endregion

#pragma region 
void PlayScene::ModelCreate()
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
void PlayScene::SetPrm()
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
	goal->SetPosition({ goal_pos.x,goal_pos.y,goal_pos.z });

	background->SetPosition({ 0, 0 });
	background->SetSize({ WinApp::window_width,WinApp::window_height });
	background->setcolor({ 1,1,1,1 });
}
#pragma endregion

#pragma region オブジェクト+ライトの更新処理
void PlayScene::objUpdate()
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
void PlayScene::Initialize(DirectXCommon* dxCommon)
{
	//

	GameUI::UISpriteSet();
	GameUI::TargetUISet();
	GameUI::PlayerUISet();
	enemy[0] = std::make_unique<MobEnemy>();
	enemy[1] = std::make_unique<MobEnemy>();
	enemy[2] = std::make_unique<ThrowEnemy>();
	enemy[3] = std::make_unique<BossEnemy>();
	enemy[4] = std::make_unique<ThrowEnemy>();
	enemy[5] = std::make_unique<ThrowEnemy>();
	enemy[6] = std::make_unique<ThrowEnemy>();
	enemy[7] = std::make_unique<ThrowEnemy>();
	enemy[8] = std::make_unique<ThrowEnemy>();
	enemy[9] = std::make_unique<BossEnemy>();
	//enemy[6] = std::make_unique<ThrowEnemy>();
	//enemy[0] = new MobEnemy();
	enemy[9]->Setposition({ 940,-4.2,0 });
	//enemy[6]->Setposition({ 270,-18.2,0 });
	enemy[8]->Setposition({ 270,-18.2,0 });
	enemy[7]->Setposition({ 270,-18.2,0 });
	enemy[6]->Setposition({ 270,-18.2,0 });
	enemy[5]->Setposition({ 170,-18.2,0 });
	enemy[4]->Setposition({ 20,-14.2,0 });
	enemy[3]->Setposition({ 80,-4.2,0 });
	enemy[2]->Setposition({ 20,-4.2,0 });
	enemy[1]->Setposition({ 350, -18, 0 });
	enemy[0]->Setposition({ 200, -7, 0 });
	for (int i = 0; i < emax; i++) {
		enemy[i]->Initialize();
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
	fbxmodel = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");

	//デバイスをセット
	f_Object3d::SetDevice(dxCommon->GetDev());
	//カメラをセット
	f_Object3d::SetCamera(camera);
	//グラフィックパイプライン生成
	f_Object3d::CreateGraphicsPipeline();

	//FBXモデルの生成
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

#pragma region 更新処理
void PlayScene::Update(DirectXCommon* dxCommon)
{
	Old_Pos = Player_Pos;
	
	LONG u_r = 32768;
	LONG a = 30000;

	//左
	player->PlayerMoves(Player_Pos, moveSpeed);

	///////// コントローラー //////////
	// スティックの方向判定
	// 無反応範囲

	//FBXモデルの更新
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

	///これより上に入力処理をかけ
	////当たり判定

	float disl;
	for (int i = 0; i < MAX_X; i++) {
		for (int j = 0; j < MAX_Y; j++) {
			if (map[j][i] == 1 || map[j][i] == 2) {
				if ((Line::GetInstance()->getpos().x + 1.0f > mapx[j][i] - (width) && Line::GetInstance()->getpos().x - 1.0f < mapx[j][i] + (width)) && Line::GetInstance()->getpos().y + 1.0f > mapy[j][i] - height && Line::GetInstance()->getpos().y - 1.0f < mapy[j][i] + height) {
					if ( Line::GetInstance()->Gettriggerflag() == true) {
						Line::GetInstance()->Setmapcol(true);
						Line::GetInstance()->Setelf(true);
					}
				}
			}
		}
	}
	//入力処理より後に当たり判定を描け
	Collision::ColMap1(map, tst, mapx, mapy,200,20, grav,time,moveSpeed, jumpFlag, Player_Pos, Old_Pos);

	if (Player_Pos.x <= goal_pos.x + goal->GetScale().x && Player_Pos.x >= goal_pos.x-goal->GetScale().x&&Player_Pos.y<=goal_pos.y+goal->GetScale().y&&Player_Pos.y>=goal_pos.y-goal->GetScale().y) {
		BaseScene* scene = new ClearScene(sceneManager_);//次のシーンのインスタンス生成
		sceneManager_->SetnextScene(scene);//シーンのセット
	}

	if (Line::GetInstance()->Getboundflag()==true) {
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

	//needlepos = Line::GetInstance()->getpos();

	Line::Update(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player, Player_Pos, colf, moveSpeed);

	Line::CollisionEnemys(enemy);
	//weffect->Update(dxcomn,camera,player[0]->GetPosition(),Line::GetInstance()->Getboundflag());
	//FBXのアニメーション再生
	if (Input::GetInstance()->Pushkey(DIK_0)) {
		object1->PlayAnimation();
	}

	//カメラ関係の処理
	camera->SetTarget({ 0,1,0 });//注視点
	camera->SetDistance(distance);//
	camera->SetEye({ Player_Pos.x,Player_Pos.y,Player_Pos.z - 27.0f });
	camera->SetTarget({ Player_Pos.x,Player_Pos.y ,Player_Pos.z });

	camera->Update();

	player->SetPosition(Player_Pos);
	player->SetRotation(Player_Rot);

	player->SetScale(Player_Scl);


	player->Attack(Player_Pos);
	player->CollisionAttack(enemy, Player_Pos);

	SetPrm();//パラメータのセット

	objUpdate();//オブジェクトの更新処理
	
	XMFLOAT3 bpos = enemy[3]->GetPosition();
	
	
	effects->Update(dxCommon, camera, enemy, player);

	//enemyにnullptr代入するときは敵が死んだら
	for (int i = 0; i < 10; i++) {
		if (enemy[i] != nullptr) {
			//プレイヤーの検知
			enemy[i]->Attack(player);
			enemy[i]->ColMap(map,tst, mapx, mapy, MAX_X, MAX_Y);
			enemy[i]->Update(Player_Pos);

			enemy[i]->EnemySearchPlayer(player);
			//もし敵が死んだら破棄
			if (enemy[i]->GetState_DEAD() == true) {
				Destroy_unique(enemy[i]);
			
			}
		}
	}
	//enemy[3]->Update(Player_Pos);
	atb = BossEnemy::GetInstance()->GetaltAttack();
	//effects->BossAttackEffect(dxCommon, camera, atb, bpos);
	item->HealEfficasy(player);
	item->Update(enemy);
	//Fader::FeedSpriteUpdate();
	GameUI::AllowUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player->GetPosition(),
		Line::GetInstance()->GetlineAngle(), Line::GetInstance()->Gettriggerflag());
	GameUI::TargetUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), Line::GetInstance()->Getelf());
	GameUI::PlayerUIUpdate(player);
	//シーンチェンジ
	if (Input::GetInstance()->TriggerKey(DIK_R)||(Player_Pos.y<=-50)) {//押されたら
		BaseScene* scene = new DesertField(sceneManager_);//次のシーンのインスタンス生成
		sceneManager_->SetnextScene(scene);//シーンのセット
		//delete scene;
	}
}
#pragma endregion 

//スプライトの描画
#pragma region モデルの描画
void PlayScene::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{
	player->PreDraw();
	player->Draw();
	player->PostDraw();

	for (int i = 0; i < 1; i++) {
		if (enemy[i] != nullptr) {
			enemy[i]->Draw(dxcomn);
		}
	}
	
	item->Draw();
	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			if (map[j][i] == 1|| map[j][i] ==2) {
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
//sプライと以外の描画
void PlayScene::MyGameDraw(DirectXCommon* dxcomn)
{

	Sprite::PreDraw(dxcomn->GetCmdList());
	background->Draw();
	//setumei->Draw();
	dxcomn->ClearDepthBuffer(dxcomn->GetCmdList());
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

}
#pragma endregion
//↓に入る
#pragma region
void PlayScene::Draw(DirectXCommon* dxcomn)
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

void PlayScene::ImGuiDraw()
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
	float x = BossEnemy::GetInstance()->GetScale().x;
	if (ImGui::TreeNode("Effect_position")) {
		ImGui::SliderFloat("positionX", &x, -200, 200);
		ImGui::SliderInt("positionY", &atb, -200, 200);
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

	ImGui::Begin("postEffect");
	if (ImGui::RadioButton("Blur", &c_postEffect)) {
		c_postEffect = Blur;
	}
	if (ImGui::RadioButton("Default", &c_postEffect)) {
		c_postEffect = Default;
	}

	ImGui::End();

}
#pragma region 解放部分
void PlayScene::Finalize()
{
	//delete sceneManager_;

	//delete efk,efk1;

}
#pragma endregion