#pragma once
#include"mEffekseer.h"
#include"Object3d.h"
#include"Model.h"
#include "Enemy.h"
#include"TyutorialSprite.h"
class MobEnemy :
    public Enemy
{

public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    MobEnemy();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary> 
    ~MobEnemy();

private:
    //�I�u�W�F�N�g�̃C���X�^���X
    Object3d* MobObject=nullptr;
    //���f���̃C���X�^���X
    Model* MobModel=nullptr;
    //
    mEffekseer* effect_dead;
private:
    XMFLOAT3 Mob_Pos;
    XMFLOAT3 Mob_Rot;
    XMFLOAT3 Mob_Scl;
public:
    void EnemySearchPlayer(Player* player)override;

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
    void Follow(Player*player);
    void Motion(Player* player)override;
    void Attack(Player*player)override;
private:
    bool followf;
    float movespeed = 0.2f;
    float grav = 0.03f;
    float time = 0;
    int Attackcount = 0;
    XMFLOAT3 Old_Pos;
    const int MaxHP = 20;//�̗͂̏����l

    float angleXs, angleZs, angleRs;
    float centerSpeed = 0.1f;
    const int AttackDamage = 2;
public:
    /// <summary>
    /// �A�N�Z�b�T
    /// </summary>
    /// <returns></returns>
    XMFLOAT3 GetPosition() { return Mob_Pos; }
    XMFLOAT3 GetRotation() { return Mob_Rot; }
    XMFLOAT3 GetScale() { return Mob_Scl; }
    void ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200],float mapy[20][200], const int X, const int Y);
    void enemyappearance(TyutorialSprite*sprite);
};

