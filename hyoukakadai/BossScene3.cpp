#include "BossScene3.h"
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
#include"Destroy.h"
#include"Fader.h"
#include"BossScene1.h"
#include"SeaBoss.h"
#include"FirstBossScene.h"
#include"GamOver.h"
#include"FishEnemy.h"
#include"Retry.h"
//コメントアウト
#include"PorcFish.h"


//シーンのコンストラクタ
BossScene3::BossScene3(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}

#pragma region スプライトの生成
//スプライト生成
void BossScene3::SpriteCreate()
{
	// デバッグテキスト用テクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont2.png");
	//普通のテクスチャ(スプライトじゃないよ)
	Line::Initialize();
	GameUI::AllowUISet();

	Texture::LoadTexture(6, L"Resources/gomi.png");
	Sprite::LoadTexture(51, L"Resources/waterground.png");
	Sprite::LoadTexture(1, L"Resources/haikei2.png");
	Sprite::LoadTexture(2, L"Resources/setumei.png");
	nTexture::LoadTexture(50, L"Resources/Buble.png");

	mech = std::make_unique<Texture>();
	mech->Create(6, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });// = Texture::Create(6, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });

	zukki = std::make_unique<Texture>();
	zukki->Create(1, { 0,-20,50 }, { 1,1,1 }, { 1,1,1,1 });
	for (int i = 0; i < 8; i++) {
		BubbleSprite[i] = nTexture::Create(50, { 0.0f,0.0f,0 }, { 200,200,0 }, {1,1,1,0.4});
		BublePos[i].x = Player_Pos.x+30;
		randPosY[i] = rand() %30-30;
		RandAngle[i] = (rand() % 50 + 10)*0.05f;
		BublemoveX[i] = rand() % 10 + 4;
		BublemoveX[i] * 0.01f;
		cycleMove[i] = rand() % 250 + 10;
	}
	background[0] = Sprite::Create(51, { 0.0f,0.0f });
	background[1] = Sprite::Create(51, { 1920.0f,0.0f });

	//setumei = Sprite::Create(2, { 0.0f,0.0f });
	// デバッグテキスト初期化
	dxcomn = new DirectXCommon();
	debugText = new DebugTxt();
	debugText->Initialize(debugTextTexNumber);
}
#pragma endregion

#pragma region 
void BossScene3::ModelCreate()
{
	playermodel = Model::CreateFromOBJ("player");
	player = Player::Create(playermodel);
	player->Initialize();
	tstmodel = Model::CreateFromOBJ("sea");
	worldmodel = Model::CreateFromOBJ("skydome");
	harimodel = Model::CreateFromOBJ("hari");
	goalmodel = Model::CreateFromOBJ("goal");


	item = new Item();
	item->Initialize();


	item2 = new Item();
	item2->Initialize();

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
	BckGrnd[0] = 0;
	BckGrnd[1] = 1900;

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
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 200; j++) {
		
			if (map[i][j] == 41) {
				if (enemy[9] != nullptr) {
					enemy[9]->Setposition(tst[i][j]->GetPosition());
				}
			}
		
			if (map[i][j] == 60) {
				if (enemy[1] != nullptr) {
					enemy[1]->Setposition(tst[i][j]->GetPosition());
				}
			}
			if (map[i][j] == 61) {
				if (enemy[2] != nullptr) {
					enemy[2]->Setposition(tst[i][j]->GetPosition());
				}
			}
			if (map[i][j] == 52) {
				if (enemy[4] != nullptr) {
					enemy[4]->Setposition(tst[i][j]->GetPosition());
				}
			}
			if (map[i][j] == 53) {
				if (enemy[5] != nullptr) {
					enemy[5]->Setposition(tst[i][j]->GetPosition());
				}
			}
			if (map[i][j] == 54) {
				if (enemy[6] != nullptr) {
					enemy[6]->Setposition(tst[i][j]->GetPosition());
				}
			}
			

		}
	}
}
#pragma endregion

