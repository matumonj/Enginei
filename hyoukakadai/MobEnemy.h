#pragma once
#include"mEffekseer.h"
#include"Object3d.h"
#include"Model.h"
#include "Enemy.h"
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
    void EnemySearchPlayer(XMFLOAT3 player)override;

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
    void Follow(XMFLOAT3 player);
    void Motion(int time)override;
    float angleXs, angleZs, angleRs;
    float centerSpeed = 0.1f;
public:
    /// <summary>
    /// �A�N�Z�b�T
    /// </summary>
    /// <returns></returns>
    XMFLOAT3 GetPosition() { return Mob_Pos; }
    XMFLOAT3 GetRotation() { return Mob_Rot; }
    XMFLOAT3 GetScale() { return Mob_Scl; }

};

