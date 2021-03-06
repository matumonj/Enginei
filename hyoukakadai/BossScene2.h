#pragma once
#include"BaseScene.h"
#include"Audio.h"
#include"Sprite.h"
#include"Input.h"
#include"WinApp.h"

#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include"DebugTxt.h"
#include"LightGroup.h"
#include"DebugCamera.h"
#include"DirectXCommon.h"
#include"mEffekseer.h"
#include "FbxLoader.h"
#include "f_Object3d.h"
#include"Texture.h"
#include"PostEffect.h"
#include"Enemy.h"
#include"Effects.h"
#include"GameUI.h"
#include"OBBCollision.h"
#include"Player.h"
#include"Item.h"
#include<memory>

class BossScene2:public BaseScene
{
public:

	//シーンのコンストラクタ
	BossScene2(SceneManager* sceneManager);
private: // エイリアス
		 // Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

private:
	const float window_width = 1900;
	const float window_height = 1020;
	static const int debugTextTexNumber = 0;
	const int MAX_X = 20;
	const int MAX_Y = 130;

private:
	DirectXCommon* dxcomn;
	Sprite* background = nullptr;
	int atb;
	Sprite* setumei = nullptr;

	DebugTxt* debugText;

	std::unique_ptr<Enemy>bossenemy;
	//Enemy* enemy[2];
	std::unique_ptr <Effects> effects;

	std::unique_ptr <Effects> effects2;

	std::unique_ptr <Effects> attackeffects;
	Collision* collision = nullptr;

	Player* player;
	//std::unique_ptr<Object3d>player[10];
	std::unique_ptr<Object3d>tst[130][20];
	std::unique_ptr<Object3d>reef[130][20];
	std::unique_ptr<Object3d>goal = nullptr;

	Collision* mapcol;

	Model* playermodel = nullptr;
	Model* tstmodel = nullptr;
	Model* goalmodel = nullptr;
	Model* reefmodel = nullptr;
	DebugCamera* camera;
	Item* item = nullptr;
	Item* item2 = nullptr;
	//Effects* effects;
private:
	//Plyer
	XMFLOAT3 Player_Pos = { 20,-30,0 };// = player->GetPosition();
	XMFLOAT3 Player_Rot;// = player->GetRotation();
	XMFLOAT3 Player_Scl = { 1,1,1 };
	XMFLOAT3 Old_Pos;


	float BossGrav;
	float BossMoveSpeed;
	bool BossJumpFlag;
	float BossTime;
	XMFLOAT3 BossPos;
	XMFLOAT3 BossOldPos;
	float moveSpeed = 0.1f;
	//tst
	XMFLOAT3 tst_Pos = { 0,200,0 };
	XMFLOAT3 tst_Scl = { 1,1,1 };
	XMFLOAT3 tst_Rot;

	XMFLOAT3 goal_pos = { 390,3,0 };

	XMFLOAT3 old_Scl = { 1,1,1 };

	float distance = 30;

	float dy;
	float dx;
	float dz;
	float xx;
	bool startSet;
	int deathcount;
	//map
	bool movenow;
	bool hintload;
	int blockSize = 2;

	bool Onflag = false;

	float goalSpeed = 0;
	float goaltime = 0;
	bool goalflag = false;

