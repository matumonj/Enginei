#include "BossScene1.h"
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
#include"CollisionPrimitive.h"
//コメントアウト


//シーンのコンストラクタ
BossScene1::BossScene1(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}

#pragma region スプライトの生成
//スプライト生成
void BossScene1::SpriteCreate()
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
void BossScene1::ModelCreate()
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
void BossScene1::SetPrm()
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

}
#pragma endregion

#pragma region オブジェクト+ライトの更新処理
void BossScene1::objUpdate()
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
void BossScene1::Initialize(DirectXCommon* dxCommon)
{
	//

	GameUI::UISpriteSet();
	GameUI::TargetUISet();
	GameUI::PlayerUISet();
	bossenemy = std::make_unique<BossEnemy>();

	//bossenemy->Setposition({ 20, -4, 0 });

	bossenemy->Initialize();
	mapcol = new Collision();

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
	object1->Initialize(dxCommon,camera);
	object1->SetModel(fbxmodel);
	/*audio = new Audio();
	audio->Initialize();
	audio->LoopWave("Resources/loop100216.wav", vol);*/
	//camerapositionx = 46.94f;
	camerapositiony = -4.5f;
	camerapositionz = -40.51f;
bossenemy->Setposition({ 40,-4,0 });
}
#pragma endregion

#pragma region 更新処理
void BossScene1::Update(DirectXCommon* dxCommon)
{
	camerapositionx = Player_Pos.x;
	Old_Pos = Player_Pos;
	spotLightpos[0] = Player_Pos.x;
	spotLightpos[1] = Player_Pos.y + 10;
	spotLightpos[2] = 0;

	LONG u_r = 32768;
	LONG a = 30000;

	//左
	player->PlayerMoves(Player_Pos, moveSpeed, jumpFlag, grav, time,Player_Rot);
	///////// コントローラー //////////
	// スティックの方向判定
	// 無反応範囲

	//左
	 //方向だけを調べる方法
	if (Input::GetInstance()->GetCMove().lX < u_r - a)
	{
		// 左に傾けた
		Player_Pos.x -= moveSpeed;

	}
	else if (Input::GetInstance()->GetCMove().lX > u_r + a)
	{
		// 右に傾けた
		Player_Pos.x += moveSpeed;
	}


	//player->PlayerMoves(Player_Pos, moveSpeed);

	//FBXモデルの更新
	object1->Updata({1,1,1,1},dxCommon,camera, TRUE);
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

	//入力処理より後に当たり判定を描け
	
	GameUI::BossUIUpdate(bossenemy.get());

	//これは移す
	
	
	Collision::ColMap1(map, tst, mapx, mapy, 200, 20, grav, time, moveSpeed, jumpFlag, Player_Pos, Old_Pos);

	//これ別んところ移すの相当めんどいから据え置き
	Ray BossLaserRay = BossEnemy::GetInstance()->GetLaserRay();
	Sphere mapsphere[20][200];
	if(BossEnemy::GetInstance()->GetAltAttacklag()==true){
	for (int i = 0; i < MAX_X; i++) {
		for (int j = 0; j < MAX_Y; j++) {

			if (map[j][i] == 1) {
				mapsphere[j][i].radius = 2.5f;
				mapsphere[j][i].center = { tst[j][i]->GetPosition().x, tst[j][i]->GetPosition().y ,tst[j][i]->GetPosition().z };

				if (Collision::CheckRay2Sphere(BossLaserRay, mapsphere[j][i]) == true) {
					map[j][i] = 0;
					break;
				}
			}
			}
		}
	}
	
	if (Player_Pos.x <= goal_pos.x + goal->GetScale().x && Player_Pos.x >= goal_pos.x - goal->GetScale().x && Player_Pos.y <= goal_pos.y + goal->GetScale().y && Player_Pos.y >= goal_pos.y - goal->GetScale().y) {
		BaseScene* scene = new ClearScene(sceneManager_);//次のシーンのインスタンス生成
		sceneManager_->SetnextScene(scene);//シーンのセット
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

	Line::CollisionEnemy(bossenemy.get());
	//weffect->Update(dxcomn,camera,player[0]->GetPosition(),Line::GetInstance()->Getboundflag());
	//FBXのアニメーション再生
	if (Input::GetInstance()->Pushkey(DIK_0)) {
		object1->PlayAnimation();
	}
	XMFLOAT3 bpos;
	if (bossenemy != nullptr) {
		bpos = bossenemy->GetPosition();
	}
	//カメラ関係の処理
	//camera->SetTarget({ 0,1,0 });//注視点
	//camera->SetDistance(distance);//
	camera->SetEye({ camerapositionx,camerapositiony,camerapositionz });
	camera->SetTarget({ camerapositionx,camerapositiony-2 ,Player_Pos.z - 10 });
	camera->Update();

	effects->BossAttackEffect(dxCommon, camera,BossEnemy::GetInstance()->GetAltStay(), atb, bpos);
	player->SetPosition(Player_Pos);
	player->SetRotation(Player_Rot);
	player->SetScale(Player_Scl);
	player->CollisionAttack1(bossenemy.get(), Player_Pos);

	player->Attack(Player_Pos);

	SetPrm();//パラメータのセット

	objUpdate();//オブジェクトの更新処理

	effects->Update(dxCommon, camera, &bossenemy, player);

	//bossenemyにnullptr代入するときは敵が死んだら
	if (bossenemy != nullptr) {
		//プレイヤーの検知

		bossenemy->Motion(player);
		bossenemy->Attack(player);
		bossenemy->Update(Player_Pos);
		bossenemy->ColMap(map, tst, mapx, mapy, 200, 20);
		bossenemy->EnemySearchPlayer(player);
		//もし敵が死んだら破棄
		if (bossenemy->GetState_DEAD() == true) {
			Destroy_unique(bossenemy);
		}
	}
	
	//BossPos = bossenemy->GetPosition();

//bossenemy[3]->Update(Player_Pos);
	atb = BossEnemy::GetInstance()->GetaltAttack();

	item->HealEfficasy(player);
	item->Update(&bossenemy);
	//Fader::FeedSpriteUpdate();
	
	GameUI::AllowUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player->GetPosition(),
		Line::GetInstance()->GetlineAngle(), Line::GetInstance()->Gettriggerflag());
	GameUI::TargetUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), Line::GetInstance()->Getelf());
	GameUI::PlayerUIUpdate(player);
	//シーンチェンジ
	if (Input::GetInstance()->TriggerKey(DIK_R) || (Player_Pos.y <= -50)) {//押されたら
		//BaseScene* scene = new ClearScene(sceneManager_);//次のシーンのインスタンス生成
		//sceneManager_->SetnextScene(scene);//シーンのセット
		//delete scene;
	}
}
#pragma endregion 

