#pragma once
#include"Sprite.h"
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include"DirectXCommon.h"
#include"Enemy.h"
//これだけは長いからGameuiとは別個で作る
class TyutorialSprite
{
public:
	~TyutorialSprite();
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	//Sprite::LoadTexture(10, L"Resources/lineshot.png");
	//sprite = Sprite::Create(10, { 500,0 });
private:
	static const int Max = 16;
	Sprite* sprite[Max];
	float alpha[Max];
private:
	int nextphaseflag_move =0;
	bool nextphaseflag_bond = false;
	bool nextphaseflag_return = false;
	bool nextphaseflag_attack = false;
	bool OK_flag = false;
	enum class Phase {
		None,
		Start,//開始
		Move,//移動
		LineShot,//糸出し
		LineLimit,//糸の上限
		LineOperation,//糸を使った移動
		Attack,//攻撃アクション
		PlayerHP,//体力ゲージ
		End,//
	};
	enum class Clear {
		None,//
		Move,//
		LineShot,//
		LineLimit,//
		LineBond,//
		LineCol,//
		Attack,//
		PlayerHP,//
	};
	Clear task = Clear::None;
	Phase phase=Phase::Start;
	const wchar_t* spritename[20];
public:
	void Initialize();
	void Update(Enemy*enemy);
	void Draw(DirectXCommon*dxcomn);
	void Finalize();
	//sprite->setcolor({ 1,1,1,alpha });
	//sprite->SetSize({ 700,600 });
};

