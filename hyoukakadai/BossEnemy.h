#pragma once
#include"Object3d.h"
#include"Model.h"
#include "Enemy.h"
#include"CollisionPrimitive.h"
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
    XMFLOAT3 Boss_Scl = {9,9,9};
    static bool altAttackflag;
    int Attackcount = 0;
    static Ray laserRay;
    Sphere playersphere;
    bool bossjumpflag=false;
    XMFLOAT3 Old_Pos;
    float bossmovespeed=0.1f;
    float bossgrav=0.05f ;
    float bosstime=0 ;
    static XMFLOAT3 position;
public:
    bool GetJumpFlag() { return bossjumpflag; }
    float GetMoveSpeed() { return bossmovespeed; }
    float GetGrav() { return bossgrav; }
    float GetTtime() { return bosstime; }
    void SetJumpFlag(bool f) {  bossjumpflag=f; }
    void SetMoveSpeed(float s) {  bossmovespeed=s; }
    void SetGrav(float g) {  bossgrav=g; }
    void SetTtime(float t) {  bosstime=t; }
    XMFLOAT3 GetOldPosition() { return Old_Pos; }
    XMFLOAT3 GetPos() { return Position; }
    Ray GetLaserRay() { return laserRay; }
    static BossEnemy* GetInstance();
   int GetaltAttack() { return altAttackflag; }
   XMFLOAT3 GetPosi() { return position; }
   void ColMapb1(int map[15][200], std::unique_ptr<Object3d> tst[15][200], float mapx[15][200], float mapy[15][200], const int X, const int Y);
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
    void Attack(Player* player)override;
public:
    /// <summary>
   /// �A�N�Z�b�T
   /// </summary>
   /// <returns></returns>
    //��]
   // XMFLOAT3 GetPosition() { return ; }
    //void Setposition(XMFLOAT3 pos) { Position = pos; }
    XMFLOAT3 GetRotation() { return Boss_Rot; }
    //�X�P�[��
    XMFLOAT3 GetScale() { return Boss_Scl; }
    void ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y)override;
    void enemyappearance(TyutorialSprite* sprite)override {};
    void Motion(int time)override;
private:
    float movement;
    bool Wrap = false;
    enum BossAction {
        None,
        MoveRight,
        MoveLeft,
        Jump,
        AltAttack,
        NormalAttack
    };
    BossAction bossAction;
};

