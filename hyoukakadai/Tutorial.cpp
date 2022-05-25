#include "Tutorial.h"
#include"Input.h"
#include"DirectXCommon.h"
#include"TitleScene.h"
#include"PlayScene.h"
#include"SceneManager.h"
#include"MobEnemy.h"
#include"BossEnemy.h"
#include"ThrowEnemy.h"
#include"Line.h"
#include"Destroy.h"
#include"Fader.h"
#include"DesertField.h"
#include"FirstBossScene.h"
//コメントアウト
//シーンのコンストラクタ
Tutorial::Tutorial(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}

#pragma region スプライトの生成
//スプライト生成
void Tutorial::SpriteCreate()
{
	//普通のテクスチャ(スプライトじゃないよ)
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
	tstmodel = Model::CreateFromOBJ("homeblock");
	harimodel = Model::CreateFromOBJ("hari");

	collision = new Collision();

	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			tst[j][i]=std::make_unique<Object3d>();
			tst[j][i]->Initialize();// Object3d::Create();
			tst[j][i]->SetModel(tstmodel);
		}
	}
	hari = Object3d::Create();
	hari->Initialize();
	hari->SetModel(harimodel);

	// ライト生成
	lightGroup = LightGroup::Create();
	// 3Dオブエクトにライトをセット
	Object3d::SetLightGroup(lightGroup);
	
	lightGroup->SetSpotLightActive(0, true);

	Player_Rot = player->GetRotation();
	Player_Scl = player->GetScale();
}
#pragma endregion

#pragma region 各パラメータのセット
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

	object1->SetPosition({ Player_Pos });
	object1->SetRotation({ Player_Rot });

}
#pragma endregion

#pragma region オブジェクト+ライトの更新処理
void Tutorial::objUpdate()
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
	hari->Update({ 1,1,1,1 });
}
#pragma endregion

#pragma region 初期化
void Tutorial::Initialize(DirectXCommon* dxCommon)
{
	//
	tyutorial = new TyutorialSprite();
	tyutorial->Initialize();
	GameUI::UISpriteSet();
	GameUI::TargetUISet();
	GameUI::PlayerUISet();

	//enemy[0] = new MobEnemy();
	enemy= std::make_unique<MobEnemy>();
	//std::make_unique()
	//enemy = new MobEnemy();
	enemy->Setposition({ 110.6, 3, 0 });
	enemy->Initialize();

	mapcol = new Collision();

	collision = new Collision();
	SpriteCreate();//
	ModelCreate();//

	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height/*input*/);
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);

	//モデル名を指定してファイル読み込み
	fbxmodel = FbxLoader::GetInstance()->LoadModelFromFile("knight");

	//デバイスをセット
	f_Object3d::SetDevice(dxCommon->GetDev());
	//カメラをセット
	f_Object3d::SetCamera(camera);
	//グラフィックパイプライン生成
	f_Object3d::CreateGraphicsPipeline();

	effect = new Effects();
	effect->Initialize(dxCommon, camera);
	//FBXモデルの生成
	object1 = new f_Object3d();
	object1->Initialize(dxCommon, camera);
	object1->SetModel(fbxmodel);
	/*audio = new Audio();
	audio->Initialize();
	audio->LoopWave("Resources/loop100216.wav", vol);*/
	Fader::SetFeedSprite();
	//FBXのアニメーション再生
	object1->PlayAnimation();
}
#pragma endregion

