#pragma once
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

private:
    XMFLOAT3 Mob_Pos;
    XMFLOAT3 Mob_Rot;
    XMFLOAT3 Mob_Scl;
public:
    /// <summary>
    /// ������
    /// </summary>
    void Initialize()override;
    
    /// <summary>
    /// �X�V����
    /// </summary>
    void Update()override;
    
    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw()override;

    /// <summary>
    /// �������
    /// </summary>
    void Finalize()override;
public:
    /// <summary>
    /// �A�N�Z�b�T
    /// </summary>
    /// <returns></returns>
    XMFLOAT3 GetPosition() { return Mob_Pos; }
    XMFLOAT3 GetRotation() { return Mob_Rot; }
    XMFLOAT3 GetScale() { return Mob_Scl; }

};

