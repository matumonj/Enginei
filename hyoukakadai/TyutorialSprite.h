#pragma once
#include"Sprite.h"
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include"DirectXCommon.h"
//���ꂾ���͒�������Gameui�Ƃ͕ʌō��
class TyutorialSprite
{
public:
	~TyutorialSprite();
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	//Sprite::LoadTexture(10, L"Resources/lineshot.png");
	//sprite = Sprite::Create(10, { 500,0 });
private:
	static const int Max = 6;
	Sprite* sprite[Max];
	float alpha[Max];
private:
	int nextphaseflag_move =0;
	bool OK_flag = false;
	enum class Phase {
		None,
		Start,
		Move,
		LineShot,
		LineOperation,
		Attack,
		End,
	};
	Phase phase=Phase::Start;
public:
	void Initialize();
	void Update();
	void Draw(DirectXCommon*dxcomn);

	//sprite->setcolor({ 1,1,1,alpha });
	//sprite->SetSize({ 700,600 });
};

