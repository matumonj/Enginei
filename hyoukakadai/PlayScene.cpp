#include "PlayScene.h"
#include"Input.h"
#include"DirectXCommon.h"
#include"TitleScene.h"
#include"SceneManager.h"
#include"MobEnemy.h"
#include"BossEnemy.h"
#include"Line.h"
#include"Destroy.h"
#define PI 3.14
#define CLENGTH     (LENGTH * 2 * PI)   // 紐を伸ばして一周させた場合に出来る円の円周の長さ
#define MASS        0.346               // ぶら下がっている物の質量
#define G           0.05               // 重力加速度
#define STX         320                 // 振り子の軸のx座標
#define STY         100                 // 振り子の軸のy座標

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

	mech = std::make_unique<Texture>();
	mech->Create(6, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });// = Texture::Create(6, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });

	zukki = std::make_unique<Texture>();
	zukki->Create(1, { 0,-20,50 }, { 1,1,1 }, { 1,1,1,1 });

	background = Sprite::Create(1, { 0.0f,-200.0f });
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
<<<<<<< HEAD
	player = Player::Create(playermodel);
	player->Initialize();
	tstmodel = Model::CreateFromOBJ("block");
=======
	tstmodel = Model::CreateFromOBJ("box1");
>>>>>>> 6c88f78ac56c1a5dc84a758497da89244adc2473
	worldmodel = Model::CreateFromOBJ("skydome");
	harimodel = Model::CreateFromOBJ("hari");

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

	Player_Pos = player->GetPosition();
	Player_Rot = player->GetRotation();
	Player_Scl = player->GetScale();
}
#pragma endregion

#pragma region 各パラメータのセット
void PlayScene::SetPrm()
{
<<<<<<< HEAD
		
	posX = player->GetPosition().x;
	posY = player->GetPosition().y;
	half_height = player->GetScale().y / 2;
	half_Width = player->GetScale().x / 2;
=======
	for (int i = 0; i < 10; i++) {
			player[i]->SetPosition({ Player_Pos[i] });
		player[i]->SetScale({ Player_Scl });
		player[i]->SetRotation({Player_Rot});
	}

	hari_Pos = Player_Pos[0];

	hari->SetPosition({ hari_Pos.x+2.0f,hari_Pos.y,hari_Pos.z });

	posX = player[0]->GetPosition().x;
	posY = player[0]->GetPosition().y;
	half_height = player[0]->GetScale().y;
	half_Width = player[0]->GetScale().x ;
>>>>>>> 6c88f78ac56c1a5dc84a758497da89244adc2473

	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			tst[j][i]->SetPosition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			tst[j][i]->SetRotation({ tst_Rot });
			tst[j][i]->SetScale({ tst_Scl });

		}
	}

	block->SetPosition({ block_pos });
	block->SetScale({ block_Scl });

	world->SetPosition({ 0,0,0 });
	world->SetScale({ 1,1,1 });

	sentan->SetPosition({ sentan_Pos });
	



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

	world->Update({ 1,1,1,1 });
	block->Update({ 1,1,1,1 });
	hari->Update({ 1,1,1,1 });
}
#pragma endregion

