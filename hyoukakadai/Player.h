#pragma once
#include"Object3d.h"
#include"Enemy.h"
#include<memory>
class Line;
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
	XMFLOAT3 Player_Rot = {0,-90,0};
	XMFLOAT3 Player_Scl;

	bool flyattack_f = false;

public:
	bool GetFlyAttack() { return flyattack_f; }
	bool Initialize()override;
	void Update(XMFLOAT4 color)override;
	void OnCollision(const CollisionInfo& info)override;
	void Attack(XMFLOAT3 playerpos);
	void CollisionAttack(std::unique_ptr<Enemy>enemy[], XMFLOAT3 playerpos);
	void CollisionAttack1(Enemy*enemy, XMFLOAT3 playerpos);
	void PlayerMoves(XMFLOAT3& move,float moveSpeed,bool& JumpFlag,float& grav,float& time);
	void FlyingAttack(Enemy*enemy);
	void FlyingAttack(std::unique_ptr<Enemy> enemy[]);
	//DebugTxt* debugtxt = nullptr;
	int DebugTexnum = 4;
	XMFLOAT2 GetArea_S() { return damageArea.Area_s; }
	XMFLOAT2 GetArea_e() { return damageArea.Area_e; }
	float getdis() { return dis[0]; }
	int getHp() { return HP; }
	void SetHp(int Hp) { HP = Hp; }
	bool GetRot_Left() { if (playerRot==State::Left) return true; }
	bool GetRot_Right() { if (playerRot == State::Right) return true; }
	void Finalize();
private:
	int HP = 100;
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

