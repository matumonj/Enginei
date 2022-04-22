#pragma once
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include"DirectXCommon.h"
#include"Player.h"
#include"Texture.h"
#include"Object3d.h"
#include"Model.h"
class Helper
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	enum class FeedState {
		Setting,
		FeedIn,
		FeedOut,
		FeedInOut,
		End,
		None
	};
	static FeedState feedState;
public:
	static void Update(float& alpha);
	static void feedIn(float& alpha);
	static void feedOut(float& alpha);
	static void feedInOut(float& alpha);
	inline float easeIn();
	inline float easeOut();

	static bool GetFeedState_End() { if (feedState == FeedState::End)return true; }
};

