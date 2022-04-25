#pragma once
#include"Sprite.h"
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include"DirectXCommon.h"
#include"Enemy.h"
//‚±‚ê‚¾‚¯‚Í’·‚¢‚©‚çGameui‚Æ‚Í•ÊŒÂ‚Åì‚é
class TyutorialSprite
{
public:
	~TyutorialSprite();
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::‚ğÈ—ª
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
		Start,
		Move,
		LineShot,
		LineOperation,
		Attack,
		End,
	};
	enum class Clear {
		None,
		Move,
		LineShot,
		LineBond,
		LineCol,
		Attack,
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