//スプライトの描画
#pragma region モデルの描画
void BossScene1::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{
	player->PreDraw();
	player->Draw();
	player->PostDraw();

	if (bossenemy != nullptr) {
		bossenemy->Draw(dxcomn);
	}

	item->Draw();
	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			if (map[j][i] == 1 || map[j][i] == 2) {
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
void BossScene1::MyGameDraw(DirectXCommon* dxcomn)
{
	Sprite::PreDraw(dxcomn->GetCmdList());

	dxcomn->ClearDepthBuffer(dxcomn->GetCmdList());
	Sprite::PostDraw(dxcomn->GetCmdList());

	//スプライトの描画
	SpriteDraw(dxcomn->GetCmdList());

	//普通のテクスチャの描画
	Line::Draw(dxcomn);

	GameUI::AllDraw(dxcomn);

	attackeffects->Draw(dxcomn);
	effects->Draw(dxcomn);
	//FBXの描画
	object1->Draw(dxcomn->GetCmdList());
}
#pragma endregion
//↓に入る
#pragma region
void BossScene1::Draw(DirectXCommon* dxcomn)
{
	dxcomn->BeginDraw();
	MyGameDraw(dxcomn);
	effects->ImGuiDraw();
	ImGuiDraw();//imguiは最後の方入れとく
	dxcomn->EndDraw();
}
#pragma endregion

void BossScene1::ImGuiDraw()
{
	//ImGui::Begin("Obj1");
	//ImGui::SetWindowPos(ImVec2(0, 0));
	//ImGui::SetWindowSize(ImVec2(500, 300));
	//if (ImGui::TreeNode("light_position")) {
	//	if (ImGui::Button("spotlight ON")) {
	//		lightGroup->SetSpotLightActive(0, true);
	//	}
	//	if (ImGui::Button("spotlight OFF")) {
	//		lightGroup->SetSpotLightActive(0, false);
	//	}
	//	ImGui::ColorPicker3("light_color", spotLightColor);
	//	ImGui::TreePop();
	//}
	////int x= bossenemy->GetHP();
	//if (ImGui::TreeNode("Effect_position")) {
	//	//ImGui::SliderInt("positionX", &x, -200, 200);
	//	ImGui::SliderFloat("positionY", &camerapositiony, -200, 200);
	//	ImGui::SliderFloat("positionz", &camerapositionz, -200, 200);
	//	//ImGui::SliderInt("positionZ", &elf, -200, 200);
	//	ImGui::TreePop();
	//}
	//if (ImGui::TreeNode("enemy_position")) {

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

	//if (ImGui::TreeNode("Old")) {
	//	ImGui::SliderFloat("Old_PosX", &Old_Pos.x, -200, 200);
	//	ImGui::SliderFloat("old_PosY", &Old_Pos.y, -200, 200);
	//	ImGui::TreePop();
	//}

	//ImGui::End();

}
#pragma region 解放部分
void BossScene1::Finalize()
{
	//delete sceneManager_;

	attackeffects.reset();
	effects.reset();
	bossenemy.reset();
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 200; j++) {
			tst[i][j].reset();
		}
	}
	goal.reset();
	delete player,playermodel;
	delete tstmodel;
	delete goalmodel, tstmodel;
	delete item;
	GameUI::Finalize();
	Line::Finalize();

}
#pragma endregion