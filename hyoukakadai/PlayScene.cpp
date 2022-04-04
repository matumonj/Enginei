#include "PlayScene.h"
#include"Input.h"
#include"DirectXCommon.h"
#include"TitleScene.h"
#include"SceneManager.h"
#include"MobEnemy.h"
#include"BossEnemy.h"
#include"Line.h"
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
	Sprite::LoadTexture(1, L"Resources/0057b6fa9ec85ae.jpg");
	Sprite::LoadTexture(2, L"Resources/tyuta_C.png");

	//普通のテクスチャ(スプライトじゃないよ)
	//Texture::LoadTexture(6, L"Resources/gomi.png");
	Texture::LoadTexture(1, L"Resources/ball.png");
	Line::Initialize();
	GameUI::AllowUISet();
	Texture::LoadTexture(6, L"Resources/gomi.png");
	Texture::LoadTexture(1, L"Resources/background.png");


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
	tstmodel = Model::CreateFromOBJ("block");
	worldmodel = Model::CreateFromOBJ("skydome");

	for (int i = 0; i < 10; i++) {
		player[i] = Object3d::Create();
		player[i]->SetModel(playermodel);
	}


	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			tst[j][i] = Object3d::Create();
			tst[j][i]->SetModel(tstmodel);
		}
	}
	
	sentan = Object3d::Create();
	sentan->SetModel(tstmodel);

	world = Object3d::Create();
	world->SetModel(worldmodel);

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


	effects = new Effects();

}
#pragma endregion

#pragma region 各パラメータのセット
void PlayScene::SetPrm()
{
	
	
	for (int i = 0; i < 10; i++) {
			player[i]->SetPosition({ Player_Pos[i] });
		player[i]->SetScale({ Player_Scl });
		player[i]->SetRotation({Player_Rot});
	}

	posX = player[0]->GetPosition().x;
	posY = player[0]->GetPosition().y;
	half_height = player[0]->GetScale().y / 2;
	half_Width = player[0]->GetScale().x / 2;

	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			tst[j][i]->SetPosition({ tst_Pos.x + blockSize * i,tst_Pos.y - blockSize * j ,tst_Pos.z });
			tst[j][i]->SetRotation({ tst_Rot });
			tst[j][i]->SetScale({ tst_Scl });
			mapx[j][i] = tst[j][i]->GetPosition().x;
			mapy[j][i]= tst[j][i]->GetPosition().y;
			map_half_heigh[j][i] = tst[j][i]->GetScale().y / 2;
			map_half_width[j][i] = tst[j][i]->GetScale().x / 2;
		}
	}


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
	for (int i = 0; i < 10; i++) {
		player[i]->Update({ 1,1,1,1 });
	}

	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			tst[j][i]->Update({ 1,1,1,1 });
		}
	}

	world->Update({ 1,1,1,1 });

}
#pragma endregion

