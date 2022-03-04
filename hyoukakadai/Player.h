#pragma once
#include"Object3d.h"
class Player :public Object3d
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	static Player* Create(Model* model = nullptr);

public:
	bool Initialize()override;
	void Update(XMFLOAT4 color)override;
	void OnCollision(const CollisionInfo& info)override;
	//DebugTxt* debugtxt = nullptr;
	int DebugTexnum = 4;
};