#pragma region 更新処理
void Tutorial::Update(DirectXCommon* dxCommon)
{
	LONG u_r = 32768;
	LONG a = 30000;
	//向いてる方向に移動

	Old_Pos = Player_Pos;
	spotLightpos[0] = Player_Pos.x;
	spotLightpos[1] = Player_Pos.y + 1000;
	spotLightpos[2] = 0;

	tyutorial->Update(enemy.get());

	//FBXモデルの更新
	object1->Updata({ 1,1,1,1 }, dxCommon, camera, TRUE);
	//object1->SetPosition({ Player_Pos.x + 4.0f,Player_Pos.y,Player_Pos.z });

	if (Line::GetInstance()->Gettriggerflag() != true || Line::GetInstance()->Getboundflag() == true) {
		player->PlayerMoves(Player_Pos, moveSpeed, jumpFlag, grav, time, Player_Rot);
	}

	

	if (Input::GetInstance()->TriggerButonY()) {
		BaseScene* scene = new  TitleScene(sceneManager_);//次のシーンのインスタンス生成
		sceneManager_->SetnextScene(scene);//シーンのセット
	}

		//入力処理より後に当たり判定を描け
			//入力処理より後に当たり判定を描け
		Collision::CollisionMap(map, tst, mapx, mapy, MAX_X, MAX_Y, grav, time, moveSpeed, jumpFlag, Player_Pos, Player_Scl, Old_Pos, 1);
#pragma region 線の処理

		if (Line::GetInstance()->Getboundflag() == true) {
			grav = 0;
			time = 0;
		}

		if (Line::GetInstance()->Getboundflag() == false || Line::GetInstance()->Gettriggerflag() == false) {
			//grav = 0.0f;
		} else {
			grav = 0.03f;
		}

		time += 0.04f;
		Player_Pos.y -= grav * time * time;
		//重力の影響で少しぐらつき
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
		Line::CollisionEnemy(enemy.get());

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
	//	player->FlyingAttack(enemy.get());
		player->CollisionAttack(&enemy, Player_Pos);

		SetPrm();//パラメータのセット

		objUpdate();//オブジェクトの更新処理

		//enemyにnullptr代入するときは敵が死んだら
			if (enemy != nullptr) {
				//Player_Pos.x+10;
				enemy->enemyappearance(tyutorial);
				//プレイヤーの検知
				enemy->Attack(player);
				enemy->ColMap(map,tst, mapx, mapy, MAX_X, MAX_Y);
				enemy->Update(Player_Pos);

				enemy->EnemySearchPlayer(player);
				//もし敵が死んだら破棄
				if (enemy->GetState_DEAD() == true) {
					Destroy_unique(enemy);
				}
			}
			effect->Update(dxCommon, camera, &enemy, player);
		GameUI::AllowUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player->GetPosition(),
			Line::GetInstance()->GetlineAngle(), Line::GetInstance()->Gettriggerflag());
		GameUI::TargetUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), Line::GetInstance()->Getelf());
		GameUI::PlayerUIUpdate(player);

	//シーンチェンジ
	if (tyutorial->Gethh()&& Input::GetInstance()->TriggerButtonA() || Input::GetInstance()->TriggerKey(DIK_N)) {//押されたら
		BaseScene* scene = new  FirstBossScene(sceneManager_);//次のシーンのインスタンス生成
		sceneManager_->SetnextScene(scene);//シーンのセット
		//delete scene;
	}
}
#pragma endregion 

//スプライトの描画
#pragma region モデルの描画
void Tutorial::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{

	
	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			if (map[j][i] == 1|| map[j][i] == 2) {
				tst[j][i]->PreDraw();
				tst[j][i]->Draw();
				tst[j][i]->PostDraw();
			}
		}
	}

}
//sプライと以外の描画
void Tutorial::MyGameDraw(DirectXCommon* dxcomn)
{

	//スプライトの描画
	SpriteDraw(dxcomn->GetCmdList());
	if (enemy != nullptr) {
		enemy->Draw(dxcomn);
	}

	//普通のテクスチャの描画
	Line::Draw(dxcomn);

	effect->Draw(dxcomn);
	//weffect->Draw(dxcomn);
	GameUI::AllowUIDraw(dxcomn);
	GameUI::TargetUIDraw(dxcomn);
	GameUI::UIDraw(dxcomn);
	GameUI::PlayerUIDraw(dxcomn);
	//FBXの描画
	object1->Draw(dxcomn->GetCmdList());
	tyutorial->Draw(dxcomn);
}
#pragma endregion
//↓に入る
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
		ImGui::SliderFloat("cx", &Player_Pos.x, 200, -200);
		ImGui::SliderFloat("cy", &cy, 200, -200);
		ImGui::TreePop();
	}
	ImGui::End();
}
#pragma region 解放部分
void Tutorial::Finalize()
{
	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			Destroy_unique(tst[j][i]);
		}
	}
	Destroy(playermodel);
	Destroy(harimodel);
	Destroy(tstmodel);
	Destroy(hari);
	Destroy(fbxmodel);
	//delete hari, fbxmodel;
	//delete sceneManager_;
	delete object1;
	player->Finalize();
	delete player, enemy;
	delete mapcol, collision;
	delete camera;
	tyutorial->Finalize();
	Destroy(tyutorial);
	
//	delete tyutorial;
	delete lightGroup;
	GameUI::Finalize();
	Line::Finalize();
	ImGui::DestroyContext;
}
#pragma endregion