#pragma region 各パラメータのセット
void BossScene3::SetPrm()
{
	//setumei->SetPosition({ 0, 400 });
	//setumei->SetSize({ 500,300 });
	//setumei->setcolor({ 1,1,1,1 });

	for (int i = 0; i < 8; i++) {
		BubbleSprite[i]->SetPosition({ BublePos[i].x,BublePos[i].y,5 });
		BubbleSprite[i]->SetScale({ 0.5,0.5,0 });
		BubbleSprite[i]->SetColor({ 1,1,1,0.4 });
	}
	hari->SetPosition({ hari_Pos.x + 2.0f,hari_Pos.y,hari_Pos.z });

	half_height = player->GetScale().y;
	half_Width = player->GetScale().x;


	player->SetPosition({ Player_Pos });
	player->SetScale({ Player_Scl });
	player->SetRotation({ Player_Rot });

	block->SetPosition({ block_pos });
	block->SetScale({ block_Scl });

	world->SetPosition({ 0,0,0 });
	world->SetScale({ 1,1,1 });

	sentan->SetPosition({ sentan_Pos });
	for (int i = 0; i < 2; i++) {
		background[i]->SetPosition({ BckGrnd[i],0});
		background[i]->SetSize({ WinApp::window_width,WinApp::window_height });
		background[i]->setcolor({ 1,1,1,0.4 });
	}

	object1->SetPosition({ Player_Pos });
	object1->SetRotation({ Player_Rot });
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 200; j++) {
		
			if (map[i][j] == 42) {
				if (enemy2[0] != nullptr) {
					enemy2[0]->Setposition(tst[i][j]->GetPosition());
				}
			}
			if (map[i][j] == 43) {
				if (enemy2[1] != nullptr) {
					enemy2[1]->Setposition(tst[i][j]->GetPosition());
				}
			}
			if (map[i][j] == 44) {
				if (enemy2[2] != nullptr) {
					enemy2[2]->Setposition(tst[i][j]->GetPosition());
				}
			}
			if (map[i][j] == 45) {
				if (enemy2[3] != nullptr) {
					enemy2[3]->Setposition(tst[i][j]->GetPosition());
				}
			}
			if (map[i][j] == 46) {
				if (enemy2[4] != nullptr) {
					enemy2[4]->Setposition(tst[i][j]->GetPosition());
				}
			}
			if (map[i][j] == 47) {
				if (enemy2[5] != nullptr) {
					enemy2[5]->Setposition(tst[i][j]->GetPosition());
				}
			}
			if (map[i][j] == 48) {
				if (enemy2[6] != nullptr) {
					enemy2[6]->Setposition(tst[i][j]->GetPosition());
				}
			}
			if (map[i][j] == 49) {
				if (enemy2[7] != nullptr) {
					enemy2[7]->Setposition(tst[i][j]->GetPosition());
				}
			}
			if (map[i][j] == 50) {
				if (enemy2[8] != nullptr) {
					enemy2[8]->Setposition(tst[i][j]->GetPosition());
				}
			}
			if (map[i][j] == 51) {
				if (enemy2[9] != nullptr) {
					enemy2[9]->Setposition(tst[i][j]->GetPosition());
				}
			}
			if (map[i][j] == 51) {
				if (enemy2[9] != nullptr) {
					enemy2[9]->Setposition(tst[i][j]->GetPosition());
				}
			}

			if (map[i][j] == 40) {
				if (enemy[7] != nullptr) {
					enemy[7]->Setposition(tst[i][j]->GetPosition());
				}
			}
			if (map[i][j] == 55) {
				if (enemy[9] != nullptr) {
					enemy[9]->Setposition(tst[i][j]->GetPosition());
				}
			}
			if (map[i][j] == 56) {
				if (enemy[8] != nullptr) {
					enemy[8]->Setposition(tst[i][j]->GetPosition());
				}
			}
		}
	}
}
#pragma endregion

#pragma region オブジェクト+ライトの更新処理
void BossScene3::objUpdate()
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


	world->Update({ 1,1,1,1 });
	block->Update({ 1,1,1,1 });
	hari->Update({ 1,1,1,1 });

	goal->Update({ 1,1,1,1 });

}
#pragma endregion

