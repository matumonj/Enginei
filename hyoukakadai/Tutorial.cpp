#include "Tutorial.h"
#include"Input.h"
#include"DirectXCommon.h"
#include"PlayScene.h"
#include"SceneManager.h"
#include"MobEnemy.h"
#include"BossEnemy.h"
#include"ThrowEnemy.h"
#include"Line.h"
#include"Destroy.h"
#include"Fader.h"
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
	tstmodel = Model::CreateFromOBJ("tutorialblock");
	harimodel = Model::CreateFromOBJ("hari");

	collision = new Collision();

	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			tst[j][i] = Object3d::Create();
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

	GameUI::UISpriteSet();
	GameUI::TargetUISet();
	GameUI::PlayerUISet();

	//enemy[0] = new MobEnemy();
	enemy = new MobEnemy();
	enemy->Setposition({ 20, -10, 0 });
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

}
#pragma endregion

#pragma region 更新処理
void Tutorial::Update(DirectXCommon* dxCommon)
{
	Old_Pos = Player_Pos;
	spotLightpos[0] = Player_Pos.x;
	spotLightpos[1] = Player_Pos.y + 10;
	spotLightpos[2] = 0;



	//FBXモデルの更新
	object1->Updata(TRUE);
	if (Input::GetInstance()->Pushkey(DIK_RIGHT)) {
		Player_Pos.x += moveSpeed;
	}
	if (Input::GetInstance()->Pushkey(DIK_LEFT)) {
		Player_Pos.x -= moveSpeed;

	}

	float disl;
	//入力処理より後に当たり判定を描け
	for (int i = 0; i < MAX_X; i++) {
		for (int j = 0; j < MAX_Y; j++) {
			if (map[j][i] == 1) {
				mapx[j][i] = tst[j][i]->GetPosition().x;
				mapy[j][i] = tst[j][i]->GetPosition().y;
				height =2.5;
				width = 1;
				if ((Line::GetInstance()->getpos().x + 1.0f > mapx[j][i] - (width) && Line::GetInstance()->getpos().x - 1.0f < mapx[j][i] + (width)) && Line::GetInstance()->getpos().y + 1.0f > mapy[j][i] && Line::GetInstance()->getpos().y - 1.0f < mapy[j][i] + height) {
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
					} else if (Old_Pos.y <mapy[j][i] && Player_Pos.y + Player_Scl.y>mapy[j][i]) {
						Player_Pos.y = mapy[j][i] - (Player_Scl.y + height);
						break;
					}

				} else {
					moveSpeed = 0.2f;
					grav = 0.03;
				}

				//プレイヤーの左辺
				if ((Player_Pos.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i]  < Player_Pos.y + Player_Scl.y)) {
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
				} else {
					moveSpeed = 0.2f;
				}
			}
		}
	}


#pragma region 線の処理


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
	Line::CollisionEnemy(enemy);
	//FBXのアニメーション再生
	if (Input::GetInstance()->Pushkey(DIK_0)) {
		object1->PlayAnimation();
	}

	//カメラ関係の処理
	camera->SetTarget({ 0,1,0 });//注視点
	camera->SetEye({Player_Pos.x,-6,Player_Pos.z - 23 });
	camera->SetTarget({Player_Pos.x,-6 ,Player_Pos.z });
	camera->Update();

	player->SetPosition(Player_Pos);
	player->SetRotation(Player_Rot);
	player->SetScale(Player_Scl);

	player->Attack(Player_Pos);
	player->CollisionAttack(enemy, Player_Pos);

	SetPrm();//パラメータのセット

	objUpdate();//オブジェクトの更新処理

	//enemyにnullptr代入するときは敵が死んだら
	for (int i = 0; i < 4; i++) {
		if (enemy != nullptr) {
			//プレイヤーの検知
			enemy->Attack(player);
			enemy->ColMap(map, mapx, mapy, MAX_X, MAX_Y);
			enemy->Update(Player_Pos);

			enemy->EnemySearchPlayer(player);
			//もし敵が死んだら破棄
			if (enemy->GetState_DEAD() == true) {
				Destroy(enemy);
			}
		}
	}

	GameUI::AllowUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player->GetPosition(),
		Line::GetInstance()->GetlineAngle(), Line::GetInstance()->Gettriggerflag());
	GameUI::TargetUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), Line::GetInstance()->Getelf());
	GameUI::PlayerUIUpdate(player);
	//シーンチェンジ
	if (Input::GetInstance()->TriggerKey(DIK_R)) {//押されたら
		BaseScene* scene = new PlayScene(sceneManager_);//次のシーンのインスタンス生成
		sceneManager_->SetnextScene(scene);//シーンのセット
		//delete scene;
	}
}
#pragma endregion 

//スプライトの描画
#pragma region モデルの描画
void Tutorial::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{
	player->PreDraw();
	player->Draw();
	player->PostDraw();

	if (enemy != nullptr) {
		enemy->Draw();
	}

	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			if (map[j][i] == 1) {
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

	//普通のテクスチャの描画
	Line::Draw(dxcomn);

	//weffect->Draw(dxcomn);
	GameUI::AllowUIDraw(dxcomn);
	GameUI::TargetUIDraw(dxcomn);
	GameUI::UIDraw(dxcomn);
	GameUI::PlayerUIDraw(dxcomn);
	//FBXの描画
	object1->Draw(dxcomn->GetCmdList());
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
		ImGui::SliderFloat("cx", &cx, 100, -100);
		ImGui::SliderFloat("cy", &cy, 100, -100);
		ImGui::TreePop();
	}
	ImGui::End();
}
#pragma region 解放部分
void Tutorial::Finalize()
{
	//delete sceneManager_;

	//delete efk,efk1;

}
#pragma endregion