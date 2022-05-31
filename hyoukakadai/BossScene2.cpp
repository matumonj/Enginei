#include "BossScene2.h"
#include"Input.h"
#include"DirectXCommon.h"
#include"ClearScene.h"
#include"TitleScene.h"
#include"SceneManager.h"
#include"MobEnemy.h"
#include"BossEnemy.h"
#include"ThrowEnemy.h"
#include"ThronEnemy.h"
#include"Line.h"
#include"ForestBoss.h"
#include"Destroy.h"
#include"Fader.h"
#include"CollisionPrimitive.h"
#include"Retry.h"
//シーンのコンストラクタ
BossScene2::BossScene2(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}

#pragma region スプライトの生成
//スプライト生成
void BossScene2::SpriteCreate()
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

}
#pragma endregion

#pragma region 
void BossScene2::ModelCreate()
{
	playermodel = Model::CreateFromOBJ("player");
	player = Player::Create(playermodel);
	player->Initialize();
	tstmodel = Model::CreateFromOBJ("wood");
	reefmodel = Model::CreateFromOBJ("reef");


	item = new Item();
	item->Initialize();

	item2 = new Item();
	item2->Initialize();

	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			tst[j][i] = std::make_unique<Object3d>();
			tst[j][i]->Initialize();// Object3d::Create();
			tst[j][i]->SetModel(tstmodel);

			reef[j][i] = std::make_unique<Object3d>();
			reef[j][i]->Initialize();
			reef[j][i]->SetModel(reefmodel);
		}
	}

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


	effects = std::make_unique<Effects>();

	//effects2 = std::make_unique<Effects>();;
	attackeffects = std::make_unique<Effects>();;

	//Player_Pos = player->GetPosition();
	Player_Rot = player->GetRotation();
	Player_Scl = player->GetScale();
	//Fader::SetFeedSprite();
}
#pragma endregion

#pragma region 各パラメータのセット
void BossScene2::SetPrm()
{
	half_height = player->GetScale().y;
	half_Width = player->GetScale().x;

	player->SetPosition({ Player_Pos });
	player->SetScale({ Player_Scl });
	player->SetRotation({ Player_Rot });

	object1->SetPosition({ Player_Pos });
	object1->SetRotation({ Player_Rot });
}
#pragma endregion

#pragma region オブジェクト+ライトの更新処理
void BossScene2::objUpdate()
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



}
#pragma endregion

#pragma region 初期化
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

	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height/*input*/);
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);

	effects->Initialize(dxCommon, camera);
	//effects2->Initialize(dxCommon, camera);

	attackeffects->Initialize(dxCommon, camera);

	//モデル名を指定してファイル読み込み
	fbxmodel = FbxLoader::GetInstance()->LoadModelFromFile("knight");

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
	//camerapositionx = 46.94f;
	camerapositiony = -4.5f;
	camerapositionz = -40.51f;
	bossenemy = std::make_unique<ForestBoss>();
	enemycolony1[0] = std::make_unique<ThronEnemy>();
	enemycolony1[1] = std::make_unique<MobEnemy>();
	enemycolony1[2] = std::make_unique<MobEnemy>();
	enemycolony1[3] = std::make_unique<ThrowEnemy>();
	enemycolony1[4] = std::make_unique<ThrowEnemy>();
	enemycolony1[5] = std::make_unique<MobEnemy>();
	enemycolony1[6] = std::make_unique<MobEnemy>();
	enemycolony1[7] = std::make_unique<ThrowEnemy>();
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

			reef[j][i]->SetPosition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			reef[j][i]->SetRotation({ tst_Rot });
			reef[j][i]->SetScale({ tst_Scl });
		}
	}
	bossenemy->Initialize();

	bossenemy->Setposition({ 40,-4,0 });
	if (startSet == false) {

		for (int i = 0; i < MAX_Y; i++) {
			for (int j = 0; j < MAX_X; j++) {
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
					//xx = tst[i][j]->GetPosition().x;
					//break;
					//break;
				}
			}
		}
	}
	//168,48
	Player_Pos = { 20,10,0 };
	object1->PlayAnimation();
}
#pragma endregion

