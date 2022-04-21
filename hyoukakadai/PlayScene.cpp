#include "PlayScene.h"
#include"Input.h"
#include"DirectXCommon.h"
#include"TitleScene.h"
#include"SceneManager.h"
#include"MobEnemy.h"
#include"BossEnemy.h"
#include"ThrowEnemy.h"
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
	Sprite::LoadTexture(1, L"Resources/haikei2.png");
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
void PlayScene::ModelCreate()
{
	playermodel = Model::CreateFromOBJ("player");
	player = Player::Create(playermodel);
	player->Initialize();
	tstmodel = Model::CreateFromOBJ("box1");
	worldmodel = Model::CreateFromOBJ("skydome");
	harimodel = Model::CreateFromOBJ("hari");
	goalmodel = Model::CreateFromOBJ("box2");


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

	Player_Pos = player->GetPosition();
	Player_Rot = player->GetRotation();
	Player_Scl = player->GetScale();
}
#pragma endregion

#pragma region 各パラメータのセット
void PlayScene::SetPrm()
{

	setumei->SetPosition({ 0, 400 });
	setumei->SetSize({ 500,300 });
	setumei->setcolor({ 1,1,1,1 });

	hari->SetPosition({ hari_Pos.x+2.0f,hari_Pos.y,hari_Pos.z });

	half_height = player->GetScale().y;
	half_Width = player->GetScale().x ;


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
	goal->SetPosition({ goal_pos.x + 185.0f,goal_pos.y-5 ,goal_pos.z });
	block->SetPosition({ block_pos });
	block->SetScale({ block_Scl });

	world->SetPosition({ 0,0,0 });
	world->SetScale({ 1,1,1 });

	sentan->SetPosition({ sentan_Pos });
	
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

	world->Update({ 1,1,1,1 });
	block->Update({ 1,1,1,1 });
	hari->Update({ 1,1,1,1 });
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
	enemy[2]= std::make_unique<ThrowEnemy>();
	enemy[3] = std::make_unique<ThrowEnemy>();
	//enemy[0] = new MobEnemy();

	enemy[3]->Setposition({ 80,-4.2,0 });
	enemy[2]->Setposition({ 100,-4.2,0 });
	enemy[1]->Setposition({ -40, -10, 0 });
	enemy[0]->Setposition({ 20, -10, 0 });
	enemy[0]->Initialize();
	enemy[1]->Initialize();
	enemy[2]->Initialize();
	enemy[3]->Initialize();

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
	Input::MouseMove mouseMove = Input::GetInstance()->GetMouseMove();
	//マウスの入力状態取得
	if (Input::GetInstance()->PushMouseLeft()) {
		dy = (float)mouseMove.lX;
		dx = (float)mouseMove.lY;
		dz = (float)mouseMove.lZ;
	}

	Old_Pos = Player_Pos;
	spotLightpos[0] = Player_Pos.x;
	spotLightpos[1] = Player_Pos.y + 10;
	spotLightpos[2] = 0;
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
		//Player_Pos.x -= 1;

	}
	else if (Input::GetInstance()->GetCMove().lX > u_r + a)
	{
		// 右に傾けた
		//Player_Pos.x += 1;
	}

	if (Input::GetInstance()->GetCMove().lY < u_r - a)
	{
		// 左に傾けた


	}
	else if (Input::GetInstance()->GetCMove().lY > u_r + a)
	{
		// 右に傾けた

	}

	//FBXモデルの更新
	object1->Updata(TRUE);
	if (Input::GetInstance()->Pushkey(DIK_RIGHT)) {
		Player_Pos.x += moveSpeed;
	}
	if (Input::GetInstance()->Pushkey(DIK_LEFT)) {
		Player_Pos.x -= moveSpeed;

	}

	/*if (Input::GetInstance()->Pushkey(DIK_UP)) {
		Player_Pos.y -= moveSpeed;
	}
	if (Input::GetInstance()->Pushkey(DIK_DOWN)) {
		Player_Pos.y += moveSpeed;
	}*/

	///これより上に入力処理をかけ
	////当たり判定

	float disl;

	//入力処理より後に当たり判定を描け
	//aaaaaaa

	for (int i = 0; i < MAX_X; i++) {
		for (int j = 0; j < MAX_Y; j++) {
			if (map[j][i] == 1) {
				mapx[j][i] = tst[j][i]->GetPosition().x;
				mapy[j][i] = tst[j][i]->GetPosition().y;
				height = tst[j][i]->GetScale().y;
				width = tst[j][i]->GetScale().x;
				if ((Line::GetInstance()->getpos().x + 1.0f > mapx[j][i] - (width) && Line::GetInstance()->getpos().x - 1.0f < mapx[j][i] + (width)) && Line::GetInstance()->getpos().y + 1.0f > mapy[j][i] - height && Line::GetInstance()->getpos().y - 1.0f < mapy[j][i] + height) {
					if (Line::GetInstance()->Getreturnflag() != true && Line::GetInstance()->Gettriggerflag() == true) {
						Line::GetInstance()->Setmapcol(true);
						Line::GetInstance()->Setelf(true);
					}
				}

				if ((Player_Pos.x + Player_Scl.x > mapx[j][i] - (width - moveSpeed) && Player_Pos.x - Player_Scl.x < mapx[j][i] + (width - moveSpeed))) {
					if (Old_Pos.y > mapy[j][i] && Player_Pos.y - Player_Scl.y < mapy[j][i] + height) {
						Player_Pos.y = height + mapy[j][i] + Player_Scl.y;
						//moveSpeed = 0;
						grav = 0.0f;
						time = 0;
						break;
					}
					else if (Old_Pos.y <mapy[j][i] && Player_Pos.y + Player_Scl.y>mapy[j][i] - height) {
						Player_Pos.y = mapy[j][i] - (Player_Scl.y + height);
						break;
					}

				}
				else {
					moveSpeed = 0.2f;
					grav = 0.03;
				}

				//プレイヤーの左辺
				if ((Player_Pos.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Player_Pos.y + Player_Scl.y)) {
					if (Player_Pos.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {
						Player_Pos.y = Player_Pos.y + 0.001f;
						Player_Pos.x = width + mapx[j][i] + Player_Scl.x;
						//grav = 0.0f;
						//time = 0;
						break;
					}
					//プレイヤーの右辺
					else if (Player_Pos.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {
						Player_Pos.x = mapx[j][i] - (Player_Scl.x + width);
						//grav = 0.0f;
						//time = 0;
						//moveSpeed = 0;
						break;
					}
				}
				else {
					moveSpeed = 0.2f;
				}
			}
		}
	}


	

	if (Line::GetInstance()->Getboundflag()==true) {
		grav = 0;
		time = 0;
	}

#pragma region 線の処理


	if (Line::GetInstance()->Getboundflag()==false ||Line::GetInstance()->Gettriggerflag()==false) {
		//grav = 0.0f;
	} else {
		grav = 0.03f;
	}

	time += 0.04f;
	Player_Pos.y -= grav*time*time;


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

	Line::Update(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player, Player_Pos, colf,moveSpeed);

	Line::CollisionEnemy(enemy);
	//weffect->Update(dxcomn,camera,player[0]->GetPosition(),Line::GetInstance()->Getboundflag());
	//FBXのアニメーション再生
	if (Input::GetInstance()->Pushkey(DIK_0)) {
		object1->PlayAnimation();
	}

	

		//}
		//カメラ関係の処理
	camera->SetTarget({ 0,1,0 });//注視点
	camera->SetDistance(distance);//
	camera->SetEye({ Player_Pos.x,Player_Pos.y +1,Player_Pos.z - 23 });
	camera->SetTarget({ Player_Pos.x,Player_Pos.y ,Player_Pos.z });

	camera->Update();


	player->SetPosition(Player_Pos);
	player->SetRotation(Player_Rot);

	player->SetScale(Player_Scl);


	player->Attack(Player_Pos);
	//for (int i = 0; i < 2; i++) {
	player->CollisionAttack(enemy,Player_Pos);

	SetPrm();//パラメータのセット

	objUpdate();//オブジェクトの更新処理

	effects->Update(dxCommon, camera, enemy, player);

	//enemyにnullptr代入するときは敵が死んだら
	for (int i = 0; i < 4; i++) {
		if (enemy[i] != nullptr) {
			//プレイヤーの検知
			enemy[i]->Attack(player);
			enemy[i]->ColMap(map, mapx, mapy, MAX_X, MAX_Y);
			enemy[i]->Update(Player_Pos);
		
			enemy[i]->EnemySearchPlayer(player);
			//もし敵が死んだら破棄
			if (enemy[i]->GetState_DEAD() == true) {
				Destroy_unique(enemy[i]);
			}
		}
	}
	
	GameUI::AllowUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player->GetPosition(),
		Line::GetInstance()->GetlineAngle(), Line::GetInstance()->Gettriggerflag());
	GameUI::TargetUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), Line::GetInstance()->Getelf());
	GameUI::PlayerUIUpdate(player);
	//シーンチェンジ
	if (Input::GetInstance()->TriggerKey(DIK_R)||(Player_Pos.y<=-50)) {//押されたら
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
	for (int i = 0; i < 4; i++) {
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
			if (map[j][i] == 2) {
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
void PlayScene::MyGameDraw(DirectXCommon* dxcomn)
{
	Sprite::PreDraw(dxcomn->GetCmdList());
	background->Draw();
	setumei->Draw();
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
	ImGui::SliderInt("positionX", &co, -100, 100);
		ImGui::SliderFloat("positionY", &rf2, -100, 100);
		ImGui::SliderFloat("positionZ", &rrr, -100, 100);
		ImGui::TreePop();
	}
	float linex = Line::GetInstance()->getpos().x;
	float liney = Line::GetInstance()->getpos().y;
	float rr = player->GetPosition().x;
	if (ImGui::TreeNode("Player_position")) {
		ImGui::SliderFloat("positionX", &linex, -100, 100);
		ImGui::SliderFloat("positionY", &liney, -100, 100);
		ImGui::SliderFloat("positionZ", &Player_Pos.z, -100, 100);
		ImGui::SliderFloat("grav", &grav, -100, 100);
		ImGui::SliderFloat("time", &time, -100, 100);
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
		ImGui::SliderFloat("map_1_width", &width, -100, 100);
		ImGui::SliderFloat("map_1_height", &height, -100, 100);
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