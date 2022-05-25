#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>
#include"mEffekseer.h"
#include"DirectXCommon.h"
#include"DebugCamera.h"
#include"Enemy.h"
#include"Player.h"
#include<memory>
class Effects
{
private:
	//Microosoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	//エフェクト用(ただプログラムでつくれるものはプログラムで作る方がいい　多用はいくない)
	mEffekseer* efk = nullptr;
	mEffekseer* attackefk = nullptr;
	mEffekseer* bossattackefk = nullptr;
	mEffekseer* Healefk = nullptr;
	bool df;
	bool attack;
	bool b_attack;
	bool healf;
public:
	~Effects();
	//XMFLOAT3 GetPosition
	XMFLOAT3 Effect_Pos = { -50.0f,-10.0f,90.0f };
	XMFLOAT3 Effect_Rot;
	XMFLOAT3 Effect_SCl;

	XMFLOAT3 a_Effect_Pos = { -50.0f,-10.0f,90.0f };
	XMFLOAT3 a_Effect_Rot;
	XMFLOAT3 a_Effect_SCl;

	XMFLOAT3 b_Effect_Pos = {  };
	XMFLOAT3 b_Effect_Rot =  {0.0f,-174.277f,0.0f};
	XMFLOAT3 b_Effect_SCl;

	bool deathf;
	float zrot;
	float yrot;
public:
	void BossAttackEffect(DirectXCommon* dxcomn, DebugCamera* camera,bool stay, bool altAttack, XMFLOAT3 bpos);
	void Initialize(DirectXCommon* dxcomn, DebugCamera* camera);
	void Update(DirectXCommon* dxcomn, DebugCamera* camera, std::unique_ptr<Enemy>enemy[],Player*player);
	void Updateo(DirectXCommon* dxcomn, DebugCamera* camera, Enemy*enemy, Player* player);
	void Update2(DirectXCommon* dxcomn, DebugCamera* camera, std::unique_ptr<Enemy>enemy[], Player* player);
	void BossDeath(XMFLOAT3 position,bool f);
	void HealEffect(bool heal, bool healfs);
	void HealEffects(bool heal);
	void HealEffect2(bool heal);
	void Draw(DirectXCommon*dxcomn);
	void Finalize();
	void ImGuiDraw();
};

