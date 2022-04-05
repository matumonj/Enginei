#include "PlayScene.h"
#include"Input.h"
#include"DirectXCommon.h"
#include"TitleScene.h"
#include"SceneManager.h"
#include"MobEnemy.h"
#include"BossEnemy.h"
#include"Line.h"

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
<<<<<<< HEAD
	Texture::LoadTexture(6, L"Resources/gomi.png");
	Texture::LoadTexture(1, L"Resources/background.png");

	mech = Texture::Create(6, { 0,-50,50 }, { 1,1,1 }, {1,1,1,1});
	zukki = Texture::Create(1, { 0,-20,50 }, { 1,1,1 }, { 1,1,1,1 });

	background = Sprite::Create(1, { 0.0f,-200.0f });
=======
	
>>>>>>> naosi
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
			map_half_heigh = tst[j][i]->GetScale().y /2;
			map_half_width = tst[j][i]->GetScale().x /2;
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
	Input::MouseMove mouseMove = Input::GetInstance()->GetMouseMove();
	//マウスの入力状態取得
	if (Input::GetInstance()->PushMouseLeft()) {
		dy = (float)mouseMove.lX;
		dx = (float)mouseMove.lY;
		dz = (float)mouseMove.lZ;
	}

	Old_Pos = Player_Pos[0];
	
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

	//残像
	for (int i = 9; i > 0; i--) {
		Player_Pos[i].x = Player_Pos[i - 1].x + zanzouSpeed;
		Player_Pos[i].y = Player_Pos[i - 1].y + zanzouSpeed;
	}
	////当たり判定
	//if (map[(int)(posY - half_height) / blockSize][(int)(posX-half_Width) / blockSize] == 1 &&
	//	map[(int)(posY - half_height) / blockSize][(int)(posX+half_Width) / blockSize] == 1) {
	//	//Player_Pos[0].y = Old_Pos.y;
	//	Player_Rot.x++;
	//	grav = 0;
	//}
	//else if (map[(int)(posY + half_height) / blockSize][(int)(posX-half_Width) / blockSize] == 1 &&
	//	map[(int)(posY + half_height) / blockSize][(int)(posX+half_Width) / blockSize] == 1) {
	//	//Player_Pos[0].y = Old_Pos.y;
	//	Player_Rot.x++;
	//	grav = 0;
	//}
	//else {
	//	grav = 0.03f;
	//}

	//if (map[(int)(posY + half_height) / blockSize][(int)(posX + half_Width) / blockSize] == 1 &&
	//	map[(int)(posY - half_height) / blockSize][(int)(posX + half_Width) / blockSize] == 1) {
	//	Player_Pos[0].x = Old_Pos.x;
	//}
	//else if (map[(int)(posY + half_height) / blockSize][(int)(posX - half_Width) / blockSize] == 1 &&
	//	map[(int)(posY - half_height) / blockSize][(int)(posX - half_Width) / blockSize] == 1) {
	//	Player_Pos[0].x = Old_Pos.x;
	//}

	for (int i = 0; i < MAX_X; i++) {
		for (int j = 0; j < MAX_Y; j++) {
			if (map[j][i] == 1) {
				if ((posX + half_Width > mapx[j][i] - map_half_width && posX - half_Width < mapx[j][i] + map_half_width) && Old_Pos.y - half_height - 1< mapy[j][i] + map_half_heigh && posY + half_height > mapy[j][i] - map_half_heigh) {
					Player_Pos[0].y = map_half_heigh + mapy[j][i] + half_height+1;
					//Player_Pos[0].y = Old_Pos.y;
					//Player_Rot.x++;
					grav = 0;
					break;
				}
				else {
					grav = 0.03f;
				}
			}
		}
	}

#pragma region 線の処理

	Line::Update(camera->GetViewMatrix(), camera->GetProjectionMatrix(), player, Player_Pos[0]);
	
	//吸い付くフラグまたは移動方向指定のフラグがtrueん時重力着る

	if (boundflag || trigger) {
		grav = 0.0f;
	}
	else {
		
	}
	
	//吸い付く処理
	if (boundflag) {
		FollowangleX = (linex2 - player[0]->GetPosition().x);
		FollowangleZ = (liney2 - player[0]->GetPosition().y);//これZじゃなくてYです
		FollowangleR = sqrtf((player[0]->GetPosition().x - linex2) * (player[0]->GetPosition().x - linex2)
			+ (player[0]->GetPosition().y - liney2) * (player[0]->GetPosition().y - liney2));

		Player_Pos[0].x+= (FollowangleX / FollowangleR)* FollowSpeed;
		Player_Pos[0].y += (FollowangleZ / FollowangleR) * FollowSpeed;
		Limitsave += 0.2;
		if (Limit <= Limitsave) {
			boundflag = false;
			returnflag = true;
		}
	}
	else {
		//吸い付くフラグがFALSEんときだけ中心点をプレイヤーの方に
	/*メモ:ずっと中心点を現時点のプレイヤーの座標に設定してるとプレイヤーが動いた分だけ
　　　　　　線の終点も動いてしまうから(subradiusの部分が中心点依存)*/
		tempx = Player_Pos[0].x;
		tempy = Player_Pos[0].y;
	}
	//線が戻ってくる処理
	if (returnflag) {
		subradius -= 1.5f;
		if (subradius <= 0) {//先の長さが０なったら切る
			returnflag = false;

	if (Line::GetInstance()->Getboundflag()==false ||Line::GetInstance()->Gettriggerflag()==false) {
		grav = 0.0f;
	} else {
		grav = 0.03f;
	}


	Player_Pos[0].y -= grav;


		}
	}

	debuga=tst[0][4]->GetPosition().y;
	//頂点座標の更新
	mech->CreateTexture(linex, linex2, liney, liney2);
	
	Player_Pos[0].y -= grav;
	//線の長さの最大値と最小値
	max(subradius, MinLen);
	min(subradius, MaxLen);

#pragma endregion
	//最大値が減るときに使うフラグはこっちで管理
	colf = Line::GetInstance()->GetColf();

	GameUI::UIUpdate(
		Line::GetInstance()->GetLength(),//
		Line::GetInstance()->Gettriggerflag(),//
		colf,//
		Line::GetInstance()->Getolddistance());//
	
	Line::GetInstance()->SetColf(colf);

	//FBXのアニメーション再生
	if (Input::GetInstance()->Pushkey(DIK_0)) {
		object1->PlayAnimation();
	}
	//FBXモデルの更新
	object1->Updata(TRUE);

	effects->Update(dxCommon, camera);
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

	if (ImGui::TreeNode("half")) {
		ImGui::SliderFloat("half_width", &half_Width, -100, 100);
		ImGui::SliderFloat("half_height", &half_height, -100, 100);
		ImGui::SliderFloat("map_half_width", &map_half_width, -100, 100);
		ImGui::SliderFloat("maphalf_height", &map_half_heigh, -100, 100);
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