#pragma region 更新処理
void BossScene2::Update(DirectXCommon* dxCommon)
{
	if (Collision::GetInstance()->Gethit() == true) {
		loadf = false;
		hintload = false;
		Fader::feedOut(0.0f, 0.1f);
		if (Fader::GetInstance()->GetAlpha() <= 0.0f) {
			//::GetInstance()->SetHit(false);
		}
	}
	else {
		hintload = true;
		loadf = true;
	}
	GameUI::NowLoadUpdate(loadf);
	GameUI::HintForeBossUpdate(hintload);
	camerapositionx = Player_Pos.x;
	Old_Pos = Player_Pos;
	spotLightpos[0] = Player_Pos.x;
	spotLightpos[1] = Player_Pos.y + 1000;
	spotLightpos[2] = 0;
	if (bossenemy != nullptr) {
		player->PlayerMoves(Player_Pos, moveSpeed, jumpFlag, grav, time, Player_Rot);
	}
	//FBXモデルの更新
	object1->Updata({ 1,1,1,1 }, dxCommon, camera,movenow);


	GameUI::BossUIUpdate(bossenemy.get());

	Collision::ColMapb1(map, tst, mapx, mapy, 20, 130, grav, time, moveSpeed, jumpFlag, Player_Pos, Player_Scl, Old_Pos, 1);
	Collision::ColMapb1(map, tst, mapx, mapy, 20, 130, grav, time, moveSpeed, jumpFlag, Player_Pos, Player_Scl, Old_Pos, 2);
	Collision::ColMapb1(map, tst, mapx, mapy, 20, 130, grav, time, moveSpeed, jumpFlag, Player_Pos, Player_Scl, Old_Pos, 9);

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
	if (bossenemy != nullptr) {
		time += 0.04f;
		Player_Pos.y -= grav * time * time;
	}
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
	Line::GetInstance()->CollisionEnemys(enemycolony1);
	Line::GetInstance()->CollisionEnemys2group(enemycolony2);

	//FBXのアニメーション再生
	if (Input::GetInstance()->Pushkey(DIK_0)) {

	}

	if (Line::GetInstance()->Getboundflag() == true) {
		movenow = true;
	}
	else {
		if (player->GetNowMove() == false) {
			movenow = false;
		} else {
			movenow = true;
		}
	}
		XMFLOAT3 bpos;
		if (bossenemy != nullptr) {
			bpos = bossenemy->GetPosition();
		}
	
	//カメラ関係の処理
	ForestBoss::GetInstance()->appearance(camerapositiony, Player_Pos.y);
	camera->SetTarget({ 0,1,0 });//注視点
	camera->SetDistance(distance);//
//	if (bossenemy != nullptr) {
		//if (bossenemy->GetHP() >= 1) {
			camera->SetEye({ Player_Pos.x,camerapositiony + 5,Player_Pos.z - 35.0f });
			camera->SetTarget({ Player_Pos.x,camerapositiony + 3 ,Player_Pos.z });
			oldcamera = camerapositiony + 3;
		
		
	//}
	camera->Update();

	effects->BossAttackEffect(dxCommon, camera, BossEnemy::GetInstance()->GetAltStay(), atb, bpos);
	player->SetPosition(Player_Pos);
	player->SetRotation(Player_Rot);
	player->SetScale(Player_Scl);
	player->CollisionAttack1(bossenemy.get(), Player_Pos);
	player->Attack(Player_Pos);
	player->CollisionAttack(enemycolony1, Player_Pos);

	player->CollisionAttack(enemycolony2, Player_Pos);

	SetPrm();//パラメータのセット

	objUpdate();//オブジェクトの更新処理

	effects->Update(dxCommon, camera, enemycolony1, player);
	effects->Update2(dxCommon, camera, enemycolony2, player);
	effects->Updateo(dxCommon, camera, bossenemy.get(), player);

	//effects->Update(dxCommon, camera, &bossenemy, player);

	//bossenemyにnullptr代入するときは敵が死んだら
	if (bossenemy != nullptr) {
		//プレイヤーの検知
		bossenemy->Motion(player);
		bossenemy->Attack(player);
		bossenemy->ColMap1(map, tst, mapx, mapy, 20, 130);
		bossenemy->ColMap1(map, reef, mapx, mapy, 20, 130);
		bossenemy->Update(Player_Pos);
		ForestBoss::GetInstance()->SkewersAttack(map, tst);

		bossenemy->EnemySearchPlayer(player);
		//もし敵が死んだら破棄
		if (bossenemy->GetState_DEAD() == true) {
			Destroy_unique(bossenemy);
			Fader::feedIn(1.0f, 1);
			if (Fader::GetInstance()->GetAlpha()>=0.9 ) {//押されたら
				//Retry::SetStage(Jungle_1_3);
				BaseScene* scene = new ClearScene(sceneManager_);//次のシーンのインスタンス生成
				sceneManager_->SetnextScene(scene);//シーンのセット
			}
		}
	}

	for (int i = 0; i < 10; i++) {
		if (enemycolony1[i] != nullptr) {
				enemycolony1[i]->ColMap1(map, tst, mapx, mapy, 20, 130);
				//enemycolony1[i]->ColMap1(map, reef, mapx, mapy, 20, 130);
				if (Collision::GetLen(enemycolony1[i]->GetPosition(), Player_Pos) < 20) {
					enemycolony1[i]->Motion(player);
					enemycolony1[i]->Attack(player);
				}
				enemycolony1[i]->Update(Player_Pos);
				enemycolony1[i]->EnemySearchPlayer(player);
				//もし敵が死んだら破棄
				if (enemycolony1[i]->GetState_DEAD() == true) {
					Destroy_unique(enemycolony1[i]);
				}
			}
	
		if (enemycolony2[i] != nullptr) {
				enemycolony2[i]->ColMap1(map, tst, mapx, mapy, 20, 130);
				enemycolony2[i]->ColMap1(map, reef, mapx, mapy, 20, 130);
				if (Collision::GetLen(enemycolony2[i]->GetPosition(), Player_Pos) < 20) {
					enemycolony2[i]->Motion(player);
					enemycolony2[i]->Attack(player);
				}
				enemycolony2[i]->Update(Player_Pos);
				enemycolony2[i]->EnemySearchPlayer(player);
				//もし敵が死んだら破棄
				if (enemycolony2[i]->GetState_DEAD() == true) {
					Destroy_unique(enemycolony2[i]);

				}
		}
	}
	Fader::FeedSpriteUpdate();

	atb = BossEnemy::GetInstance()->GetaltAttack();

	item->HealEfficasy(player);
	item2->HealEfficasy(player);

	effects->HealEffect(item->ColItem(), item2->ColItem());
	item->Update(enemycolony1);
	item2->Update(enemycolony2);

	GameUI::AllowUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player->GetPosition(),
		Line::GetInstance()->GetlineAngle(), Line::GetInstance()->Gettriggerflag());
	GameUI::TargetUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), Line::GetInstance()->Getelf());
	GameUI::PlayerUIUpdate(player);
	//シーンチェンジ
	if (Input::GetInstance()->TriggerKey(DIK_R) || (Player_Pos.y <= -50)) {//押されたら
		Retry::SetStage(Jungle_1_3);
		BaseScene* scene = new ClearScene(sceneManager_);//次のシーンのインスタンス生成
		sceneManager_->SetnextScene(scene);//シーンのセット
	}
}
#pragma endregion 

