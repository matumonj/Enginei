#pragma once
#include"Texture.h"
#include"mEffekseer.h"
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include"DirectXCommon.h"
#include"DebugCamera.h"
class pEffect
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	mEffekseer* effect = nullptr;
	//エフェクト描画のフラグ
	bool drawf = false;
	//
	int timer = 0;
	XMFLOAT3 Effect_Rot;
	XMFLOAT3 Effect_SCl;
	bool eflag = false;
public:
	void Initialize(DirectXCommon*dxcomn,DebugCamera*camera);
	void Update(DirectXCommon* dxcomn, DebugCamera* camera, XMFLOAT3 position,bool flag);
	void Draw(DirectXCommon* dxcomn);
};

