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
	// DirectX::を省略
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
	static bool inoutflag;
public:
	static void Update(float& alpha, const float Max);
	static void feedIn(float& alpha, const float Max);
	static void feedOut(float& alpha, const float Min);
	static void feedInOut(float& alpha, const float Max, const float Min);
	//feedoutのタイミング指定
	static void feedInOut_f(float& alpha,const float Max, const float Min,bool &flag);
	inline float easeIn();
	inline float easeOut();

	static bool GetFeedState_End() { if (feedState == FeedState::End)return true; }
};