#pragma region 初期化
void PlayScene::Initialize(DirectXCommon* dxCommon)
{
	//
	
	GameUI::UISpriteSet();
	GameUI::TargetUISet();
	enemy[0] = std::make_unique<MobEnemy>();
	//enemy[0] = new MobEnemy();
	enemy[0]->Initialize();
	enemy[1] = std::make_unique<MobEnemy>();
	enemy[1]->Initialize();
	enemy[1]->Setposition({ -40, 0, 0
		});
	enemy[0]->Setposition({ 
		20, 0, 0 });
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
	spotLightpos[0] = 10;
	spotLightpos[2] = 0;

	//モデル名を指定してファイル読み込み
	fbxmodel = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
	//efk = new Effects();
	//efk = std::make_unique<Effects>();
	//effects->Initialize(dxCommon, camera);
	//weffect = new pEffect();
	//weffect->Initialize(dxCommon, camera);
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
	Input::MouseMove mouseMove = Input::GetInstance()->GetMouseMove();
	//マウスの入力状態取得
	if (Input::GetInstance()->PushMouseLeft()) {
		dy = (float)mouseMove.lX;
		dx = (float)mouseMove.lY;
		dz = (float)mouseMove.lZ;
	}

	Old_Pos = Player_Pos;

	//コントローラー
	if (Input::GetInstance()->TriggerButtonA()) {
		//攻撃処理

	}

	if (Input::GetInstance()->TriggerButtonRB()) {
		Line::GetInstance()->SetTrigger(true);
		//Line = 1;
	}

	///////// コントローラー //////////
	// スティックの方向判定
	// 無反応範囲
	LONG u_r = 32768;
	LONG a = 30000;

	//左
	// 方向だけを調べる方法
	if (Input::GetInstance()->GetCMove().lX < u_r - a)
	{
		// 左に傾けた
		//Player_Pos[0].x -= 1;

	} else if (Input::GetInstance()->GetCMove().lX > u_r + a)
	{
		// 右に傾けた
		//Player_Pos[0].x += 1;
	}

	if (Input::GetInstance()->GetCMove().lY < u_r - a)
	{
		// 左に傾けた


	} else if (Input::GetInstance()->GetCMove().lY > u_r + a)
	{
		// 右に傾けた

	}

	//// 右
	//// 方向だけを調べる方法
	//if (Input::GetInstance()->GetCMove().lRx < u_r - a)
	//{
	//	// 左に傾けた
	//	
	//} else if (Input::GetInstance()->GetCMove().lRx > u_r + a)
	//{
	//	// 右に傾けた
	//	
	//}

	//if (Input::GetInstance()->GetCMove().lRy < u_r - a)
	//{
	//	// 左に傾けた
	//	
	//} else if (Input::GetInstance()->GetCMove().lRy > u_r + a)
	//{
	//	// 右に傾けた
	//	
	//}

	// 傾きの比率を調べる方法
	//LONG length = 32768; // 原点から最小、最大までの長さ
	//float y_vec = (Input::GetInstance()->GetCMove().lY - u_r) / (length - u_r);

	///

<<<<<<< HEAD
	if (posX - Player_Scl.x < block_pos.x + block_Scl.x && block_pos.x < Old_Pos.x - Player_Scl.x - 1 && (block_pos.y - block_Scl.y < posY + Player_Scl.y && posY - Player_Scl.y < block_pos.y + block_Scl.y)) {
		Player_Pos.x = Old_Pos.x;
=======
	if (Input::GetInstance()->Pushkey(DIK_RIGHT)) {
		Player_Pos[0].x += moveSpeed;
	}
	if (Input::GetInstance()->Pushkey(DIK_LEFT)) {


		Player_Pos[0].x -= moveSpeed;


	}

	if (Input::GetInstance()->Pushkey(DIK_UP)) {
		Player_Pos[0].y -= moveSpeed;
	}
	if (Input::GetInstance()->Pushkey(DIK_DOWN)) {
		Player_Pos[0].y += moveSpeed;
	}

	//残像
	for (int i = 9; i > 0; i--) {
		Player_Pos[i].x = Player_Pos[i - 1].x + zanzouSpeed;
		Player_Pos[i].y = Player_Pos[i - 1].y + zanzouSpeed;
	}
	////当たり判定

	//grav = 0.03;

	//Player_Pos[0].y = block_pos.y + block_Scl.y+Player_Scl.y+0.01;

	if (posX - Player_Scl.x < block_pos.x + block_Scl.x && block_pos.x < Old_Pos.x - Player_Scl.x -1 && (block_pos.y - block_Scl.y < posY + Player_Scl.y && posY - Player_Scl.y < block_pos.y + block_Scl.y)) {
		Player_Pos[0].x = Old_Pos.x ;
>>>>>>> 6c88f78ac56c1a5dc84a758497da89244adc2473
	}
	//a


	for (int i = 0; i < MAX_X; i++) {
		for (int j = 0; j < MAX_Y; j++) {
			if (map[j][i] == 1) {
				mapx[j][i] = tst[j][i]->GetPosition().x;
				mapy[j][i] = tst[j][i]->GetPosition().y;
				map_half_heigh = tst[j][i]->GetScale().y;
				map_half_width = tst[j][i]->GetScale().x;
<<<<<<< HEAD
				//下辺の当たり判定
				if ((posX + half_Width > mapx[j][i] - map_half_width && posX - half_Width < mapx[j][i] + map_half_width) && Old_Pos.y - half_height - 1 < mapy[j][i] + (map_half_heigh / 2) && posY + half_height > mapy[j][i] - (map_half_heigh / 2)) {
					posY = map_half_heigh + mapy[j][i] + half_height + 0.5;
					Old_Pos.y = posY;
					Player_Pos.y = Old_Pos.y;
					//Player_Rot.x++;
					grav = 0;
					break;
				}
				//上辺の当たり判定
				else if ((posX + half_Width > mapx[j][i] - map_half_width && posX - half_Width < mapx[j][i] + map_half_width) && Old_Pos.y + half_height < mapy[j][i] && posY + half_height + 0.5 > mapy[j][i] - map_half_heigh - 0.5) {
					posY = mapy[j][i] - map_half_heigh - half_height - 0.5;
					Old_Pos.y = posY;
					Player_Pos.y = Old_Pos.y;
					//Player_Rot.x++;
					grav = 0;
=======

				if ((Player_Pos[0].x + (Player_Scl.x) > mapx[j][i] - (map_half_width) && Player_Pos[0].x - (Player_Scl.x) < mapx[j][i] + (map_half_width)) && Old_Pos.y - Player_Scl.y>mapy[j][i] && Player_Pos[0].y - half_height<mapy[j][i]+map_half_heigh ) {
					Player_Pos[0].y = map_half_heigh + mapy[j][i] + Player_Scl.y + 0.001f;
					grav = 0.0f;
					break;
				}
				else if ((Player_Pos[0].x + (Player_Scl.x) > mapx[j][i] - (map_half_width ) && Player_Pos[0].x - (Player_Scl.x) < mapx[j][i] + (map_half_width )) && Old_Pos.y + Player_Scl.y<mapy[j][i] && Player_Pos[0].y + Player_Scl.y>mapy[j][i] - map_half_heigh) {
					Player_Pos[0].y = Player_Pos[0].y -  moveSpeed;
>>>>>>> 6c88f78ac56c1a5dc84a758497da89244adc2473
					break;
				}
				else {
					grav = 0.03;
				}
<<<<<<< HEAD
				//左
				if (posX - half_Width - 0.5 < mapx[j][i] + map_half_width + 0.5 && mapx[j][i] < Old_Pos.x - half_Width && (mapy[j][i] - map_half_heigh < posY + half_Width && posY - half_Width < mapy[j][i] + map_half_width)) {
					posX = mapx[j][i] + map_half_width + half_Width + 0.55;
					Old_Pos.x = posX;
					Player_Pos.x = Old_Pos.x;
					break;
				}
				//右
				else if (posX + half_Width + 0.5 > mapx[j][i] - map_half_width - 0.5 && mapx[j][i] > Old_Pos.x + half_Width && (mapy[j][i] - map_half_heigh < posY + half_Width && posY - half_Width < mapy[j][i] + map_half_width)) {
					posX = mapx[j][i] - map_half_width - half_Width - 0.55;
					Old_Pos.x = posX;
					Player_Pos.x = Old_Pos.x;
=======
				//プレイヤーの左辺
				if ((Player_Pos[0].y - (Player_Scl.y) < mapy[j][i] + map_half_heigh && mapy[j][i] - map_half_heigh < Player_Pos[0].y + (Player_Scl.y)) && Player_Pos[0].x - Player_Scl.x < mapx[j][i] + map_half_width && mapx[j][i] < Old_Pos.x - Player_Scl.y) {
					Player_Pos[0].x = map_half_width + mapx[j][i] + Player_Scl.x + 0.001f;
					break;
				}
				//プレイヤーの右辺
				else if ((Player_Pos[0].y - (Player_Scl.y) < mapy[j][i] + map_half_heigh && mapy[j][i] - map_half_heigh < Player_Pos[0].y + (Player_Scl.y))&&Player_Pos[0].x+Player_Scl.x > mapx[j][i]-map_half_width&&mapx[j][i]>Old_Pos.x+Player_Scl.x-0.5f) {
					Player_Pos[0].x = Player_Pos[0].x - moveSpeed;
					moveSpeed = 0;
>>>>>>> 6c88f78ac56c1a5dc84a758497da89244adc2473
					break;
				}
				else {
					moveSpeed = 0.2f;
				}


					////右
				//else if (posX + half_Width  > mapx[j][i] - map_half_width  && mapx[j][i] > Old_Pos.x + half_Width && (mapy[j][i] - map_half_heigh < posY + half_Width && posY - half_Width < mapy[j][i] + map_half_width)) {
				//	posX = mapx[j][i] - map_half_width - Player_Scl.x;
				//	Old_Pos.x = posX;
				//	Player_Pos[0].x = Old_Pos.x;
				//	break;
				//}
				////下辺の当たり判定
				//if ((posX + half_Width > mapx[j][i] - map_half_width && posX - half_Width < mapx[j][i] + map_half_width) && Old_Pos.y - half_height  < mapy[j][i] + map_half_heigh && posY + half_height > mapy[j][i] - (map_half_heigh / 2)) {
				//	posY = map_half_heigh + mapy[j][i] + Player_Scl.y;
				//	Old_Pos.y = posY;
				//	Player_Pos[0].y = Old_Pos.y;
				//	//Player_Rot.x++;
				//	grav = 0;
				//	break;
				//}
				////上辺の当たり判定
				//else if ((posX + half_Width > mapx[j][i] - map_half_width && posX - half_Width < mapx[j][i] + map_half_width) && Old_Pos.y + half_height < mapy[j][i]  && posY + half_height > mapy[j][i] - map_half_heigh - Player_Scl.y) {
				//	posY = mapy[j][i] - map_half_heigh - Player_Scl.y;
				//	Old_Pos.y = posY;
				//	Player_Pos[0].y = Old_Pos.y;
				//	//Player_Rot.x++;
				//	grav = 0;
				//	break;
				//} else {
				//	grav = 0.03;
				//}
				////左
				//if (posX - half_Width  < mapx[j][i] + map_half_width  && mapx[j][i] < Old_Pos.x - half_Width && (mapy[j][i] - map_half_heigh < posY + half_Width && posY - half_Width < mapy[j][i] + map_half_width)) {
				//	posX = mapx[j][i] + map_half_width + Player_Scl.x;
				//	Old_Pos.x = posX;
				//	Player_Pos[0].x = Old_Pos.x;
				//	break;
				//}
				
			}
		}
	}

#pragma region 線の処理


<<<<<<< HEAD
	if (Line::GetInstance()->Getboundflag() == false || Line::GetInstance()->Gettriggerflag() == false) {
		grav = 0.0f;
=======
	if (Line::GetInstance()->Getboundflag()==false ||Line::GetInstance()->Gettriggerflag()==false) {
		//grav = 0.0f;
>>>>>>> 6c88f78ac56c1a5dc84a758497da89244adc2473
	} else {
		//grav = 0.03f;
	}

<<<<<<< HEAD
	Player_Pos.y -= grav;
=======
//	Player_Pos[0].y -= grav;
>>>>>>> 6c88f78ac56c1a5dc84a758497da89244adc2473

	//頂点座標の更新
	mech->CreateLineTexture(linex, linex2, liney, liney2);

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

	Line::Update(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player, Player_Pos, colf);

	Line::CollisionEnemy(enemy);
	//weffect->Update(dxcomn,camera,player[0]->GetPosition(),Line::GetInstance()->Getboundflag());
	//FBXのアニメーション再生
	if (Input::GetInstance()->Pushkey(DIK_0)) {
		object1->PlayAnimation();
	}

	//FBXモデルの更新
	object1->Updata(TRUE);
	if (Input::GetInstance()->Pushkey(DIK_RIGHT)) {
		Player_Pos.x += moveSpeed;
	}
	if (Input::GetInstance()->Pushkey(DIK_LEFT)) {
		Player_Pos.x -= moveSpeed;

	}

	if (Input::GetInstance()->Pushkey(DIK_UP)) {
		Player_Pos.y -= moveSpeed;
	}
	if (Input::GetInstance()->Pushkey(DIK_DOWN)) {
		Player_Pos.y += moveSpeed;
	}

		//}
		//カメラ関係の処理
	camera->SetTarget({ 0,1,0 });//注視点
	camera->SetDistance(distance);//
<<<<<<< HEAD
	camera->SetEye({ Player_Pos.x,Player_Pos.y ,Player_Pos.z - 18 });
	camera->SetTarget({ Player_Pos.x,Player_Pos.y ,Player_Pos.z });
=======
	camera->SetEye({ Player_Pos[0].x,Player_Pos[0].y+5 ,Player_Pos[0].z - 18 });
	camera->SetTarget({ Player_Pos[0].x,Player_Pos[0].y ,Player_Pos[0].z });
>>>>>>> 6c88f78ac56c1a5dc84a758497da89244adc2473
	camera->Update();


	player->SetPosition(Player_Pos);
	player->SetRotation(Player_Rot);

	player->SetScale(Player_Scl);


	player->Attack(Player_Pos);
	//for (int i = 0; i < 2; i++) {
	player->CollisionAttack(enemy,Player_Pos);

	SetPrm();//パラメータのセット

	objUpdate();//オブジェクトの更新処理

	//デバッグ用、敵滅殺
	if (Input::GetInstance()->TriggerKey(DIK_D) && enemy[1] != nullptr) {
		enemy[1]->SetDead(true);
	}

	effects->Update(dxCommon, camera, enemy, player);

	//enemyにnullptr代入するときは敵が死んだら
	for (int i = 0; i < 2; i++) {
		if (enemy[i] != nullptr) {

			enemy[i]->Update(Player_Pos);
			//プレイヤーの検知
			enemy[i]->EnemySearchPlayer(player->GetPosition());
			//もし敵が死んだら破棄
			if (enemy[i]->GetState_DEAD() == true) {
				Destroy_unique(enemy[i]);
			}
		}
	}
	
	GameUI::AllowUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player->GetPosition(),
		Line::GetInstance()->GetlineAngle(), Line::GetInstance()->Gettriggerflag());
	GameUI::TargetUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), Line::GetInstance()->Getelf());
	//シーンチェンジ
	if (Input::GetInstance()->TriggerKey(DIK_R)) {//押されたら
		BaseScene* scene = new TitleScene(sceneManager_);//次のシーンのインスタンス生成
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

	world->PreDraw();
	//world->Draw();
	world->PostDraw();
	for (int i = 0; i < 2; i++) {
		if (enemy[i] != nullptr) {
			enemy[i]->Draw();
		}
	}
	block->PreDraw();
	block->Draw();
	block->PostDraw();

	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			if (map[j][i] == 1) {
				tst[j][i]->PreDraw();
				tst[j][i]->Draw();
				tst[j][i]->PostDraw();
			}
		}
	}

	hari->PreDraw();
	hari->Draw();
	hari->PostDraw();

}
//sプライと以外の描画
void PlayScene::MyGameDraw(DirectXCommon* dxcomn)
{
	//スプライトの描画
	SpriteDraw(dxcomn->GetCmdList());

	//普通のテクスチャの描画
	Line::Draw(dxcomn);

	//weffect->Draw(dxcomn);
	GameUI::AllowUIDraw(dxcomn);
	GameUI::TargetUIDraw(dxcomn);

	GameUI::UIDraw(dxcomn);
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
		//ImGui::SliderFloat("positionX", &needlepos.x, -100, 100);
		///ImGui::SliderFloat("positionY", &needlepos.y, -100, 100);
		///ImGui::SliderFloat("positionZ", &needlepos.z, -100, 100);
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
		//ImGui::SliderInt("positionX", &L_Cflag, -100, 100);
		//ImGui::SliderFloat("positionY", &debuga, -100, 100);
		//ImGui::SliderInt("positionZ", &elf, -100, 100);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("enemy_position")) {
		float rf = enemy[0]->GetPosition().x;
		float rf2 = enemy[0]->GetPosition().y;
		float rrr = player->getdis();
		//float rf3 = enemy->GetPosition().z;
	ImGui::SliderFloat("positionX", &rf, -100, 100);
		ImGui::SliderFloat("positionY", &rf2, -100, 100);
		ImGui::SliderFloat("positionZ", &rrr, -100, 100);
		ImGui::TreePop();
	}

	float rr = player->GetPosition().x;
	if (ImGui::TreeNode("Player_position")) {
		ImGui::SliderFloat("positionX", &rr, -100, 100);
		ImGui::SliderFloat("positionY", &Player_Pos.y, -100, 100);
		ImGui::SliderFloat("positionZ", &Player_Pos.z, -100, 100);
		ImGui::TreePop();
	}
	float sx = player->GetArea_S().x;
	float sy = player->GetArea_S().y;

		float ex= player->GetArea_e().x;
	float ey = player->GetArea_e().y;

	if (ImGui::TreeNode("half")) {
		ImGui::SliderFloat("sx", &sx, -100, 100);
		ImGui::SliderFloat("sy", &sy, -100, 100);
		ImGui::SliderFloat("ex", &ex, -100, 100);
		ImGui::SliderFloat("ey", &ey, -100, 100);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Old")) {
		ImGui::SliderFloat("Old_PosX", &Old_Pos.x, -100, 100);
		ImGui::SliderFloat("old_PosY", &Old_Pos.y, -100, 100);
		ImGui::TreePop();
	}

	/*if (ImGui::TreeNode("1")) {
		ImGui::SliderFloat("+_width", &half_Width, -100, 100);
		ImGui::SliderFloat("+_height", &half_height, -100, 100);
		ImGui::SliderFloat("-_width", &half_Width, -100, 100);
		ImGui::SliderFloat("-_height", &half_height, -100, 100);
		ImGui::SliderFloat("map_1_width", &map_half_width, -100, 100);
		ImGui::SliderFloat("map_1_height", &map_half_heigh, -100, 100);
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
#pragma region 解放部分
void PlayScene::Finalize()
{
	//delete sceneManager_;

	//delete efk,efk1;

}
#pragma endregion