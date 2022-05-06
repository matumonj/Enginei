#pragma once
#include"mEffekseer.h"
#include"Object3d.h"
#include"Model.h"
#include "Enemy.h"
class BoundEnemy:public Enemy
{
public: 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	BoundEnemy();
	/// <summary>
	/// デストラクタ
	/// </summary> 
	~BoundEnemy();
private:
	Model* EnemyModel = nullptr;
	Object3d* EnemyObj = nullptr;

	mEffekseer* effect_dead;

    float moveSpeed=0.2f;

private:
	XMFLOAT3 Ene_Pos;
	XMFLOAT3 Ene_Scl;
	XMFLOAT3 Ene_Rot;

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize()override;

    /// <summary>
    /// 更新処理
    /// </summary>
    void Update(XMFLOAT3 position)override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;

    /// <summary>
    /// 解放処理
    /// </summary>
    void BoundMove();
    void Finalize()override;
    void Follow(Player* player);
    void Motion(int time)override;
    void Attack(Player* player)override;
    float angleXs, angleZs, angleRs;
    float centerSpeed = 0.1f;
    const int AttackDamage = 2;
public:
    /// <summary>
    /// アクセッサ
    /// </summary>
    /// <returns></returns>
    XMFLOAT3 GetPosition() { return Ene_Pos; }
    XMFLOAT3 GetRotation() { return Ene_Rot; }
    XMFLOAT3 GetScale() { return Ene_Scl; }
    void ColMap(int map[15][200], float mapx[15][200], float mapy[15][200], const int X, const int Y);
    void enemyappearance(TyutorialSprite* sprite);

};