#pragma region 初期化
void BossScene3::Initialize(DirectXCommon* dxCommon)
{
	GameUI::UISpriteSet();
	GameUI::TargetUISet();
	GameUI::PlayerUISet();
	enemy[0] = std::make_unique<SeaBoss>();
	//enemy[0] = std::make_unique<ThrowEnemy>();
	enemy[9] = std::make_unique<PorcFish>();
	enemy[8] = std::make_unique<PorcFish>();
	enemy[7] = std::make_unique<PorcFish>();

	enemy[1] = std::make_unique<MobEnemy>();
	enemy[2] = std::make_unique<ThrowEnemy>();
	enemy[3] = std::make_unique<ThrowEnemy>();
	enemy[4] = std::make_unique<ThrowEnemy>();
	enemy[5] = std::make_unique<ThrowEnemy>();
	enemy[6] = std::make_unique<MobEnemy>();
	//enemy[0] = new MobEnemy();
	//enemy[9]->Setposition({ 1070,-18.2f,0 });
	enemy[8]->Setposition({ 80,-12.2f,0 });
	//enemy[7]->Setposition({ 800,-4.2f,0 });
	enemy[3]->Setposition({ 80,-4.2f,0 });
	//enemy[0]->Setposition({ 50, -15, 0 });
	enemy[0]->Initialize();
	enemy[1]->Initialize();
	enemy[2]->Initialize();
	enemy[3]->Initialize();
	enemy[4]->Initialize();
	enemy[5]->Initialize();
	enemy[6]->Initialize();
	enemy[7]->Initialize();
	enemy[8]->Initialize();
	enemy[9]->Initialize();
	mapcol = new Collision();
	
	//bossenemy->Setposition({ 20, -4, 0 });
	enemy2[0] = std::make_unique<PorcFish>();
	enemy2[1] = std::make_unique<PorcFish>();
	enemy2[2] = std::make_unique<PorcFish>();
	enemy2[3] = std::make_unique<PorcFish>();
	enemy2[4] = std::make_unique<PorcFish>();
	enemy2[5] = std::make_unique<PorcFish>();
	enemy2[6] = std::make_unique<PorcFish>();
	enemy2[7] = std::make_unique<PorcFish>();
	enemy2[8] = std::make_unique<PorcFish>();
	enemy2[9] = std::make_unique<PorcFish>();

	for (int i = 0; i < 10; i++) {
		//enemy2[i] = nullptr;
		//enemycolony1[i]->Initialize();
		enemy2[i]->Initialize();
		//enemy2[i]->Setposition({ 1222,1,1 });
	}

	SpriteCreate();//
	ModelCreate();//

	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height/*input*/);
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);

	effects->Initialize(dxCommon, camera);
	attackeffects->Initialize(dxCommon, camera);
	
	//モデル名を指定してファイル読み込み
	fbxmodel = FbxLoader::GetInstance()->LoadModelFromFile("knight");
	fbxmodel2 = FbxLoader::GetInstance()->LoadModelFromFile("shark");

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

	object2 = new f_Object3d();
	object2->Initialize(dxCommon, camera);
	object2->SetModel(fbxmodel2);
	/*audio = new Audio();
	audio->Initialize();
	audio->LoopWave("Resources/loop100216.wav", vol);*/
	postEffect = new PostEffect();
	postEffect->Initialize();
	object2->PlayAnimation();
	object1->PlayAnimation();

}
#pragma endregion

