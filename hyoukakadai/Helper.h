#pragma once
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include"DirectXCommon.h"
#include"Player.h"
#include"Texture.h"
#include"Object3d.h"
#include"Model.h"
#include"Sprite.h"
class Helper
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	inline float easeIn();
	inline float easeOut();
	static void Follow(XMFLOAT3& position, XMFLOAT3& position2,float dis,float speed);
};