//スプライトの描画
#pragma region モデルの描画
void BossScene2::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{
	/*player->PreDraw();
	player->Draw();
	player->PostDraw();*/

	item->Draw();
	item2->Draw();
	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			if (map[j][i] == 2) {
				tst[j][i]->PreDraw();
				tst[j][i]->Draw();
				tst[j][i]->PostDraw();
			}
			if (map[j][i] == 1) {
				reef[j][i]->PreDraw();
				reef[j][i]->Draw();
				reef[j][i]->PostDraw();
			}
		}
	}


}
//sプライと以外の描画
void BossScene2::MyGameDraw(DirectXCommon* dxcomn)
{
	Sprite::PreDraw(dxcomn->GetCmdList());

	dxcomn->ClearDepthBuffer(dxcomn->GetCmdList());
	Sprite::PostDraw(dxcomn->GetCmdList());

	//スプライトの描画
	SpriteDraw(dxcomn->GetCmdList());

	if (bossenemy != nullptr) {
		bossenemy->Draw(dxcomn);
	}
	for (int i = 0; i < 10; i++) {
		//if (Collision::GetLen(enemycolony1[i]->GetPosition(), Player_Pos) < 10) {
		if (enemycolony1[i] != nullptr) {
			enemycolony1[i]->Draw(dxcomn);
		}
		//}
	//	if (Collision::GetLen(enemycolony2[i]->GetPosition(), Player_Pos) < 10) {
		if (enemycolony2[i] != nullptr) {
			enemycolony2[i]->Draw(dxcomn);
		}
		//}
	}
	//普通のテクスチャの描画
	Line::Draw(dxcomn);

	GameUI::AllDraw(dxcomn);

	//attackeffects->Draw(dxcomn);
	effects->Draw(dxcomn);
	//effects2->Draw(dxcomn);
	//FBXの描画
	object1->Draw(dxcomn->GetCmdList());
	Sprite::PreDraw(dxcomn->GetCmdList());
	//setumei->Draw();
	//dxcomn->ClearDepthBuffer(dxcomn->GetCmdList());
	Fader::FeedSpriteDraw();
	Sprite::PostDraw(dxcomn->GetCmdList());

	GameUI::NowLoadDraw(dxcomn);
	GameUI::HintForeBossDraw(dxcomn);
}
#pragma endregion
//↓に入る
#pragma region
void BossScene2::Draw(DirectXCommon* dxcomn)
{
	dxcomn->BeginDraw();
	MyGameDraw(dxcomn);
	effects->ImGuiDraw();
	ImGuiDraw();//imguiは最後の方入れとく
	dxcomn->EndDraw();
}
#pragma endregion

void BossScene2::ImGuiDraw()
{
	/*ImGui::Begin("ww");
	int index = Line::GetInstance()->Getindex();
	ImGui::SliderInt("index", &index, 200, -200);
	ImGui::End();*/

}
#pragma region 解放部分
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