#pragma region 更新処理
void BossScene3::Update(DirectXCommon* dxCommon)
{
	Old_Pos = Player_Pos;
	spotLightpos[0] = Player_Pos.x;
	spotLightpos[1] = Player_Pos.y + 1000;
	spotLightpos[2] = 0;

	object1->SetPosition({ Player_Pos.x,Player_Pos.y,Player_Pos.z });
	//object1->SetPosition({ Player_Pos.x + 4.0f,Player_Pos.y,Player_Pos.z });

	if (Line::GetInstance()->Gettriggerflag() != true || Line::GetInstance()->Getboundflag() == true) {
		player->PlayerMoves(Player_Pos, moveSpeed, jumpFlag, grav, time, Player_Rot);
	}
	if (enemy[0]->GetPosition().x < 400) {
		if (Collision::GetInstance()->Gethit() == true) {
			loadf = false;
			hintload = false;

			Fader::feedOut(0.0f, 0.1f);
			if (Fader::GetInstance()->GetAlpha() <= 0.0f) {
				//::GetInstance()->SetHit(false);
			}
		} else {
			hintload = true;
			loadf = true;
		}
	}
	GameUI::HintSeaBossUpdate(hintload);
	GameUI::NowLoadUpdate(loadf);

	BckGrnd[0] -= 10;
	BckGrnd[1] -= 10;
	if (BckGrnd[0] <= -1900) {
		BckGrnd[0] = 1900;
	}
	if (BckGrnd[1] <= -1900) {
		BckGrnd[1] = 1900;
	}
	BubleMove();

	////当たり判定
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
			Player_Pos.z += 0.05f;
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
		grav = -0.01f;
	}

	time += 0.04f;
	Player_Pos.y -= grav *time* time;


	//頂点座標の更新
	
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
	Line::CollisionEnemys2group(enemy2);


	object2->setcounter(2);

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

	player->SetPosition(Player_Pos);
	player->SetRotation(Player_Rot);
	player->SetScale(Player_Scl);
	player->Attack(Player_Pos);
	//for (int i = 0; i < 2; i++) {
	player->CollisionAttack(enemy, Player_Pos);

	player->CollisionAttack(enemy2, Player_Pos);

	SetPrm();//パラメータのセット

	objUpdate();//オブジェクトの更新処理

	effects->Update2(dxCommon, camera, enemy2, player);
	
	SetPrm();//パラメータのセット
	object1->Updata({ 1,1,1,1 }, dxCommon, camera, TRUE);
	//if (enemy[0]->GetHP() ==20) {
		//if (Input::GetInstance()->TriggerKey(DIK_0)) {
			
		//}
	//}
	object2->Updata({ 1,1,1,1 }, dxCommon, camera, TRUE);


	for (int i = 0; i < 8; i++) {
	
		BubbleSprite[i]->Update(camera->GetViewMatrix(), camera->GetProjectionMatrix());
	}
	objUpdate();//オブジェクトの更新処理
	for (int i = 1; i < 10; i++) {
		if (enemy[i] != nullptr) {

			if (Collision::GetLen(enemy[0]->GetPosition(), enemy[i]->GetPosition()) < 15) {
				enemy[i]->SetHP(0);
				enemy[i]->SetDead(true);
			}
		}
	}
	effects->HealEffects(item->ColItem());
	effects->HealEffects(item2->ColItem());
	effects->Update(dxCommon, camera, enemy, player);

	//enemyにnullptr代入するときは敵が死んだら

	//SeaBoss::GetInstance()->EatEnemy(enemy);

	for (int i = 0; i < 10; i++) {
		if (enemy[i] != nullptr) {
			//プレイヤーの検知
			enemy[i]->Motion(player);
			enemy[i]->ColMap(map, tst, mapx, mapy, MAX_X, MAX_Y);
			enemy[i]->Attack(player);
			enemy[i]->Update(Player_Pos);

			enemy[i]->EnemySearchPlayer(player);
			enemy[i]->SearchAction(camera->GetViewMatrix(), camera->GetProjectionMatrix(), Player_Pos);

			//もし敵が死んだら破棄
			if (enemy[i]->GetState_DEAD() == true) {
				Destroy_unique(enemy[i]);

			}
		}

	if (enemy2[i] != nullptr) {
		enemy2[i]->ColMap(map, tst, mapx, mapy, 20, 130);
		//enemy2[i]->ColMap(map, tst, mapx, mapy, 20, 130);
		if (Collision::GetLen(enemy2[i]->GetPosition(), Player_Pos) < 20) {
			enemy2[i]->Motion(player);
			enemy2[i]->Attack(player);
		}
		enemy2[i]->Update(Player_Pos);
		enemy2[i]->EnemySearchPlayer(player);
		//もし敵が死んだら破棄
		if (enemy2[i]->GetState_DEAD() == true) {
			Destroy_unique(enemy2[i]);
		}
	}
	}
	if (!SeaBoss::GetInstance()->Getdeathf()) {
		if (BRotation.z < -90) {
			RotMove = 1;
		} else if (BRotation.z > 0) {
			RotMove = -1;
		}

		BRotation.y = -90;
		BRotation.z += RotMove * 1;
	}
	object2->SetRotation(BRotation);
	object2->SetPosition(enemy[0]->GetPosition());
	object2->SetScale({ 0.11,0.13,0.11 });
	//Player_Pos.y+=moves
	item->HealEfficasy(player);
	item2->HealEfficasy(player);
	item->Update(enemy);
	item2->Update(enemy2);

	Fader::FeedSpriteUpdate();
	GameUI::AllowUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player->GetPosition(),
		Line::GetInstance()->GetlineAngle(), Line::GetInstance()->Gettriggerflag());
	GameUI::TargetUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), Line::GetInstance()->Getelf());
	GameUI::PlayerUIUpdate(player);
	//シーンチェンジ
	if (player->getHp() <= 0 || (Player_Pos.y <= -50)) {
		Retry::SetStage(Sea_1_3);
		BaseScene* scene = new GamOver(sceneManager_);//次のシーンのインスタンス生成
		sceneManager_->SetnextScene(scene);//シーンのセット
		//delete scene;
	}
}
#pragma endregion 