	float oldcamera;
	int map[130][20] = {
		//マップチップ振り分け
		//20~ボスの移動位置(イージング用)
		//10~モブ敵の湧く位置
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{2,2,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,2,2},
		{2,2,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,2,2},
		{2,2,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,2,2},
		{2,2,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,2,2},
		{2,2,0,0,1,1,0,0,0,30,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,5,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,3,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,88,2,2},
		{2,2,0,0,0,0,0,0,0,23,0,0,1,1,1,1,1,1,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,2,2,2,2,1,1,1,0,0,0,0,1,1,1,1,1,2,2},
		{2,2,2,2,2,2,1,1,1,0,0,0,0,1,1,1,1,1,2,2},
		{2,2,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,2,2},
		{2,2,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,1,1,1,1,1,0,0,0,0,0,0,2,2,2,2,2,2,2},
		{2,2,1,1,1,1,1,0,0,0,0,0,0,1,1,2,2,2,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,18,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,2,2,2,1,1,0,0,0,0,1,1,0,0,0,0,0,2,2},
		{2,2,0,0,0,1,1,0,0,0,1,1,1,2,2,2,2,2,2,2},
		{2,2,0,0,0,0,1,0,0,0,0,1,1,2,2,2,2,2,2,2},
		{2,2,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,2,2},
		{2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2},
		{2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2},
		{2,2,2,2,17,2,2,0,0,0,0,0,0,0,0,1,0,0,2,2},
		{2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,1,0,0,2,2},
		{2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,1,0,15,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,14,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,13,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,2,2,2,2,1,1,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,1,2,2,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,2,2},
		{2,2,0,12,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,2,2,2,1,1,0,0,0,0,0,0,0,0,0,0,11,2,2},
		{2,2,2,2,2,2,2,0,0,0,0,0,0,2,2,2,2,2,2,2},
		{2,2,2,2,2,1,1,0,0,0,0,0,0,1,1,2,2,2,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2},
		{2,2,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,2,2},
		{2,2,0,10,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,0,0,73,0,0,0,0,0,0,0,0,2,2},
		{2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2},
		{2,2,2,2,2,2,2,0,0,0,0,0,0,2,2,2,2,2,2,2},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		//{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 }
		};

		std::unique_ptr<Enemy>enemycolony1[10];
		std::unique_ptr<Enemy>enemycolony2[10];
	float posX = 0;
	float posY = 0;
	float half_Width;
	float half_height = 0;


	float mapx[130][20];
	float mapy[130][20];

	float width;
	float height;
	bool jumpFlag = false;
	float camerapositionx;
	float camerapositiony;
	float camerapositionz;
	bool colf = false;
	float grav = 0.03f;
	float time = 0.1f;
	OBB pobb;// = nullptr;
	
	int Ontime = 300;
	bool OnFlag = false;
	//float botttomy = 0;
private://点光源
	LightGroup* lightGroup = nullptr;
	float ambientColor0[3] = { 1,1,1 };

	float lightDir0[3] = { 0,0,1 };
	float lightColor0[3] = { 1,0,0 };

	float lightDir1[3] = { 0,1,0 };
	float lightColor1[3] = { 0,1,0 };

	float lightDir2[3] = { 1,0,0 };
	float lightColor2[3] = { 0,0,1 };

	float pointLightPos[3] = { 0,0,-50 };
	float pointLightColor[3] = { 1,1,1 };
	float pointLightAtten[3] = { 0.05f,0.05f,0.05f };

	int SpotLightflag = false;
private://スポットライト
	float spotLightDir[3] = { 0,-1,0 };
	float spotLightpos[3] = { 0,5,0 };
	float spotLightColor[3] = { 1,1,1 };
	float spotLightAtten[3] = { 0.0f,0.0f,0.0f };
	float spotLightFactorAngle[2] = { 20.0f,30.0f };

public:
	void SpriteCreate();
	void ModelCreate();
	void MyGameDraw(DirectXCommon* dxcomn);
	void SetPrm();
	void objUpdate();
	bool loadf;
public:
	XMFLOAT3 texpo = { 0,0,0 };
	void Initialize(DirectXCommon* dxCommon)override;
	void Update(DirectXCommon* dxCommon)override;
	void Draw(DirectXCommon* dxcomn)override;
	void PreBackGround(ID3D12GraphicsCommandList* cmdList);
	void BackGround(ID3D12GraphicsCommandList* cmdList);

	void PostBackGround(ID3D12GraphicsCommandList* cmdList);
	void SpriteDraw(ID3D12GraphicsCommandList* cmdList);
	void ImGuiDraw();
	void Finalize()override;

public:
	XMFLOAT3 efkposition = { -50,-10,90 };
	//エフェクト用(ただプログラムでつくれるものはプログラムで作る方がいい　多用はいくない)

	f_Model* fbxmodel = nullptr;
	f_Object3d* object1 = nullptr;

};