#pragma region 初期化
void PlayScene::Initialize(DirectXCommon* dxCommon)
{
	//
	GameUI::UISpriteSet();
	
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
	spotLightpos[0] = 10;
	spotLightpos[2] = 0;

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
	
	//liney += 0.01f;
	//liney2 -= 0.01f;
	Input::MouseMove mouseMove = Input::GetInstance()->GetMouseMove();
	//マウスの入力状態取得
	if (Input::GetInstance()->PushMouseLeft()) {
		dy = (float)mouseMove.lX;
		dx = (float)mouseMove.lY;
		dz = (float)mouseMove.lZ;
		//Player_Rot.y -= -dy * 0.2;
		//Player_Rot.z -= dx * 0.2;
	}
	effects->Update(dxCommon, camera);
	Old_Pos = Player_Pos[0];
	//Player_Pos[0].y -= gravity;
	

	if (Input::GetInstance()->Pushkey(DIK_RIGHT)) {
		Player_Pos[0].x += 0.2f;
	}
	if (Input::GetInstance()->Pushkey(DIK_LEFT)) {

		Player_Pos[0].x -= 0.2f;
	}

	if (Input::GetInstance()->Pushkey(DIK_UP)) {
		Player_Pos[0].y -= 0.2f;
	}
	if (Input::GetInstance()->Pushkey(DIK_DOWN)) {
		Player_Pos[0].y += 0.2f;
	}


	if (Input::GetInstance()->Pushkey(DIK_SPACE)) {
		Line = 1;
		//ito_Scl.y+=1;
	}

	//残像
	for (int i = 9; i > 0; i--) {
		Player_Pos[i].x = Player_Pos[i - 1].x + zanzouSpeed;
		Player_Pos[i].y = Player_Pos[i - 1].y + zanzouSpeed;
	}
	////当たり判定
	//if (map[(int)(Player_Pos[0].y - (Player_Scl.y/2)) / blockSize][(int)(Player_Pos[0].x - (Player_Scl.x/2)) / blockSize] == 1 &&
	//	map[(int)(Player_Pos[0].y - (Player_Scl.y/2)) / blockSize][(int)(Player_Pos[0].x + (Player_Scl.x/2)) / blockSize] == 1) {
	//	Player_Pos[0].y = Old_Pos.y;
	//}
	//else if (map[(int)(Player_Pos[0].y + (Player_Scl.y / 2)) / blockSize][(int)(Player_Pos[0].x - (Player_Scl.x / 2)) / blockSize] == 1 &&
	//	map[(int)(Player_Pos[0].y + (Player_Scl.y / 2)) / blockSize][(int)(Player_Pos[0].x + (Player_Scl.x / 2)) / blockSize] == 1) {
	//	Player_Pos[0].y = Old_Pos.y;
	//}

	//for (int i = 0; i < MAX_X; i++) {
	//	for (int j = 0; j < MAX_Y; j++) {
	//		if ((posX + half_Width >= mapx[j][i] - map_half_width[j][i] && posX - half_Width <= mapx[j][i] + map_half_width[j][i]) && posY - half_height >= mapy[j][i] + map_half_heigh[j][i]) {
	//			//Player_Pos[0].y = Old_Pos.y;
	//			Player_Rot.x++;
	//			grav = 0;
	//		}
	//	}
	//}

	if (Player_Pos[0].x >= 65) {
		Player_Pos[0].x = 65;
	}
	else if (Player_Pos[0].x <= -65) {
		Player_Pos[0].x = -65;
	}

	if (Player_Pos[0].y >= 65) {
		Player_Pos[0].y = 65;
	}
	else if (Player_Pos[0].y <= -65) {
		Player_Pos[0].y = -65;
	}

#pragma region 線の処理

	Line::Update(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player, Player_Pos[0]);
	//吸い付くフラグまたは移動方向指定のフラグがtrueん時重力着る
	if (Line::GetInstance()->Getboundflag()==false ||Line::GetInstance()->Gettriggerflag()==false) {
		grav = 0.0f;
	} else {
		grav = 0.03f;
	}

	Player_Pos[0].y -= grav;

#pragma endregion
	//マップとの当たり判定処理
	//右の壁にあたったとき
	colf = Line::GetInstance()->GetColf();

	GameUI::UIUpdate(
		Line::GetInstance()->GetLength(),
		Line::GetInstance()->Gettriggerflag(),
		colf,
		Line::GetInstance()->Getolddistance());
	
	Line::GetInstance()->SetColf(colf);
	//FBXのアニメーション再生
	if (Input::GetInstance()->Pushkey(DIK_0)) {
		object1->PlayAnimation();
	}
	//FBXモデルの更新
	object1->Updata(TRUE);

	
	//カメラ関係の処理
	camera->SetTarget({ 0,1,0 });//注視点
	camera->SetDistance(distance);//
	camera->SetEye({ Player_Pos[0].x,Player_Pos[0].y ,Player_Pos[0].z - 18 });
	camera->SetTarget({ Player_Pos[0].x,Player_Pos[0].y ,Player_Pos[0].z });
	camera->Update();

	SetPrm();//パラメータのセット
	
	objUpdate();//オブジェクトの更新処理
	GameUI::AllowUIUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player[0]->GetPosition(),
		Line::GetInstance()->GetlineAngle(),Line::GetInstance()->Gettriggerflag());

	//シーンチェンジ
	if (Input::GetInstance()->TriggerKey(DIK_R)) {//押されたら
	BaseScene* scene = new TitleScene(sceneManager_);//次のシーンのインスタンス生成
	sceneManager_->SetnextScene(scene);//シーンのセット
	}
}
#pragma endregion 

//スプライトの描画
#pragma region モデルの描画
void PlayScene::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{
	
	for (int i = 0; i < 10; i++) {
		player[i]->PreDraw();
		player[i]->Draw();
		player[i]->PostDraw();
	}

	world->PreDraw();
	world->Draw();
	world->PostDraw();
	


	/*for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			if (map[j][i] == 1) {
				tst[j][i]->PreDraw();
				tst[j][i]->Draw();
				tst[j][i]->PostDraw();
			}
		}
	}*/

}
//sプライと以外の描画
void PlayScene::MyGameDraw(DirectXCommon* dxcomn)
{
	//スプライトの描画
	SpriteDraw(dxcomn->GetCmdList());
	GameUI::UIDraw(dxcomn);
	
	GameUI::AllowUIDraw(dxcomn);
	
	//普通のテクスチャの描画
	Line::Draw(dxcomn);

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
		ImGui::SliderFloat("positionX", &Player_Pos[0].x, -100, 100);
		ImGui::SliderFloat("positionY", &spotLightpos[1], -100, 100);
		ImGui::SliderFloat("positionZ", &spotLightpos[2], -100, 100);
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
		ImGui::SliderFloat("positionZ", &efkposition.z, -100, 100);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Texture_position")) {
		float rf = GameUI::GetInstance()->Getsclx();
		ImGui::SliderFloat("positionX", &rf, -100, 100);
		ImGui::SliderFloat("positionY", &texpo.y, -100, 100);
		ImGui::SliderFloat("positionZ", &texpo.z, -100, 100);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Player_position")) {
		ImGui::SliderFloat("positionX", &Player_Pos[0].x, -100, 100);
		ImGui::SliderFloat("positionY", &Player_Pos[0].y, -100, 100);
		ImGui::SliderFloat("positionZ", &Player_Pos[0].z, -100, 100);
		ImGui::TreePop();
	}


	ImGui::End();

	ImGui::Begin("postEffect");
	if(ImGui::RadioButton("Blur", &c_postEffect)) {
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
	//delete efk,efk1;
	delete mech, zukki;
	
	delete debugText;
	delete collision;
	delete lightGroup;
	delete camera;
	delete background;
}
#pragma endregion