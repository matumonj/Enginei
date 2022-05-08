#pragma once
#include"mEffekseer.h"
#include"Object3d.h"
#include"Model.h"
#include "Enemy.h"
class BoundEnemy:public Enemy
{
public: 
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	BoundEnemy();
	/// <summary>
	/// �f�X�g���N�^
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
    /// ������
    /// </summary>
    void Initialize()override;

    /// <summary>
    /// �X�V����
    /// </summary>
    void Update(XMFLOAT3 position)override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw()override;

    /// <summary>
    /// �������
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
    /// �A�N�Z�b�T
    /// </summary>
    /// <returns></returns>
    XMFLOAT3 GetPosition() { return Ene_Pos; }
    XMFLOAT3 GetRotation() { return Ene_Rot; }
    XMFLOAT3 GetScale() { return Ene_Scl; }
    void ColMap(int map[15][200], float mapx[15][200], float mapy[15][200], const int X, const int Y);
    void enemyappearance(TyutorialSprite* sprite);

};