//スプライトの描画
#pragma region モデルの描画
void BossScene3::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{


	/*player->PreDraw();
	player->Draw();
	player->PostDraw();*/


	item->Draw();
	item2->Draw();
	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			if (map[j][i] == 1 ) {
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


	/*hari->PreDraw();
	hari->Draw();
	hari->PostDraw();*/

}
//sプライと以外の描画
void BossScene3::MyGameDraw(DirectXCommon* dxcomn)
{

	
	//スプライトの描画
	SpriteDraw(dxcomn->GetCmdList());

	for (int i = 0; i < 10; i++) {
		if (enemy[i] != nullptr) {
			enemy[i]->Draw(dxcomn);
			enemy[i]->SearchActionDraw(dxcomn);
		}
		if (enemy2[i] != nullptr) {
			enemy2[i]->Draw(dxcomn);
		}
	}
	//普通のテクスチャの描画
	Line::Draw(dxcomn);

	//weffect->Draw(dxcomn);
	GameUI::AllowUIDraw(dxcomn);
	GameUI::TargetUIDraw(dxcomn);

	GameUI::PlayerUIDraw(dxcomn);
	GameUI::UIDraw(dxcomn);

	attackeffects->Draw(dxcomn);
	effects->Draw(dxcomn);
	//FBXの描画
	object1->Draw(dxcomn->GetCmdList());
	object2->Draw(dxcomn->GetCmdList());
	nTexture::PreDraw(dxcomn->GetCmdList());
	for (int i = 0; i < 8; i++) {
		BubbleSprite[i]->Draw();
	}
	//dxcomn->ClearDepthBuffer(dxcomn->GetCmdList());
	Sprite::PreDraw(dxcomn->GetCmdList());
	background[0]->Draw();
	background[1]->Draw();

	//setumei->Draw();
	//dxcomn->ClearDepthBuffer(dxcomn->GetCmdList());
	Fader::FeedSpriteDraw();
	Sprite::PostDraw(dxcomn->GetCmdList());


	nTexture::PostDraw();
	GameUI::NowLoadDraw(dxcomn);
	GameUI::HintSeaBossDraw(dxcomn);
}
#pragma endregion
//↓に入る
#pragma region
void BossScene3::Draw(DirectXCommon* dxcomn)
{

	dxcomn->BeginDraw();
	MyGameDraw(dxcomn);
	ImGuiDraw();
	dxcomn->EndDraw();
}
#pragma endregion

void BossScene3::ImGuiDraw()
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
	//	ImGui::SliderFloat("positionY", &rf2, -100, 100);
	//	ImGui::SliderFloat("positionZ", &rrr, -100, 100);
	//	ImGui::SliderFloat("positionY", &rf2, -200, 200);
	//	ImGui::SliderFloat("positionZ", &rrr, -200, 200);
	//	ImGui::TreePop();
	//}
	//float linex = Line::GetInstance()->getpos().x;
	//float liney = Line::GetInstance()->getpos().y;
	//float rr = player->GetPosition().x;
	//if (ImGui::TreeNode("Player_position")) {
	//	ImGui::SliderFloat("positionX", &BublePos[0].x, -200, 200);
	int xf=Line::GetInstance()->Getindex();
	int xf2= Line::GetInstance()->Getindex2();
	//	ImGui::SliderFloat("positionY", &BublePos[0].y, -200, 200);
	/*	ImGui::SliderInt("positionZ", &xf, -200, 200);
		ImGui::SliderInt("positionZ", &xf2, -200, 200);*/
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


	ImGui::End();

	//
	//ImGui::End();

}
#pragma region 解放部分
void BossScene3::Finalize()
{
	//delete sceneManager_;

	//delete efk,efk1;

}

void BossScene3::BubleMove()
{
	float PI = 3.14;
	for (int i = 0; i < 8; i++) {
		//RandAngle[i] * 0.01f;
		countMove[i]++;
		const float moveCycle = 120.0f;
			BublePos[i].y = (randPosY[i] ) + sin(PI * 2 / moveCycle * countMove[i]) * RandAngle[i];
			BublePos[i].x -= BublemoveX[i]*0.05f;

			if (BublePos[i].x < Player_Pos.x-30) {
				BublePos[i].x = Player_Pos.x + 30;
			}
		}
}
#pragma endregion
