#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>
#include"Input.h"
#include"TyutorialSprite.h"
#include"Texture.h"
#include"Object3d.h"
/// <summary>
/// 敵キャラの基底クラス
/// </summary>
/// 
class Player;
class Enemy
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Enemy();

protected:
	//Microosoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	
protected:
	XMFLOAT3 Position;
	XMFLOAT3 Rotation;
	XMFLOAT3 Scale;

	enum class State {
		ALIVE,
		DEAD,
	};
	State enemyState = State::ALIVE;
	int HP;// = 10;
public:
	void SearchActionInit();
	virtual void SearchAction(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position)=0;
	void SearchActionDraw(DirectXCommon* dxcomn);
	inline bool GetState_DEAD() {
		if (enemyState == State::DEAD) {
			return true;
		} else {
			return false;
		}
	}

	inline bool GetState_ALIVE() {
		if (enemyState == State::ALIVE) {
			return true;
		} else {
			return false;
		}
	}
	void SetDead(bool f) {
		if (f) { enemyState = State::DEAD; } 
	}
	virtual void SetHP(int HP) { this->HP = HP; }
	virtual int GetHP() { return HP; }
	virtual void EnemySearchPlayer(Player* player) = 0;
	virtual void enemyappearance(TyutorialSprite* sprite) = 0;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update(XMFLOAT3 position);

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw(DirectXCommon* dxcomn);

	virtual void Motion(Player* player)=0;
	//virtual float Distance(Player* player);
	virtual void Attack(Player*player)=0;
	/// <summary>
	/// 解放処理
	/// </summary>
	virtual void Finalize();
	void Setposition(XMFLOAT3 position) { Position = position; }
	void SetScale(XMFLOAT3 scale) { Scale = scale; }
	void SetRotation(XMFLOAT3 rot) { Rotation = rot; }
	XMFLOAT3 GetPosition() { return Position; }
	virtual void ColMap(int map[20][200] , std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y) =0;
};

