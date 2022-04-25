#pragma once
#include"Object3d.h"
#include"Enemy.h"
#include<memory>
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

	Object3d* playerobj = nullptr;
	Model* playermodel = nullptr;

	XMFLOAT3 Player_Pos;
	XMFLOAT3 Player_Rot;
	XMFLOAT3 Player_Scl;


public:
	bool Initialize()override;
	void Update(XMFLOAT4 color)override;
	void OnCollision(const CollisionInfo& info)override;
	void Attack(XMFLOAT3 playerpos);
	void CollisionAttack(std::unique_ptr<Enemy>enemy[], XMFLOAT3 playerpos);
	void CollisionAttack(Enemy*enemy, XMFLOAT3 playerpos);
	//DebugTxt* debugtxt = nullptr;
	int DebugTexnum = 4;
	XMFLOAT2 GetArea_S() { return damageArea.Area_s; }
	XMFLOAT2 GetArea_e() { return damageArea.Area_e; }
	float getdis() { return dis[0]; }
	int getHp() { return HP; }
	void SetHp(int Hp) { HP = Hp; }
	bool GetRot_Left() { if (playerRot==State::Left) return true; }
	bool GetRot_Right() { if (playerRot == State::Right) return true; }

private:
	int HP = 10;
	int AttackCoolTime = 10;
	int index = -1;
	float dis[2];
	//ダメージ範囲
	struct DamageArea {
		XMFLOAT2 Area_s;
		XMFLOAT2 Area_e;
	};
	//右向いてるか左向いてるか
	enum class State {
		Left,
		Right,
	};
	//Collision col;
	//プレイヤーの攻撃アクション
	enum class Action {
		None,
		Attack,
		Move_Stick,
		Move_Shotline,
	};
	float Area_X_s;
	float Area_X_e;
	DamageArea damageArea;
	State playerRot = State::Right;
	Action action = Action::None;
	bool EAcol[2] = { false };
	float timer=0;
};

