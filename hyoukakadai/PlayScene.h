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
#include"Player.h"
#include<memory>
class PlayScene :public BaseScene
{
public:
	
	//シーンのコンストラクタ
	PlayScene(SceneManager* sceneManager);
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
	const int MAX_X = 100;
	const int MAX_Y = 20;
private:
	DirectXCommon* dxcomn;
	Sprite* background = nullptr;
	Sprite* setumei = nullptr;


	DebugTxt* debugText;
	std::unique_ptr<Enemy>enemy[4];
	//Enemy* enemy[2];
	std::unique_ptr <Effects> effects;
	std::unique_ptr <Effects> attackeffects;
	Collision* collision = nullptr;

	std::unique_ptr <Texture>mech = nullptr;
	std::unique_ptr <Texture>zukki = nullptr;

	Player* player;
	//std::unique_ptr<Object3d>player[10];
	std::unique_ptr<Object3d>tst[20][100];
	std::unique_ptr<Object3d> sentan = nullptr;
	std::unique_ptr<Object3d> world = nullptr;
	std::unique_ptr<Object3d>block = nullptr;
	std::unique_ptr<Object3d>hari = nullptr;
	std::unique_ptr<Object3d>goal = nullptr;

	Collision* mapcol;

	Model* playermodel = nullptr;
	Model* tstmodel = nullptr;
	Model* worldmodel = nullptr;
	Model* harimodel = nullptr;
	Model* goalmodel = nullptr;

	PostEffect* postEffect = nullptr;
	DebugCamera* camera;

	//Effects* effects;
private:
	//Plyer

	XMFLOAT3 Player_Pos = {0,0,0};// = player->GetPosition();
	XMFLOAT3 Player_Rot;// = player->GetRotation();
	XMFLOAT3 Player_Scl = { 1,1,1 };
	XMFLOAT3 Old_Pos;
	float moveSpeed = 0.1f;
	//tst
	XMFLOAT3 tst_Pos = { 0,11,0 };
	XMFLOAT3 tst_Scl = { 1,1,1 };
	XMFLOAT3 tst_Rot;
	//sentan
	XMFLOAT3 sentan_Pos;
	XMFLOAT3 sentan_Scl = { 1,1,0 };
	XMFLOAT3 sentan_Rot;
	//block
	XMFLOAT3 block_pos = { -5,-1,0 };
	XMFLOAT3 block_Scl = { 1,1,1 };
	//hari
	XMFLOAT3 hari_Pos;

	XMFLOAT3 goal_pos = { 1,1,1 };

	XMFLOAT3 old_Scl = { 1,1,1 };

	float distance = 30;

	float dy;
	float dx;
	float dz;

	float zanzouSpeed = 0;

	int Line = 0;
	float Limit = 10;
	float Limitsave = 0;
	float speed = 1.0f;
	float vec_x = 0.0f;
	float vec_y = 0.0f;
	float length = 0.0f;
	float normal_x;
	float rot = 0;
	//map
	int blockSize = 2;
	int map[20][100] = {
	{0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1},
	{0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1},
	{1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
	float posX = 0;
	float posY = 0;
	float half_Width;
	float half_height = 0;


	float mapx[20][100];
	float mapy[20][100];

	float width;
	float height;
	float FollowangleX, FollowangleZ, FollowangleR;
	float FollowSpeed = 1.0f;
	//float Limit = 0;
	bool trigger = false;
	bool boundflag = false;
	bool returnflag = false;
	float debuga;
	float tempx, tempy;
	float linex, linex2, liney, liney2;
	float lineangle = 0;
	float subradius = 0;
	float Startsubradius = 2.0f;
	float olddistance = 0;
	const float LengThenSpeed = 3.0f;
	const float MaxLen = 30.0f;
	const float MinLen = 0.0f;
	bool lengthserchf = false;


	bool colf = false;
	float grav = 0.05f;
	float time = 0.1;
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

	int c_postEffect;


private:
	int co = 0;
	enum {
		Blur,
		Default,
	};
};

