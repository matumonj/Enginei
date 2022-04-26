#pragma once
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include"Object3d.h"
#include"Model.h"
#include"Enemy.h"
#include<memory>
class Item
{
public:
	Item();
	~Item();
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void Initialize();
	void Update(std::unique_ptr<Enemy>enemy[]);
	void Draw();
	void Drop(std::unique_ptr<Enemy>enemy[]);
	void HealEfficasy(Player*player);
	void GetItem(Player* plauer);
private:
	static const int itemMax = 4;
	bool GetPossible[itemMax];
	Object3d* itemObj[itemMax] = { nullptr };
	Model* itemModel =  nullptr ;

	//XMFLOAT3 positione[itemMax];
	XMFLOAT3 position[itemMax];
	XMFLOAT3 rotation[itemMax];
	XMFLOAT3 scale[itemMax];
};

