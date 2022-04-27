#pragma once
#include"Object3d.h"
#include"Model.h"
#include "Enemy.h"
class BossEnemy :
    public Enemy
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    BossEnemy();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~BossEnemy();

private:
    //�I�u�W�F�N�g�̃C���X�^���X
    Object3d* BossObject=nullptr;
    //���f���̃C���X�^���X
    Model* BossModel=nullptr;

private:
    //�p�����[�^
    XMFLOAT3 Boss_Pos;
    XMFLOAT3 Boss_Rot;
    XMFLOAT3 Boss_Scl;

public:
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
    void Finalize()override;

    void EnemySearchPlayer(Player*player)override;

public:
    /// <summary>
   /// �A�N�Z�b�T
   /// </summary>
   /// <returns></returns>
   //���W
    XMFLOAT3 GetPosition() { return Boss_Pos; }
    //��]
    XMFLOAT3 GetRotation() { return Boss_Rot; }
    //�X�P�[��
    XMFLOAT3 GetScale() { return Boss_Scl; }
    void ColMap(int map[15][200], float mapx[15][200], float mapy[15][200], const int X, const int Y);
    void enemyappearance(TyutorialSprite* sprite)override {};
};

