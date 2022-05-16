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
    float bossmovespeed = 0.1f;
    float bossgrav = 0.03f;
    float bosstime = 0;
    int Attackcount = 0;
    static Ray laserRay;//�}�b�v�u���b�N�Ƃ̓����蔻��ɂ��g������static
    Sphere playersphere;
    bool hitf;
    const int MaxHP = 20;//�̗͂̏����l
   
    static bool altAttackflag;
    bool bossjumpflag=false;
    bool bossjumpflag2 = false;
private:
    XMFLOAT3 Old_Pos;
    static XMFLOAT3 position;
    static bool altattacklag;
    float oldx, oldy;
    int time = 0;
    int time2 = 0;
   
public:
    static BossEnemy* GetInstance();

    bool GetAltAttacklag() { return altattacklag; }

    bool GetJumpFlag() { return bossjumpflag; }

    float GetMoveSpeed() { return bossmovespeed; }

    float GetGrav() { return bossgrav; }

    float GetTtime() { return bosstime; }

    XMFLOAT3 GetOldPosition() { return Old_Pos; }

    XMFLOAT3 GetPos() { return Position; }

    XMFLOAT3 GetPosi() { return position; }
    
    XMFLOAT3 GetRotation() { return Boss_Rot; }

    XMFLOAT3 GetScale() { return Boss_Scl; }

    Ray GetLaserRay() { return laserRay; }

    bool GetaltAttack() { return altAttackflag; }
    
public:

    void SetJumpFlag(bool f) { bossjumpflag = f; }

    void SetMoveSpeed(float s) { bossmovespeed = s; }

    void SetGrav(float g) { bossgrav = g; }

    void SetTtime(float t) { bosstime = t; }

public:
    void Initialize()override;

    void Update(XMFLOAT3 position)override;

    void Draw(DirectXCommon*dxcomn)override;

    void Finalize()override;

public:
    //���ߍ��݉��p
    void MoveBlockJump();
    //�����
    void ColMapb1(int map[15][200], std::unique_ptr<Object3d> tst[15][200], float mapx[15][200], float mapy[15][200], const int X, const int Y);
    //�v���C���[���m
    void EnemySearchPlayer(Player* player)override;
    //����񂩂�
    void Attack(Player* player)override;
    //�}�b�g�̓����蔻��
    void ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y)override;
    //
    void enemyappearance(TyutorialSprite* sprite)override {};
    //�{�X�̃A�N�V����
    void Motion(Player* player)override;
    //�����U��
    void ThrowAttack(Player* player);
    //�ǐ�
    void Follow(XMFLOAT3 position);
    //
    void SummonEnemy(XMFLOAT3 position);
    void SearchAction(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position)override;
    void ColMap1(int map[130][20], std::unique_ptr<Object3d>  tst[130][20], float mapx[130][20], float mapy[130][20], const int X, const int Y)override;
private:
    static const int ThrowObjMax = 5;
    const int ThrowDamage = 1;
    const int AltDamage = 1;
    const int NormalDmage = 1;
    Model* ThrowModel =  nullptr ;
    Object3d* ThrowObj[ThrowObjMax] = { nullptr };

    XMFLOAT3 thposition[ThrowObjMax] = {};
    XMFLOAT3 thscale[ThrowObjMax] = {};
    XMFLOAT3 throtation[ThrowObjMax] = {};
    struct ThrowParam {
        float movex, movey;
        float initialvec_x = 1;
        float initialvec_y = 3;
        float grav = -5.0f / 60;
        int time = 0;
        bool flag = false;
        bool smflag = false;
    };
    ThrowParam throwparam[ThrowObjMax];
    int attackf[ThrowObjMax] = { false };
    int attackcount = 0;
    int pm[ThrowObjMax];
    bool summonattackflag;
    static int counter;
 private:
     struct SummonEnemys {
         float movex, movey;
         XMFLOAT3 SOld_Pos;
         float initialvec_x = 1;
         float initialvec_y = 5;
         float grav = -5.0f / 60;
         int time;
         bool followflag = false;
         bool flag = false;
         bool bomflag = false;
         bool landingflag;
         //bool followflag;
     };
     static const int SummonMax = 5;
     std::unique_ptr<Enemy>enemy[SummonMax];
     SummonEnemys summonEnemy[SummonMax];
     XMFLOAT3 SummonEnemyPos[SummonMax];
private:
    XMFLOAT3 startPos;
    float movement;
    bool Wrap = false;
    enum BossAction {
        None,
        MoveRight,
        MoveLeft,
        Jump,
        Stay,
        AltAttack,
        NormalAttack,
        SummonEnemyAttack,
        MobEnemySummon,
        SetStartPos
    };
    
    BossAction bossAction=None;
    static bool stayflag;
public:
    bool GetAltStay() { return stayflag; }
    bool GetAltAction() { if (bossAction == AltAttack) { return true; } else { return false; } }
};

