#pragma once
#include"Sprite.h"
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include"DirectXCommon.h"
class GameUI
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	//各スプライトのパラメータにはstatic付けといてください
	//playsceneの呼び出しでGameUIのインスタンス何個も必要ないため
	//糸にかかわるUI
	static Sprite* LineLength;
	static Sprite* LineLengthout;
	static XMFLOAT2 lpos,loutpos;//座標
	static XMFLOAT2 lscl,loutscl;//スケール
	static float tempx;
	static float lsclMax;
public:
	static void UISpriteSet();
	static void UIUpdate(float length,bool flag, bool &boundflag,float movement);
	static void UIDraw(DirectXCommon*dxcomn);
};

